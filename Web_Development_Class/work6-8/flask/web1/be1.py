from flask import Flask, render_template, request, jsonify
app = Flask(__name__)

@app.route('/')
def index():
    return render_template('1.html')  

@app.route('/Hello', methods=['POST'])
def hello():
    data = {'d': 'Hello, AJAX!'}
    return jsonify(data) 

if __name__ == '__main__':
    app.run(debug=True)
