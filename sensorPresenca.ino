int pinoLed = 12;       
int pinoSensor = 8;     
int buzzer = 13;        

void setup() {
  pinMode(pinoSensor, INPUT);  
  pinMode(pinoLed, OUTPUT);    
  pinMode(buzzer, OUTPUT);     
  digitalWrite(pinoLed, LOW);  
}

void loop() {
  if (digitalRead(pinoSensor) == LOW) { 
    digitalWrite(pinoLed, HIGH);        
    dispararSirene();                   
  } else {                              
    digitalWrite(pinoLed, LOW);         
    noTone(buzzer);                     
  }
}


void dispararSirene() {
  for (int i = 1000; i <= 2000; i += 10) { // Frequência crescente
    tone(buzzer, i);
    delay(5); // Tempo entre os tons
  }
  for (int i = 2000; i >= 1000; i -= 10) { // Frequência decrescente
    tone(buzzer, i);
    delay(5); // Tempo entre os tons
  }
}
