
#include <Adafruit_NeoPixel.h>
#include <Anim.h>
#include <Sensores.h>
#include "mascaraTelmaArduino1.h"
#include "mascaraBecoArduino1.h"


// Led objects initialization
Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);

Anim animTelma(&Telma,0,White,White,corTelma,40,&strip);
Anim animApagaTelma(&Telma,0,White,corTelma,White,200,&strip);
Anim animBeco(&Beco,0,White,White,corBeco,40,&strip);
Anim animApagaBeco(&Beco,0,White,corBeco,White,200,&strip);
//Anim minhaAnimEntrada(&Telma,150,White,&animCores,80,&strip);


// sensor objects initialization
remRead2 reciever;
sensorRemoto sensorTelma(&reciever,1),sensorBeco(&reciever,3);
//sensorRemoto sensorEntrada(&reciever,2);

void setup() {
  startAll(14,White.toUint32(),&strip);
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
delay(30);
}
