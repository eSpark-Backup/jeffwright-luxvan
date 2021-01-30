#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
AsyncWebServer server(80);
const char *ssid = "ESP32-AP";
const char *password = "12345678";
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
}
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP); //WiFi in AP Mode for Server Creation
  WiFi.softAP(ssid, password);
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "application/json", "{\"message\":\"Welcome\"}");
  });
  server.on("/get-message", HTTP_GET, [](AsyncWebServerRequest *request) {
    StaticJsonDocument<100> data;
    if (request->hasParam("message"))
    {
      data["message"] = request->getParam("message")->value();
    }
    else
    {
      data["message"] = "No message parameter";
    }
    String response;
    serializeJson(data, response);
    request->send(200, "application/json", response);
  });
  AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler("/post-message", [](AsyncWebServerRequest *request, JsonVariant &json) {
    StaticJsonDocument<200> data;
    if (json.is<JsonArray>())
    {
      data = json.as<JsonArray>();
    }
    else if (json.is<JsonObject>())
    {
      data = json.as<JsonObject>();
    }
    String response;
    serializeJson(data, response);
    request->send(200, "application/json", response);
    Serial.println(response);
  });
  server.addHandler(handler);
server.onNotFound(notFound);
  server.begin();
}
void loop()
{
}
