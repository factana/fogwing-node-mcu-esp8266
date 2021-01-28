# _fogwing-simulator-for-node-mcu-esp8266_

This directory provide a files that sends sample data over Fogwing IoTHub using node-mcu-esp8266.

####  Note:- that these SDKs are currently in preview and are subject to change.

## Fogwing IoT Simulation using node-mcu-esp8266

We have provided a file:
* [sample_payload.ino](https://github.com/factana/fogwing-node-mcu-esp8266/blob/main/fw-iothub-sample-payload/sample_payload.ino)

The logic behind the code is to send the sample data over Fogwing IoTHub using node-mcu-esp8266.

## Step:1
### Arduino sketch

* Copy the **sample_payload.ino** file into your Arduino IDE and you are good to start !

## Step:2
### Credentials
* Open the sketch and update it with your [Fogwing](https://enterprise.fogwing.net/) IoTHub access(MQTT Credentials).

## Step:3
### Upload the sketch
* Once you updated the sketch with Fogwing IoTHub access, compile the sketch to avoid errors if any.
* After successful compilation select the correct board for node-mcu-esp8266 from board manager and upload the sketch into the board.
* If you see the **Uploading done** than you successfully uploaded the sketch into the board.

**Note:-** Provided everything goes in line with the above mentioned instructions, you will be able to see the data on [Fogwing](https://enterprise.fogwing.net/) Platform.

## Step:4
### Start analyzing your data at Fogwing Platform
* Now you are ready to analyze your data at [Fogwing](https://enterprise.fogwing.net/)  Platform portal, you can check all the data within the Data Storage in the portal.

## Getting help and finding Fogwing docs:
* [Fogwing Platform Forum](https://enterprise.fogwing.net/)
* [Fogwing Platform Docs](https://docs.fogwing.io/fogwing-platform/)