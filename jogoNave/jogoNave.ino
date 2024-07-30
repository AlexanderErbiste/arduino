#include <LiquidCrystal_I2C.h>

//Definindo LCD
#define endereco 0x27
#define colunas 16
#define linhas 2
//Definindo os botões do jogo
#define btcima 8
#define btbaixo 9
#define bttiro 10

LiquidCrystal_I2C lcd(endereco,colunas,linhas); 
//Criação de variaveis 
double vel = 300.0;
int pxnave, pynave, pxcometa, pycometa, pxenergia,
pyenergia, pxtiro, pytiro;
bool game, vtiro, bateria;
int pontuacao, tela, fase;
double energia;
//Criando o desenho dos objetos
byte nave[8] = {B11000,B01100,B01110,B01111,B01111,B01110,B11000};
byte cometa[8] = {B00000,B00100,B01110,B10111,B11101,B01110,B00100,B00000};
byte explosao [8] = {B10001,B10101,B01010,B10100,B00101,B01010,B10101,B10001};
byte energy [8] = {B01110,B11011,B10001,B10101,B10101,B10101,B10001,B11111};
byte bala [8] = {B00000,B00000,B00000,B00111,B00111,B00000,B00000,B00000};


void setup() {
  lcd.init();//Inicia a comunicação
  lcd.backlight();//Liga a iluminação
  lcd.clear();// Limpa o Display

  //Inicializando as variaveis
  pxnave = pynave = pycometa = pxenergia = pyenergia = pytiro = 0;
  pxtiro = -1;
  pxcometa = 12;
  energia = 100;
  tela = 0;
  fase = 1;
  //Alocando o desenho dos objetos na memoria
  lcd.createChar(1,nave);
  lcd.createChar(2,cometa);
  lcd.createChar(3,explosao);
  lcd.createChar(4,energy);
  lcd.createChar(5,bala);
  lcd.begin(16,2);
  lcd.clear();
  game = false;

  vtiro, bateria = false;

}

void loop() {
  if(game){
    energia -= 0.25;
    lcd.clear();
    if(energia <= 0){
      tela = 2;
      game = false;
    }
    painel(13);
    if(digitalRead(btcima)==1){
      pynave=0;
    }
    if(digitalRead(btbaixo)==1){
      pynave=1;
    }
    if(digitalRead(bttiro)==1){
      pxtiro=1;
      vtiro = true;
      pytiro = pynave;
    }
    pxcometa -= 1;
    criaDesenho(pxnave, pynave, 1);
    criaDesenho(pxcometa, pycometa, 2); 
    if(vtiro){
      criaDesenho(pxtiro, pytiro, 5);
      pxtiro += 1;
    }
    if (pxcometa <0){
      pxcometa = 12;
      pycometa = random(0,2);
    }
    if (pxtiro > 16){
      vtiro = false;
      pxtiro = -1;
    }
    if (((pxtiro == pxcometa + 1) && (pytiro == pycometa)) || ((pxtiro == pxcometa) && (pytiro == pycometa))){
      vtiro = false;
      pxtiro = -1;
      criaExplosaoC(pxcometa, pycometa);
      pycometa = random(0,2);
      pxcometa = 12;
      pontuacao += (2 * fase);
      if (pontuacao >= (20*fase)){
        fase += 1;
        vel = 150.0/fase;
      }
    }
    if((pxnave == pxcometa) && (pynave == pycometa)){
      game = false;
      criaExplosaoN (pxnave, pynave);
      tela = 2;
    }
    if (!bateria){
      if(random (0,50)>40){
        pxenergia = 12;
        bateria = true;
        pyenergia = random (0,2);
      }
    } else {
      criaDesenho (pxenergia, pyenergia, 4);
      pxenergia -= 1;
      if (((pxnave == pxenergia + 1) && (pynave == pyenergia)) || ((pxnave == pxenergia) && (pynave == pyenergia))){
        bateria = false;
        pxenergia = -1;
        energia = 100;
      }
    }
    delay(vel);
  } else{
    verificaJogo(tela);
    if(digitalRead(bttiro)==1){
      reset();
    }
  }

}

//Função para criar os objetos do game
void criaDesenho (int px, int py, int desenho){
  lcd.setCursor(px,py);
  lcd.write(desenho);
}
//Função para animação de nave destruida
void criaExplosaoN (int px, int py){
  lcd.clear();
  lcd.setCursor(px,py);
  lcd.write(3);
  delay(1000);
  lcd.clear();
}
//Função para animação de cometa destruido
void criaExplosaoC (int px, int py){
  
  lcd.setCursor(px,py);
  lcd.write(3);
  delay(500);
  
}
//Função para reiniciar o jogo
void reset(){
  pontuacao = 0;
  energia = 100;
  game = true;
  tela = 0;
}
//Função para a interface do jogo
void painel (int px){
  lcd.setCursor(px,0);
  lcd.print(pontuacao);
  lcd.setCursor(px,1);
  lcd.print(energia);
}
/* Função que verifica o estado atual do jogo 
0= TelaInicial 1= Ganhou 2= Perdeu */
void verificaJogo (int cond){
  if (cond<1){
    lcd.setCursor(3,0);
    lcd.print("ETEC GAME");
    lcd.setCursor(0,1);
    lcd.print("Pressione tiro");
  } else {
      String txt = {cond>1 ? "Perdeu" : "Ganhou"};
      lcd.setCursor(9,0);
      lcd.print("pts:");
      lcd.setCursor(13,0);
      lcd.print(pontuacao);
      lcd.setCursor(1,0);
      lcd.print(txt);
      lcd.setCursor(0,1);
      lcd.print("Pressione tiro");
  }

}