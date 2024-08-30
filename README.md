A] Code Overview
1. `index.html` – Web Application
Purpose: Provides the front-end interface for the web-based dashboard.
Features:
•	Displays real-time data on cow health and environmental conditions.
•	Visualizes temperature trends, activity levels, and environmental factors.
•	Generates alerts for abnormal conditions.
Technologies: HTML, CSS, JavaScript for responsive design and dynamic content.

2. `app.py` – Flask Server Application
Purpose: Serves as the back-end server application to handle data processing and communication.
Features:
•	Handles API requests from the ESP8266 and updates the web application.
•	Processes incoming sensor data and performs necessary computations.
•	Manages database interactions and real-time data updates.
Technologies: Python with Flask framework for building a web server.

3. `test.ino` – ESP8266 Firmware
Purpose: Contains the code for the ESP8266 Wi-Fi module to interface with sensors and transmit data.
Features:
•	Reads data from DS3231 temperature sensors, DHT22 sensors, and ADXL345 accelerometers.
•	Connects to Wi-Fi network and sends data to the Flask server.
•	Includes error handling and data transmission protocols.
Technologies: Arduino IDE with C++ for ESP8266 programming.

