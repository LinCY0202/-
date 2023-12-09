#include <SoftwareSerial.h>

SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-08 TX to Arduino pin 2 RX.
// Connect the HC-08 RX to Arduino pin 3 TX through a voltage divider.

void setup()
{
  Serial.begin(9600);
  BTserial.begin(9600);
  delay(200);
  Serial.write("AT");
}

void loop()
{
  if (BTserial.available())
  {
    Serial.write(BTserial.read());
  }
  if (Serial.available())
  {
    BTserial.write(Serial.read());
  }
}

//https://www.dmatektw.com/archive/product/item/%E4%B8%AD%E6%96%87/Peripheral-P/BT/BLE4-20160321.pdf
