from flask import Flask, render_template, request, jsonify
app = Flask(__name__)

@app.route('/')
def index():
    return render_template('2.html') 

@app.route('/calCu', methods=['POST'])
def calculate():
    data = request.get_json()
    p1 = data.get('p1', 0)
    p2 = data.get('p2', 0)
    p3 = int(p1) + int(p2)
    return jsonify({'p3': p3})
        
if __name__ == '__main__':
    app.run(debug=True)