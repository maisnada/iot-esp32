#define btn 12
#define led 13

void setup() {
  
  pinMode(btn, INPUT);
  
  pinMode(led, OUTPUT);

  digitalWrite(led, LOW);

}

void loop() {
  
  if(digitalRead(btn) == LOW){

    digitalWrite(led,HIGH);

  }else{

    digitalWrite(led, LOW);
  }

}
