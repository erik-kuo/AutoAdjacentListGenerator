
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

void send_BT(const char& msg)
{
     // TODO
     BT.write(msg);
}
#endif
/*
char convert_to_hex(int x)
{
    if(x==0)return'0';
    if(x==1)return'1';
    if(x==2)return'2';
    if(x==3)return'3';
    if(x==4)return'4';
    if(x==5)return'5';
    if(x==6)return'6';
    if(x==7)return'7';
    if(x==8)return'8';
    if(x==9)return'9';
    if(x==10)return'A';
    if(x==11)return'B';
    if(x==12)return'C';
    if(x==13)return'D';
    if(x==14)return'E';
    if(x==15)return'F';
}

void send_byte(byte *id, byte idSize){
    for(int i=0;i<idSize;i++)
    {
        char a=convert_to_hex(id[i]/16);
        char b=convert_to_hex(id[i]%16);
        BT.write(a);
        BT.write(b);
    }
}
*/
