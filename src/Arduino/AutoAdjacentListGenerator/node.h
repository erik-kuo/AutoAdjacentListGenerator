/***************************************************************************/
// File			[node.h]
// Author		[Erik Kuo, Joshua Lin]
// Synopsis		[Code used when encounter a node]
// Functions    [fiveBlack_adjest, Backward_fiveBlack_adjest, checkline, 
//               forward, right_ture, left_ture, U_turn]
// Modify		[2020/01/02 Joshua Lin]
/***************************************************************************/

#include <SoftwareSerial.h>
#include <Wire.h>

int extern r1, l1, r2, l2, m;
const float max_err_deg = 3.0; // 與目標方向差多少度 +-5

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
        MotorWriting(80, 80);
        r1 = digitalRead(R1); // right-outer sensor
        l1 = digitalRead(L1); // left-outer sensor
    }
    MotorWriting(0,0);
    delay(100);
}

// 最後沒有用到
void Backward_fiveBlack_adjest() // 校正成與方格切齊
{
    MotorWriting(0,0);
    delay(50);    
    r1 = digitalRead(R1); // right-outer sensor
    l1 = digitalRead(L1); // left-outer sensor
    while(r1 == 0 || l1 == 0)
    {
        MotorWriting(65 * (r1-1), 65 * (l1-1));
        r1 = digitalRead(R1); // right-outer sensor
        l1 = digitalRead(L1); // left-outer sensor
    }
    delay(100);
    MotorWriting(0,0);
    delay(100);
}

// Check if theres a line in front of the car.
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
        send_BT('L');
        return true;
    }
    Serial.println("No line");
    send_BT('N');
    return false;
}

void forward()
{
    r1 = digitalRead(R1); // right-outer sensor
    l1 = digitalRead(L1); // left-outer sensor
    int cnt =100;
    while((r1+l1)== 2 || ((r1+l1 == 1)&& cnt > 0)) // 最旁邊到白表示離開node
    {
        MotorWriting(80,80);
        r1 = digitalRead(R1); // right-outer sensor
        l1 = digitalRead(L1); // left-outer sensor
        cnt--;
    }
    MotorWriting(0,0);
    delay(500);
    /*
    Backward_fiveBlack_adjest();
    cnt = 0;
    while(!(r1 == 0 && l1 == 0)|| cnt > 0) // 最旁邊到白表示離開node
    {
        MotorWriting(80,80);
        r1 = digitalRead(R1); // right-outer sensor
        l1 = digitalRead(L1); // left-outer sensor
        cnt--;
    }
    MotorWriting(0,0);
    delay(500);
    */
}

void left_turn()
{
    forward();
    // 先直走一段
    // 計算目標角度 = 現在角度-90
    int target_phi = get_phi() - 90;
    // 處理超過0~360的值
    if(target_phi < 0)
      target_phi += 360;
    // 當與目標差 <= max_err_deg時停止
    MotorWriting(80,-80);
    delay(100);
    while(abs(get_phi()- target_phi) > max_err_deg)
    {
      MotorWriting(55,-55);
      Serial.print("Phi:");
      Serial.println(get_phi());
    }
    MotorWriting(0,0);
    delay(100);
    forward();
    /*
    r1 = digitalRead(R1); // right-outer sensor
    l1 = digitalRead(L1); // left-outer sensor
    int cnt =100;
    while(!(r1 == 0 && l1 == 0)|| cnt > 0) // 最旁邊到白表示離開node
    {
        MotorWriting(80,80);
        r1 = digitalRead(R1); // right-outer sensor
        l1 = digitalRead(L1); // left-outer sensor
        cnt--;
    }
    MotorWriting(0,0);
    delay(500);*/
}

void right_turn()
{
    forward();
    // 先直走一段
    // 計算目標角度 = 現在角度+90
    int target_phi = get_phi() + 90;
    // 處理超過0~360的值
    if(target_phi > 360)
      target_phi -= 360;
    // 當與目標差 <= max_err_deg時停止
    MotorWriting(-80,80);
    delay(100);
    while(abs(get_phi()- target_phi) > max_err_deg)
    {
      MotorWriting(-55,55);
      Serial.print("Phi:");
      Serial.println(get_phi());
    }
    MotorWriting(0,0);
    delay(100);
    forward();
    /*
    r1 = digitalRead(R1); // right-outer sensor
    l1 = digitalRead(L1); // left-outer sensor
    int cnt =100;
    while(!(r1 == 0 && l1 == 0)|| cnt > 0) // 最旁邊到白表示離開node
    {
        MotorWriting(80,80);
        r1 = digitalRead(R1); // right-outer sensor
        l1 = digitalRead(L1); // left-outer sensor
        cnt--;
    }
    MotorWriting(0,0);
    delay(500);*/
}

void U_turn()
{
    forward();
    // 先直走一段
    // 計算目標角度 = 現在角度-180(左轉)
    int target_phi = get_phi() - 180;
    // 處理超過0~360的值
    if(target_phi < 0)
      target_phi += 360;
    // 當與目標差 <= max_err_deg時停止(左轉)
    MotorWriting(-80,80);
    delay(100);
    while(abs(get_phi()- target_phi) > max_err_deg)
    {
      MotorWriting(-55,55);
      Serial.print("Phi:");
      Serial.println(get_phi());
    }
    MotorWriting(0,0);
    delay(100);
    forward();
    /*
    r1 = digitalRead(R1); // right-outer sensor
    l1 = digitalRead(L1); // left-outer sensor
    int cnt =100;
    while(!(r1 == 0 && l1 == 0)|| cnt > 0) // 最旁邊到白表示離開node
    {
        MotorWriting(80,80);
        r1 = digitalRead(R1); // right-outer sensor
        l1 = digitalRead(L1); // left-outer sensor
        cnt--;
    }
    MotorWriting(0,0);
    delay(500);*/
}
