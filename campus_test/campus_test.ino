/*
Raw data example
This example reads raw readings from the magnetometer gyroscope and the accelerometer and then
displays them in serial monitor.
*/

#include <MPU9255.h>//include MPU9255 library
#include <math.h>

MPU9255 mpu;

void get_maxmin(int16_t& x_max, int16_t& x_min, int16_t& y_max, int16_t& y_min){
  mpu.read_mag();
}

float get_phi(int16_t x_max, int16_t x_min, int16_t y_max, int16_t y_min){
  mpu.read_mag();
  float x, phi, x_offset, y_offset;
  x_offset = (x_max + x_min)/2;
  x = mpu.mx - x_offset;
  if(abs(x) > abs(x_offset)){ x = (float(x_offset)) * (x > 0 ? 1 : -1); }

  if(mpu.my > (y_max + y_min)/2){  }
  phi = acos(x/x_offset)*180/PI;
  return phi;
}

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

}

void loop() {
  mpu.read_mag();//get data from the magnetometer
  int16_t x_max, x_min, y_max, y_min;
  
  Serial.print("MX: ");
  Serial.print(mpu.mx);
  Serial.print(" MY: ");
  Serial.print(mpu.my);
  Serial.print(" MZ: ");
  Serial.print(mpu.mz);
  Serial.print("   Phi: ");
  Serial.println(get_phi(-25, -360, 440, 100));
  
  delay(100);
}
