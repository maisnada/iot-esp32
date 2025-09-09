void setup() {
  
  pinMode(14, INPUT);

  Serial.begin(9600);

}

void loop() {
  
  int leitura = analogRead(14);

  Serial.print("A leitura ADC: ");

  Serial.println(leitura);

  delay(500);

}
