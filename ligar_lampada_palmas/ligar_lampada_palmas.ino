#define sensor 2
#define rele 3

int palmas = 0;
boolean temPalmas = true;
boolean contaPalma = true;
unsigned long tempo = 0;

void setup() {
  pinMode(sensor, INPUT);
  pinMode(rele, OUTPUT);
  
  digitalWrite(rele, HIGH);
}

void loop() {
 temPalmas = digitalRead(sensor);
 
 if(!temPalmas){
  if(contaPalma){
    palmas++;
    tempo = millis();
    contaPalma = false;
  }
  else{
    if(millis() - tempo > 200){
      contaPalma = true;
    }
  }
 }

 if(millis() - tempo > 400){
  switch(palmas){
    case 1:
    digitalWrite(rele, HIGH);
    break;

    case 2:
    digitalWrite(rele, LOW);
    break;
  }
  palmas = 0;
 }
}
