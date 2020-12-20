//Programa para controle de um robô seguidor de linha baseado no SoC ESP32

#include <QTRSensors.h>

//MACRO AUXILIAR
#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)
#define RAN(a,b,c) (MAX(MIN(a,c),b))
#define ABS(a) (a < 0 ? -a : a)
//----------------------------------
//SENSORES
#define EDGEVAL 800
#define NUMSENSORS 4
#define BLACKL 0
#define WHITEL 1
#define MID ((NUMSENSORS - 1)*500)
#define TIMEOUT 1000

unsigned char midsensor[NUMSENSORS] = { 18, 32, 33, 25 };
unsigned char edgesensor[2] = {19, 21};

unsigned int sensors[NUMSENSORS], sensors_c[NUMSENSORS], sensors_e[2];
unsigned int r_min[NUMSENSORS];
unsigned int r_max[NUMSENSORS];
unsigned int e_min[2];
unsigned int e_max[2];
//-----------------------------------
//MOTORES
#define PWMA 13
#define AIN2 12
#define AIN1 14

#define PWMB 2
#define BIN2 15
#define BIN1 4

#define MA_PWMCHANNEL 0
#define MB_PWMCHANNEL 1

#define FREQ 5000
#define RESOLUTION  8

void followLine(int velocidadeA, int velocidadeB, bool sa = HIGH, bool sb = HIGH);

