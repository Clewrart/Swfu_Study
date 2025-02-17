import os
from flask import Flask, redirect, render_template, send_from_directory, session, url_for, request, flash
import pymysql
from flask_paginate import Pagination, get_page_parameter

app = Flask(__name__)
app.config['SECRET_KEY'] = os.urandom(30)
app.config['UPLOAD_FOLDER'] = 'static/uploads'
app.config['ALLOWED_EXTENSIONS'] = {'png', 'jpg', 'jpeg', 'gif'}

# MySQL连接配置
db = pymysql.connect(host='127.0.0.1', user='root', password='805345', database='blogsys')

@app.route("/")
def index():
    username = session.get("username", "")
    cursor = db.cursor(pymysql.cursors.DictCursor)


    # 获取当前页码
    page = request.args.get(get_page_parameter(), type=int, default=1)
    per_page = 6  # 每页显示6篇文章
    offset = (page - 1) * per_page

    # 获取文章数据并分页
    cursor.execute("SELECT * FROM posts LIMIT %s OFFSET %s ", (per_page, offset))
    posts = cursor.fetchall()

    # 获取文章总数
    cursor.execute("SELECT COUNT(*) FROM posts")
    total = cursor.fetchone()['COUNT(*)']
    cursor.close()

    pagination = Pagination(page=page, total=total, per_page=per_page, css_framework='bootstrap5')

    return render_template("index.html", posts=posts, pagination=pagination, usernow=username)


@app.route('/view_post/<int:post_id>')
def view_post(post_id):
    cursor = db.cursor(pymysql.cursors.DictCursor)
    sql = "SELECT * FROM posts WHERE id=%s"
    cursor.execute(sql, (post_id,))
    post = cursor.fetchone()
    cursor.close()
    if post:
        return render_template('post.html', post=post)
    else:
        flash('文章不存在！')
        return redirect(url_for('index'))

@app.route("/login/")
def login():
    return render_template("login.html")

@app.route('/logout/')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

@app.route("/regi/")
def regi():
    return render_template("regi.html")



@app.route("/regi_submit/", methods=["POST"])
def regi_submit():
    if request.method == "POST":
        result = request.form
        cursor = db.cursor()
        sql = "INSERT INTO user (username, password, email) VALUES (%s, %s, %s)"
        try:
            cursor.execute(sql, (result['username'], result['password'], result['email']))
            db.commit()
            return redirect(url_for('login'))
        except Exception as e:
            db.rollback()
            return render_template("regi.html", message="对不起，注册失败，请重新提交！")
        finally:
            cursor.close()

@app.route("/login_submit/", methods=["POST"])
def login_submit():
    if request.method == "POST":
        result = request.form
        cursor = db.cursor(pymysql.cursors.DictCursor)
        sql = "SELECT * FROM user WHERE username=%s AND password=%s"
        cursor.execute(sql, (result['username'], result['password']))
        row = cursor.fetchone()
        cursor.close()
        if row:
            session['username'] = row['username']
            session['userid'] = row['id']
            session['email'] = row['email']
            return redirect(url_for('index'))
        else:
            return render_template("login.html", user_not_found=True)

@app.route('/issue/', methods=['GET', 'POST'])
def issue():
    username = session.get('username')
    if not username:
        return redirect(url_for('login'))

    if request.method == 'POST':
        issue_date = request.form.get('issue_date')
        title = request.form.get('title')
        content = request.form.get('content')

        cursor = db.cursor()
        sql = "INSERT INTO posts (username, issue_date, title, content) VALUES (%s, %s, %s, %s)"
        try:
            cursor.execute(sql, (username, issue_date, title, content))
            db.commit()
            return redirect(url_for('index'))
        except Exception as e:
            db.rollback()
            flash('文章发布失败，请重试。')
            return render_template('issue.html', usernow=username)
        finally:
            cursor.close()
    return render_template('issue.html', usernow=username)

@app.route('/img/', methods=['GET', 'POST'])
def img():
    username = session.get("username", "")
    if request.method == 'POST':
        if 'file' not in request.files:
            flash('没有选择文件')
            return redirect(request.url)
        file = request.files['file']
        if file.filename == '':
            flash('没有选择文件')
            return redirect(request.url)
        if file and (file.filename):
            filename = (file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
            # 保存文件信息到数据库
            cursor = db.cursor()
            sql = "INSERT INTO images (filename) VALUES (%s)"
            try:
                cursor.execute(sql, (filename,))
                db.commit()
                flash('文件成功上传')
            except Exception as e:
                db.rollback()
                flash('文件上传失败')
            finally:
                cursor.close()
            return redirect(url_for('img'))
    else:
        cursor = db.cursor(pymysql.cursors.DictCursor)
        cursor.execute("SELECT * FROM images")
        images = cursor.fetchall()
        cursor.close()
        return render_template('img.html', images=images, usernow=username)
    
    
    
@app.route('/uploads/<filename>')
def uploaded_file(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

@app.route('/manage/')
def manage():
    username = session.get("username", "")
    if not username:
        return redirect(url_for('login'))

    cursor = db.cursor(pymysql.cursors.DictCursor)
    cursor.execute("SELECT * FROM posts WHERE username=%s", (username,))
    posts = cursor.fetchall()
    cursor.close()
    
    return render_template('manage.html', posts=posts, usernow=username)

@app.route('/delete_post/<int:post_id>', methods=['POST'])
def delete_post(post_id):
    username = session.get("username", "")
    if not username:
        return redirect(url_for('login'))

    cursor = db.cursor()
    sql = "DELETE FROM posts WHERE id=%s AND username=%s"
    try:
        cursor.execute(sql, (post_id, username))
        db.commit()
        flash('文章删除成功')
    except Exception as e:
        db.rollback()
        flash('文章删除失败')
    finally:
        cursor.close()

    return redirect(url_for('manage'))

if __name__ == '__main__':
    app.run(debug=True)
