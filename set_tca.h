#define TCA9555_INPUT_PORT_REGISTER_0 0x00  //  read(0-7)
#define TCA9555_INPUT_PORT_REGISTER_1 0x01  //  read(8-15)
byte data_tca1_port0 = 0;
byte data_tca1_port1 = 0;

byte data_tca2_port0 = 0;
byte data_tca2_port1 = 0;
bool port0 = 0;
bool port1 = 1;

byte addr_tca1 = 0x20;
byte addr_tca2 = 0x21;

bool baca_input1(byte addr, bool port);
bool baca_input2(byte addr, bool port);

char dt_pin_tca1[16];
char dt_pin_tca2[16];

void get_input1() {
  byte _retry = 0;
  while (!baca_input1(addr_tca1, port0) && _retry < 10) {
    _retry++;
    Serial.print("retry: ");
    Serial.println(_retry);
    delay(100);
  }
  _retry = 0;
  while (!baca_input1(addr_tca1, port1) && _retry < 10) {
    _retry++;
    Serial.print("retry: ");
    Serial.println(_retry);
    delay(100);
  }

  Serial.print("tca1 port0: ");
  Serial.println(data_tca1_port0, BIN);
  Serial.print("tca1 port1: ");
  Serial.println(data_tca1_port1, BIN);
}

void get_input2() {
  byte _retry = 0;
  while (!baca_input2(addr_tca2, port0) && _retry < 10) {
    _retry++;
    Serial.print("retry: ");
    Serial.println(_retry);
    delay(100);
  }
  _retry = 0;
  while (!baca_input2(addr_tca2, port1) && _retry < 10) {
    _retry++;
    Serial.print("retry: ");
    Serial.println(_retry);
    delay(100);
  }

  Serial.print("tca2 port0: ");
  Serial.println(data_tca2_port0, BIN);
  Serial.print("tca2 port1: ");
  Serial.println(data_tca2_port1, BIN);
}


bool baca_input1(byte addr, bool port) {
  bool flag_tca = 0;
  Wire.beginTransmission(addr);
  switch (port) {
    case 0:
      Wire.write(TCA9555_INPUT_PORT_REGISTER_0);
      break;
    case 1:
      Wire.write(TCA9555_INPUT_PORT_REGISTER_1);
      break;
  }

  int rv = 0;
  rv = Wire.endTransmission();
  Serial.print("rv: ");
  Serial.println(rv);
  if (rv != 0) {
    flag_tca = 0;
  } else {
    Wire.requestFrom(addr, (uint8_t)1);
    switch (port) {
      case 0:
        data_tca1_port0 = Wire.read();
        break;
      case 1:
        data_tca1_port1 = Wire.read();
        break;
    }

    flag_tca = 1;
  }
  return flag_tca;
}

bool baca_input2(byte addr, bool port) {
  bool flag_tca = 0;
  Wire.beginTransmission(addr);
  switch (port) {
    case 0:
      Wire.write(TCA9555_INPUT_PORT_REGISTER_0);
      break;
    case 1:
      Wire.write(TCA9555_INPUT_PORT_REGISTER_1);
      break;
  }

  int rv = 0;
  rv = Wire.endTransmission();
  Serial.print("rv: ");
  Serial.println(rv);
  if (rv != 0) {
    flag_tca = 0;
    Serial.println("gagal baca");
  } else {
    Wire.requestFrom(addr, (uint8_t)1);
    switch (port) {
      case 0:
        data_tca2_port0 = Wire.read();
        break;
      case 1:
        data_tca2_port1 = Wire.read();
        break;
    }

    flag_tca = 1;
  }
  return flag_tca;
}
