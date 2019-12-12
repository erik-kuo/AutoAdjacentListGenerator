#include <SoftwareSerial.h>
#include <Wire.h>

int extern r1, l1;

void fiveBlack_adjest() // 校正成與方格切齊
{
    MotorWriting(0,0);
    delay(50);    
    r1 = digitalRead(R1); // right-outer sensor
    l1 = digitalRead(L1); // left-outer sensor
    while(r1 == 1 || l1 == 1)
    {
        MotorWriting(-60 * r1, -60 * l1);
        r1 = digitalRead(R1); // right-outer sensor
        l1 = digitalRead(L1); // left-outer sensor
    }
    MotorWriting(0,0);
    delay(1000);
}

bool checkline()
{
    return true;
}

void forward()
{
    MotorWriting(150,150); // 先直走一段
    delay(200);
    r1 = digitalRead(R1); // right-outer sensor
    l1 = digitalRead(L1); // left-outer sensor
    while(r1 != 0 && l1 != 0) // 最旁邊到白表示離開node
    {
        MotorWriting(150,150);
        r1 = digitalRead(R1); // right-outer sensor
        l1 = digitalRead(L1); // left-outer sensor
    }
    MotorWriting(0,0);
}

void left_turn()
{
    MotorWriting(150,-150); // 先轉一段
    delay(200);
    // 看MPU9255的角度修正 TODO
    MotorWriting(0,0);
}

void right_turn()
{
    MotorWriting(-150,150); // 先轉一段
    delay(200);
    // 看MPU9255的角度修正 TODO
    MotorWriting(0,0);
}

void U_turn()
{
    MotorWriting(150,-150); // 先轉一段
    delay(400);
    // 看MPU9255的角度修正 TODO
    MotorWriting(0,0);
}
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
