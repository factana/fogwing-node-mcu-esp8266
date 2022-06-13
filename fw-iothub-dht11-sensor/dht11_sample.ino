#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN 4     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials
#define WIFI_SSID "Your WiFi SSID"
#define WIFI_PASS "Your WiFi Password"

// MQTT broker
#define MQTT_BROKER "iothub.enterprise.fogwing.net"

// Fogwing MQTT Access credentials
#define CLIENT_ID "Client ID"
#define USER_NAME "MQTT User Name"
#define PASSWORD "MQTT Password"

// Fogwing MQTT Access publish and subscribe topics
#define PUB_EDGE "Publish Topic"
#define SUB_EDGE "Subscribe Topic"

// 1 min time frequency to send the data to Fogwing IoT Hub
#define TIME_FREQ ((1000 * 60) * 1)


// Client object for WiFi
WiFiClient wifiClient;

// Client object for MQTT
PubSubClient client(wifiClient);

void setup() {
  // Initialize ESP8266 serial interface
  Serial.begin(9600);

  dht.begin();

  // Initialize WiFi
  initWiFi();

  // Set server and port here
  client.setServer(MQTT_BROKER, 1883);

  // Set function to receive the subscribed message
  client.setCallback(onMsgReception);
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

    float h = dht.readHumidity();        // read humidity
    float t = dht.readTemperature();     // read temperature

    // Create JSON object
    StaticJsonDocument<500> jsonData;

    // Variable to store JSON payload
    char payload[500];

    // JSON payload
    jsonData["temperature"] = t;
    jsonData["humidity"] = h;


    // Serialize JSON to send over network
    serializeJson(jsonData, payload);

    // Publish your data
    if (client.publish(PUB_EDGE, payload)) {
      Serial.print(F("Published >> "));
      Serial.println(payload);
    }
    else
      Serial.println(F("Error publishing payload"));

    // Subscribe to topic
    if (client.subscribe(SUB_EDGE)) {
      Serial.print(F("Subscribed to topic"));
      Serial.println(SUB_EDGE);
    }
    else
      Serial.println(F("Error subscribing to topic"));

    tLast = tNow;
  }

  // Check continuously for incomming message from subscribed topic
  client.loop();
  delay(100);
}

void initWiFi() {
  Serial.print(F("Connecting to AP"));

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
    Serial.println(F("\nConnected to AP\n"));
  else
    Serial.println(F("Error connecting to WiFi"));
}

void reconnect() {
  // Loop untill reconnect
  while (!client.connected()) {
    if (WiFi.status() != WL_CONNECTED)
      initWiFi();

    Serial.println(F("Connecting to MQTT Broker"));
    if (client.connect(CLIENT_ID, USER_NAME, PASSWORD))
      Serial.println(F("Connected to MQTT"));
    else
      Serial.println(F("Failed to connect to MQTT"));
  }
}

// This function is responsible to receive message from MQTT Broker
void onMsgReception(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';

  Serial.println(F("\n<------------- [Message Arrived] ------------->"));
  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.println((char*)payload);
  Serial.println(F("<-------------- [End of Message] ------------->\n"));
}
