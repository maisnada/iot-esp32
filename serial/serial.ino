#define led 16

char acionaLed = 0;

void setup() {
  
  Serial.begin(9600);

  pinMode(led, OUTPUT);

}

void loop() {
  
  if(Serial.available() > 0){

    acionaLed = Serial.read();
  }

  if(acionaLed == 'l'){

    digitalWrite(led, HIGH);

    Serial.print(acionaLed);

    Serial.println(" LED ON");
  }


  if(acionaLed == 'd'){

    digitalWrite(led, LOW);

    Serial.print(acionaLed);

    Serial.println(" LED OFF");
  }

}
