from flask import Blueprint, jsonify, render_template, request, session
from db import db_connect
import pymysql.cursors


reserve_bp = Blueprint('reserve', __name__)

@reserve_bp.route('/reserve')
def location():
    id = session.get("id", "")
    if(id):
        return render_template('reserve.html')
    else:
        return render_template('login.html')

@reserve_bp.route('/get_reserve_list', methods=['POST'])
def get_location_list():
    result = request.json
    page = int(result['page'])
    pageSize = int(result['pageSize'])
    offset = (page - 1) * pageSize
    
    status = result.get('status')
    parknum = result.get('parknum')
    
    db = db_connect()
    cursor = db.cursor(pymysql.cursors.DictCursor)
    
    where_conditions = []
    search_params = []
    
    if status and status != 'all':
        where_conditions.append("l.status = %s")
        search_params.append(status)
        
    if parknum and parknum != 'all':
        where_conditions.append("l.parknum = %s")
        search_params.append(parknum)
    
    where_clause = " WHERE " + " AND ".join(where_conditions) if where_conditions else ""
    
    sql = f"""
        SELECT 
            r.id AS reserve_id, 
            c.carnum AS carnum, 
            DATE_FORMAT(r.expire_time, '%%Y-%%m-%%d %%H:%%i:%%s') AS expire_time, 
            r.status AS reserve_status,
            u.username AS username, 
            u.phonenum AS phone, 
            l.parknum AS parknum, 
            l.numinpark AS numinpark
        FROM 
            reserve_table r
        JOIN 
            car_table c ON r.for_carid = c.id
        JOIN 
            user_table u ON c.for_userid = u.id
        JOIN 
            location l ON r.for_locationid = l.id
        {where_clause}
        LIMIT %s OFFSET %s
    """
    
    sql_params = search_params + [pageSize, offset]
    cursor.execute(sql, tuple(sql_params))
    rows = cursor.fetchall()
    
    count_sql = f"""
        SELECT COUNT(*) as total
        FROM reserve_table r
        JOIN car_table c ON r.for_carid = c.id
        JOIN user_table u ON c.for_userid = u.id
        JOIN location l ON r.for_locationid = l.id
        {where_clause}
    """
    cursor.execute(count_sql, tuple(search_params))
    count = cursor.fetchone()
    
    db.close()
    
    return jsonify({"reserve_info": rows, "total": count['total']})

@reserve_bp.route('/delete_reserve', methods=['POST'])
def delete_reserve():
    result = request.json
    reserve = result.get('reserve')
        
    try:
        db = db_connect()
        cursor = db.cursor()
        

        reserve_sql = "DELETE FROM reserve_table WHERE id = %s"
        cursor.execute(reserve_sql, (reserve,))

        db.commit()
        
        affected_rows = cursor.rowcount
        db.close()
        
        if affected_rows > 0:
            return jsonify({"status": "success", "message": "删除成功"})
        else:
            return jsonify({"status": "error", "message": "未找到该记录"})
            
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)})
