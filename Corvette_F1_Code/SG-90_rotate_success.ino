/*  2023/12/10
 *   成功不使用Servo.h 使兩個SG-90同時以反翻向旋轉
 * 
 * 
 */

const int servoPin = 9; // 連接到第一個伺服馬達的腳位
const int servoPin2 = 7; // 連接到第二個伺服馬達的腳位

unsigned long previousMillis = 0;
const int interval = 20; // 每個脈衝的時間間隔（20ms）

int pulseWidth1 = 1500; // 初始脈衝寬度（中位）
int pulseWidth2 = 1500; // 初始脈衝寬度（中位）

void setup() {
  pinMode(servoPin, OUTPUT);
  pinMode(servoPin2, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // 更新計時
    previousMillis = currentMillis;

    // 控制第一個伺服馬達
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulseWidth1);
    digitalWrite(servoPin, LOW);

    // 控制第二個伺服馬達
    digitalWrite(servoPin2, HIGH);
    delayMicroseconds(pulseWidth2);
    digitalWrite(servoPin2, LOW);
  }

  // 以下是你的控制邏輯，根據需要修改 pulseWidth1 和 pulseWidth2 的值
  if (currentMillis < 500000000) {
    pulseWidth1 = 1000;
    pulseWidth2 = 2000;
  } else {
    pulseWidth1 = 1500;
    pulseWidth2 = 1500;
  }
}
