from flask import Flask, jsonify, render_template
import serial
import platform
import time

system = platform.system()
if system == "Linux":
    port = '/dev/ttyACM0'
elif system == "Windows":
    port = 'COM5'
else:
    raise Exception(f"Unsupported platform: {system}")
try:
    pico = serial.Serial(port, 115200, timeout=1)
    time.sleep(2)
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    pico = None

site_path = "../website"
app = Flask(__name__, template_folder=site_path, static_folder=site_path)

def read_data():
    if pico is None:
        return jsonify({"error": "Serial port not available"}), 500

    try:
        line = pico.readline().decode('utf-8', errors='ignore').strip()
        if line:
            try:
                x_str, y_str = line.split(',')
                data = {
                    "temperature": float(x_str),
                    "humidity": float(y_str)
                }
                return jsonify(data)
            except ValueError:
                return jsonify({"error": f"Invalid data format: {line}"}), 400
        else:
            return jsonify({"error": "No data received"}), 500
    except serial.SerialException as e:
        return jsonify({"error": str(e)}), 500

@app.route("/api/weather")
def weather():
    return read_data()

@app.route("/")
def index():
    return render_template("index.html")

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
