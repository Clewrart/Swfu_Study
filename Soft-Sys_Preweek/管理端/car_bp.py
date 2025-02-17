from flask import Blueprint, jsonify, request
from db import db_connect
import pymysql.cursors
from functools import wraps
import re

car_bp = Blueprint('car', __name__)

@car_bp.route('/get_car_list', methods=['POST'])
def get_car_list():
    result = request.json
    page = result['page']
    offset = (page - 1) * result['pageSize']
    status = result.get('status', 'all')
    carnum = result.get('carnum', '')
    
    db = db_connect()
    cursor = db.cursor(pymysql.cursors.DictCursor)
    
    sql = """
    SELECT c.carnum, c.status,
        u.phonenum AS phone, 
        u.username AS ownername
    FROM car_table c
    JOIN user_table u ON u.id = c.for_userid
    """
    
    where_conditions = []
    params = []
    
    if status != 'all': 
        where_conditions.append("c.status = %s")
        params.append(status)
    
    if carnum:
        where_conditions.append("c.carnum LIKE %s")
        params.append(f"%{carnum}%")
    
    if where_conditions:
        sql += " WHERE " + " AND ".join(where_conditions)
    
    sql += " LIMIT %s OFFSET %s"
    params.extend([int(result['pageSize']), offset])
    
    
    cursor.execute(sql, tuple(params))
    rows = cursor.fetchall()
    
    count_sql = "SELECT COUNT(*) FROM car_table c"
    count_params = []
    
    if where_conditions:
        count_sql += " WHERE " + " AND ".join(where_conditions)
        count_params = params[:-2]
    
    cursor.execute(count_sql, tuple(count_params))
    count = cursor.fetchone()
    db.close()
    
    return jsonify({
        "status": "success", 
        "carinfo": rows, 
        "total": count['COUNT(*)']
    })


@car_bp.route('/delete_car', methods=['POST'])
def delete_car():
    result = request.json
    carnum = result.get('carnum')    
    try:
        db = db_connect()
        cursor = db.cursor()
        
        
        
        car_query = "SELECT id FROM car_table WHERE carnum = %s"
        cursor.execute(car_query, (carnum,))
        car_result = cursor.fetchone()
        
        if not car_result:
            db.rollback()
            db.close()
            return jsonify({"status": "error", "message": "未找到该车辆记录"})
            
        car_id = car_result[0]
        
        reserve_sql = "DELETE FROM reserve_table WHERE for_carid = %s"
        cursor.execute(reserve_sql, (car_id,))
        
        car_sql = "DELETE FROM car_table WHERE carnum = %s"
        cursor.execute(car_sql, (carnum,))
        
        db.commit()
        
        affected_rows = cursor.rowcount
        db.close()
        
        if affected_rows > 0:
            return jsonify({
                "status": "success", 
                "message": "删除成功"
            })
        else:
            return jsonify({
                "status": "error", 
                "message": "删除失败"
            }) 
            
    except Exception as e:
        if db:
            db.rollback()
            db.close()
        return jsonify({"status": "error", "message": str(e)})
    

@car_bp.route('/get_eidt_car_info', methods=['POST'])
def get_eidt_car_info():
    result = request.json
    carnum = result.get('carnum')
    
    if not carnum:
        return jsonify({"status": "error", "message": "车牌号不能为空"})
    
    db = db_connect()
    cursor = db.cursor(pymysql.cursors.DictCursor)
    
    sql = """
    SELECT c.carnum, c.id AS carid,
        u.phonenum AS phone, 
        u.username AS owner,
        u.id AS userid
    FROM car_table c
    JOIN user_table u ON u.id = c.for_userid
    WHERE c.carnum = %s
    """
    
    cursor.execute(sql, (carnum,))
    car_info = cursor.fetchone()
    
    db.close()
    return jsonify({
        "status": "success",
        "car_info": car_info
    })


@car_bp.route('/save_car_info', methods=['POST'])
def save_car_info():
    try:
        result = request.json
        userid = result.get('userid')
        carid = result.get('carid')
        carnum = result.get('carnum')
        phone = result.get('phone')
        owner = result.get('owner')
        
        db = db_connect()
        cursor = db.cursor()
        
        try:
            user_sql = "UPDATE user_table SET username = %s, phonenum = %s WHERE id = %s"
            cursor.execute(user_sql, (owner, phone, userid))
            
            car_sql = "UPDATE car_table SET carnum = %s WHERE id = %s"
            cursor.execute(car_sql, (carnum, carid))
            
            db.commit()
            return jsonify({
                "status": "success", 
                "message": "保存成功"
            })
            
        except Exception as e:
            db.rollback()
            raise e
            
    except Exception as e:
        return jsonify({
            "status": "error", 
            "message": f"操作失败: {str(e)}"
        })
        
    finally:
        if 'db' in locals():
            cursor.close()
            db.close()