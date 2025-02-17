from flask import Flask, render_template, url_for, session
import pymysql
import pymysql.cursors
from werkzeug.utils import redirect
import os
from auth import auth_bp
from car_bp import car_bp
from location_bp import location_bp
from reserve_bp import reserve_bp
from user_bp import user_bp
from register import register_bp
from data_bp import data_bp


def db_connect():
    db = pymysql.connect(host='47.96.10.165',
                        user='sysusr',
                        passwd='202412',
                        database='softSys',
                        )
    return db


app = Flask(__name__)

app.config['SECRET_KEY'] = os.urandom(30)
app.register_blueprint(auth_bp)
app.register_blueprint(car_bp)
app.register_blueprint(location_bp)
app.register_blueprint(reserve_bp)
app.register_blueprint(user_bp)
app.register_blueprint(register_bp)
app.register_blueprint(data_bp)

@app.route('/')
def index():
    id = session.get("id", "")
    if(id):
        return render_template('index.html')
    else:
        return redirect(url_for('auth.login'))


app.debug = True

if __name__ == '__main__':
    app.run(host='0.0.0.0',port=1522)