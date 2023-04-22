
#include <Adafruit_NeoPixel.h>;
#include <Anim.V.0.3.h>;
#include <Sensores.V.0.3.h>;
#include "mascaraTelmaArduino1.h";
#include "mascaraBecoArduino1.h";


// Led objects initialization
Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);

uint32_t Branco= strip.Color(90,65,65);


uint32_t animCoresSobe (uint8_t step){
  if(step<40) return (strip.Color(80-2*step,80-step,4*step));
  else return Branco;

}

uint32_t animCoresDesce (uint8_t step){
  if(step<40) return (strip.Color(2*step,40+step,160-2*step));
  else return Branco;
}

uint32_t animCores (uint8_t step){
  return strip.Color(240,40,0);
  /*
  if(step<40) return animCoresSobe(step);
  if(step<80) return animCoresDesce(40+step);
  else return Branco;
*/
}
uint32_t apaga (uint8_t step){
  return Branco;
}



Anim animTelma(&Telma,500,Branco,animCores,2,&strip);
Anim animApagaTelma(&Telma,500,Branco,apaga,2,&strip);
Anim animBeco(&Beco,500,Branco,animCores,2,&strip);
Anim animApagaBeco(&Beco,500,Branco,apaga,2,&strip);
//Anim minhaAnimEntrada(&Telma,150,Branco,&animCores,80,&strip);


// sensor objects initialization
remRead2 reciever;
sensorRemoto sensorTelma(&reciever,1),sensorBeco(&reciever,3);
//sensorRemoto sensorEntrada(&reciever,2);

void setup() {
  startAll(14,Branco,&strip);
  delay(5000);
}


void loop() {

reciever.update();
  if(!animTelma.runStep() && !animApagaTelma.runStep()){ 
    if(sensorTelma.checkSensor()) animTelma.begin();
    else animApagaTelma.begin();
  }
  if(!animBeco.runStep() && !animApagaBeco.runStep()){ 
    if(sensorBeco.checkSensor()) animBeco.begin();
    else animApagaBeco.begin();
  }
  delay(10);

}
