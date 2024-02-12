#include "aws_credentials.h"

#include <WiFiClientSecure.h>   // library for secure WiFi client
#include <PubSubClient.h>       // library for MQTT communication
#include <ArduinoJson.h>        // library for JSON parsing
#include "WiFi.h"               // WiFi library for ESP32
 
#include "DHT.h"        // library for DHT sensor

#define DHTPIN 14       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

// defined topic for publishing and subscribing data from AWS IoT
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"
 
float h;    // variable for humidity
float t;    // variable for temperature
 
// instance of the DHT sensor
DHT dht(DHTPIN, DHTTYPE);
 
// WiFi client instance
WiFiClientSecure net = WiFiClientSecure();  
PubSubClient client(net);


// Function to connect to AWS IoT
void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined in aws credentials
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 

 // to check if the connection to AWS IoT is successfull
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // Subscribe to  topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
}

// Function to publish messgae to AWS IoT
void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["humidity"] = h;
  doc["temperature"] = t;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);         // print to client
 
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

 // MQTT message handler function
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);
 
  StaticJsonDocument<200> doc;            // create a json document
  deserializeJson(doc, payload);          // deserialize the incoming json message
  const char* message = doc["message"];   // extract the "message" from json message
  Serial.println(message);                // print the received message
}
 
void setup()
{
  Serial.begin(9600);   // serial communication at 9600 baudrate
  connectAWS();         // connect to AWS IoT
  dht.begin();          // initliailize the DHT sensor
}
 
void loop()
{
  h = dht.readHumidity();       // read humidity from DHT sensor
  t = dht.readTemperature();    // read temperature from DHT sensor
 
 
  if (isnan(h) || isnan(t) )  // Check if any reads failed and exit early (to try again).
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
 
  publishMessage();         // publish the sensor data to IoT
  client.loop();            // Handle MQTT messages 
  delay(1000);              // delay of one second before publishing the next message 
}