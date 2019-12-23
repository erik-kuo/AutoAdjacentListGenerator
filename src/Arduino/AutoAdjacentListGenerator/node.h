#include <SoftwareSerial.h>
#include <Wire.h>

int extern r1, l1, r2, l2, m;
const float max_err_deg = 5.0; // 與目標方向差多少度 45+-5

void fiveBlack_adjest() // 校正成與方格切齊
{
    MotorWriting(0,0);
    delay(50);    
    r1 = digitalRead(R1); // right-outer sensor
    l1 = digitalRead(L1); // left-outer sensor
    while(r1 == 1 || l1 == 1)
    {
        MotorWriting(-80 * r1, -80 * l1);
        r1 = digitalRead(R1); // right-outer sensor
        l1 = digitalRead(L1); // left-outer sensor
    }
    MotorWriting(0,0);
    delay(100);
    while(r1 == 0 || l1 == 0)
    {
        MotorWriting(100, 100);
        r1 = digitalRead(R1); // right-outer sensor
        l1 = digitalRead(L1); // left-outer sensor
    }
    MotorWriting(0,0);
    delay(100);
}

bool checkline()
{
    // read sensor value
    r1 = digitalRead(R1); // right-outer sensor
    r2 = digitalRead(R2); // right-inner sensor
    m  = digitalRead(M);  // middle sensor
    l2 = digitalRead(L2); // left-inner sensor
    l1 = digitalRead(L1); // left-outer sensor
    if(r1 == 1 || r2 == 1 || m == 1 || l2 == 1 || l1 == 1)
    {
        Serial.println("Have line");
        return true;
    }
    Serial.println("No line");
    return false;
}

void forward()
{
    r1 = digitalRead(R1); // right-outer sensor
    l1 = digitalRead(L1); // left-outer sensor
    while(!(r1 == 0 && l1 == 0)) // 最旁邊到白表示離開node
    {
        MotorWriting(100,100);
        r1 = digitalRead(R1); // right-outer sensor
        l1 = digitalRead(L1); // left-outer sensor
    }
    MotorWriting(0,0);
    delay(500);
}

void left_turn()
{
    // forward()?
    forward();
    // 先直走一段
//    MotorWriting(150,150);
//    delay(500);
    // 計算目標角度 = 現在角度-90
    int target_phi = get_phi() - 90;
    // 處理超過0~360的值
    if(target_phi < 0)
      target_phi += 360;
    // 當與目標差 <= max_err_deg時停止
    while(abs(get_phi()- target_phi) > max_err_deg)
    {
      MotorWriting(60,-60);
      Serial.print("Phi:");
      Serial.println(get_phi());
    }
    MotorWriting(0,0);
    delay(100);
}

void right_turn()
{
    forward();
    // 先直走一段
    //MotorWriting(150,150);
    //delay(500);
    // 計算目標角度 = 現在角度+90
    int target_phi = get_phi() + 90;
    // 處理超過0~360的值
    if(target_phi > 360)
      target_phi -= 360;
    // 當與目標差 <= max_err_deg時停止
    while(abs(get_phi()- target_phi) > max_err_deg)
    {
      MotorWriting(-60,60);
      Serial.print("Phi:");
      Serial.println(get_phi());
    }
    MotorWriting(0,0);
}

void U_turn()
{
    forward();
    // 先直走一段
    //MotorWriting(150,150);
    //delay(500);
    // 計算目標角度 = 現在角度-180(左轉)
    int target_phi = get_phi() - 180;
    // 處理超過0~360的值
    if(target_phi < 0)
      target_phi += 360;
    // 當與目標差 <= max_err_deg時停止(左轉)
    while(abs(get_phi()- target_phi) > max_err_deg)
    {
      MotorWriting(60,-60);
      Serial.print("Phi:");
      Serial.println(get_phi());
    }
    MotorWriting(0,0);
}
