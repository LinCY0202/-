/*   此藍芽模組可能不是HC-08，有可能是BT-05，詳細請參照下面文件指令 
 *   2023/12/6 
 *   若另一端以進入AT模式，此端則可忽略下方。並稱此端為Slave端
 *   請嘗試進入AT模式，並參照https://www.dmatektw.com/archive/product/item/%E4%B8%AD%E6%96%87/Peripheral-P/BT/BLE4-20160321.pdf指令
 *   來連接另一快藍芽模組，資料傳遞使用ASCII碼
 *    
 *   進入AT模式的可能方法，確保藍芽沒有連接到其他裝置。輸入AT OR 'AT'，如不行請重置板子，長按10秒以上
 *   
 * 
 */
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
int data=1;
void loop()
{
  

  if (BTserial.available())//收到藍芽訊號
  {
    auto a=BTserial.read();
    Serial.write(BTserial.read());
    
    Serial.println("->");
    Serial.println(a);
    if(a==49){
      BTserial.print(data);
      Serial.write("OK");
    }
      
  }
  if (Serial.available())//Serial傳遞出去
  {
    BTserial.write(Serial.read());
  }
}

//https://www.dmatektw.com/archive/product/item/%E4%B8%AD%E6%96%87/Peripheral-P/BT/BLE4-20160321.pdf
