from flask import Blueprint, render_template, jsonify, request, session
from db import db_connect
import pymysql.cursors

auth_bp = Blueprint('auth', __name__)

@auth_bp.route('/login')
def login():
    return render_template('login.html')

@auth_bp.route('/login_submit', methods=['POST'])
def login_submit():
    result = request.json
    db = db_connect() 
    cursor = db.cursor(pymysql.cursors.DictCursor)
    sql = "SELECT * FROM manager WHERE manage_num = %s and password = %s"
    try:
        cursor.execute(sql, (result['username'], result['password']))
        row = cursor.fetchone()
        if row:
            session['id'] = row['id']
            session['manage_name'] = row['manage_name']
            return jsonify({"status": "success", "msg": "登录成功"})
        else:
            return jsonify({"status": "fail", "msg": "抱歉，未查询到该用户, 请联系相关人员添加"})
    except:
        return jsonify({"status": "fail", "msg": "抱歉，登录失败，请稍后再试"})
    finally:
        db.close()

@auth_bp.route('/get_user_name', methods = ['GET'])
def get_user_name():
    username = session.get("manage_name", "")
    if(id):
        return jsonify({"status": "success", "username": username})
    else:
        return jsonify({"status": "fail", "msg": "请先登录登录"})

@auth_bp.route('/logout', methods = ['GET'])
def logout():
    session.pop("id", None)
    session.pop("manage_name", None)
    if(session.get("id", "")):
        return jsonify({"status": "fail", "msg": "登出失败"})
    else:
        return jsonify({"status": "success", "msg": "登出成功"})