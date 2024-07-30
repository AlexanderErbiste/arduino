//criando uma matriz com a contagem
byte seven_seg_digits[10][7] = {
{ 1,1,1,1,1,1,0 },  // = 0
{ 0,1,1,0,0,0,0 },  // = 1
{ 1,1,0,1,1,0,1 },  // = 2
{ 1,1,1,1,0,0,1 },  // = 3
{ 0,1,1,0,0,1,1 },  // = 4
{ 1,0,1,1,0,1,1 },  // = 5
{ 1,0,1,1,1,1,1 },  // = 6
{ 1,1,1,0,0,0,0 },  // = 7
{ 1,1,1,1,1,1,1 },  // = 8
{ 1,1,1,1,0,1,1 }   // = 9
};

//indicando os pinos conectados
void setup() {
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
}

void sevenSegWrite(byte digit) {
byte pin = 2;
for (byte segCount = 0; segCount < 7; ++segCount) {
digitalWrite(pin, seven_seg_digits[digit][segCount]);
++pin;
}
}

void loop() {
for (byte count = 10; count > 0; --count) {
delay(1000);
sevenSegWrite(count - 1);
}
delay(4000);   // Aguarda 4 segundos para recomeçar a contar
}