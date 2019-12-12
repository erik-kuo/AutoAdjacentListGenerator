/*
Raw data example
This example reads raw readings from the magnetometer gyroscope and the accelerometer and then
displays them in serial monitor.
*/

#include <MPU9255.h>//include MPU9255 library

MPU9255 mpu;
//L298N
#define MotorL_I1     12  //定義 I1 接腳（左）
#define MotorL_I2     6  //定義 I2 接腳（左）
#define MotorR_I3     9  //定義 I3 接腳（右）
#define MotorR_I4     10 //定義 I4 接腳（右）
#define MotorL_PWML   3  //定義 ENA (PWM調速) 接腳
#define MotorR_PWMR   5  //定義 ENB (PWM調速) 接腳

// 循線模組
#define L1  A0  // Define Second Right Sensor Pin
#define L2  A1  // Define First Right Sensor Pin
#define M   A2  // Define Middle Sensor Pin
#define R2  A3  // Define First Left Sensor Pin
#define R1   2  // Define Second Leftt Sensor Pin

// initalize parameter
int r2=0,r1=0,m=0,l1=0,l2=0;
int _Tp=80;
double _rl_ratio = 1.33; // to match the motor on straight line
bool adj = true;

void setup() {
  Serial.begin(115200);//initialize Serial port

  if(mpu.init())
  {
  Serial.println("initialization failed");
  }
  else
  {
  Serial.println("initialization successful!");
  }
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

#include "track.h"
#include "compass.h"
#include "node.h"

void loop() {
  if(adj){
    get_maxmin();
    adj = false;
    delay(5000);
  }
  else
  {
    Serial.print("Phi:");
    Serial.println(get_phi());
    delay(1000);
    /*
    r1 = digitalRead(R1); // right-outer sensor
    r2 = digitalRead(R2); // right-inner sensor
    m  = digitalRead(M);  // middle sensor
    l2 = digitalRead(L2); // left-inner sensor
    l1 = digitalRead(L1); // left-outer sensor
    if(r1 == 1 && l1 == 1)
    {
        fiveBlack_adjest();
        left_turn();
    }
    else
    {
        tracking(r2,r1,m,l1,l2);
    }*/
  }
}
