#define ledVermelho 15
#define ledAmarelo 2
#define ledVerde 4
#define tempo 500

void configuracao();
void vermelho();
void amarelo();
void verde();

void setup() {

  configuracao();
}

void loop() {
  
  verde();
  amarelo();
  vermelho();
}

void configuracao(){

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
}

void vermelho(){

  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVerde, LOW);

  delay(tempo);
}

void amarelo(){

  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, HIGH);
  digitalWrite(ledVerde, LOW);

  delay(tempo);
}

void verde(){

  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVerde, HIGH);

  delay(tempo);
}