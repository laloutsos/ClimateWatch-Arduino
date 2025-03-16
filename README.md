# 🌡️ Climate Watch - Arduino 

## 📌 Overview
Climate Watch is a smart system that monitors temperature and humidity using an **Arduino**, **DHT11 sensor**, **DS3231 RTC module**, **LCD display**, and **IR remote control**. It allows users to view real-time data and control the display with an IR remote.

## 🛠️ Features
- 📊 **Real-time temperature & humidity monitoring**
- 🕒 **Date & time display** with RTC module
- 📺 **16x2 LCD display** for easy data visualization
- 🎮 **IR remote control support** to navigate the menu
- 🚨 **Overheat warning system** with LED indicators

## 🏗️ Components Required
- **Arduino Uno**
- **DHT11 Temperature & Humidity Sensor**
- **DS3231 Real-Time Clock Module**
- **16x2 LCD Display**
- **IR Remote and Receiver**
- **Resistors, LEDs, Wires & Breadboard**

## 🔌 Circuit Diagram
*(Include a schematic or Fritzing diagram here)*

## 📜 Installation & Setup
1. Clone this repository:
   ```sh
   git clone https://github.com/laloutsos/ClimateWatch-Arduino.git
   ```
2. Open the `.ino` file in the **Arduino IDE**.
3. Install the necessary libraries:
   - **DS3231** (RTC Library)
   - **IRremote** (IR Sensor Library)
   - **dht_nonblocking** (DHT11 Library)
   - **LiquidCrystal** (LCD Library)
4. Upload the code to the Arduino board.
5. Connect the components as per the circuit diagram.

## 🎮 Remote Control Functions
| Button | Function |
|--------|----------|
| EQ     | Main Menu |
| 0      | Show Date & Time |
| 1      | Thermistor Temperature |
| 2      | Humidity Display |
| 3      | Room Temperature |
| Up/Down | Navigation |


## 🤝 Contributing
Feel free to fork this repository, create pull requests, or suggest improvements in the Issues section.

## 📜 License
This project is licensed under the **MIT License**.



