#define TILT 2
#define LED 4
#define BUZZER 3


void setup() {
  Serial.begin(9600);
  pinMode(TILT, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

}

void loop() {
  int TILT_VALUE = digitalRead(TILT);
  if (TILT_VALUE == LOW){
    digitalWrite(LED,HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(1000);
  }
  else {
    digitalWrite(LED,LOW);
    digitalWrite(BUZZER, LOW);
  }

}
