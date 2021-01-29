# **Fogwing enterprise**

# *IoT emulator programs for node-mcu-esp8266*

This repository contains emulated code for the Fogwing IoT for node-mcu-esp8266 that enables devices to send the data seamlessly to Fogwing IoTHub [Fogwing](https://enterprise.fogwing.net/) platform.

##### Note: that these SDKs are currently in preview and are subject to change.

## Fogwing IoT emulation for Arduino
This repository contains the following sensor's code:
* [DHT11 Sensor](https://github.com/factana/fogwing-node-mcu-esp8266/tree/main/fw-iothub-dht11-sensor)
* [Sample Message](https://github.com/factana/fogwing-node-mcu-esp8266/tree/main/fw-iothub-sample-payload)


## Installing the libraries
Install all required libraries using Arduino IDE.
* [ArduinoJson.zip](https://github.com/factana/fogwing-node-mcu-esp8266/blob/main/ArduinoJson.zip)
* [DHT_sensor_library.zip](https://github.com/factana/fogwing-node-mcu-esp8266/blob/main/DHT_sensor_library.zip)
* [PubSubClient.zip](https://github.com/factana/fogwing-node-mcu-esp8266/blob/main/PubSubClient.zip)

Download the above ZIP files. Now open Arduino IDE, go to **Sketch -> Include Library -> Add.ZIP Library...** and include all the above libraries one by one. You can also download these libraries from library manager.



## Run and Get Started with Fogwing IoT
Change required credentials with your Fogwing IoTHub access credentials after which you can upload the sketch into the board.

provided everything goes well you will find a message that reads **Done Uploading...** in the Arduino IDE.

## Start Analyzing your Data at Fogwing Platform
Now you are ready to analyze your data at [Fogwing Platform](https://enterprise.fogwing.net/) portal, you can access the data in data logs section of the portal.

## Getting help and finding Fogwing docs
* [Fogwing Platform Forum](https://enterprise.fogwing.net/)
* [Fogwing Platform Docs](https://docs.fogwing.io/)
