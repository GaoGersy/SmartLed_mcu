
//#include "config.h"
//#include "configStore.h"

#include "LedServer.h"
#include "setting.h"

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
  begin();
  set_wifi();
  startServer();
}

void loop() {
  runLedFlow();
}
