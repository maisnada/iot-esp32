#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

#define colunas 16 
#define linhas  2 
#define endereco  0x27 

LiquidCrystal_I2C lcd(endereco,colunas,linhas); 

int currentState;

int lastState = LOW; 

void bip(){

  tone(3, 1200); 
  delay(400);  
  noTone(3);
  delay(100);
  tone(3, 1200); 
  delay(200);  
  noTone(3);
}

void setup() 
{  
  lcd.init(); 
  lcd.backlight(); 
  lcd.clear(); 

  pinMode(2, INPUT);

  pinMode(3, OUTPUT);

}

void loop() 
{
  /*delay(3000);  
  lcd.clear(); */

  lcd.setCursor(0,0); 
  
  currentState = digitalRead(2);

  if(lastState == LOW && currentState == HIGH){
    
    lcd.print("OK"); 

    bip();

    }else{

      lcd.print("NO"); 
    }    

  
  lastState = currentState;

  delay(500);  
  lcd.clear(); 

 
 /*
 for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(300);
  }*/    

}