
#include <Adafruit_NeoPixel.h>
#include <Anim.h>
#include <Sensores.h>
#include "mascaraDiogo.h"

// Led objects initialization
Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);

uint32_t Branco= strip.Color(90,65,65);



uint32_t animCoresSobe (uint8_t step){
  if(step<40) return (strip.Color(90-2*step,65-step,65+4*step));
  else return Branco;

}

uint32_t animCoresDesce (uint8_t step){
  if(step<40) return (strip.Color(10+2*step,25+step,221-4*step));
  else return Branco;
}



Anim minhaAnimDiogoSobe(&Diogo,10,Branco,&animCoresSobe,40,&strip);
Anim minhaAnimDiogoDesce(&Diogo, 100,Branco,&animCoresDesce,40,&strip);


// sensor objects initialization
sensorLocal sensorDiogo(A4,A5,2000,7900);


void setup() {

startAll(12,Branco,&strip);
delay(100);
minhaAnimDiogoSobe.run();
minhaAnimDiogoDesce.run();

}


void loop() {

  if(sensorDiogo.checkSensor()){
    minhaAnimDiogoSobe.run();
    while(sensorDiogo.checkSensorAverage()){
      delay(30);
    }
    minhaAnimDiogoDesce.run();
  }
  
delay(1);

}
