import hashlib
import os
from flask import Flask, redirect, render_template, send_from_directory, session, url_for, request, flash, jsonify, \
    send_file
import pymysql,base64
from datetime import datetime
from dbutils.pooled_db import PooledDB

app = Flask(__name__)
app.config['SECRET_KEY'] = os.urandom(30)
#数据库连接池
pool = PooledDB(
    creator=pymysql,
    maxconnections=10,
    mincached=2,
    maxcached=5,
    blocking=True,
    maxusage=None,
    setsession=[],
    ping=0,
    host='127.0.0.1',
    user='root',
    password='805345',
    database='postsys',
    charset='utf8mb4'
)

##主页
@app.route("/")
def index():
    username = session.get("username", "")
    return render_template("index.html", usernow=username)

##全局模糊搜索
@app.route("/search")
def search():
    username = session.get("username", "")
    cursor = pool.connection().cursor(pymysql.cursors.DictCursor)
    posts_per_page = 5
    page = request.args.get('page', 1, type=int)
    offset = (page - 1) * posts_per_page
    search = request.args.get('search', '')

    if search:
        cursor.execute("""SELECT id, username, title, issue_date, image FROM posts WHERE title LIKE %s LIMIT %s OFFSET %s""",
                       ('%' + search + '%', posts_per_page, offset))
        posts = cursor.fetchall()
    else:
        posts = []
    if search:
        cursor.execute("""SELECT COUNT(*) as total FROM posts WHERE title LIKE %s""", ('%' + search + '%',))
        total_posts = cursor.fetchone().get('total', 0)
    else:
        total_posts = 0
    cursor.close()

    for post in posts:
        if post["image"]:
            post["image"] = base64.b64encode(post["image"]).decode('utf-8')

    #计算总页数
    total_pages = (total_posts + posts_per_page - 1) // posts_per_page
    return render_template('search.html', posts=posts, usernow=username, total_pages=total_pages, current_page=page,
                           search=search)

#分类列表
@app.route("/category.html")
def category():
    username = session.get("username", "")
    category = request.args.get('category', '')
    page = int(request.args.get('page', 1))  # 获取当前页，默认第1页
    conn = pool.connection()
    cursor = conn.cursor(pymysql.cursors.DictCursor)

    try:
        posts_per_page = 5
        offset = (page - 1) * posts_per_page
        cursor.execute(
            """SELECT id, title, issue_date, username, image FROM posts WHERE category=%s LIMIT %s OFFSET %s""",
            (category, posts_per_page, offset))
        posts = cursor.fetchall()

        cursor.execute("""SELECT COUNT(*) as total FROM posts WHERE category=%s""", (category,))

        total_posts = cursor.fetchone().get('total', 0)
        total_pages = (total_posts + posts_per_page - 1) // posts_per_page

        for post in posts:
            if post["image"]:
                post["image"] = base64.b64encode(post["image"]).decode('utf-8')

        return render_template("category.html", category=category, page=page, posts=posts, usernow=username,
                               total_pages=total_pages)

    except Exception as e:
        flash("查询失败，请稍后再试。")
        return redirect(url_for("index"))
    finally:
        cursor.close()
        conn.close()

#获取文章
@app.route("/api/get_articles", methods=["GET"])
def get_articles():
    username = session.get("username", "")
    category = request.args.get("category", "")
    page = int(request.args.get("page", 1))
    search = request.args.get("search", "").strip()
    per_page = 9
    offset = (page - 1) * per_page
    conn = pool.connection()
    cursor = conn.cursor(pymysql.cursors.DictCursor)

    try:
        query = """SELECT id, title, DATE_FORMAT(issue_date, '%%Y-%%m-%%d %%H:%%i:%%s') AS issue_date, username, image 
                   FROM posts WHERE 1=1"""
        params = []
        if category:
            query += " AND category = %s"
            params.append(category)
        if search:
            query += " AND title LIKE %s"
            params.append(f"%{search}%")
        query += " ORDER BY issue_date DESC LIMIT %s OFFSET %s"
        params.extend([per_page, offset])

        cursor.execute(query, tuple(params))
        articles = cursor.fetchall()

        for article in articles:
            if article['image']:
                article['image'] = base64.b64encode(article['image']).decode('utf-8')

        #分页
        count_query = "SELECT COUNT(*) AS total FROM posts WHERE 1=1"
        count_params = []
        if category:
            count_query += " AND category = %s"
            count_params.append(category)
        if search:
            count_query += " AND title LIKE %s"
            count_params.append(f"%{search}%")

        cursor.execute(count_query, tuple(count_params))
        total = cursor.fetchone()['total']
        total_pages = (total + per_page - 1) // per_page
        return jsonify({"status": "success", "data": articles, "total_pages": total_pages})

    except Exception as e:
        return jsonify({"status": "error", "message": "错误！"})
    finally:
        cursor.close()
        conn.close()

