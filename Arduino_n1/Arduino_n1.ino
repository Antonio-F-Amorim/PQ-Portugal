
#include <Adafruit_NeoPixel.h>
#include <Anim.h>
#include <Sensores.h>
#include "mascaraTelmaArduino1.h"
#include "mascaraBecoArduino1.h"


// Led objects initialization
Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);

Anim AnimTelma(&Telma,0,White,White,corTelma,30,150,&strip);
Anim AnimApagaTelma(&Telma,0,White,corTelma,White,50,50,&strip);
Anim AnimBeco(&Beco,0,White,White,corBeco,30,80,&strip);
Anim AnimApagaBeco(&Beco,0,White,corBeco,White,30,30,&strip);

AnimWithBeat AnimHeart(&Coracao,0,White,White,corCoracao,7,80,&strip);


//Anim AnimCoracao(&Coracao,0,White,White,corCoracao,30,80,&strip);
Anim AnimApagaCoracao(&Coracao,0,White,corCoracao,White,30,30,&strip);

Anim2 totalBeco(&AnimBeco,(Anim*)&AnimHeart);
Anim2 totalApagaBeco(&AnimApagaBeco,&AnimApagaCoracao);


tempo n1Timer(80);

// sensor objects initialization
remRead2 reciever;
sensorRemoto sensorTelma(&reciever,1),sensorBeco(&reciever,3);


void setup() {
  startAll(14,White.toUint32(),&strip);
  delay(2000);
  Serial.begin(9600);
  delay(100);
}



void loop() {

n1Timer.start();

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

/* if(!totalBeco.runStep()&&!totalApagaBeco.runStep()){ 

   if(sensorBeco.checkSensor()) {
     if(!totalBeco.justFinished){ 
        totalBeco.begin();
        totalBeco.justFinished=true;
     }
   }
   
   else if(totalBeco.justFinished) {
      totalApagaBeco.begin();
      totalBeco.justFinished=false;
    }
  }*//*
 if(!AnimBeco.runStep()&&!AnimApagaBeco.runStep()){ 

    if(sensorBeco.checkSensor()){
     if(!AnimBeco.justFinished){ 
        AnimBeco.begin();
        AnimBeco.justFinished=true;
     } else {
       AnimApagaBeco.begin();
       AnimBeco.justFinished=false;
     }
   }
  }*/
 if(!totalBeco.runStepNonStop()&&!totalApagaBeco.runStep()){ 

    if(sensorBeco.checkSensor()){
     if(!totalBeco.justFinished){ 
        totalBeco.begin();
        totalBeco.justFinished=true;
     } else {
       totalBeco.isRunning=0;
       totalApagaBeco.begin();
       totalBeco.justFinished=false;
     }
   }
  }

n1Timer.correctedDelay();
}
