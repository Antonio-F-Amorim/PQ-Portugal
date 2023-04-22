
#include <Adafruit_NeoPixel.h>
#include <Anim.h>
#include <Sensores.h>
#include "mascaraTelmaArduino2.h"
#include "mascaraBecoArduino2.h"

class Adafruit_NeoPixel;
// Led objects initialization
Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);

uint32_t Branco= strip.Color(90,65,65);


uint32_t animCoresSobe (uint8_t step){
  if(step<40) return (strip.Color(0,step,2*step));
  else return Branco;

}

uint32_t animCoresDesce (uint8_t step){
  if(step<80 && step>39) return (strip.Color(0,80-step,160-2*step));
  else return Branco;
}

uint32_t animCores (uint8_t step){
  return strip.Color(240,40,0);
}

uint32_t apaga (uint8_t step){
  return Branco;
}



Anim minhaAnimTelma(&Telma,500,Branco,animCores,2,&strip);
Anim minhaAnimApagaTelma(&Telma,500,Branco,apaga,2,&strip);
Anim minhaAnimBeco(&Beco,500,Branco,animCores,2,&strip);
Anim minhaAnimApagaBeco(&Beco,500,Branco,apaga,2,&strip);

remWrite2 sender;
sensorParteLocal sensorTelma(A0,A1,2000,8000,&sender,1),sensorEntrada(A2,A3,2000,8000,&sender,2),sensorBeco(A4,A5,2000,8000,&sender,3);

void setup() {
  startAll(12,Branco,&strip);
  delay(5000);
  digitalWrite(12,LOW);

}


void loop() {

 if(!minhaAnimTelma.runStep()&&!minhaAnimApagaTelma.runStep()){ 
    if(sensorTelma.checkSensor()) minhaAnimTelma.begin();
    else minhaAnimApagaTelma.begin();
  }
  if(!minhaAnimBeco.runStep()&&!minhaAnimApagaBeco.runStep()){ 
    if(sensorBeco.checkSensor()) minhaAnimBeco.begin();
    else minhaAnimApagaBeco.begin();
  }
  delay(10);
}
