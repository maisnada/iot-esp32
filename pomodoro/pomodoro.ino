#include <stdbool.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

#define COLUNS 16 
#define LINES 2 
#define ADDRESS  0x27 

#define TOUCH 2
#define BUZZER 3 

LiquidCrystal_I2C lcd(ADDRESS, COLUNS, LINES); 

int lastState = LOW; 

bool start = false;
bool work = false;
bool breakTime = false;
bool longBreakTime = false;

//in seconds
int timeToBreak = 300; //5 minutes
int timeToWork = 1500; //25 minutes
int timeToLongBreak = 600; //10 minutes

int cycle = 1;
int count = 0;

void bip(){
  
  int melody[] = { 660, 660, 0, 660, 0, 510, 660, 0, 770 };

  int duration[] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };

  for (int i = 0; i < 9; i++) {

    if (melody[i] == 0) {

      delay(duration[i]);

    } else {

      tone(BUZZER, melody[i], duration[i]);
      
      delay(duration[i] * 1.30);
      
      noTone(BUZZER);
    }
  }

}

void setup(){

  lcd.init(); 
  lcd.backlight(); 
  lcd.clear(); 

  pinMode(TOUCH, INPUT);
  pinMode(BUZZER, OUTPUT);
}

void printLongBreak(LiquidCrystal_I2C lcd, int cycle, int count){
  
  char buffer[COLUNS]; 

  char bufferAux[COLUNS];
    
  lcd.clear();

  lcd.setCursor(0,0);

  sprintf(bufferAux, "Long Break   >.<", cycle);

  lcd.print(bufferAux);

  lcd.setCursor(0,1);
     
  sprintf(buffer, "%d seconds", count); 

  lcd.print(buffer);
}

void printBreak(LiquidCrystal_I2C lcd, int cycle, int count){

  char buffer[COLUNS]; 

  char bufferAux[COLUNS];
  
  lcd.clear();

  lcd.setCursor(0,0);

  sprintf(bufferAux, "Break         %dC", cycle);

  lcd.print(bufferAux);

  lcd.setCursor(0,1);
     
  sprintf(buffer, "%d seconds", count); 

  lcd.print(buffer);
}

void printWork(LiquidCrystal_I2C lcd, int cycle, int count){
    
  char buffer[COLUNS]; 

  char bufferAux[COLUNS];
  
  lcd.clear();

  lcd.setCursor(0,0);

  sprintf(bufferAux, "Work          %dC", cycle);

  lcd.print(bufferAux);

  lcd.setCursor(0,1);
     
  sprintf(buffer, "%d seconds", count); 
   
  lcd.print(buffer);

}

bool isPressed(int lastState){

  int currentState = digitalRead(TOUCH);

  if(lastState == LOW && currentState == HIGH){

    return true;
  }

  return false;
}

void printPauseTimer(LiquidCrystal_I2C lcd){

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Pomodoro Timer"); 
     
  lcd.setCursor(0,1);
  lcd.print("Pause");      
}

void printStartTimer(LiquidCrystal_I2C lcd){
  
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Pomodoro Timer");
   
  lcd.setCursor(0,1);
  lcd.print("Start!");
}

void printWaitStartTimer(LiquidCrystal_I2C lcd){

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Pomodoro Timer"); 
     
  lcd.setCursor(0,1);
  lcd.print("Wait start >");
}

void menu(bool *start, bool *work, int count, int lastState){
  
  if(isPressed(lastState) && !*start && count == 0){
    
   *start = true;

   *work = true;

   printStartTimer(lcd);
    
   bip();
  
  }else if(isPressed(lastState) && *start){

     *start = false;
   
  }else if(isPressed(lastState) && !*start){

     *start = true; 

  }else if(!*start && count != 0){

     printPauseTimer(lcd);
   
  }else{
  
     printWaitStartTimer(lcd);
  }    
}

void loop(){
 
  lcd.clear();

  menu(&start, &work, count, lastState); 

  if(start){

    if(work){
      
      printWork(lcd, cycle, count);
     
      if(count == timeToWork){
      
        count = 0;
        work = false;
        breakTime = true;

        bip();
      }
    }

    if(breakTime){
   
      if(cycle == 3){

        longBreakTime = true;
   
      }else{

        printBreak(lcd, cycle, count);

        if(count == timeToBreak){

          count = 0;
          cycle++;
          work = true;
          breakTime = false;

          bip();
        }
      }
    }

    if(longBreakTime){

      printLongBreak(lcd, cycle, count);
      
      if(count == timeToLongBreak){

        count = 0;
        cycle = 1;
        work = true;
        breakTime = false;
        longBreakTime = false;

        bip();
      }   
    } 

    count++;
  }
  
  lastState = digitalRead(TOUCH);
  
  delay(1000);
}
