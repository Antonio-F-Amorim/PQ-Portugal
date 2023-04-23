
#include <Adafruit_NeoPixel.h>
#include <Anim.h>
#include <Sensores.h>
#include "mascaraTelmaArduino1.h"
#include "mascaraBecoArduino1.h"


// Led objects initialization
Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);

Anim AnimTelma(&Telma,0,White,White,corTelma,60,&strip);
Anim AnimApagaTelma(&Telma,0,White,corTelma,White,100,&strip);
Anim AnimBeco(&Beco,0,White,White,corBeco,60,&strip);
Anim AnimApagaBeco(&Beco,0,White,corBeco,White,100,&strip);
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

 if(!AnimTelma.runStep()&&!AnimApagaTelma.runStep()){ 

   if(sensorTelma.checkSensor()) {
     if(!AnimTelma.justFinished){ 
        AnimTelma.begin();
        AnimTelma.justFinished=true;
     }
   }
   
   else if(AnimTelma.justFinished) {
      AnimApagaTelma.begin();
      AnimTelma.justFinished=false;
    }
  }

 if(!AnimBeco.runStep()&&!AnimApagaBeco.runStep()){ 

   if(sensorBeco.checkSensor()) {
     if(!AnimBeco.justFinished){ 
        AnimBeco.begin();
        AnimBeco.justFinished=true;
     }
   }
   
   else if(AnimBeco.justFinished) {
      AnimApagaBeco.begin();
      AnimBeco.justFinished=false;
    }
  }


delay(30);
}
