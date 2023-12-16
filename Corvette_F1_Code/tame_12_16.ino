/*  2023/12/16 test
 *   成功不使用 Servo.h 使四個 SG-90 同時以反翻向旋轉
 * 
 * 
 */

const int servoPin9 = 9;   // 連接到第一個伺服馬達的腳位
const int servoPin10 = 10;  // 連接到第二個伺服馬達的腳位
const int servoPin5 = 5;    // 連接到第三個伺服馬達的腳位
const int servoPin6 = 6;    // 連接到第四個伺服馬達的腳位

unsigned long previousMillis = 0;
const int interval = 20;  // 每個脈衝的時間間隔（20ms）

int pulseWidth1 = 1500;  // 初始脈衝寬度（中位）
int pulseWidth2 = 1500;  // 初始脈衝寬度（中位）
int pulseWidth3 = 1500;  // 初始脈衝寬度（中位）
int pulseWidth4 = 1500;  // 初始脈衝寬度（中位）

void setup() {
  pinMode(servoPin9, OUTPUT);
  pinMode(servoPin10, OUTPUT);
  pinMode(servoPin5, OUTPUT);
  pinMode(servoPin6, OUTPUT);
}

// 旋轉函式
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

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // 更新計時
    previousMillis = currentMillis;

    // 使用旋轉函式
    rotateServos(pulseWidth1, pulseWidth2, pulseWidth3, pulseWidth4);
  }

  // 以下是你的控制邏輯，根據需要修改 pulseWidth1 到 pulseWidth4 的值
  if (currentMillis < 10000) {
    pulseWidth1 = 2000;
    pulseWidth2 = 1000;
    pulseWidth3 = 1000;
    pulseWidth4 = 2000;
  } else {
    pulseWidth1 = 1500;
    pulseWidth2 = 1500;
    pulseWidth3 = 1500;
    pulseWidth4 = 1500;
  }
}
