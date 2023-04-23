#include <Adafruit_NeoPixel.h>



Adafruit_NeoPixel strip(150,0, NEO_GRB + NEO_KHZ800);



void setup() {
  for(int i=1;i<14;i++){
  pinMode(i,OUTPUT);
  }
  delay(1000);
  strip.begin();
  strip.clear();
  strip.show();

}

uint32_t cor= strip.Color(63,23,23);
uint32_t preto= strip.Color(80,80,80);

void loop() {
  strip.fill(cor,0,149);
  
  for (uint16_t i=0;i<14;i++){
  strip.setPinTony(i);
  strip.show();
  }
delay(1000);
}
