from flask import Flask, redirect,render_template, request, session,jsonify, send_from_directory, url_for
import pymysql
import pymysql.cursors
import os
import hashlib
from datetime import datetime, timedelta
from apscheduler.schedulers.background import BackgroundScheduler
from apscheduler.events import EVENT_JOB_EXECUTED, EVENT_JOB_ERROR

def generate_md5_hash(data):
    md5 = hashlib.md5()
    md5.update(data.encode('utf-8'))
    return md5.hexdigest()

app = Flask(__name__)
app.config['SECRET_KEY'] = os.urandom(30)

db = pymysql.connect(host = '47.96.10.165',
                     user = 'sysusr',
                     password = '202412',
                     database = 'softSys',
                     autocommit=True,
                     connect_timeout = 15)

#定时任务：检查预约是否过期
def check_appointments():
    try:
        #获取当前时间
        current_time = datetime.now()
        print(current_time)
        #打印当前时间
        print(f"Checking appointments at {current_time}")

        with db.cursor(pymysql.cursors.DictCursor) as cursor:
            # 查询所有状态为 '1'（有效）的预约
            sql = "SELECT id, expire_time, for_locationid, for_carid FROM reserve_table WHERE status = '1';"
            cursor.execute(sql)
            appointments = cursor.fetchall()

            # 遍历所有预约，检查是否过期
            for appointment in appointments:
                appointment_time = appointment['expire_time']

                # 判断预约时间是否超时30分钟
                if current_time - appointment_time > timedelta(minutes=30):
                    print(f"Marking appointment {appointment['id']} as expired")
                    # 更新预约状态为 0
                    update_sql = "UPDATE reserve_table SET status = 0 WHERE id = %s"
                    cursor.execute(update_sql, (appointment['id'],))
                    db.commit()
                    update_sql = "UPDATE location SET status = 0, for_carid = NULL WHERE id = %s"
                    cursor.execute(update_sql, (appointment['for_locationid'],))
                    db.commit()
                    update_sql = "UPDATE car_table SET status = 0 WHERE id = %s"
                    cursor.execute(update_sql, (appointment['for_carid'],))
                    db.commit()
                if current_time - appointment_time > timedelta(days=30):
                    delete_sql = "DELETE FROM reserve_table WHERE id = %s"
                    cursor.execute(delete_sql, (appointment['id'],))
                    db.commit()



    except Exception as e:
        print(f"Error checking appointments: {e}")


##车主注册登录
@app.route("/")
def login():
    return render_template("login.html")

@app.route('/logout/')
def logout():
    session.pop('username', None)
    session.pop('id', None)
    session.pop('phonenum', None)
    return render_template("login.html")

@app.route("/regi/")
def regi():
    return render_template("regi.html")


@app.route("/regi_submit/", methods=["POST"])
def regi_submit():
    if request.method == "POST":
        result = request.form
        md5_password = generate_md5_hash(result['password'])
        cursor = db.cursor()
        with db.cursor(pymysql.cursors.DictCursor) as cursor:
            sql = "INSERT INTO user_table (username, password, phonenum) VALUES ('%s','%s','%s');" % (result['username'], md5_password, result['telnum'])
            cursor.execute(sql)
            db.commit()
    return redirect(url_for('login'))



@app.route("/login_submit/", methods=["POST"])
def login_submit():
    if request.method == "POST":
        result = request.form
        md5_password = generate_md5_hash(result['password'])
        cursor = db.cursor(pymysql.cursors.DictCursor)
        sql = "SELECT * FROM user_table WHERE phonenum=%s AND password=%s"
        cursor.execute(sql, (result['telephone'], md5_password))
        row = cursor.fetchone()
        cursor.close()
        if row:
            session['username'] = row['username']
            session['id'] = row['id']
            session['phonenum'] = row['phonenum']
            return redirect(url_for('index'))
        else:
            jest="账户信息错误，新用户请注册！"
            return render_template("login.html",jest=jest)


#启动定时任务
def start_scheduler():
    scheduler = BackgroundScheduler()
    scheduler.add_job(check_appointments, 'interval', minutes=1)  #每6秒执行一次
    scheduler.start()
    print("Scheduler started successfully!")

#启动 Flask 应用上下文，初始化定时任务
def initialize_scheduler():
    with app.app_context():  #手动推入应用上下文
        start_scheduler()

