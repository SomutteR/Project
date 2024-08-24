from flask import Flask, jsonify, request, render_template
import json
app = Flask(__name__)
# Simulated in-memory storage for data
data_storage = {
    "datetime": "",
    "temperature": 0.0,
    "x": 0.0,
    "y": 0.0,
    "z": 0.0
}
