/***************************************************************************/
// File			  [compass.h]
// Author		  [Joshua Lin]
// Synopsis		[Arduino code for compass]
// Functions  [get_maxmin, get_phi]
// Modify		  [2020/01/02 Joshua Lin]
/***************************************************************************/

#include <MPU9255.h> //include MPU9255 library
#include <math.h> // for arccos

int16_t x_max = -1000, x_min = +1000, z_max = -1000, z_min = +1000;
int16_t sample_time = 1; // to get average phi then return phi

// get max, min to get offset
void get_maxmin(){
  int cnt = 3300;
  MotorWriting(80,-80);
  delay(100);
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
      MotorWriting(+60,-60);
      cnt--;
  }
  MotorWriting(0,0);
}

// return current phi for turning
float get_phi(){
  mpu.read_mag();
  
  // use x to evalute phi
  float x, x_offset, phi_x = 0;
  x_offset = (float)(x_max + x_min)/2;
  for(int16_t i = 0; i < sample_time; ++i)
  {
      x = max(min(mpu.mx, x_max), x_min) - x_offset;
      phi_x += acos(x/(x_max-x_offset))*180/PI;
  }
  phi_x /= sample_time;

  // use z to evalute phi
  float z, z_offset, phi_z = 0;
  z_offset = (float)(z_max + z_min)/2;
  for(int16_t i = 0; i < sample_time; ++i)
  {
      z = max(min(mpu.mz, z_max), z_min) - z_offset;
      phi_z += acos(z/(z_max-z_offset))*180/PI;
  }
  phi_z /= sample_time;

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
