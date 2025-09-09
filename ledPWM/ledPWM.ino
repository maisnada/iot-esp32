#define led 16

// setting PWM properties
const int freq = 5000;
const int resolution = 8;
 
void setup(){
  // configure LED PWM
  ledcAttach(led, freq, resolution);
}
 
void loop(){
  
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
  
    ledcWrite(led, dutyCycle);
    
    delay(10);
  }
  
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    
    ledcWrite(led, dutyCycle);   
    
    delay(10);
  }
}