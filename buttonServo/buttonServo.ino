#include <Servo.h>

#define pot 0

Servo servo;

int pot_valor;
int servo_valor;

void setup() {
  servo.attach(3);
    
}

void loop() {
  pot_valor=analogRead(pot);
  servo_valor=map(pot_valor,0,1023,0,180);
  servo.write(servo_valor);  
  delay(10);

}

 
