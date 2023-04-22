#include<Adafruit_NeoPixel.h>;

Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);

void startAll(uint16_t numPins,uint32_t cordebase,Adafruit_NeoPixel* strips){
  for(uint16_t i=0;i<numPins;i++){
    pinMode(i,OUTPUT);
  }
  strips->fill(cordebase,0,149);

  for(uint16_t i=0; i<numPins; i++){
    strips->setPinTony(i);
    delay(10);
    strips->show();
    delay(10);
  }
}

void setup() {
  startAll(14,strip.Color(80,80,80),&strip);

  delay(100);

}

void loop() {
  strip.fill(125,0,149);
  for (int i=0;i<14;i++){
    strip.setPinTony(i);
    strip.show();
    delay(1000);
  }
  strip.fill(strip.Color(80,80,80),0,149);
    for (int i=0;i<14;i++){
    strip.setPinTony(i);
    strip.show();
  }
  delay(1000);
}
