from flask import Flask, jsonify, request, render_template
import json
app = Flask(__name__)
data_storage = {
    "datetime": "",
    "temperature": 0.0,
    "x": 0.0,
    "y": 0.0,
    "z": 0.0
}
@app.route('/')
def index():
    return render_template('index.html')

@app.route('/receive_data', methods=['GET'])
def receive_data():
    global data_storage
    x = request.args.get('x', default=0.0, type=float)
    y = request.args.get('y', default=0.0, type=float)
    z = request.args.get('z', default=0.0, type=float)
    datetime = request.args.get('datetime', default="", type=str)
    temperature = request.args.get('temperature', default=0.0, type=float)
    
    data_storage = {
        "datetime": datetime,
        "temperature": temperature,
        "x": x,
        "y": y,
        "z": z
    }
print(f"Received data - X: {x}, Y: {y}, Z: {z}, Datetime: {datetime}, Temperature: {temperature}")
    return "Data received", 200

@app.route('/get_data', methods=['GET'])
def get_data():
    return jsonify(data_storage)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5007)
