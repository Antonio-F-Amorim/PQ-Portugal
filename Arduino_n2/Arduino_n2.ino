
#include <Adafruit_NeoPixel.h>
#include <Anim.h>
#include <Sensores.h>
#include "mascaraTelmaArduino2.h"
#include "mascaraBecoArduino2.h"

class Adafruit_NeoPixel;
// Led objects initialization
Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);



Anim AnimTelma(&Telma,0,White,White,corTelma,30,150,&strip);
Anim AnimApagaTelma(&Telma,0,White,corTelma,White,50,50,&strip);
Anim AnimBeco(&Beco,0,White,White,corBeco,30,80,&strip);
Anim AnimApagaBeco(&Beco,0,White,corBeco,White,30,30,&strip);

tempo n2Timer(80);

remWrite2 sender;
sensorParteLocal sensorTelma(A0,A1,2000,4650,&sender,1),sensorBeco(A4,A5,2000,8000,&sender,3);
//sensorParteLocal sensorTelma(A0,A1,2000,8000),sensorBeco(A4,A5,2000,8000);

void setup() {
  startAll(12,White.toUint32(),&strip);
  digitalWrite(12,LOW);
  delay(1000);
  

}



void loop() {

 n2Timer.start();
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

 /* 
 if(!AnimBeco.runStep()&&!AnimApagaBeco.runStep()){ 

  if(sensorBeco.checkSensor()){
     if(!AnimBeco.justFinished){ 
        AnimBeco.begin();
        AnimBeco.justFinished=true;
     }
   } else if(AnimBeco.justFinished) {
      AnimApagaBeco.begin();
      AnimBeco.justFinished=false;
    }
  }
*/
 if(!AnimBeco.runStep()&&!AnimApagaBeco.runStep()){ 

  if(sensorBeco.checkSensor()){
     if(!AnimBeco.justFinished){ 
        AnimBeco.begin();
        AnimBeco.justFinished=true;
        sender.clear(3);
     } else {
       AnimApagaBeco.begin();
       AnimBeco.justFinished=false;
       sender.clear(3);
     }
   }
  }

n2Timer.correctedDelay();
}
