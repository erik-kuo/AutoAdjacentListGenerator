#include<SoftwareSerial.h> // for BlueTooth
#include <MPU9255.h> //include MPU9255 library
//BlueTooth
SoftwareSerial BT(8,7);   //bluetooth RX,TX
//compass
MPU9255 mpu;
//L298N
#define MotorL_I1     12  //定義 I1 接腳（左）
#define MotorL_I2     6  //定義 I2 接腳（左）
#define MotorR_I3     9  //定義 I3 接腳（右）
#define MotorR_I4     10 //定義 I4 接腳（右）
#define MotorL_PWML   3  //定義 ENA (PWM調速) 接腳
#define MotorR_PWMR   5  //定義 ENB (PWM調速) 接腳

// 循線模組
#define L1  A0  // Define Left Most Sensor Pin
#define L2  A1  // Define Left Middle Sensor Pin
#define M   A2  // Define Middle Sensor Pin
#define R2  A3  // Define Right Middle Sensor Pin
#define R1   2  // Define Right Most Sensor Pin

enum ControlState {
   HAULT_STATE,
   SEARCH_STATE,
   COMPASS_STATE,
};

ControlState _state=HAULT_STATE;

// search graph
void Search_Mode();
// wait for start cmd
void Hault_Mode();
void SetState();
// initalize parameter
int r2=0,r1=0,m=0,l1=0,l2=0;
int _Tp=80;
double _rl_ratio = 1.28; // to match the motor on straight line

void setup()
{
   //bluetooth initialization
   BT.begin(9600);
   //Serial window
   Serial.begin(9600);
   // mpu initialization
   mpu.init();
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
#include "bluetooth.h"
#include "compass.h"
#include "node.h"


// head direction
enum Direction {
   PX,
   PY,
   NX,
   NY,
};

Direction _dir = PX;

// BT command
BT_CMD _cmd=NOTHING;

void loop()
{
   // search graph
   if(_state == SEARCH_STATE) Search_Mode();
   // wait for start cmd
   else if(_state == HAULT_STATE) Hault_Mode();
   // adjust compass
   else if(_state == COMPASS_STATE) Compass_Mode();
   SetState(); 
}

void SetState() {
  // ask BT cmd
  _cmd=ask_BT();
  // TODO
  if(_state==HAULT_STATE){
      if(_cmd==SEARCH)
        _state= SEARCH_STATE;
      else if(_cmd == ADJUSTMENT)
        _state= COMPASS_STATE;
      else _state = _state;
  }
  else if(_state==SEARCH_STATE){
      if(_cmd==HAULT)
        _state=HAULT_STATE;
      if(_cmd==ADJUSTMENT)
        _state=COMPASS_STATE;
      else _state=_state;
  }
  else if(_state==COMPASS_STATE){
        _state=HAULT_STATE;
  }
}

void Hault_Mode(){
  MotorWriting(0,0);
}

void Compass_Mode()
{
    get_maxmin();
}

// checkline return bool
bool HaveLine = true;

void Search_Mode(){
    // read sensor value
    r1 = digitalRead(R1); // right-outer sensor
    r2 = digitalRead(R2); // right-inner sensor
    m  = digitalRead(M);  // middle sensor
    l2 = digitalRead(L2); // left-inner sensor
    l1 = digitalRead(L1); // left-outer sensor
   // 進入node
   if((r1 == 1 && l1 == 1) || !HaveLine)// 5 black or no line TODO
   {
      MotorWriting(0,0);
      // 知道要往哪個方向
      do
      {
          _cmd = ask_BT();
      }while(_cmd == NOTHING);
      
      if(HaveLine)
      {
          // 從tracking進node時做 5 black 校正成與方格切齊
          fiveBlack_adjest();
      }
      
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
                  default:
                      MotorWriting(0,0);
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
                  default:
                      MotorWriting(0,0);
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
                  default:
                      MotorWriting(0,0);
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
                  default:
                      MotorWriting(0,0);
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
