#include <FS.h>  

String path="/config.data";

void configInit(){
  if(SPIFFS.begin()){                       // 启动闪存文件系统
    Serial.println("SPIFFS Started.");
  } else {
    Serial.println("SPIFFS Failed to Start.");
  }
}

String read(){
  if (SPIFFS.exists(path)) {                     // 如果访问的文件可以在SPIFFS中找到
    File file = SPIFFS.open(path, "r");          // 则尝试打开该文件
    String config = file.readString();
    file.close();                                // 并且关闭文件
    return config;                                 // 返回读取结果
  }
}

bool write(String config){
  File file = SPIFFS.open(path, "w");
  bool result = file.println(config);
  file.close();                                // 并且关闭文件
  return result;
}

bool append(String config){
  File file = SPIFFS.open(path, "a");
  bool result = file.println(config);
  file.close();                                // 并且关闭文件
  return result;
}
