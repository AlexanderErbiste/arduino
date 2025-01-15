#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8

#define BOTAO 6

int numSorteado;

//FUNÇÃO PARA ZERAR O DISPLAY
void clearDisplay(){
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

//FUNÇÃO QUE EXIBE O NÚMERO 0 (ZERO) NO DISPLAY
void showZero(){
  clearDisplay();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
}

//FUNÇÃO QUE EXIBE O NÚMERO 1 NO DISPLAY
void showUm(){
  clearDisplay();
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
}

//FUNÇÃO QUE EXIBE O NÚMERO 2 NO DISPLAY
void showDois(){
  clearDisplay();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(D, HIGH);
}

//FUNÇÃO QUE EXIBE O NÚMERO 3 NO DISPLAY
void showTres(){
  clearDisplay();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(G, HIGH);
}

//FUNÇÃO QUE EXIBE O NÚMERO 4 NO DISPLAY
void showQuatro(){
  clearDisplay();
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(F, HIGH);
}

//FUNÇÃO QUE EXIBE O NÚMERO 5 NO DISPLAY
void showCinco(){
  clearDisplay();
  digitalWrite(A, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
}

//FUNÇÃO QUE EXIBE O NÚMERO 6 NO DISPLAY
void showSeis(){
  clearDisplay();
  digitalWrite(A, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(G, HIGH);
}

//FUNÇÃO QUE EXIBE O NÚMERO 7 NO DISPLAY
void showSete(){
  clearDisplay();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
}

//FUNÇÃO QUE EXIBE O NÚMERO 8 NO DISPLAY
void showOito(){
  clearDisplay();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

//FUNÇÃO QUE EXIBE O NÚMERO 9 NO DISPLAY
void showNove(){
   clearDisplay();
   digitalWrite(G, HIGH);
   digitalWrite(F, HIGH);
   digitalWrite(A, HIGH);
   digitalWrite(B, HIGH);
   digitalWrite(C, HIGH);
}

 //EXIBE UM EFEITO ANTES DE MOSTRAR O NÚMERO SORTEADO
 void efeitoNumerico(){
    for(int i=0; i<=1; i++){
      showZero();
      delay(150);
      showUm();
      delay(150);
      showDois();
      delay(150);
      showTres();
      delay(150);
      showQuatro();
      delay(150);
      showCinco();
      delay(150);
      showSeis();
      delay(150);
      showSete();
      delay(150);
      showOito();
      delay(150);
      showNove();
      delay(150);
    }
 }

void setup(){
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  
  pinMode(BOTAO, INPUT_PULLUP);

  //INICIA A SEQUÊNCIA EM UM PONTO VARIÁVEL
  randomSeed(analogRead(0));
}

void loop(){
  if(digitalRead(BOTAO) == LOW){
    //SORTEIA NÚMERO DE 0 ATÉ 9 E ATRIBUI
    numSorteado = random(0, 10);

    efeitoNumerico();

    switch(numSorteado){
      case 0:
      for(int i=0; i<=3; i++){
        clearDisplay();
        delay(100);
        showZero();
        delay(100);
      }
      break;
      
      case 1:
      for(int i=0; i<=3; i++){
        clearDisplay();
        delay(100);
        showUm();
        delay(100);
      }
      break;
      
      case 2:
      for(int i=0; i<=3; i++){
        clearDisplay();
        delay(100);
        showDois();
        delay(100);  
      }
      break;
      
      case 3:
      for(int i=0; i<=3; i++){
        clearDisplay();
        delay(100);
        showTres();
        delay(100);     
      }
      break;
      
      case 4:
      for(int i=0; i<=3; i++){
        clearDisplay();
        delay(100);
        showQuatro();
        delay(100);
      }
      break;
      
      case 5:
      for(int i=0; i<=3; i++){
        clearDisplay();
        delay(100);
        showCinco();
        delay(100);
      }
      break;
      
      case 6:
      for(int i=0; i<=3; i++){
        clearDisplay();
        delay(100);
        showSeis();
        delay(100);
      }
      break;
      
      case 7:
      for(int i=0; i<=3; i++){
        clearDisplay();
        delay(100);
        showSete();
        delay(100);
      }
      break;
      
      case 8:
      for(int i=0; i<=3; i++){
        clearDisplay();
        delay(100);
        showOito();
        delay(100);
      }
      break;
      
      case 9:
      for(int i=0; i<=3; i++){
        clearDisplay();
        delay(100);
        showNove();
        delay(100);
      }
    }
  }
  delay(100);
}
