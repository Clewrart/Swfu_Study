from flask import Blueprint, jsonify, render_template, request, session
from db import db_connect

data_bp = Blueprint('data_bp', __name__)

@data_bp.route('/data')
def location():
    id = session.get("id", "")
    if(id):
        return render_template('data_manage.html')
    else:
        return render_template('login.html')

@data_bp.route('/get_distinct_parknum', methods=['GET'])
def get_distinct_parknum():
    try:
        conn = db_connect()
        cursor = conn.cursor()
        
        query = """
        SELECT DISTINCT parknum 
        FROM location 
        WHERE parknum != '00000'
        ORDER BY parknum
        """
        
        cursor.execute(query)
        parknums = cursor.fetchall()
        
        cursor.close()
        conn.close()
        
        return jsonify({
            'status': 'success',
            'parknums': [{'parknum': row[0]} for row in parknums]
        })
        
    except Exception as e:
        return jsonify({
            'status': 'error',
            'message': str(e)
        }), 500

@data_bp.route('/api/reservation/stats', methods=['GET'])
def get_reservation_stats():
    try:
        conn = db_connect()
        cursor = conn.cursor()
        
        parknum = request.args.get('parknum', 'all')
        time_dimension = request.args.get('time_dimension', 'day')

        if time_dimension == 'day':
            hourly_query = """
            SELECT 
                HOUR(r.expire_time) as hour,
                l.parknum,
                COUNT(*) as count
            FROM reserve_table r
            JOIN location l ON r.for_locationid = l.id
            """
        elif time_dimension == 'week':
            hourly_query = """
            SELECT 
                WEEKDAY(r.expire_time) as weekday,
                l.parknum,
                COUNT(*) as count
            FROM reserve_table r
            JOIN location l ON r.for_locationid = l.id
            """
        elif time_dimension == 'month':
            hourly_query = """
            SELECT 
                (DAY(r.expire_time) - 1) as day,  # 用括号确保计算顺序
                l.parknum,
                COUNT(*) as count
            FROM reserve_table r
            JOIN location l ON r.for_locationid = l.id
            """
        elif time_dimension == 'year':
            hourly_query = """
            SELECT 
                (MONTH(r.expire_time) - 1) as month,  # 用括号确保计算顺序
                l.parknum,
                COUNT(*) as count
            FROM reserve_table r
            JOIN location l ON r.for_locationid = l.id
            """
        else:
            hourly_query = None

        params = []
        if parknum != 'all':
            params.append(parknum)
            if hourly_query:
                hourly_query += " WHERE l.parknum = %s"


        if hourly_query:
            if time_dimension == 'day':
                hourly_query += " GROUP BY HOUR(r.expire_time), l.parknum ORDER BY hour, l.parknum"
            elif time_dimension == 'week':
                hourly_query += " GROUP BY WEEKDAY(r.expire_time), l.parknum ORDER BY weekday, l.parknum"
            elif time_dimension == 'month':
                hourly_query += " GROUP BY (DAY(r.expire_time) - 1), l.parknum ORDER BY day, l.parknum"  # 使用与SELECT相同的表达式
            elif time_dimension == 'year':
                hourly_query += " GROUP BY (MONTH(r.expire_time) - 1), l.parknum ORDER BY month, l.parknum"  # 使用与SELECT相同的表达式



        if hourly_query:
            if parknum != 'all':
                cursor.execute(hourly_query, tuple(params))
            else:
                cursor.execute(hourly_query)
            
            hourly_data = cursor.fetchall()
        else:
            hourly_data = []
        
        processed_hourly = {}
        if time_dimension == 'week':
            for row in hourly_data:
                pnum = row[1]
                if pnum not in processed_hourly:
                    processed_hourly[pnum] = [0] * 7
                weekday = row[0]
                if 0 <= weekday < 7:
                    processed_hourly[pnum][weekday] = row[2]
        elif time_dimension == 'month':
            for row in hourly_data:
                pnum = row[1]
                if pnum not in processed_hourly:
                    processed_hourly[pnum] = [0] * 31 
                day = row[0]
                if 0 <= day < 31:
                    processed_hourly[pnum][day] = row[2]
        elif time_dimension == 'year':
            for row in hourly_data:
                pnum = row[1]
                if pnum not in processed_hourly:
                    processed_hourly[pnum] = [0] * 12
                month = row[0]
                if 0 <= month < 12:
                    processed_hourly[pnum][month] = row[2]

        else:
            for row in hourly_data:
                pnum = row[1]
                if pnum not in processed_hourly:
                    processed_hourly[pnum] = [0] * 24
                hour = row[0]
                if 0 <= hour < 24:
                    processed_hourly[pnum][hour] = row[2]

        if parknum != 'all' and not processed_hourly and time_dimension == 'day':
            processed_hourly[parknum] = [0] * 24

        
        response_data = {
            'status': 'success',
            'data': {
                'time_dimension': time_dimension,
                'hourly': processed_hourly
            }
        }


        cursor.close()
        conn.close()

        return jsonify(response_data)
        
    except Exception as e:
        print(f"Error: {str(e)}")
        if 'cursor' in locals() and cursor:
            cursor.close()
        if 'conn' in locals() and conn:
            conn.close()
        return jsonify({
            'status': 'error',
            'message': str(e)
        }), 500
