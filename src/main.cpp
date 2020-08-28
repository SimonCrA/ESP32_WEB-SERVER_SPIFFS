#include <Arduino.h>
#include "ESPAsyncWebServer.h"
#include <WiFi.h>
#include <SPIFFS.h>

//SSID & PASSWORD
const char* ssid = "noShar3";
const char* password = "holacomoestas";

//Set the number of pins
const int ledPin26 = 26;
const int ledPin27 = 27;

//Stores LED state
String led26State;
String led27State;

//Create AsyncWebServer Object on port 80
AsyncWebServer server(80);

// Replaces placeholder with LED state value PIN 26
String processorPIN26(const String &var)
{
  Serial.println(var);
  if (var == "STATE")
  {
    if (digitalRead(ledPin26))
    {
      led26State = "ON";
    }
    else
    {
      led26State = "OFF";
    }
    Serial.println(led26State);

    return led26State;
  }
  return String();
}
// Replaces placeholder with LED state value PIN 27
String processorPIN27(const String &var)
{
  Serial.println(var);
  if (var == "STATE")
  {
    if (digitalRead(ledPin27))
    {
      led27State = "ON";
    }
    else
    {
      led27State = "OFF";
    }
    Serial.println(led27State);

    return led27State;
  }
  return String();
}

void setup() {

  Serial.begin(115200);
  pinMode(ledPin26, OUTPUT);
  pinMode(ledPin27, OUTPUT);

  //Initialize SPIFFS, if an error has ocurred while mounting spiffs, we handle it right here.|
  if(!SPIFFS.begin(true)) {
    Serial.println("An Error has ocurred while mounting SPIFFS");
    return;
  }

  //Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.println("Connecting to WiFi...");
  }

  //Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  //Route for root / web Page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", String(), false, processorPIN26);
    // request->send(SPIFFS, "index.html", String(), false, processorPIN27);
  });

  //route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS,"/style.css","text/css");
  });

  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(ledPin26, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processorPIN26);
  });

  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(ledPin26, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processorPIN26);
  });
  
  //start server
  server.begin();

}

void loop() {
  
}