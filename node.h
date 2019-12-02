#include <SoftwareSerial.h>
#include <Wire.h>

// TODO
bool checkline()
{
    return true;
}

void forward(){}
void left_turn(){}
void right_turn(){}
void U_turn(){}
/*
void node(int dir){
    switch(dir){
        case 0:
            MotorWriting(200,150);
            delay(250);
            MotorWriting(0,0);
            //tracking(r2,r1,m,l1,l2);break;
        
        case 1: //turn right
            MotorWriting(-200,200);//轉彎(小)
            delay(140);
             MotorWriting(0,0);
            // Serial.print("2nd");
           // delay(2000);
            //Serial.print(digitalRead(R1));
            //轉到偵測到黑
            while(digitalRead(L1) ==0){
              Serial.print("white");
              MotorWriting(-80,80);
            }
           
            MotorWriting(0,0);
            //Serial.print("3rd");
            //delay(2000);
            MotorWriting(100,100);//直走小(可嘗試刪掉)
            delay(100);break;
            
            
        
        case 2: //turn left
            MotorWriting(200,-200);
            delay(140);
            MotorWriting(0,0);
            //delay(2000);
            
            while(digitalRead(R1)==0){
              MotorWriting(100,-100);
            }
            
            MotorWriting(0,0);
            //delay(2000);
            MotorWriting(100,100);
            delay(100);break;
            
        case 3: //180
            MotorWriting(-255,255);
            delay(400);
             MotorWriting(0,0);
            //delay(2000);
            while(digitalRead(L1)==0){
              MotorWriting(-100,100);
            }
             MotorWriting(0,0);
            //delay(2000);
           break;
            
        case 4://halt
            MotorWriting(0,0);
            delay(100);break;
    }
}
*/