##用户注册与登录
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
        result = request.get_json()
        connection = pool.connection()
        cursor = connection.cursor()
        username = result['username']
        password = result['password']
        tel = result['tel']

        cursor.execute("""SELECT * FROM user WHERE tel = %s""", (tel,))
        existing_user = cursor.fetchone()
        if existing_user:
            cursor.close()
            connection.close()
            return jsonify(success=False, message="电话号码已存在")

        cursor.execute("""SELECT * FROM user WHERE username = %s""", (username,))
        existing_username = cursor.fetchone()

        if existing_username:
            cursor.close()
            connection.close()
            return jsonify(success=False, message="用户名已存在")

        hashed_password = hashlib.md5(password.encode('utf-8')).hexdigest()

        try:
            cursor.execute("""INSERT INTO user (username, password, tel) VALUES (%s, %s, %s)""",
                           (username, hashed_password, tel))
            connection.commit()
            return jsonify(success=True)
        except Exception as e:
            connection.rollback()
            return jsonify(success=False, message="服务器错误")
        finally:
            cursor.close()
            connection.close()


@app.route("/login/")
def login():
    return render_template("login.html")
@app.route("/login_submit/", methods=["POST"])
def login_submit():
    if request.method == "POST":
        result = request.form
        connection = pool.connection()
        cursor = connection.cursor(pymysql.cursors.DictCursor)
        password = result['password']
        hashed_password = hashlib.md5(password.encode('utf-8')).hexdigest()
        cursor.execute("""SELECT * FROM user WHERE tel=%s AND password=%s""", (result['tel'], hashed_password))
        user = cursor.fetchone()
        cursor.close()
        connection.close()
        if user:
            session['username'] = user['username']
            session['userid'] = user['id']
            session['tel'] = user['tel']
            return jsonify(success=True)
        else:
            return jsonify(success=False, message="用户名或密码错误，请重试。")

##写作
@app.route('/issue/', methods=['GET', 'POST'])
def issue():
    username = session.get('username')
    if not username:
        return redirect(url_for('login'))
    isserTime = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    if request.method == 'POST':
        title = request.form.get('title')
        content = request.form.get('content')
        category = request.form.get('category')
        image_base64 = request.form.get('image')
        image_data = None
        files = request.files.getlist('files[]')
        file_paths = []
        attachment_info = []

        for file in files:
            if file:
                file_path = os.path.join('uploads', file.filename)
                file.save(file_path)
                file_size = os.path.getsize(file_path)
                file_type = file.content_type
                #保存附件列表
                attachment_info.append({'file_name': file.filename, 'file_path': file_path, 'file_size': file_size,
                                        'file_type': file_type})
        #图片的Base64编码
        if image_base64:
            header, encoded_image = image_base64.split(",", 1)
            image_data = base64.b64decode(encoded_image)

        connection = pool.connection()
        cursor = connection.cursor()
        try:
            #文章插入
            cursor.execute(
                """INSERT INTO posts (username, issue_date, title, content, image, category) VALUES (%s, %s, %s, %s, %s, %s)""",
                (username, isserTime, title, content, image_data, category))
            connection.commit()
            post_id = cursor.lastrowid

            #附件信息
            for attachment in attachment_info:
                cursor.execute(
                    """INSERT INTO attachments (post_id, file_name, file_path, file_size, file_type)VALUES (%s, %s, %s, %s, %s)""",
                    (post_id, attachment['file_name'], attachment['file_path'], attachment['file_size'],
                     attachment['file_type']))
            connection.commit()
            flash('文章发布成功')
            return jsonify({'status': 'success', 'message': '操作成功'})
        except Exception as e:
            connection.rollback()
            return jsonify({'status': 'error', 'message': '操作失败'})
        finally:
            cursor.close()
            connection.close()
    return render_template('issue.html', usernow=username)

