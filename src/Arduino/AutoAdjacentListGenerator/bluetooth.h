/***************************************************************************/
// File			[bluetooth.h]
// Author		[Erik Kuo]
// Synopsis		[Code used to catch and send bluetooth command]
// Functions    [fiveBlack_adjest, Backward_fiveBlack_adjest, checkline, 
//               forward, right_ture, left_ture, U_turn]
// Modify		[2020/01/02 Joshua Lin]
/***************************************************************************/

#include<SoftwareSerial.h>
#ifndef BT_H
#define BT_H
enum BT_CMD {
  NOTHING,
  HAULT,
  SEARCH,
  ADJUSTMENT,
  BT_PX,
  BT_PY,
  BT_NX,
  BT_NY,
};

BT_CMD ask_BT(){
    BT_CMD message=NOTHING;
    char cmd;
    if(BT.available()){cmd=BT.read();
    Serial.print("cmd : ");
    Serial.println(cmd);
    if(cmd=='H')message=HAULT;
    if(cmd=='S')message=SEARCH;
    if(cmd=='A')message=ADJUSTMENT;
    if(cmd=='n')message=BT_PY;
    if(cmd=='e')message=BT_PX;
    if(cmd=='w')message=BT_NX;
    if(cmd=='s')message=BT_NY;
    }
    return message;
}
char newline = '\n';
void send_BT(const char& msg)
{
     // TODO
     BT.write(msg);
     BT.write(newline);
}
#endif
