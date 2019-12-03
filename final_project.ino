#include <SoftwareSerial.h>
#include <SPI.h>
//BlueTooth
SoftwareSerial BT(8,7);   //bluetooth RX,TX
//L298N
#define MotorL_I1     12  //定義 I1 接腳（左）
#define MotorL_I2     6  //定義 I2 接腳（左）
#define MotorR_I3     9  //定義 I3 接腳（右）
#define MotorR_I4     10 //定義 I4 接腳（右）
#define MotorL_PWML   3  //定義 ENA (PWM調速) 接腳
#define MotorR_PWMR   5  //定義 ENB (PWM調速) 接腳
// 循線模組
#define R2  A0  // Define Second Right Sensor Pin
#define R1  A1  // Define First Right Sensor Pin
#define M   A2  // Define Middle Sensor Pin
#define L1  A3  // Define First Left Sensor Pin
#define L2   2  // Define Second Leftt Sensor Pin

enum ControlState {
   HAULT_STATE,
   SEARCH_STATE,
};

ControlState _state=HAULT_STATE;

// search graph
void Search_Mode();
// wait for start cmd
void Hault_Mode();
void SetState();
int _cmd=0;

void setup()
{
   //bluetooth initialization
   BT.begin(9600);
   //Serial window
   Serial.begin(9600);
   //L298N pin
   pinMode(MotorL_I1,   OUTPUT);
   pinMode(MotorL_I2,   OUTPUT);
   pinMode(MotorR_I3,   OUTPUT);
   pinMode(MotorR_I4,   OUTPUT);
   pinMode(MotorL_PWML, OUTPUT);
   pinMode(MotorR_PWMR, OUTPUT);
   //tracking pin
   pinMode(R1, INPUT); 
   pinMode(R2, INPUT);
   pinMode(M,  INPUT);
   pinMode(L1, INPUT);
   pinMode(L2, INPUT);
   
}

//Self define header
#include "track.h"
//#include "node.h"
#include "bluetooth.h"
int r2=0,r1=0,m=0,l1=0,l2=0;

// head direction
enum Direction {
   PX,
   PY,
   NX,
   NY,
};

Direction _dir = PY;

int _Tp=80;

void loop()
{
   // search graph
   if(_state == SEARCH_STATE) Search_Mode();
   // wait for start cmd
   else if(_state == HAULT_STATE) Hault_Mode();
   SetState(); 
}

void SetState() {
  // ask BT cmd
  _cmd=ask_BT();
  // TODO
  if(_state==HAULT_STATE){
      if(_cmd==5){
        _state= SEARCH_STATE; }
      else _state=_state;
  }
  else if(_state==SEARCH_STATE){
      if(_cmd==6){
        _state=HAULT_STATE;
      }
      else _state=_state;
  }
}

void Hault_Mode(){
  MotorWriting(0,0);
  // 羅盤校正
  //TODO
}

// checkline return bool
bool HaveLine = true;

void Search_Mode(){
    // read sensor value
    r1 = digitalRead(R1); // right-outer sensor
    r2 = digitalRead(R2); // right-inner sensor
    m  = digitalRead(M);  // middle sensor
    l2 = digitalRead(L1); // left-inner sensor
    l1 = digitalRead(L2); // left-outer sensor
   // 進入node
   if(... || !HaveLine)// 5 black or no line TODO
   {
      // 知道要往哪個方向
      _cmd = ask_BT();
      switch(_dir)
      {
          // 車頭向+X
          case PX:
              switch(_cmd)
              {
                  case BT_PX:
                      forward();
                      _dir = PX;
                      break;
                  case BT_PY:
                      left_turn();
                      _dir = PY;
                      break;
                  case BT_NX:
                      U_turn();
                      _dir = NX;
                      break;
                  case BT_NY:
                      right_turn();
                      _dir = NY;
                      break;
              }
              break;
          // 車頭向+Y
          case PY:
              switch(_cmd)
              {
                  case BT_PX:
                      right_turn();
                      _dir = PX;
                      break;
                  case BT_PY:
                      forward();
                      _dir = PY;
                      break;
                  case BT_NX:
                      left_turn();
                      _dir = NX;
                      break;
                  case BT_NY:
                      U_turn();
                      _dir = NY;
                      break;
              }
              break;
          // 車頭向-X
          case NX:
              switch(_cmd)
              {
                  case BT_PX:
                      U_turn();
                      _dir = PX;
                      break;
                  case BT_PY:
                      right_turn();
                      _dir = PY;
                      break;
                  case BT_NX:
                      forward();
                      _dir = NX;
                      break;
                  case BT_NY:
                      left_turn();
                      _dir = NY;
                      break;
              }
              break;
          // 車頭向-Y
          case NY:
              switch(_cmd)
              {
                  case BT_PX:
                      left_turn();
                      _dir = PX;
                      break;
                  case BT_PY:
                      U_turn();
                      _dir = PY;
                      break;
                  case BT_NX:
                      right_turn();
                      _dir = NX;
                      break;
                  case BT_NY:
                      forward();
                      _dir = NY;
                      break;
              }
              break;
      }// switch(_dir)
      HaveLine = checkline();// 包含send_BT()
   }
   // 基本直線
   else
   {
      tracking(r2,r1,m,l1,l2);
   }
}
