/*  2023/12/7
 *  紅綠燈系統
 *  外接LCD螢幕顯示，使用中斷函示庫
 *  顯示部分的delay()可能需要再討論。以及是否要外接LED燈
 * 
 * 
 */

#include <FlexiTimer2.h> // 引入計時中斷函式庫
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

static unsigned int num;

void print_light(int light){
  
  if(light<=5){
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
  
  FlexiTimer2::set(1000, timer_isr_routine); // 每1000ms產生中斷，進入中斷服務常式
  FlexiTimer2::start(); // 啟動開始計時
  lcd.begin(16, 2);
  //lcd.print("Timer");
  num = 0;
}

void loop() { // 主程式無作用，或執行其它程式
  
  print_light(num);

}
