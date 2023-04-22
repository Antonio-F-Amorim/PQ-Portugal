
#include <Adafruit_NeoPixel.h>;
#include "Anim.h";
#include "Sensores.h";
#include "mascaraDiogo.h";

// Led objects initialization
Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);

uint32_t Branco= strip.Color(80,80,80);



uint32_t animCores (uint8_t step){
  if(step<40) return (strip.Color(0,step,2*step));
  else if(step<80) return (strip.Color(0,40-step,160-2*step));
  else return Branco;
  //return strip.Color(80,0,0);
}



Anim minhaAnimDiogo(&Diogo, 150,Branco,&animCores,80,&strip);


// sensor objects initialization
sensorLocal sensorDiogo(A4,A5,2000,7900);


void setup() {

startAll(12,Branco,&strip);
delay(100);
minhaAnimDiogo.run();

}


void loop() {

  if(sensorDiogo.checkSensor()){
    minhaAnimDiogo.run();
  }
  delay(30);

}