@app.route('/dashboard',methods=["GET","POST"])
def index():
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "SELECT * FROM car_table WHERE for_userid = '%s';" % (session['id'])
        #sql = "SELECT * FROM car_table;"
        cursor.execute(sql)
        cars = cursor.fetchall()
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "SELECT parknum FROM location GROUP BY parknum;"
        cursor.execute(sql)
        locations = cursor.fetchall()
    return render_template("index.html", title='Home Page', username=session['username'], phonenum=session['phonenum'], cars=cars, locations=locations)

@app.route('/order_submit/', methods=["GET","POST"])
def order_submit():
    data = request.get_json()
    carid = data['carid']
    parknum = data['parknum']
    time = datetime.now()
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "SELECT * FROM location WHERE parknum = '%s' and status = 0 LIMIT 1;" % (parknum)
        cursor.execute(sql)
        location = cursor.fetchone()
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "SELECT for_userid FROM car_table WHERE id = '%s';" % (carid)
        cursor.execute(sql)
        for_userid = cursor.fetchone()

    if not location:
        return jsonify({'code': "False"})
    else :
        for_locationid = location['id']
        with db.cursor(pymysql.cursors.DictCursor) as cursor:
            sql = "INSERT INTO reserve_table (for_carid, for_locationid, expire_time, status, for_userid) VALUES ('%s','%s','%s','1','%s');" % (carid, for_locationid, time, for_userid['for_userid'])
            cursor.execute(sql)
            db.commit()
        with db.cursor(pymysql.cursors.DictCursor) as cursor:
            sql = "UPDATE location SET status = 2, for_carid = '%s' WHERE id = '%s';" % (carid, for_locationid)
            cursor.execute(sql)
            db.commit()
        with db.cursor(pymysql.cursors.DictCursor) as cursor:
            sql = "UPDATE car_table SET status = 2 WHERE id = '%s';" % (carid)
            cursor.execute(sql)
            db.commit()
        return jsonify({'code': "True"})
    
@app.route('/no_order/', methods=["GET","POST"])
def no_order():
    data = request.get_json()
    parknum = data['parknum']
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "SELECT * FROM location WHERE parknum = '%s' and status = 0 LIMIT 1;" % (parknum)
        cursor.execute(sql)
        location = cursor.fetchone()
    if not location:
        return jsonify({'code': "False"})
    else :
        for_locationid = location['id']
        return jsonify({'code': "True", 'for_locationid': for_locationid})

    
@app.route('/have_order/', methods=["GET","POST"])
def have_order():
    data = request.get_json()
    carid = data['carid']
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "SELECT for_locationid FROM reserve_table WHERE for_carid = '%s' AND status = 1;" % (carid)
        cursor.execute(sql)
        for_locationid = cursor.fetchone()
    return jsonify({'code': "True", 'for_locationid': for_locationid['for_locationid']})

@app.route('/move/<string:for_locationid>/<string:carid>', methods=["GET","POST"])
def move(for_locationid, carid):
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "UPDATE reserve_table SET status = 0 WHERE for_carid = '%s' AND status = 1;" % (carid)
        cursor.execute(sql)
        db.commit()
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "UPDATE location SET status = 1, for_carid = '%s' WHERE id = '%s';" % (carid, for_locationid)
        cursor.execute(sql)
        db.commit()
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "UPDATE car_table SET status = 1 WHERE id = '%s';" % (carid)
        cursor.execute(sql)
        db.commit()
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "Select address from location Where id = '%s';" % (for_locationid)
        cursor.execute(sql)
        db.commit()
        address = cursor.fetchone()['address']
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = """
        SELECT carnum FROM car_table 
        WHERE id = (SELECT for_carid FROM location WHERE id = %s LIMIT 1);
        """
        cursor.execute(sql, (for_locationid,))
        result = cursor.fetchone()
        carplate = result['carnum'] if result else None
    return render_template("move.html", title='Move Page', for_locationid=for_locationid, carid=carid, address=address, carplate=carplate,)


#连接数据库，查询车位经纬度
@app.route('/getParkingLocation', methods=['GET'])
def get_parking_location():
    car_plateid = request.args.get('id')
    if not car_plateid:
        return jsonify({"error": "车位ID不能为空"})
    cursor = db.cursor(pymysql.cursors.DictCursor)
    query = "SELECT position_lat, position_lng FROM location WHERE id = %s"
    cursor.execute(query, (car_plateid,))
    location = cursor.fetchone()

    if location:
        return jsonify({
            "lat": location['position_lat'],
            "lng": location['position_lng']
        })
    else:
        return jsonify({"error": "车位未找到"})

