from flask import Flask, jsonify, render_template

site_path = "../website"
app = Flask(__name__, template_folder=site_path, static_folder=site_path)

data = {
    "temperature": 20,
    "humidity": 60,
}

@app.route("/api/weather")
def weather():
    return jsonify(data)

@app.route("/")
def index():
    return render_template("index.html")

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)