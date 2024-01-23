


#include <ArduinoJson.h>

#include <Wire.h>
#include "TCA9555.h"
TCA9555 TCA1(0x20);
TCA9555 TCA2(0x21);



unsigned long cur_time, old_time;

#include "set_tca.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.setClock(10000);
  Wire.begin();
  TCA1.begin();
  TCA2.begin();
  for (int i = 0; i < sizeof(pin_tca1); i++) {
    Serial.print(i);
    Serial.print(",");
    TCA1.pinMode1(pin_tca1[i], INPUT);
  }
  for (int i = 0; i < sizeof(pin_tca2); i++) {
    Serial.print(i);
    Serial.print(",");
    TCA1.pinMode1(pin_tca2[i], INPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  cur_time = millis();
  if (cur_time - old_time > 100) {
    genereteJsonData();
    old_time = millis();
  }
}

String genereteJsonData() {
  String jsonData;
  DynamicJsonDocument doc(512);
  JsonObject root = doc.to<JsonObject>();

  get_input1();  // di panggil utk baca tca1
  get_input2();  // di panggil utk baca tca2

  for (int i = 0; i < sizeof(pin_tca1); i++) {
    root[String(i + 1)] = TCA1.read1(pin_tca1[i]);
  }
  for (int i = 0; i < sizeof(pin_tca2); i++) {
    root[String(i + 13)] = TCA2.read1(pin_tca2[i]);
  }

  serializeJson(root, jsonData);
  Serial.print("json: ");
  Serial.println(jsonData);
  root.clear();
  return jsonData;
}
