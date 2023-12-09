/*  2023/12/6 成功樣板
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

const char *ssid = "Pixel";
const char *password = "12345679";
const unsigned int localPort = 2390;
const char *serverIp = "192.168.120.165"; // 替換成你的伺服器的 IP 地址
const unsigned int serverPort = 2390;

WiFiUDP udp;

void setup() {
  Serial.begin(9600);

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
  // Your main code here

  // Send a UDP packet to the server
  //sendPacket("Hello from client!");
  int myInteger = 123;
  sendPacket(reinterpret_cast<uint8_t*>(&myInteger), sizeof(myInteger));

  // Send a boolean
  bool myBool = true;
  sendPacket(reinterpret_cast<uint8_t*>(&myBool), sizeof(myBool));

  // Handle any incoming UDP packets
  receivePacket();
}

//void sendPacket(const char *message) {
//  // Send a UDP packet to the server
//  udp.beginPacket(serverIp, serverPort);
//  udp.write(message);
//  udp.endPacket();
//  Serial.println("Packet sent to server");
//}
void sendPacket(uint8_t *data, size_t dataSize) {
  // Send a UDP packet to the server
  udp.beginPacket(serverIp, serverPort);
  udp.write(data, dataSize);
  udp.endPacket();
  Serial.println("Packet sent to server");
}

//void receivePacket() {
//  // Check if there's a UDP packet available
//  int packetSize = udp.parsePacket();
//  if (packetSize) {
//    char packetBuffer[255];
//    // Read the packet into the buffer
//    udp.read(packetBuffer, packetSize);
//    packetBuffer[packetSize] = 0; // Null-terminate the string
//
//    // Print the received packet
//    Serial.print("Received packet from server: ");
//    Serial.println(packetBuffer);
//  }
//}
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