##管理
@app.route('/manage/')
def manage():
    username = session.get("username", "")
    if not username:
        return redirect(url_for('login'))

    posts_per_page = 5
    page = request.args.get('page', 1, type=int)
    offset = (page - 1) * posts_per_page
    search = request.args.get('search', '')

    connection = pool.connection()
    cursor = connection.cursor(pymysql.cursors.DictCursor)

    try:
        if username == "root":
            if search:
                cursor.execute("""SELECT id, title, username, issue_date, image 
                                  FROM posts WHERE title LIKE %s LIMIT %s OFFSET %s""",
                               ('%' + search + '%', posts_per_page, offset))
            else:
                cursor.execute("""SELECT id, title, username, issue_date, image 
                                  FROM posts LIMIT %s OFFSET %s""",
                               (posts_per_page, offset))
        else:
            if search:
                cursor.execute("""SELECT id, title, issue_date, username, image 
                                  FROM posts WHERE username=%s AND title LIKE %s LIMIT %s OFFSET %s""",
                               (username, '%' + search + '%', posts_per_page, offset))
            else:
                cursor.execute("""SELECT id, title, issue_date, username, image 
                                  FROM posts WHERE username=%s LIMIT %s OFFSET %s""",
                               (username, posts_per_page, offset))
        posts = cursor.fetchall()
        if search:
            cursor.execute("""SELECT COUNT(*) as total FROM posts WHERE title LIKE %s""", ('%' + search + '%',))
        else:
            if username == "root":
                cursor.execute("""SELECT COUNT(*) as total FROM posts""")
            else:
                cursor.execute("""SELECT COUNT(*) as total FROM posts WHERE username=%s""", (username,))
        total_posts = cursor.fetchone()['total']

        for post in posts:
            if post["image"]:
                post["image"] = base64.b64encode(post["image"]).decode('utf-8')
        total_pages = (total_posts + posts_per_page - 1) // posts_per_page
        return render_template('manage.html', posts=posts, usernow=username, total_pages=total_pages,
                               current_page=page, search=search)
    except Exception as e:
        return jsonify({"status": "error", "message": "操作失败"})
    finally:
        cursor.close()
        connection.close()

#编辑
@app.route('/edit_post', methods=['GET', 'POST'])
def edit_post():
    username = session.get("username", "")
    if not username:
        return redirect(url_for('login'))

    post_id = request.args.get('post_id')
    if not post_id:
        return jsonify({"success": False, "message": "无效的文章ID"})

    connection = pool.connection()
    cursor = connection.cursor(pymysql.cursors.DictCursor)

    try:
        if request.method == 'POST':
            data = request.get_json()
            title = data.get('title')
            content = data.get('content')
            category = data.get('category')
            image_base64 = data.get('image')

            if username == "root":
                cursor.execute("SELECT * FROM posts WHERE id=%s", (post_id,))
            else:
                cursor.execute("SELECT * FROM posts WHERE id=%s AND username=%s", (post_id, username))
            post = cursor.fetchone()

            if not post:
                return jsonify({"success": False, "message": "无权编辑该文章"})
            if not image_base64:
                image_data = post.get('image')
            else:
                image_data = base64.b64decode(image_base64)

            cursor.execute("""
                UPDATE posts SET title=%s, content=%s, category=%s, image=%s 
                WHERE id=%s AND (username=%s OR 'root' = %s)""",
                (title, content, category, image_data, post_id, username, username))

            if username == "root":
                cursor.execute("""
                    UPDATE posts SET title=%s, content=%s, category=%s, image=%s 
                    WHERE id=%s""",
                    (title, content, category, image_data, post_id))

            files = request.files.getlist('files[]')
            for file in files:
                if file:
                    file_path = os.path.join('uploads', file.filename)
                    file.save(file_path)
                    cursor.execute("""
                        INSERT INTO attachments (post_id, file_name, file_path, file_size, file_type) 
                        VALUES (%s, %s, %s, %s, %s)""",
                        (post_id, file.filename, file_path, os.path.getsize(file_path), file.content_type))
            connection.commit()

            return jsonify({"success": True, "message": "文章更新成功"})
        cursor.execute("SELECT * FROM attachments WHERE post_id=%s", (post_id,))
        attachments = cursor.fetchall()

        if username == "root":
            cursor.execute("SELECT * FROM posts WHERE id=%s", (post_id,))
        else:
            cursor.execute("SELECT * FROM posts WHERE id=%s AND username=%s", (post_id, username))
        post = cursor.fetchone()

        if not post:
            return jsonify({"success": False, "message": "无权编辑该文章"})
        if post.get("image"):
            post["image"] = base64.b64encode(post["image"]).decode('utf-8')
        return render_template('edit.html', post=post, usernow=username, attachments=attachments)

    except Exception as e:
        return jsonify({"success": False, "message": "更新失败, 请重试"})
    finally:
        cursor.close()
        connection.close()

