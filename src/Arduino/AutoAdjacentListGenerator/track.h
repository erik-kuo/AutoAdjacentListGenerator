/***************************************************************************/
// File			[track.h]
// Author		[Erik Kuo]
// Synopsis		[Code used for tracking]
// Functions    [MotorInverter, MotorWriting, tracking]
// Modify		[2020/01/02 Joshua Lin]
/***************************************************************************/

#include <SoftwareSerial.h>
#include <Wire.h>
#define DEBUG

int extern _Tp;
double extern  _rl_ratio; // to match the motor on straight line

// Handle negative motor_PWMR value.
void MotorInverter(int motor, bool& dir) {
    if(motor==MotorL_PWML){
        if(dir){
            digitalWrite(MotorL_I1,HIGH);
            digitalWrite(MotorL_I2,LOW);
        }
        else{
            digitalWrite(MotorL_I1,LOW);
            digitalWrite(MotorL_I2,HIGH);
        }
    }
    if(motor==MotorR_PWMR){
        if(dir){
            digitalWrite(MotorR_I3,HIGH);
            digitalWrite(MotorR_I4,LOW);
        }
        else{
            digitalWrite(MotorR_I3,LOW);
            digitalWrite(MotorR_I4,HIGH);
        }
    }
}

// Write the voltage to motor.
void MotorWriting(double vR, double vL) {
    vR = vR * _rl_ratio;
    bool R_dir,L_dir;
    if(vR<0)
    {
        R_dir=false;
        vR=-vR;
    }
    else R_dir=true;
    //Serial.println(vL);
    if(vL<0)
    {
        L_dir=false;
        vL=-vL;
        
    }
    else L_dir=true;
    MotorInverter(MotorR_PWMR,R_dir);
    MotorInverter(MotorL_PWML,L_dir);
    analogWrite(MotorL_PWML,vL);
    analogWrite(MotorR_PWMR,vR);
    //Serial.println(vL);
    
}

// P control Tracking
void tracking(int r2,int r1,int m,int l1,int l2){
    double _w1=10;
    double _w2=_w1/2.0;
    double _Kp=9;
    double error=l1*_w1+l2*_w2+r2*(-_w2)+r1*(-_w1);
    if ((r1+r2+l1+l2)>0) error/=(r1+r2+l1+l2);
    error*=_Kp;
    MotorWriting((_Tp+error), _Tp-error);
}