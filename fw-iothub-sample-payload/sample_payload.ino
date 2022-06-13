#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

// WiFi credentials
#define WIFI_SSID "Enter your SSID"
#define WIFI_PASS "Enter your Wi-Fi password"

// MQTT broker
#define MQTT_BROKER "iothub.enterprise.fogwing.net"

// Fogwing MQTT Access credentials
#define CLIENT_ID "Enter Fogwing IoTHub ClientID"
#define USER_NAME "Enter Fogwing IoTHub username"
#define PASSWORD "Enter Fogwing IoTHub password"

// Fogwing MQTT Access publish and subscribe topics
#define PUB_EDGE "Enter Fogwing IoTHub publish topic"
#define SUB_EDGE "Enter Fogwing IoTHub subscribe topic"

// 5 min time frequency to send the data to Fogwing IoT Hub
#define TIME_FREQ ((1000 * 60) * 0.5)

// Client object for WiFi
WiFiClient wifiClient;

// Client object for MQTT
PubSubClient client(wifiClient);

String cmdJson;

void setup() {


  // Initialize ESP8266 serial interface
  Serial.begin(9600);

  Serial.println("..................Welcome to Fogwing IIoT Platform..................");

  // Initialize WiFi
  initWiFi();

  // Set server and port here
  client.setServer(MQTT_BROKER, 1883);

  // Set function to receive the subscribed message
  client.setCallback(callback);

  pinMode(LED_BUILTIN , OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

}

void loop() {
  static uint32_t tNow, tLast = 0;

  // Check for MQTT Server connection
  if (!client.connected())
    reconnect();

  // Store the current time ticks
  tNow = millis();

  // Send the payload at every TIME_FREQ
  if ((tNow - tLast) > TIME_FREQ) {
    // Create JSON object
    StaticJsonDocument<500> jsonData;

    // Variable to store JSON payload
    char payload[500];

    // JSON payload
    jsonData["temperature"] = random(250, 300) / 10.0;
    jsonData["humidity"] = random(500, 600) / 10.0;
    jsonData["CO2"] = random(100, 130)  / 10.0;
    jsonData["$rssi"] = random(-32, -35);
    jsonData["$battery"] = random(700, 750) / 10.0;


    // Serialize JSON to send over network
    serializeJson(jsonData, payload);

    // Publish your data
    if (client.publish(PUB_EDGE, payload)) {
      Serial.print(F("Published >> "));
      Serial.println(payload);
    }
    else
      Serial.println(F("Error publishing payload"));


    tLast = tNow;
  }

  // Check continuously for incomming message from subscribed topic
  client.loop();
  delay(100);
}

void initWiFi() {
  Serial.printf("\n Connecting to %s", WIFI_SSID);

  // Set ESP8266 in station mode
  WiFi.mode(WIFI_STA);

  // Attempt to connect to WiFi network
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait till connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED)
    Serial.printf("\n Connected to %s\n", WIFI_SSID);
  else
    Serial.println(F("Error connecting to WiFi"));
}

void reconnect() {
  // Loop untill reconnect
  while (!client.connected()) {
    if (WiFi.status() != WL_CONNECTED)
      initWiFi();

    Serial.println(F("\n Connecting to Fogwing IoTHub"));
    if (client.connect(CLIENT_ID, USER_NAME, PASSWORD)) {
      Serial.println(F("\n Connected to Fogwing IoTHub"));
      client.subscribe(SUB_EDGE);
    }
    else
      Serial.println(F("\n Failed to connect Fogwing IoTHub"));
  }
}

// This function is responsible to receive message from MQTT Broker
void callback(char* topic, byte* message, unsigned int length) {
  Serial.println();
  Serial.println("..................iothub.enterprise.fogwing.net..................");
  Serial.println();
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    //    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

  Serial.println(messageTemp);
  Serial.println();

  if (String(SUB_EDGE) == topic)
  {


    StaticJsonDocument<500> jsonData;
    DeserializationError error = deserializeJson(jsonData, messageTemp);


    if (!error) {
      if ("ON" == jsonData["LED"])
      {
        digitalWrite(LED_BUILTIN , LOW);
        Serial.println("LED status: ON");

      }
      else if ("OFF" == jsonData["LED"])
      {
        digitalWrite(LED_BUILTIN , HIGH);
        Serial.println("LED status: OFF");

      }
      else Serial.println("Invalid JSON");
    }

  }
}
