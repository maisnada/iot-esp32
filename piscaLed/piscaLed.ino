void setup() {

  pinMode(15, OUTPUT);
}

void loop() {

  digitalWrite(15, HIGH);

  delay(400);

  digitalWrite(15, LOW);

  delay(400);
}