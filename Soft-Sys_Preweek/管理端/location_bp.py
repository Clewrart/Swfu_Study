from flask import Blueprint, jsonify, render_template, request, url_for, session
from db import db_connect
import pymysql.cursors


location_bp = Blueprint('location', __name__)

@location_bp.route('/location')
def location():
    id = session.get("id", "")
    if(id):
        return render_template('location_list.html')
    else:
        return render_template('login.html')

@location_bp.route('/get_location_list', methods=['POST'])
def get_location_list():
    result = request.json
    page = result['page']
    pageSize = result['pageSize']
    offset = (page - 1) * pageSize
    
    status = result.get('status')
    parknum = result.get('parknum')
    
    db = db_connect()
    cursor = db.cursor(pymysql.cursors.DictCursor)
    
    where_conditions = []
    params = []
    
    if status and status != 'all':
        where_conditions.append("l.status = %s")
        params.append(status)
        
    if parknum and parknum != 'all':
        where_conditions.append("l.parknum = %s")
        params.append(parknum)
    
    where_clause = " WHERE " + " AND ".join(where_conditions) if where_conditions else ""
    
    sql = f"""
    SELECT l.id, l.parknum,
       l.numinpark, l.status,
       c.carnum AS carnum,
       DATE_FORMAT(l.warn_time, '%%Y-%%m-%%d %%H:%%i:%%s') AS warn_time
    FROM location l
    LEFT JOIN car_table c ON c.id = l.for_carid
    {where_clause}
    LIMIT %s OFFSET %s
    """
    
    params.extend([pageSize, offset])
    cursor.execute(sql, tuple(params))
    rows = cursor.fetchall()
    
    count_sql = f"""
    SELECT COUNT(*) as total
    FROM location l
    LEFT JOIN car_table c ON c.id = l.for_carid
    {where_clause}
    """
    cursor.execute(count_sql, tuple(params[:-2]) if params else ())
    total = cursor.fetchone()['total']
    
    db.close()
    
    return jsonify({
        "status": "success", 
        "location_info": rows, 
        "total": total
    })

@location_bp.route('/get_distinct_parknum', methods=['GET'])
def get_distinct_parknum():
    db = db_connect()
    cursor = db.cursor(pymysql.cursors.DictCursor)
    
    sql = "SELECT DISTINCT parknum FROM location ORDER BY parknum"
    cursor.execute(sql)
    parknums = cursor.fetchall()
    
    db.close()
    return jsonify({
        "status": "success",
        "parknums": parknums
    })

@location_bp.route('/delete_location', methods=['POST'])
def delete_location():
    result = request.json
    location = result.get('location')
        
    try:
        db = db_connect()
        cursor = db.cursor()
        
        car_query = "SELECT for_carid FROM location WHERE id = %s"
        cursor.execute(car_query, (location,))
        car_result = cursor.fetchone()
        
        if car_result:
            car_id = car_result[0]
            reserve_sql = "DELETE FROM reserve_table WHERE for_carid = %s"
            cursor.execute(reserve_sql, (car_id,))

        location_sql = "DELETE FROM location WHERE id = %s"
        cursor.execute(location_sql, (location,))

        db.commit()
        
        affected_rows = cursor.rowcount
        db.close()
        
        if affected_rows > 0:
            return jsonify({"status": "success", "message": "删除成功"})
        else:
            return jsonify({"status": "error", "message": "未找到该记录"})
            
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)})
    
@location_bp.route('/insert_location', methods=['POST'])
def insert_location():
    result = request.json
    parknum = result.get('parknum')
    numinpark = result.get('numinpark')
    position_lat = result.get('longitude')
    position_lng = result.get('latitude')
    
    if not all([parknum, numinpark, position_lat, position_lng]):
        return jsonify({"status": "error", "message": "数据未填写完整"})
        
    address = '测试' + parknum.split(' ')[-1] + '号停车位' + numinpark
    
    try:
        db = db_connect()
        cursor = db.cursor()
        
        check_park_sql = """
            SELECT COUNT(*) 
            FROM location 
            WHERE parknum = %s AND numinpark = %s
        """
        cursor.execute(check_park_sql, (parknum, numinpark))
        if cursor.fetchone()[0] > 0:
            db.close()
            return jsonify({
                "status": "error", 
                "message": "该停车场编号和场内编号组合已存在"
            })
            
        check_position_sql = """
            SELECT COUNT(*) 
            FROM location 
            WHERE position_lat = %s AND position_lng = %s
        """
        cursor.execute(check_position_sql, (position_lat, position_lng))
        if cursor.fetchone()[0] > 0:
            db.close()
            return jsonify({
                "status": "error", 
                "message": "该位置坐标已存在"
            })
        
        location_sql = """
            INSERT INTO location 
            (parknum, numinpark, position_lat, position_lng, address, status) 
            VALUES (%s, %s, %s, %s, %s, 0)
        """
        cursor.execute(location_sql, (
            parknum, 
            numinpark, 
            position_lat, 
            position_lng, 
            address
        ))
        
        db.commit()
        affected_rows = cursor.rowcount
        db.close()
        
        if affected_rows > 0:
            return jsonify({
                "status": "success", 
                "message": "添加成功"
            })
        else:
            return jsonify({
                "status": "error", 
                "message": "添加失败"
            })
            
    except Exception as e:
        if db:
            db.close()
        return jsonify({
            "status": "error", 
            "message": f"数据库错误: {str(e)}"
        })