##上传新附件
@app.route('/upload_attachments', methods=['POST'])
def upload_attachments():
    post_id = request.args.get('post_id')
    if not post_id:
        return jsonify({"success": False, "message": "无效的文章ID"})

    files = request.files.getlist('files[]')
    connection = pool.connection()
    cursor = connection.cursor(pymysql.cursors.DictCursor)

    try:
        for file in files:
            if file:
                file_path = os.path.join('uploads', file.filename)
                file.save(file_path)
                cursor.execute("""
                    INSERT INTO attachments (post_id, file_name, file_path, file_size, file_type) 
                    VALUES (%s, %s, %s, %s, %s)""",
                               (post_id, file.filename, file_path, os.path.getsize(file_path), file.content_type))
        connection.commit()

        return jsonify({"success": True, "message": "附件上传成功"})
    except Exception as e:
        connection.rollback()
        return jsonify({"success": False, "message": "上传失败，请重试"})
    finally:
        cursor.close()
        connection.close()

#附件删除
@app.route('/delete_attachment', methods=['POST'])
def delete_attachment():
    username = session.get("username", "")
    if not username:
        return jsonify({"success": False, "message": "未登录"})
    data = request.get_json()
    attachment_id = data.get('attachment_id')
    post_id = data.get('post_id')
    conn = pool.connection()
    cursor = conn.cursor(pymysql.cursors.DictCursor) #返回字典

    try:
        cursor.execute("SELECT * FROM attachments WHERE id=%s AND post_id=%s", (attachment_id, post_id))
        attachment = cursor.fetchone()
        if not attachment:
            return jsonify({"success": False, "message": "附件不存在"})
        file_path = attachment.get('file_path')
        cursor.execute("DELETE FROM attachments WHERE id=%s", (attachment_id,))
        conn.commit()
        if file_path and os.path.exists(file_path):
            os.remove(file_path)

        return jsonify({"success": True, "message": "附件删除成功"})

    except Exception as e:
        conn.rollback()
        return jsonify({"success": False, "message": "删除附件失败，请重试"})

    finally:
        cursor.close()
        conn.close()

#附件下载
@app.route('/download/<int:attachment_id>')
def download(attachment_id):
    conn = pool.connection()
    cursor = conn.cursor()
    cursor.execute("SELECT file_path FROM attachments WHERE id = %s", (attachment_id,))
    attachment = cursor.fetchone()
    cursor.close()
    conn.close()

    if attachment:
        file_path = attachment[0]
        if os.path.exists(file_path):
            return send_file(file_path, as_attachment=True)
        else:
            flash('文件不存在')
            return redirect(url_for('index'))
    else:
        flash('附件未找到')
        return redirect(url_for('index'))

##删文章
@app.route('/delete_post', methods=['POST'])
def delete_post():
    username = session.get("username", "")
    if not username:
        return redirect(url_for('login'))
    post_id = request.form.get("post_id")
    connection = pool.connection()
    cursor = connection.cursor()

    try:
        if username == "root":
            cursor.execute("""DELETE FROM posts WHERE id=%s""", (post_id,))
        else:
            cursor.execute("""DELETE FROM posts WHERE id=%s AND username=%s""", (post_id, username))
        connection.commit()
        return jsonify({"success": True, "message": "文章删除成功"})

    except Exception as e:
        connection.rollback()
        return jsonify({"success": False, "message": "文章删除失败"})
    finally:
        cursor.close()
        connection.close()

##看
@app.route('/view_post')
def view_post():
    username = session.get("username", "")
    post_id = request.args.get('post_id')
    if not post_id:
        flash("文章ID无效")
        return redirect(url_for('manage'))

    connection = pool.connection()
    cursor = connection.cursor(pymysql.cursors.DictCursor)

    try:
        cursor.execute("""SELECT * FROM posts WHERE id=%s""", (post_id,))
        post = cursor.fetchone()
        #访问量
        if post:
            cursor.execute("UPDATE posts SET views = views + 1 WHERE id = %s", (post_id,))
            connection.commit()
        if not post:
            flash("文章不存在")
            return redirect(url_for('manage'))
        #评论
        cursor.execute(
            """SELECT c.id, c.content, c.created_at, u.username FROM comments c JOIN user u ON c.userid = u.id WHERE c.post_id = %s ORDER BY c.created_at DESC""",
            (post_id,))
        comments = cursor.fetchall()
        #附件
        cursor.execute("SELECT * FROM attachments WHERE post_id = %s", (post_id,))
        attachments = cursor.fetchall()
    finally:
        cursor.close()
        connection.close()
    #图片
    if post.get("image"):
        post["image"] = base64.b64encode(post["image"]).decode('utf-8')

    return render_template('view.html', post=post, comments=comments, usernow=username, attachments=attachments)

