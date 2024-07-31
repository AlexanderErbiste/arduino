const int ledPinA =  9;
const int ledPinB =  10;
const int ledPinC =  11;
const int ledPinD =  12;
const int ledPinE =  13;

const int buttonPin = 2;

int currentLed = 3;
int currentDelay = 1000;
int points = 0;

int inc = 1;

long lastBlink = millis();

bool playing = true;

void setup() {
  Serial.begin(9600);
  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinC, OUTPUT);
  pinMode(ledPinD, OUTPUT);
  pinMode(ledPinE, OUTPUT);

  pinMode(buttonPin,INPUT_PULLUP);
  attachInterrupt(0, test, RISING);
}

void loop() {
  if(playing){
    onNext(); 
  }
}

void onNext(){
  offAll();
  switch(currentLed) {
    case 1:
      digitalWrite(ledPinA, HIGH);
      break;
    case 2:
      digitalWrite(ledPinB, HIGH);
      break;
    case 3:
      digitalWrite(ledPinC, HIGH);
      break;
    case 4:
      digitalWrite(ledPinD, HIGH);
      break;
    default:
      digitalWrite(ledPinE, HIGH);
      break;
  }
  delay(currentDelay);
  
  if(currentLed >= 5){
    inc = -1;
  } else if (currentLed <= 1) {
    inc = 1;
  }
  currentLed += inc;
}

void offAll(){
  digitalWrite(ledPinA, LOW);
  digitalWrite(ledPinB, LOW);
  digitalWrite(ledPinC, LOW);
  digitalWrite(ledPinD, LOW);
  digitalWrite(ledPinE, LOW);
}

void onAll(){
  digitalWrite(ledPinA, HIGH);
  digitalWrite(ledPinB, HIGH);
  digitalWrite(ledPinC, HIGH);
  digitalWrite(ledPinD, HIGH);
  digitalWrite(ledPinE, HIGH);
}

void test() {
  if ( millis() - lastBlink > 1000) {
    lastBlink = millis();
    if(currentLed == 3) {
      hit();
    } else {
      miss();
    }
  }
}

void hit() {
  playing = false;
  delay(3000);
  splash();
  delay(1000);
  currentDelay = currentDelay * 0.95;
  points++;
  playing = true;
  Serial.print(points);
  Serial.println(" points");
}

void miss() {
  playing = false;
  wrong();
  currentLed = 2;
  inc = 1;
  currentDelay = 1000;
  points = 0;
  playing = true;
  Serial.println("=============");
  Serial.println("  YOU LOSE!  ");
  Serial.println("=============");
}

void splash() {
  offAll();
  digitalWrite(ledPinC, HIGH);
  delay(10000);
  digitalWrite(ledPinB, HIGH);
  digitalWrite(ledPinD, HIGH);
  delay(10000);
  digitalWrite(ledPinA, HIGH);
  digitalWrite(ledPinE, HIGH);
  delay(10000);
  digitalWrite(ledPinA, LOW);
  digitalWrite(ledPinE, LOW);
  delay(10000);
  digitalWrite(ledPinB, LOW);
  digitalWrite(ledPinD, LOW);
  delay(10000);
  digitalWrite(ledPinC, HIGH);
}

void wrong() {
  onAll();
  delay(30000);
  offAll();
  delay(20000);
  onAll();  
  delay(20000);
  offAll();
  delay(10000);
  onAll();  
  delay(10000);
  offAll();
}
