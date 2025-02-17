from flask import Flask, render_template, request, jsonify
app = Flask(__name__)

@app.route('/')
def index():
    return render_template('3.html') 

@app.route('/login', methods=['POST'])
def login():
    data = request.get_json()
    p1 = data.get('p1', '')
    p2 = data.get('p2', '')
    if (p1)=="admin" and (p2)=="123456":
        return {"d":"1"}
    else:
        return {"d":"0"}
    
if __name__ == '__main__':
    app.run(debug=True)