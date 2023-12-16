/*  
    2023/12/16   結合wifi 紅綠燈

 */


#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <FlexiTimer2.h> // 引入計時中斷函式庫
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int ledPin0 = 10; //R
int ledPin1 = 2;  //G
int ledPin2 = 11; //Y
 
static unsigned int num;

int status = WL_IDLE_STATUS;
const char *ssid = "Pixel";
const char *password = "12345679";    // your network password (use for WPA, or use as key for WEP)

unsigned int localPort = 2390;      // local port to listen on

//char packetBuffer[255]; //buffer to hold incoming packet
//char  ReplyBuffer[] = "acknowledged";       // a string to send back

WiFiUDP Udp;
void print_light(int light){

  if(light<=5){
    digitalWrite(ledPin1, HIGH); 
    if(light==0){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Green");
      lcd.setCursor(0, 1);
      lcd.print(num*-1+5);
      delay(1000);
    }
      
    lcd.setCursor(0, 0);
    lcd.print("Green");
    lcd.setCursor(0, 1);
    lcd.print(num*-1+5);
  }
  else if(light>5 && light <=10){
    digitalWrite(ledPin2, HIGH); 
    if(light==6){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Yellow");
      lcd.setCursor(0, 1);
      lcd.print(num*-1+10);
      delay(1000);
    }
    
    lcd.setCursor(0, 0);
    lcd.print("Yellow");
    lcd.setCursor(0, 1);
    lcd.print(num*-1+10);
  }
  else{
    digitalWrite(ledPin0, HIGH); 
    if(light==11){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("red");
      lcd.setCursor(0, 1);
      lcd.print(num*-1+15);
      delay(1000);
    }
    lcd.setCursor(0, 0);
    lcd.print("red");
    lcd.setCursor(0, 1);
    lcd.print(num*-1+15);
  }
    
}
void timer_isr_routine() { // 計時中斷函數
  num++;
  if(num>15)
    num=0;
    
}

void setup() {
  //Initialize serial and wait for port to open:
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  FlexiTimer2::set(1000, timer_isr_routine); // 每1000ms產生中斷，進入中斷服務常式
  FlexiTimer2::start(); // 啟動開始計時
  lcd.begin(16, 2);
  //lcd.print("Timer");
  num = 0;
  Serial.begin(9600);

  WiFi.begin(ssid, password);                   //網路連接
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(localPort);
}

void loop() {
      digitalWrite(ledPin0, LOW); 
      digitalWrite(ledPin1, LOW); 
      digitalWrite(ledPin2, LOW); 
  print_light(num);
  
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    uint8_t packetBuffer[255];
    // Read the packet into the buffer
    Udp.read(packetBuffer, packetSize);

    // Assuming the data is an integer
    if (packetSize == sizeof(int)) {
      int receivedInteger;
      memcpy(&receivedInteger, packetBuffer, sizeof(int));
      Serial.print("Received integer: ");
      Serial.println(receivedInteger);
      // Add your logic for handling the received integer here
    }

    // Assuming the data is a boolean
    if (packetSize == sizeof(bool)) {
      bool receivedBool;
      memcpy(&receivedBool, packetBuffer, sizeof(bool));
      Serial.print("Received boolean: ");
      Serial.println(receivedBool ? "true" : "false");
      // Add your logic for handling the received boolean here
    }
  }


}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
