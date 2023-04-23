
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

Anim AnimCoracao(&Coracao,0,White,White,corCoracao,60,&strip);
Anim AnimApagaCoracao(&Coracao,0,White,corCoracao,White,100,&strip);

Anim2 totalBeco(&AnimBeco,&AnimCoracao);
Anim2 totalApagaBeco(&AnimApagaBeco,&AnimApagaCoracao);



// sensor objects initialization
remRead2 reciever;
sensorRemoto sensorTelma(&reciever,1),sensorBeco(&reciever,3);


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

 if(!totalBeco.runStep()&&!totalApagaBeco.runStep()){ 

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
  }


delay(30);
}
