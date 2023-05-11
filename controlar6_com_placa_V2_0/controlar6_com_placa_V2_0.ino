#include<PCA9685.h>
#include<string.h>

PCA9685 pwmController(0x7F);

bool direc[6];
double angle[6];
double step[6];
//double step=0.15;
//long PWM;


void setup() {

  byte SELECT_SD[8] = {0x7E, 0xFF ,0x06, 0x09 ,0x00, 0x00, 0x02, 0xEF};
  byte SET_VOLUME[8] = {0x7E,0xFF,0x06,0x06,0x00,0x00,0x1E,0xEF};
  byte PLAY_FIRST[8] = {0x7E, 0xFF, 0x06, 0x03, 0x00, 0x00, 0x01, 0xEF};

  Wire.begin();

  pwmController.resetDevices();       // Resets all PCA9685 devices on i2c line

  pwmController.init();               // Initializes module using default totem-pole driver mode, and default disabled phase balancer

  pwmController.setPWMFrequency(49); // Set PWM freq to 100Hz (default is 200Hz, supports 24Hz to 1526Hz)

  pwmController.setAllChannelsPWM(140); // 4096 - 20ms -> 500us é  103, 2500 us é 512. spread é 409

  Serial.begin(9600);
  
  delay(2000);

  Serial.write(SELECT_SD,sizeof(SELECT_SD));
  delay(100);

  Serial.write(SET_VOLUME,sizeof(SET_VOLUME));
  delay(100);

  Serial.write(PLAY_FIRST,sizeof(PLAY_FIRST));
  delay(100);

  direc[0]=true;
  direc[1]=true;
  direc[2]=true;
  direc[3]=true;
  direc[4]=true;
  direc[5]=true;

  angle[0]=18;
  angle[1]=5;
  angle[2]=5;
  angle[3]=5;
  angle[4]=5;
  angle[5]=5;

  step[0]=0.13;
  step[1]=0.15;
  step[2]=0.11;
  step[3]=0.10;
  step[4]=0.12;
  step[5]=0.14;

}

long convertAngleToPWM(double angle){
     double i =((angle/180)*409+103);
     return (long) i ;
}


void loop() {
delay(25);
  for(int i=0;i<6;i++){


    if (angle[i]>=(175-step[i]) || angle[i]<=step[i]) {
      if(direc[i]) direc[i]=false; else direc[i]=true;
    }
    if(direc[i]) angle[i]+=step[i]; else angle[i]-=step[i];



  long PWM = convertAngleToPWM(angle[i]);
  pwmController.setChannelPWM(i,PWM);
  //Serial.print(i);Serial.print(" ");Serial.println(angle[i]);

  }
  
}






