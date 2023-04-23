#include <Adafruit_NeoPixel.h>
#include <Anim.h>
#include <Sensores.h>
#include "mascaraDiogo.h"

// Led objects initialization
Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);


Anim minhaAnimDiogoSobe(&Diogo,40,White,White,corDiogo,5,&strip);
Anim minhaAnimDiogoDesce(&Diogo,40,White,corDiogo,White,60,&strip);

// sensor objects initialization
sensorLocal sensorDiogo(A4,A5,2000,7900);


void setup() {

startAll(12,White.toUint32(),&strip);
delay(100);

}


void loop() {

  if(sensorDiogo.checkSensor()){
    minhaAnimDiogoSobe.run();
    while(sensorDiogo.checkSensorAverage()){
      delay(30);
    }
    minhaAnimDiogoDesce.run();
  }
  
delay(10);

}
