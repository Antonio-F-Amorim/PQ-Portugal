
#include <Adafruit_NeoPixel.h>
#include <Anim.h>
#include <Sensores.h>
#include "mascaraTelmaArduino2.h"
#include "mascaraBecoArduino2.h"

class Adafruit_NeoPixel;
// Led objects initialization
Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);



Anim minhaAnimTelma(&Telma,0,White,White,corTelma,40,&strip);
Anim minhaAnimApagaTelma(&Telma,0,White,corTelma,White,200,&strip);
Anim minhaAnimBeco(&Beco,0,White,White,corBeco,40,&strip);
Anim minhaAnimApagaBeco(&Beco,0,White,corBeco,White,200,&strip);

remWrite2 sender;
sensorParteLocal sensorTelma(A0,A1,2000,8000,&sender,1),sensorEntrada(A2,A3,2000,8000,&sender,2),sensorBeco(A4,A5,2000,8000,&sender,3);

void setup() {
  startAll(12,White.toUint32(),&strip);
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
delay(30);
}
