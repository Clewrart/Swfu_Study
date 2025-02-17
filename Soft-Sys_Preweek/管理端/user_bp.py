from flask import Blueprint, jsonify, render_template, request, session
from db import db_connect
import pymysql.cursors


user_bp = Blueprint('user', __name__)

@user_bp.route('/user')
def location():
    id = session.get("id", "")
    if(id):
        return render_template('user_list.html')
    else:
        return render_template('login.html')

@user_bp.route('/get_user_list', methods=['POST'])
def get_location_list():
    result = request.json
    page = int(result['page'])
    pageSize = int(result['pageSize'])
    offset = (page - 1) * pageSize
    
    db = db_connect()
    cursor = db.cursor(pymysql.cursors.DictCursor)
    
    sql = f"""
        SELECT * FROM user_table
        LIMIT %s OFFSET %s
    """
    cursor.execute(sql, (pageSize, offset))
    rows = cursor.fetchall()

    count_sql = f"""
        SELECT COUNT(*) as total
        FROM user_table
    """
    cursor.execute(count_sql)
    count = cursor.fetchone()
    
    db.close()
    
    return jsonify({"user_list": rows, "total": count['total']})


@user_bp.route('/delete_user', methods=['POST'])
def delete_user():
    result = request.json
    user_id = result.get('user')
    
    if not user_id:
        return jsonify({"status": "error", "message": "未提供用户ID"})
        
    try:
        db = db_connect()
        cursor = db.cursor()
        
        db.begin()
        
        try:
            reserve_sql = "DELETE FROM reserve_table WHERE for_userid = %s"
            cursor.execute(reserve_sql, (user_id,))
            
            car_sql = "DELETE FROM car_table WHERE for_userid = %s"
            cursor.execute(car_sql, (user_id,))
            
            user_sql = "DELETE FROM user_table WHERE id = %s"
            cursor.execute(user_sql, (user_id,))
            
            db.commit()
            
            affected_rows = cursor.rowcount
            
            if affected_rows > 0:
                return jsonify({
                    "status": "success", 
                    "message": "用户及其关联数据已成功删除"
                })
            else:
                db.rollback()
                return jsonify({
                    "status": "error", 
                    "message": "未找到该用户"
                })
                
        except Exception as e:
            db.rollback()
            raise e
            
    except Exception as e:
        return jsonify({
            "status": "error", 
            "message": f"删除失败：{str(e)}"
        })
        
    finally:
        cursor.close()
        db.close()

@user_bp.route('/get_edit_user_info', methods=['POST'])
def get_edit_user_info():
    result = request.json
    user_id = result.get('user')
    
    if not user_id:
        return jsonify({"status": "error", "message": "未提供用户ID"})
    
    db = db_connect()
    cursor = db.cursor(pymysql.cursors.DictCursor)
    
    sql = "SELECT * FROM user_table WHERE id = %s"
    cursor.execute(sql, (user_id,))
    user_info = cursor.fetchone()
    
    db.close()
    
    return jsonify({
        "status": "success",
        "user_info": user_info
    })

@user_bp.route('/save_user_info', methods=['POST'])
def save_user_info():
    result = request.json
    user_id = result.get('user_id')
    username = result.get('username')
    phonenum = result.get('phonenum')
    
    if not user_id:
        return jsonify({"status": "error", "message": "未提供用户ID"})
    
    try:
        db = db_connect()
        cursor = db.cursor()
        
        sql = "UPDATE user_table SET username = %s, phonenum = %s WHERE id = %s"
        cursor.execute(sql, (username, phonenum, user_id))
        
        db.commit()
        
        affected_rows = cursor.rowcount
        
        if affected_rows > 0:
            return jsonify({
                "status": "success", 
                "message": "用户信息已更新"
            })
        else:
            return jsonify({
                "status": "error", 
                "message": "未找到该用户"
            })
            
    except Exception as e:
        return jsonify({
            "status": "error", 
            "message": f"更新失败：{str(e)}"
        })
        
    finally:
        cursor.close()
        db.close()  