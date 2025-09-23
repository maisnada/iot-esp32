#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

#define colunas 16 
#define linhas 2 
#define endereco  0x27 

LiquidCrystal_I2C lcd(endereco,colunas,linhas); 

int currentState;

int lastState = LOW; 

bool work = false;
bool breakTime = false;
int timeToBreak = 200;
//int timeToWork = 1800;
int timeToWork = 200;
int timeToBreakLong = 600;
int cycle = 0;
int count = 0;

char buffer[17]; 
char bufferAux[17];

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
 
  lcd.clear(); 
  
  currentState = digitalRead(2);

  if(work){
  
    buffer[0] = '\0';
    bufferAux[0] = '\0';
    
    lcd.setCursor(0,0);

    sprintf(bufferAux, "Work | Cycle: %d", cycle);

    lcd.print(bufferAux);

    lcd.setCursor(0,1);
     
    sprintf(buffer, "%d seconds", count); 

    lcd.print(buffer);

    count++;

    delay(200);
    
    if(count > timeToWork){

      count = 0;
      work = false;
      breakTime = true;

      bip();
    }

    return;

  }

  if(breakTime){

    buffer[0] = '\0';
    bufferAux[0] = '\0';
    
    if(cycle == 3){

    }

    lcd.setCursor(0,0);

    sprintf(bufferAux, "Break | Cycle: %d", cycle);

    lcd.print(bufferAux);

    lcd.setCursor(0,1);
     
    sprintf(buffer, "%d seconds", count); 

    lcd.print(buffer);

    count++;

    delay(200);

    if(count > timeToBreak){

      count = 0;
      cycle++;
      work = true;
      breakTime = false;

      bip();
    }

    return;

  }

  if(lastState == LOW && currentState == HIGH){
    
    lcd.print("Work"); 

    work = true;
    
    count = 0;

    cycle++;

    bip();

    }else{

      count++;

      lcd.setCursor(0,0);
      lcd.print("~ Pomodoro Timer"); 
      
      lcd.setCursor(0,1);

      if(count % 2 == 1){
      
        lcd.print("Wait start >");
      
      }else{

        lcd.print("Wait start <");
      } 
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
