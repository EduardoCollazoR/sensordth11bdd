
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
//#include <SPI.h>
//#include <MFRC522.h>

#define DHTPIN D2

#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);


float humidityData;
float temperatureData;


const char* ssid = "FAM-COLLAZO";
const char* password = "familiaCOLLAZO";

char server[] = "192.168.100.157";   


WiFiClient client;    


void setup()
{
 Serial.begin(115200);
  delay(10);
  dht.begin();
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
//  server.begin();
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");
 }
void loop()
{ 
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature(); 
  Sending_To_phpmyadmindatabase(); 
  delay(60000); // interval
 }

 void Sending_To_phpmyadmindatabase()   //CONNECTING WITH DATABASE
 {
   if (client.connect(server, 8080)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET http://localhost:8080/Sensor/dth11.php?temperatura=");
    client.print("GET http://localhost:8080/Sensor/dth11.php?temperatura=");     //URL
    Serial.println(temperatureData);
    client.print(temperatureData);
    client.print("&humedad=");
    Serial.println("&humedad=");
    client.print(humidityData);
    Serial.println(humidityData);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: Your Local IP");
    client.println("Connection: close");
    client.println();
  } else {
    
    Serial.println("connection failed");
  }
 }
