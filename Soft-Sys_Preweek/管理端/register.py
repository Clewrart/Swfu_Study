from flask import Blueprint, jsonify, render_template, request
from db import db_connect

register_bp = Blueprint('register', __name__)

@register_bp.route('/register')
def register_page():
    return render_template('register.html')

@register_bp.route('/check_username', methods=['POST'])
def check_username():
    result = request.json
    username = result.get('username')
    
    if not username:
        return jsonify({"exists": False, "message": "用户名不能为空"})
    
    db = db_connect()
    cursor = db.cursor()
    
    check_sql = "SELECT COUNT(*) FROM manager WHERE manage_name = %s"
    cursor.execute(check_sql, (username,))
    count = cursor.fetchone()[0]
    
    db.close()
    
    return jsonify({"exists": count > 0})

@register_bp.route('/check_phone', methods=['POST'])
def check_phone():
    result = request.json
    phonenum = result.get('phone')
    
    if not phonenum:
        return jsonify({"exists": False, "message": "手机号不能为空"})
    
    db = db_connect()
    cursor = db.cursor()
    
    check_sql = "SELECT COUNT(*) FROM manager WHERE manage_num = %s"
    cursor.execute(check_sql, (phonenum,))
    count = cursor.fetchone()[0]
    
    db.close()
    
    return jsonify({"exists": count > 0})

@register_bp.route('/register_user', methods=['POST'])
def register_user():
    result = request.json
    username = result.get('username')
    phonenum = result.get('phone')
    password = result.get('password')
    
    if not username or not phonenum or not password:
        return jsonify({"status": "error", "message": "信息不完整"})
    
    db = db_connect()
    cursor = db.cursor()
    
    try:
        cursor.execute("SELECT COUNT(*) FROM manager WHERE manage_name = %s", (username,))
        if cursor.fetchone()[0] > 0:
            return jsonify({"status": "error", "message": "用户名已存在"})
        
        cursor.execute("SELECT COUNT(*) FROM manager WHERE manage_num = %s", (phonenum,))
        if cursor.fetchone()[0] > 0:
            return jsonify({"status": "error", "message": "手机号已被注册"})
        
        sql = """
        INSERT INTO manager(manage_name, manage_num, password)
        VALUES(%s, %s, %s)
        """
        cursor.execute(sql, (username, phonenum, password))
        db.commit()
        
        return jsonify({"status": "success", "message": "注册成功"})
        
    except Exception as e:
        db.rollback()
        return jsonify({"status": "error", "message": str(e)})
    
    finally:
        db.close()