//SETUP---------------------------
void setup() {

  Serial.begin(115200);

  //MOTOR SETUP 
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  ledcSetup(MA_PWMCHANNEL, FREQ, RESOLUTION);
  ledcAttachPin(PWMA, MA_PWMCHANNEL);
  ledcSetup(MB_PWMCHANNEL, FREQ, RESOLUTION);
  ledcAttachPin(PWMB, MB_PWMCHANNEL);
  //-------------------------

  for(unsigned char k = 0; k < NUMSENSORS; k++){
    r_max[k] = 0;
    r_min[k] = 9999;
  }

  for(unsigned char y = 0; y < 2; y++){
    e_max[y] = 0;
    e_min[y] = 9999;
  }
  
  //CALIBRAÇÃO SENSORES
  Serial.println("CALIBRANDO");
  for (int i = 0; i < 250; i++){
    
    edgeRead();
    for(unsigned char x = 0; x < 2; x++){
      e_min[x] = MIN( e_min[x], sensors_e[x]);
      e_max[x] = MAX( e_max[x], sensors_e[x]);
    }
    midRead();
    for(int j = 0; j < NUMSENSORS; j++){
      r_min[j] = MIN( r_min[j], sensors[j]);
      r_max[j] = MAX( r_max[j], sensors[j]);
    }
    delay(20);
  }
  Serial.println("CALIBRADO");
  //--------------------------
}
unsigned char lapsMod[35] = {1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
void setupLap(){
  
}

bool fim = false;
//INICIA OS MOTORES
void followLine(int velocidadeA, int velocidadeB, bool sa, bool sb){
  if(fim) return;
  velocidadeA = RAN(velocidadeA, 0, 255);
  velocidadeB = RAN(velocidadeB, 0, 255);
  ledcWrite(MA_PWMCHANNEL, velocidadeA);
  digitalWrite(AIN2, sa);
  digitalWrite(AIN1, !sa);
  ledcWrite(MB_PWMCHANNEL, velocidadeB);
  digitalWrite(BIN2, sb);
  digitalWrite(BIN1, !sb);
}

//VARIAVES E CONSTANTES SEGUIDOR DE LINHA
#define VTURN 90
#define KP 0.1
#define KD 1.5
#define KI 0
#define KRD 0
double ajust = 0, sum, rd;
long pos = 0;
double error[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte sensorsInLine;
char borda = 0;
int lap = 0;

int vmax = 160, vmin = 130;
//---------------------

//-----------LOOP---------------
void loop() {
  static long setuptime = millis();

  edgeCalibrate();
  
  posLine(WHITEL);

  addToVec(pos - MID);

  if(bordaEsquerda()){
    lap++;
    Serial.println(lap);
    switch(lapsMod[lap]){
      case 0:
      vmax = 100;
      vmin = 100;
      break;
      case 1:
      vmax = 160;
      vmin = 160;
      break;
    }
    
  }
  
  if((bordaDireita() && millis() > 10000) || ( millis() - setuptime > 40000)){
    followLine(0, 0);
    fim = true;
  }
  
  if(false){
    if (ajust > 0)followLine(VTURN, VTURN, true, false);
    else followLine(VTURN, VTURN, false, true);
  }else{
    
    sum = 0;
    for (int i = 0; i < 10; i++) sum += error[i];
    ajust = KP*error[0] + KD*(error[0] - error[1]) + KI*sum;
    rd = KRD * ABS(error[0]);

    if (ajust > 0)followLine(MAX(vmax - rd, vmin), vmax - ajust - rd);
    else followLine(vmax + ajust - rd, MAX(vmax - rd, vmin));
  }
  
 
}

void addToVec(double err){
  for(int i = 8; i >= 0; i--)error[i + 1] = error[i];
  error[0] = err;
}

void posLine(byte line){
  midRead();
  
  double w, v, sum = 0, division = 0;
  sensorsInLine = 0;
  
  for(int j = 0; j < NUMSENSORS; j++){
    w = RAN(sensors[j], r_min[j], r_max[j]);
    w -= r_min[j];
    w /= (r_max[j] - r_min[j]);
    if (line) w = 1 - w;
    if (w > 0.8) sensorsInLine ++;
    sum += 1000*j*w;
    division += w;
  }

  if (!sensorsInLine){
    if(pos > MID){
      pos = 2*MID;
    }else{
      pos = 0;
    }
  }else{
    pos = sum/division;
  }
  
}

void edgeCalibrate(){
  edgeRead();
  double w;
  for(int j = 0; j < 2; j++){
    w = RAN(sensors_e[j], e_min[j], e_max[j]);
    w -= e_min[j];
    w /= (e_max[j] - e_min[j]);
    w *= 1000;
    sensors_e[j] = w;
  }
}

bool bordaDireita(){
  static bool senDir = false;
  static long t1, elapsed;
  
  if (!senDir && sensors_e[0] < 850 && ABS(error[0]) < 400 ){
    senDir = true;
    t1 = millis();
  }

  if(senDir){
    if(sensors_e[1] < 700 || sensorsInLine >= 3) {
      senDir = false;
      return false;
    }
    elapsed = millis() - t1;
    if(elapsed > 50 && sensors_e[0] > 700){
      senDir = false;
      return true;
    }
  }
  return false;
}

bool bordaEsquerda(){
  static bool senDir = false;
  static long t1, elapsed;

  
  if (!senDir && sensors_e[1] < 800 && ABS(error[0]) < 500 ){
    senDir = true;
    t1 = millis();
  }

  if(senDir){
    if(sensors_e[0] < 800 || sensorsInLine >= 3) {
      senDir = false;
      return false;
    }
    elapsed = millis() - t1;
    if(elapsed > 50 && sensors_e[1] > 800){
      senDir = false;
      return true;
    }
  }
  return false;
}

void midRead(){
  unsigned char i;
  for (i = 0; i < NUMSENSORS; i++) {
    sensors[i] = TIMEOUT;
    digitalWrite(midsensor[i], HIGH);
    pinMode(midsensor[i], OUTPUT);
  }

  delayMicroseconds(10);  
  for(i = 0; i < NUMSENSORS; i++) {
    pinMode(midsensor[i], INPUT);      
    digitalWrite(midsensor[i], LOW);        
  }
  
  unsigned long startTime = micros();
  while (micros() - startTime < TIMEOUT)
  {
    unsigned int time = micros() - startTime;
    for (i = 0; i < NUMSENSORS; i++)
    {
        if (digitalRead(midsensor[i]) == LOW && time < sensors[i])
            sensors[i] = time;
    }
  }
}

void edgeRead(){
  unsigned char i;
  for (i = 0; i < 2; i++) {
    sensors_e[i] = TIMEOUT;
    digitalWrite(edgesensor[i], HIGH);
    pinMode(edgesensor[i], OUTPUT);
  }

  delayMicroseconds(10);  
  for(i = 0; i < NUMSENSORS; i++) {
    pinMode(edgesensor[i], INPUT);      
    digitalWrite(edgesensor[i], LOW);        
  }
  

  unsigned long startTime = micros();
  while (micros() - startTime < TIMEOUT)
  {
    unsigned int time = micros() - startTime;
    for (i = 0; i < NUMSENSORS; i++)
    {
        if (digitalRead(edgesensor[i]) == LOW && time < sensors_e[i])
            sensors_e[i] = time;
    }
  }
}
