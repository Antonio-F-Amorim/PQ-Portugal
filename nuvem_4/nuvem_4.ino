#include<PCA9685.h>

PCA9685 pwmController(0x7F);

class motor {
 public: 
  uint8_t MID;
  double posicao;
  uint8_t minimo;
  uint8_t maximo;
  uint8_t step;
  bool direc;

  motor(uint8_t mid,float pos,uint8_t min,uint8_t max,uint8_t stp,bool dir){
    MID=mid;
    posicao=pos;
    minimo=min;
    maximo=max;
    step=stp;
    direc=dir;
  }

  void moveServo( double y){

     if(MID<0||MID>16||y<0||y>100) return;
    double PWM = y*401/100+105;
    pwmController.setChannelPWM(MID,PWM);
    
  //  Serial.print(" set channel ");
  //  Serial.print(MID);
  //  Serial.print(" to ");
  //  Serial.println(PWM);
  }

  void incrementMove(){
    if(direc) {
      posicao += (double)step/1000;
      if (posicao>= maximo) {
        posicao=maximo; direc=!direc;
      } 
    }
    else {
      posicao -= (double) step/1000;
      if (posicao<=minimo) {
        posicao=minimo; direc=!direc;
      } 
    }
    moveServo(posicao);
    
  }
};

  motor motor1(7,55,35,75,50,1);
  motor motor2(5,62,28,85,40,1);
  motor motor3(8,60,45,70,45,1);
  motor motor4(11,11,1,26,65,1);



//pwmController.setChannelPWM(x-1,PWM);

void setup() {
  
  Wire.begin();

  pwmController.resetDevices();       // Resets all PCA9685 devices on i2c line

  pwmController.init();               // Initializes module using default totem-pole driver mode, and default disabled phase balancer

  pwmController.setPWMFrequency(49);

  Serial.begin(9600);

  delay(1000);

}


void loop() {
motor1.incrementMove();
motor2.incrementMove();
motor3.incrementMove();
motor4.incrementMove();
delay(15);
}
