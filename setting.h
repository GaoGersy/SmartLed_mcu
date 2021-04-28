#include <ESP8266WiFi.h>

//配置 AP 

const char *ssid = "ESP8266";
const char *password = "12345678";

IPAddress ip(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);


void set_wifi()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid, password);
}
