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
  
  // use x to evalute phi
  float x, phi_x, x_offset;
  x_offset = (float)(x_max + x_min)/2;
  x = max(min(mpu.mx, x_max), x_min) - x_offset;
  phi_x = acos(x/(x_max-x_offset))*180/PI;

  // use z to evalute phi
  float z, phi_z, z_offset;
  z_offset = (float)(z_max + z_min)/2;
  z = max(min(mpu.mz, z_max), z_min) - z_offset;
  phi_z = acos(z/(z_max-z_offset))*180/PI;

  // shift phi_z to match phi_x
  if(mpu.mz < (z_max + z_min)/2){ phi_x = 360 - phi_x; } // make phi : 0 ~ 360
  if(mpu.mx > (x_max + x_min)/2){ phi_z = 360 - phi_z; }
  phi_z += 90;
  if(phi_z > 360) phi_z -= 360;

  // combine phi_x and phi_z to get phi
  float phi, phi_ave = (phi_x + phi_z)/2;
  if((phi_ave > 45 && phi_ave < 135) || (phi_ave > 225 && phi_ave < 315))
    phi = phi_x;
  else
    phi = phi_z;
  
  return phi;
}
