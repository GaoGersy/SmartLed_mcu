#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "ws2812b.h"

bool isFlow=false;

AsyncWebServer server(80);


void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}


void startServer(){
  Serial.println("HTTP server started");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", "成功");
  });

//  server.on("/setColor", HTTP_POST, [](AsyncWebServerRequest *request) {
//    JsonArray& arr=json.as<JsonArray>();
//    int colors[3] ;
//    for(int i=0;i<3;i++){
//      colors[i] = arr[i].as<int>();
//    }
//    setColor(colors);
//    request->send(200, "text/html", "成功");
//    
//  });

    server.on("/setSpeed", HTTP_GET, [](AsyncWebServerRequest *request) {
      if(request->hasParam("speed")){ //Check if FILE was uploaded
        int speed = request->getParam("speed")->value().toInt();
        setSpeed(speed);
        request->send(200, "text/plain", "成功");
      }else{
        request->send(500, "text/plain", "失败");
      }
    });

   server.on("/setBrightness", HTTP_GET, [](AsyncWebServerRequest *request) {
      if(request->hasParam("brightness")){ //Check if FILE was uploaded
        int brightness = request->getParam("brightness")->value().toInt();
        setIsFlow(false);
        setBrightness(brightness);
        request->send(200, "text/plain", "成功");
      }else{
        request->send(500, "text/plain", "失败");
      }
    });

    server.on("/flow", HTTP_GET, [](AsyncWebServerRequest *request) {
      setIsFlow(true);
      if(request->hasParam("color")){
        AsyncWebParameter* p = request->getParam("color");
        int color= p->value().toInt();
//        Serial.println(color);
//        DynamicJsonDocument doc(100);
//        deserializeJson(doc, color);
//        JsonArray arr = doc.as<JsonArray>();
//        
//        uint32_t colors[3] ;
//        for(int i=0;i<3;i++){
//          colors[i] = arr[i].as<uint32_t>();
//        }
        setFlowColor(toColor(color));
      }
      
      request->send(200, "text/plain", "成功");
    });

   server.on("/setColor", HTTP_GET, [](AsyncWebServerRequest *request) {
    setIsFlow(false);
    if(request->hasParam("color")){ //Check if FILE was uploaded
      AsyncWebParameter* p = request->getParam("color");
      int color= p->value().toInt();
//      Serial.println(color);
//      DynamicJsonDocument doc(100);
//      deserializeJson(doc, color);
//      JsonArray arr = doc.as<JsonArray>();
//      
//      uint32_t colors[3] ;
//      for(int i=0;i<3;i++){
//        colors[i] = arr[i].as<uint32_t>();
//      }
      setColor(toColor(color));
      request->send(200, "text/plain", "成功");
      Serial.println("成功");
    }else{
      Serial.println("失败");
      request->send(500, "text/plain", "失败");
    }
  });

  server.onNotFound(notFound);

  //启动 web 服务器
  server.begin();
}

void runLedFlow(){
    runFlow();
}
