// Definição dos Pinos
#define pinoatuador     3
#define pinotempo 4
#define Ref      A0

unsigned long ultimaacao = 0;
const unsigned long intervalo = 2500;

int ValorRef;
float E = 0, E1 = 0, E2 = 0, E3 = 0; 
float S1 = 0, S2 = 0, S3 = 0;        
float Y = 0;                         

float num0 = 0.00001476;
float num1 = 0.00004427;
float num2 = 0.00004427;
float num3 = 0.00001476;

float den1 = 2.9350;
float den2 = -2.8749;
float den3 = 0.9398;

void setup() {
  Serial.begin(9600);
  pinMode(Ref, INPUT);
  pinMode(pinoatuador, OUTPUT);
  pinMode(pinotempo, OUTPUT);
}

void Filtro() {
  digitalWrite(pinotempo, HIGH);

  ValorRef = analogRead(Ref);
  E = (double)map(ValorRef, 0, 1023, 0, 255);

  Y = (E * num0 + E1 * num1 + E2 * num2 + E3 * num3) + (S1 * den1 + S2 * den2 + S3 * den3);

  if (Y > 255.0) Y = 255.0;
  if (Y < 0.0)   Y = 0.0;

  analogWrite(pinoatuador, (int)Y);

  S3 = S2;
  S2 = S1;
  S1 = Y;
  
  E3 = E2;
  E2 = E1;
  E1 = E;
  
  digitalWrite(pinotempo, LOW);
}

void loop() {
  unsigned long valoratual = micros();

  if (valoratual - ultimaacao >= intervalo) {
    ultimaacao = valoratual;
    Filtro();
  }
}
