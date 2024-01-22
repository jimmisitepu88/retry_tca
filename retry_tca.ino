


#include <ArduinoJson.h>

#include <Wire.h>
#include "TCA9555.h"
TCA9555 TCA1(0x20);
TCA9555 TCA2(0x21);
byte pin_tca[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

unsigned long cur_time, old_time;

#include "set_tca.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.setClock(10000);
  Wire.begin();
  TCA1.begin();
  TCA2.begin();
  for (int i = 0; i < sizeof(pin_tca); i++) {
    Serial.print(i);
    Serial.print(",");
    TCA1.pinMode1(pin_tca[i], INPUT);
    TCA2.pinMode1(pin_tca[i], INPUT);
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

  get_input1();
  get_input2();
  String str_tca1 = String(data_tca1_port1, BIN) + String(data_tca1_port0, BIN);
  String str_tca2 = String(data_tca2_port1, BIN) + String(data_tca2_port0, BIN);
  str_tca1.toCharArray(dt_pin_tca1, str_tca1.length() + 1);
  str_tca1.toCharArray(dt_pin_tca2, str_tca2.length() + 1);
  for (int i = 0; i < 12; i++) {
    root[String(i + 1)] = String(dt_pin_tca1[i]);
  }

  for (int i = 0; i < 12; i++) {
    root[String(i + 13)] = String(dt_pin_tca2[i]);
  }

  serializeJson(root, jsonData);
  Serial.print("json: ");
  Serial.println(jsonData);
  root.clear();
  return jsonData;
}
