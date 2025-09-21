#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

#define colunas 16 
#define linhas 2 
#define endereco  0x27 

LiquidCrystal_I2C lcd(endereco,colunas,linhas); 

int currentState;

int lastState = LOW; 

bool work = false;
int timeToWork = 1800;
int timeToBreak = 300;
int timeToBreakLong = 600;
int cycle = 0;
int count = 0;

char buffer[17]; 

void bip(){

  tone(3, 1200); 
  delay(200);  
  noTone(3);
  delay(150);
  tone(3, 1200); 
  delay(150);  
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
 
  lcd.setCursor(0,0); 
  
  currentState = digitalRead(2);

  if(work){
   
    sprintf(buffer, "Work %d seconds ", count); 

    lcd.print(buffer);

    //lcd.setCursor(0,1); 

    //lcd.print(count); 

    count++;

    delay(1000);

    buffer[0] = '\0';

    return;

  }

  if(lastState == LOW && currentState == HIGH){
    
    lcd.print("Work"); 

    work = true;

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