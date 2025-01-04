#define sensor A0
#define buzzer 2
#define led1 3
#define led2 4

void setup() 
{
  Serial.begin(9600);

  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() 
{
  int valor = analogRead(sensor);
  Serial.println(valor);

  if(valor > 400)
  {
    alarme();
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    delay(100);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }
  else
  {
    noTone(buzzer);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
  delay(100);
}

void alarme()
{
  tone(buzzer, 1000);
  delay(50);
  noTone(buzzer);
}