@app.route('/out/', methods=["GET","POST"])
def out():
    carid = request.get_json()['carid']
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "UPDATE location SET status = 0, for_carid = NULL WHERE for_carid = '%s';" % (carid)
        cursor.execute(sql)
        db.commit()
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "UPDATE car_table SET status = 0 WHERE id = '%s';" % (carid)
        cursor.execute(sql)
        db.commit()
    return jsonify({'code': "True"})

@app.route('/order/', methods=["GET","POST"])
def order():
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "SELECT * FROM reserve_table WHERE for_userid = '%s' ORDER BY expire_time DESC ;" % (session['id']) 
        cursor.execute(sql)
        cars = cursor.fetchall()
    for car in cars:
        with db.cursor(pymysql.cursors.DictCursor) as cursor:
            sql = "SELECT * FROM car_table WHERE id = '%s';" % (car['for_carid'])
            cursor.execute(sql)
            car['carinfo'] = cursor.fetchone()
        with db.cursor(pymysql.cursors.DictCursor) as cursor:
            sql = "SELECT * FROM location WHERE id = '%s';" % (car['for_locationid'])
            cursor.execute(sql)
            car['locationinfo'] = cursor.fetchone()
    return render_template("order.html", title='Order Page', cars=cars)

@app.route('/cancel_order/', methods=["GET","POST"])
def cancel_order():
    data = request.get_json()
    car_id = data['car_id']
    reserve_id = data['reserve_id']
    location_id = data['location_id']
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "UPDATE reserve_table SET status = 0 WHERE id = '%s';" % (reserve_id)
        cursor.execute(sql)
        db.commit()
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "UPDATE location SET status = 0, for_carid = NULL WHERE id = '%s';" % (location_id)
        cursor.execute(sql)
        db.commit()
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "UPDATE car_table SET status = 0 WHERE id = '%s';" % (car_id)
        cursor.execute(sql)
        db.commit()
    return jsonify({'code': "True"})

@app.route('/car/', methods=["GET","POST"])
def car():
    id = session.get('id')
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "SELECT * FROM car_table WHERE for_userid = '%s';" % (session['id'])
        cursor.execute(sql)
        cars = cursor.fetchall()
    return render_template("car.html", title='Car Page', cars=cars, id=id)

@app.route('/add_car/', methods=["GET","POST"])
def add_car():
    userid = request.get_json()['userid']
    carnum = request.get_json()['carnum']
    cartype = request.get_json()['cartype']
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "SELECT * FROM car_table WHERE carnum = '%s';" % (carnum)
        cursor.execute(sql)
        result = cursor.fetchone()
    if result is not None:
        return jsonify({'code': "False"})
    else:
        with db.cursor(pymysql.cursors.DictCursor) as cursor:
            sql = "INSERT INTO car_table (for_userid, carnum, cartype, status) VALUES ('%s','%s','%s',0);" % (userid, carnum, cartype)
            cursor.execute(sql)
            db.commit()
        return jsonify({'code': "True"})

@app.route('/delete_car/', methods=["GET","POST"])
def delete_car():
    data = request.get_json()
    car_id = data['car_id']
    print(car_id)
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "DELETE FROM car_table WHERE id = '%s';" % (car_id)
        cursor.execute(sql)
        db.commit()
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "UPDATE location SET status = 0, for_carid = NULL WHERE for_carid = '%s';" % (car_id)
        cursor.execute(sql)
        db.commit()
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "UPDATE reserve_table SET status = 0 WHERE for_carid = '%s';" % (car_id)
        cursor.execute(sql)
        db.commit()
    return jsonify({'code': "True"})

@app.route('/use_location/', methods=["GET","POST"])
def use_location():
    with db.cursor(pymysql.cursors.DictCursor) as cursor:
        sql = "SELECT l.* FROM location l JOIN car_table c ON l.for_carid = c.id WHERE c.for_userid = %s AND l.status > 0;" % (session['id'])
        cursor.execute(sql)
        cars = cursor.fetchall()
    for car in cars:
        with db.cursor(pymysql.cursors.DictCursor) as cursor:
            sql = "SELECT * FROM car_table WHERE id = '%s';" % (car['for_carid'])
            cursor.execute(sql)
            car['carinfo'] = cursor.fetchone()
    return render_template("use_location.html", title='Use Location Page', cars=cars)


if __name__ == '__main__':
    initialize_scheduler()  # 初始化定时任务
    Flask.debug = True
    app.run(host='0.0.0.0',port=5000)