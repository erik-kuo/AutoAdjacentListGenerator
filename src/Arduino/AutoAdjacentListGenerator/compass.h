#include <MPU9255.h> //include MPU9255 library
#include <math.h> // for arccos

int16_t x_max = -1000, x_min = +1000, z_max = -1000, z_min = +1000;

// get max, min to get offset
void get_maxmin(){
  int cnt = 2200;
  mpu.read_mag();
  while(cnt > 0)
  {
      mpu.read_mag();
      if(x_max < mpu.mx)
        x_max = mpu.mx;
      if(x_min > mpu.mx)
        x_min = mpu.mx;
      if(z_max < mpu.mz)
        z_max = mpu.mz;
      if(z_min > mpu.mz)
        z_min = mpu.mz;
      MotorWriting(+80,-80);
      cnt--;
  }
  MotorWriting(0,0);
}

// return phi for turning
float get_phi(){
  mpu.read_mag();
  float x, phi, x_offset, z_offset;
  x_offset = (x_max + x_min)/2;
  x = mpu.mx - x_offset;
  phi = acos(x/(x_max-x_offset))*180/PI;
  if(mpu.mz < (z_max + z_min)/2){ phi = 360 - phi; } // make phi : 0 ~ 360
  return phi;
}
