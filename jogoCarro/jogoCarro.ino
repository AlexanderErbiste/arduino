// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal_I2C.h> //inclui biblioteca lcd


// --- Mapeamento de Hardware ---
#define   buzzer        2     //Buzzer para efeito sonoro no pino digital 2
#define   noise        A0     //Ruído aleatória para função rand
#define   carControl   A1     //Potenciômetro de controle do carro no analógico 1


// --- Constantes Utilizadas ---
#define   maxPoint   1024     //Resolução do conversor AD (movimento máximo para o potenciômetro)
#define   minVelo     100     //Velocidade mínima do trânsito
#define   maxVelo     350     //Velocidade máxima do trânsito


// --- Protótipo das Funções Auxiliares ---

void Road(); //função para gerar a estrada
void positionPot(); //Lê posição atual do potenciômetro



// --- Hardware do LCD ---
#define endereco 0x27
#define colunas 16
#define linhas 2

//instanciando objetos
LiquidCrystal_I2C lcd(endereco,colunas,linhas);

                    
byte glyphs[6][8] = {  //Matriz para exibir carros e caminhões

  { B00000, //Carro acima
    B01110,
    B11111,
    B01010,
    B00000,
    B00000,
    B00000,
    B00000}

  ,{B00000, //Carro abaixo
    B00000,
    B00000,
    B00000,
    B01110,
    B11111,
    B01010,
    B00000}

  ,{B01100, //Caminhão acima
    B11111,
    B11111,
    B11011,
    B00000,
    B00000,
    B00000,
    B00000}

  ,{B00000, //Caminhão abaixo
    B00000,
    B00000,
    B01100,
    B11111,
    B11111,
    B11011,
    B00000}

  ,{B10101, //Colisão acima
    B00100,
    B01110,
    B10101,
    B00000,
    B00000,
    B00000,
    B00000}

  ,{B00000, //Colisão abaixo
    B00000,
    B00000,
    B10101,
    B00100,
    B01110,
    B10101,
    B00000}

};

const char BLANK=32;

char car2glyphs[4][2] = {

  {1,BLANK},{2,BLANK},{BLANK,1},{BLANK,2}

};

char truck2glyphs[4][2] = {

  {3,BLANK},{4,BLANK},{BLANK,3},{BLANK,4}

};

char crash2glyphs[4][2] = {

  {5,BLANK},{6,BLANK},{BLANK,5},{BLANK,6}

};
 


int road[15];                 //Posição dos carros para desvio
char line_buff[2+15];         //Buffer de preenchimento de linha
int road_index;               //Indicador da estrada
int car_pos;                  //Posição do seu carro
const int MAXROADPOS = 3*4;   //Propabilidade de um carro numa coluna
int step_duration;            //Tempo de duração
boolean crash;                //flag de colisão
unsigned int crashtime;       //tempo de colisão



// --- Configurações Iniciais ---
void setup()
{
  lcd.backlight();
  // Inicia variáveis
  crash      = 0x00;
  crashtime  = 0x00;
  road_index = 0x00;
  step_duration = maxVelo;
  line_buff[1+15] = '\0';

//Semente aleatória
  randomSeed(analogRead(noise));

//Gera caracteres especiais (carros)
  for (int i=0; i<6; i++) lcd.createChar(i+1,glyphs[i]);
  
  for (int i=0; i<15; i++) road[i]=-1;
   

  pinMode(buzzer, OUTPUT);  //Saída para controle do buzzer

  analogWrite(buzzer,0);    //inicia desligado


  lcd.begin(16,2);  //Inicializa LCD 16x2

//Chama funções auxiliares 
  positionPot();
  Road();

  lcd.setCursor(1,0); //Posiciona cursor
  lcd.print("Jogo do Trafego");  //Imprime no lcd

  lcd.setCursor(1,1); //Posiciona cursor
  lcd.print(" ETEC "); //Imprime no lcd

  delay(2000); // Aguarda 2 segundos antes de começar o jogo.

} //end setup



// --- Loop Infinito ---
void loop() 
{

  unsigned long now = millis()-2000;   //Tempo atual do contador de programa menos o atraso inicial

  if (!crash) //Houve colisão?
  {           //Não

    positionPot(); //Pega a posição atual do potenciômetro

    crash = (car_pos==road[road_index]);

  } //end if !crash


  if (crash) //Houve colisão?
  {          //Sim

    if (!crashtime) 
    {

      crashtime=now;

      Road();

      lcd.setCursor(2,0); //posiciona cursor

      lcd.print("Houve colisao  "); //imprime no LCD

      lcd.setCursor(2,1); //posiciona cursos

      lcd.print(now/1000); //imprime tempo atual em segundos

      lcd.print(" segundos."); //imprime no LCD

    } //end if !crashtime
    

    if ((now-crashtime) < 250) analogWrite(buzzer,random(255));
     
    else analogWrite(buzzer,0);
   
    delay(20); 

  } 

  else 
  {

    int prev_pos = road[(road_index-1)%15];

    int this_pos = random(MAXROADPOS);

    while (abs(this_pos-prev_pos)<2) 
    { 

      this_pos = random(MAXROADPOS);

    }
    

    road[road_index] = this_pos;

    road_index = (road_index+1)%15;

    Road();

    delay(step_duration); // Delay de 300 milisegundos.
    
    if (step_duration>minVelo) step_duration--;
    

  }


} // end loop



// --- Desenvolvimento das funções auxiliares ---
void positionPot() //Lê posição atual do potenciômetro
{

  car_pos = map(analogRead(carControl),0,1024,0,4);

}


void Road() //Desenha a estrada
{

  for (int i=0; i<2; i++) 
  {

    if(crash) line_buff[0]=crash2glyphs[car_pos][i];

    else line_buff[0]=car2glyphs[car_pos][i];

      
     for (int j=0; j<15; j++) 
     {

        int pos = road[(j+road_index)%15];

        line_buff[j+1]= pos>=0&&pos>4?truck2glyphs[pos][i]:BLANK;

    } //end for aninhado

       lcd.setCursor(0,i);
       lcd.print(line_buff);

  } //end for

} //end Road
