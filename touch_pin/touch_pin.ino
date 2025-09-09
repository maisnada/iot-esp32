#define touchPin 27
#define ledPin 16
#define limite 20

int touchValue;

void setup() {
  
  Serial.begin(9600);
  
  delay(1000);

  pinMode(ledPin, OUTPUT);

}

void loop() {
  
  for(int i = 0; i < 100; i++){

    touchValue += touchRead(touchPin);
  }

  touchValue /= 100;

  Serial.print(touchValue);

  if(touchValue < limite){

    digitalWrite(ledPin, HIGH);

    Serial.println(" - led acesso");
  
  }else{

    digitalWrite(ledPin, LOW);
    
    Serial.println(" - led apagado");
  }

  delay(500);

}
