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
int timeToBreak = 50;
//int timeToWork = 1800;
int timeToWork = 50;
int timeToLongBreak = 50;
int cycle = 0;
int count = 0;

char buffer[17]; 
char bufferAux[17];

void bip(){

  /*tone(3, 1200); 
  delay(150);

  noTone(3);
  delay(20);

  tone(3, 1200); 
  delay(100);
  
  noTone(3);
  delay(20);

  tone(3, 1200);
  delay(50);

  noTone(3);*/
  
  int melody[] = { 660, 660, 0, 660, 0, 510, 660, 0, 770 };
  int duration[] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };

  for (int i = 0; i < 9; i++) {
      if (melody[i] == 0) {
         delay(duration[i]);
      } else {
         tone(3, melody[i], duration[i]);
         delay(duration[i] * 1.30);
         noTone(3);
      }
  }
  delay(2000);

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

    sprintf(bufferAux, "Work          %dC", cycle);

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

      lcd.setCursor(0,0);

      sprintf(bufferAux, "Long Break   >.<", cycle);

      lcd.print(bufferAux);

      lcd.setCursor(0,1);
     
      sprintf(buffer, "%d seconds", count); 

      lcd.print(buffer);

      count++;

      delay(200);

      if(count > timeToLongBreak){

        count = 0;
        cycle = 1;
        work = true;
        breakTime = false;

        bip();
      }

      return;
    }

    lcd.setCursor(0,0);

    sprintf(bufferAux, "Break         %dC", cycle);

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
    
    lcd.setCursor(0,0);
    lcd.print("Pomodoro Timer");
    
    lcd.setCursor(0,1);
    lcd.print("Start!");
    
    work = true;
    
    count = 0;

    cycle++;

    bip();

    }else{

      count++;

      lcd.setCursor(0,0);
      lcd.print("Pomodoro Timer"); 
      
      lcd.setCursor(0,1);

      if(count % 2 == 1){
      
        lcd.print("Wait start >");
      
      }else{

        lcd.print("Wait start <");
      }
    }    
  
  lastState = currentState;

  delay(200);
 
 /*
 for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(300);
  }*/    

}
