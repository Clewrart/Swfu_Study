import pymysql

def db_connect():
    db = pymysql.connect(
        host='47.96.10.165',
        user='sysusr',
        passwd='202412',
        database='softSys'
    )
    return db
