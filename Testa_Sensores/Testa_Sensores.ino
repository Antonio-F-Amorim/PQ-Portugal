#include <Adafruit_NeoPixel.h>;
#include "Sensores.V.0.3.h";
#include "Anim.V.0.3.h";

Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);

sensorLocal ypshi;

remWrite2 sender;
sensorParteLocal sensorTelma(A0,A1,2000,8000,&sender,1),sensorEntrada(A2,A3,2000,8000,&sender,2),sensorBeco(A4,A5,2000,8000,&sender,3);

void setup() {:

}

void loop() {


}
