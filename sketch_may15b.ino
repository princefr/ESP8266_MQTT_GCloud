#include "HX711.h"
#include "esp8266_mqtt.h"
#include <ArduinoJson.h>


HX711 scale;

#ifndef LED_BUILTIN
  #define LED_BUILTIN 13
#endif

const int LOADCELL_DOUT_PIN = D2;
const int LOADCELL_SCK_PIN = D1;
// 2. Adjustment settings
const long LOADCELL_OFFSET = 50682624;
const long LOADCELL_DIVIDER = 5895655;
long formerValue = 0;



void setup() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("brut");
  setupCloudIoT();
  Serial.println("cloud iot setuped");
  scale.set_scale(LOADCELL_DIVIDER);
  scale.set_offset(LOADCELL_OFFSET); 
  Serial.println("the scale is setuped");
}



void loop() {
    mqttClient->loop();
    delay(10);  // <- fixes some issues with WiFi stability
  
    if (!mqttClient->connected()) {
      connect();
    }

   if (scale.wait_ready_timeout(1000)) {
      long reading = scale.get_units(10);
      if (reading == formerValue) {
        Serial.println("the value is similar no need to store it");
      }else{
        String action = reading < formerValue ? "adding": "removing";
        String values[] = {String(reading), action, "weight_sens_demo_01"};
        DynamicJsonDocument doc(1024);
        doc["action"] = action;
        doc["weight"]   = reading;
        doc["id"] = "weight_sens_demo_01";
        doc["former_weight"] = formerValue
        publishTelemetry(topic, doc.as<String>());
        formerValue = reading;
      }
      Serial.print("Weight: ");
      Serial.println(reading, 2);
  } else {
      Serial.println("HX711 not found.");
  }

}
