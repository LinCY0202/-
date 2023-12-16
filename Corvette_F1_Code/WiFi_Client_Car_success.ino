//2023/12/16 測距、wifi、馬達

#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "Pixel";
const char *password = "12345679";
const unsigned int localPort = 2390;
const char *serverIp = "192.168.137.157"; // 替換成你的伺服器的 IP 地址
const unsigned int serverPort = 2390;
int Speed=10;
WiFiUDP udp;

const int servoPin9 = 9;
const int servoPin10 = 10;
const int servoPin5 = 5;
const int servoPin6 = 6;

unsigned long previousMillis = 0;
const int interval = 20;

int pulseWidth1 = 1500;
int pulseWidth2 = 1500;
int pulseWidth3 = 1500;
int pulseWidth4 = 1500;

int trigPin = 12;    // 超音波感測器 Trig腳接 Arduino pin 11
int echoPin = 13;    // 超音波感測器 Echo 腳接 Arduino pin 12

long duration, cm ;  // 宣告計算距離時，需要用到的兩個實數

void setup() {
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("連接到WiFi中...");
  }
  Serial.println("已連接到WiFi");

  // 設置UDP
  udp.begin(localPort);

  // 設置伺服馬達腳位
  pinMode(servoPin9, OUTPUT);
  pinMode(servoPin10, OUTPUT);
  pinMode(servoPin5, OUTPUT);
  pinMode(servoPin6, OUTPUT);

  // 設置超音波感測器腳位
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    // 更新計時
    previousMillis = currentMillis;

    // 旋轉伺服馬達
    rotateServos(pulseWidth1, pulseWidth2, pulseWidth3, pulseWidth4);
  }

  // 處理接收到的UDP封包
  receivePacket();

  // 控制伺服馬達脈衝寬度的邏輯
  if (currentMillis < 10000) {
    pulseWidth1 = 500;
    pulseWidth2 = 2500;
    pulseWidth3 = 500;
    pulseWidth4 = 2500;
  } else {
    pulseWidth1 = 1500;
    pulseWidth2 = 1500;
    pulseWidth3 = 1500;
    pulseWidth4 = 1500;
  }

  // 顯示超音波距離
  measureDistance();
}

void rotateServos(int pulse1, int pulse2, int pulse3, int pulse4) {
  // 控制第一個伺服馬達
  digitalWrite(servoPin9, HIGH);
  delayMicroseconds(pulse1);
  digitalWrite(servoPin9, LOW);

  // 控制第二個伺服馬達
  digitalWrite(servoPin10, HIGH);
  delayMicroseconds(pulse2);
  digitalWrite(servoPin10, LOW);

  // 控制第三個伺服馬達
  digitalWrite(servoPin5, HIGH);
  delayMicroseconds(pulse3);
  digitalWrite(servoPin5, LOW);

  // 控制第四個伺服馬達
  digitalWrite(servoPin6, HIGH);
  delayMicroseconds(pulse4);
  digitalWrite(servoPin6, LOW);
}

void receivePacket() {
  // 檢查是否有可用的UDP封包
  int packetSize = udp.parsePacket();
  if (packetSize) {
    uint8_t packetBuffer[255];
    // 讀取封包到緩衝區
    udp.read(packetBuffer, packetSize);

    // 假設數據是一個整數
    if (packetSize == sizeof(int)) {
      int receivedInteger;
      memcpy(&receivedInteger, packetBuffer, sizeof(int));
      Serial.print("接收到整數: ");
      Serial.println(receivedInteger);
    }

    // 假設數據是一個布爾值
    if (packetSize == sizeof(bool)) {
      bool receivedBool;
      memcpy(&receivedBool, packetBuffer, sizeof(bool));
      Serial.print("接收到布爾值: ");
      Serial.println(receivedBool ? "true" : "false");
    }
  }
}

void sendPacket(uint8_t *data, size_t dataSize) {
  // 向伺服器發送UDP封包
  udp.beginPacket(serverIp, serverPort);
  udp.write(data, dataSize);
  udp.endPacket();
  Serial.println("封包發送到伺服器");
}

void measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2) / 29.1;
  if(cm>100)
    sendPacket(reinterpret_cast<uint8_t*>(&Speed), sizeof(Speed));
  Serial.print("超音波距離: ");
  Serial.print(cm);
  Serial.println(" 公分");
}