#加评论
@app.route('/add_comment', methods=['POST'])
def add_comment():
    if 'username' not in session:
        return jsonify({'success': False, 'message': '请先登录'})
    post_id = request.form.get('post_id')
    content = request.form.get('content')
    parent_id = request.form.get('parent_id', 0)
    if not content:
        return jsonify({'success': False, 'message': '评论内容不能为空'})

    userid = session.get('userid')
    if not userid:
        return jsonify({'success': False, 'message': '无法获取用户信息'})

    connection = pool.connection()
    cursor = connection.cursor()

    try:
        cursor.execute(
            """INSERT INTO comments (post_id, userid, content, parent_id, created_at) VALUES (%s, %s, %s, %s, NOW())""",
            (post_id, userid, content, parent_id))
        connection.commit()
    except Exception as e:
        connection.rollback()
        return jsonify({'success': False, 'message': '服务器错误'})
    finally:
        cursor.close()
        connection.close()

    return jsonify({'success': True, 'message': '评论成功'})


##评论表
@app.route('/get_comments/<int:post_id>', methods=['GET'])
def get_comments(post_id):
    connection = pool.connection()
    cursor = connection.cursor(pymysql.cursors.DictCursor)
    try:
        #主评论
        cursor.execute("""SELECT c.id, c.content, c.created_at, u.username, c.parent_id 
                          FROM comments c 
                          JOIN user u ON c.userid = u.id 
                          WHERE c.post_id = %s AND c.parent_id = 0 
                          ORDER BY c.created_at DESC""", (post_id,))
        comments = cursor.fetchall()

        #获取所有回复
        for comment in comments:
            comment['replies'] = get_replies(comment['id'], connection)
            comment['created_at'] = comment['created_at'].strftime('%Y-%m-%d %H:%M:%S')
    finally:
        cursor.close()
        connection.close()

    return jsonify(comments)


#递归获取回复
def get_replies(parent_id, connection):
    cursor = connection.cursor(pymysql.cursors.DictCursor)
    try:
        cursor.execute("""SELECT c.id, c.content, c.created_at, u.username, c.parent_id 
                          FROM comments c 
                          JOIN user u ON c.userid = u.id 
                          WHERE c.parent_id = %s 
                          ORDER BY c.created_at DESC""", (parent_id,))
        replies = cursor.fetchall()

        #递归加载回复
        for reply in replies:
            reply['replies'] = get_replies(reply['id'], connection)
            reply['created_at'] = reply['created_at'].strftime('%Y-%m-%d %H:%M:%S')
    finally:
        cursor.close()
    return replies


##删除评论
@app.route('/delete_comment', methods=['POST'])
def delete_comment():
    if 'username' not in session:
        return jsonify({'success': False, 'message': '请先登录'})

    comment_id = request.form.get('comment_id')
    username = session['username']
    userid = session['userid']

    connection = pool.connection()
    cursor = connection.cursor(pymysql.cursors.DictCursor)

    try:
        cursor.execute("""SELECT c.userid AS comment_userid, p.username AS post_author 
                          FROM comments c 
                          JOIN posts p ON c.post_id = p.id 
                          WHERE c.id = %s """, (comment_id,))
        comment = cursor.fetchone()

        if not comment:
            return jsonify({'success': False, 'message': '评论不存在'})
        if username != 'root' and userid != comment['comment_userid'] and username != comment['post_author']:
            return jsonify({'success': False, 'message': '无权操作！'})
        #递归删除所有回复
        delete_replies(comment_id, connection)
        #删评
        cursor.execute("""DELETE FROM comments WHERE id = %s""", (comment_id,))
        connection.commit()

        return jsonify({'success': True, 'message': '评论删除成功'})
    except Exception as e:
        connection.rollback()
        return jsonify({'success': False, 'message': '服务器错误'})
    finally:
        cursor.close()
        connection.close()

#递归删除回复
def delete_replies(parent_id, connection):
    cursor = connection.cursor()
    try:
        cursor.execute("""SELECT id FROM comments WHERE parent_id = %s""", (parent_id,))
        replies = cursor.fetchall()

        for reply in replies:
            delete_replies(reply['id'], connection)
            cursor.execute("""DELETE FROM comments WHERE id = %s""", (reply['id'],))
    finally:
        cursor.close()

if __name__ == '__main__':
    app.run(debug=True)
