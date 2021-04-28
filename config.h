#include <ESP8266WiFi.h>

const char *ssid = "HUAWEI_ESP";
const char *password = "12345678";

IPAddress ip(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);

void startAp()
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid, password);
}

void startConnect(){
  WiFi.begin("TP-LINK_D75A", "zqwdhnr2"); 
  while (WiFi.status() != WL_CONNECTED) {//等待WiFi连接
    delay(500);
    Serial.println("连接失败");
  }
  Serial.println(WiFi.localIP());
  Serial.print("当前模式为： ");     // 通过串口监视器输出信息
  Serial.println(WiFi.getMode());  // 告知用户设备当前工作模式
}
