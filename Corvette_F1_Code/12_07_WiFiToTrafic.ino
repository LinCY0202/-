/*  2023/12/7 
 *  請確認SSID 和 PASSWORD 和 LOCALPORT
 *  wifi傳遞、接收資料，使用udp封包。
 *  此處設為Client端，可以接收也可以傳遞資料
 *  
 * 
 * 
 *
 */


#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <FlexiTimer2.h> 

const char *ssid = "Pixel";
const char *password = "12345679";
const unsigned int localPort = 2390;
const char *serverIp = "192.168.120.149"; // 替換成你的伺服器的 IP 地址
const unsigned int serverPort = 2390;

WiFiUDP udp;
static unsigned int num;

//void print_light(int light){
//  
//  if(light<=5){
//    if(light==0){
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      lcd.print("Green");
//      lcd.setCursor(0, 1);
//      lcd.print(num*-1+5);
//      delay(1000);
//    }
//      
//    lcd.setCursor(0, 0);
//    lcd.print("Green");
//    lcd.setCursor(0, 1);
//    lcd.print(num*-1+5);
//  }
//  else if(light>5 && light <=10){
//    if(light==6){
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      lcd.print("Yellow");
//      lcd.setCursor(0, 1);
//      lcd.print(num*-1+10);
//      delay(1000);
//    }
//    
//    lcd.setCursor(0, 0);
//    lcd.print("Yellow");
//    lcd.setCursor(0, 1);
//    lcd.print(num*-1+10);
//  }
//  else{
//    if(light==11){
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      lcd.print("red");
//      lcd.setCursor(0, 1);
//      lcd.print(num*-1+15);
//      delay(1000);
//    }
//    lcd.setCursor(0, 0);
//    lcd.print("red");
//    lcd.setCursor(0, 1);
//    lcd.print(num*-1+15);
//  }
//    
//}
void timer_isr_routine() { // 計時中斷函數
  num++;
  if(num>15)
    num=0;
    
}
void setup() {
  Serial.begin(9600);
  FlexiTimer2::set(1000, timer_isr_routine); // 每1000ms產生中斷，進入中斷服務常式
  FlexiTimer2::start(); // 啟動開始計時
  num=0;
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Setup UDP
  udp.begin(localPort);
}

void loop() {

  
  // Send a UDP packet to the server
  //sendPacket("Hello from client!");
  int pass = num;
  if(pass<=5){
      bool myBool = true;
      sendPacket(reinterpret_cast<uint8_t*>(&myBool), sizeof(myBool));
  }
  else if(pass>5 && pass <=10){
      bool myBool = true;
      sendPacket(reinterpret_cast<uint8_t*>(&myBool), sizeof(myBool));
  }
  else{
      bool myBool = false;
      sendPacket(reinterpret_cast<uint8_t*>(&myBool), sizeof(myBool));
  }


  // Send a boolean
  

  receivePacket();
}

void sendPacket(uint8_t *data, size_t dataSize) {
  // Send a UDP packet to the server
  udp.beginPacket(serverIp, serverPort);
  udp.write(data, dataSize);
  udp.endPacket();
  Serial.println("Packet sent to server");
}

void receivePacket() {
  // Check if there's a UDP packet available
  int packetSize = udp.parsePacket();
  if (packetSize) {
    uint8_t packetBuffer[255];
    // Read the packet into the buffer
    udp.read(packetBuffer, packetSize);

    // Assuming the data is an integer
    if (packetSize == sizeof(int)) {
      int receivedInteger;
      memcpy(&receivedInteger, packetBuffer, sizeof(int));
      Serial.print("Received integer: ");
      Serial.println(receivedInteger);
    }

    // Assuming the data is a boolean
    if (packetSize == sizeof(bool)) {
      bool receivedBool;
      memcpy(&receivedBool, packetBuffer, sizeof(bool));
      Serial.print("Received boolean: ");
      Serial.println(receivedBool ? "true" : "false");
    }
  }
}
