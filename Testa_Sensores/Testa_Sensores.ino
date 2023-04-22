#include <Adafruit_NeoPixel.h>
#include <Sensores.h>
#include <Anim.h>

Adafruit_NeoPixel strip(150,1, NEO_GRB + NEO_KHZ800);


remWrite2 sender;
sensorLocal sensorTelma(A0,A1,2000,8000),sensorEntrada(A2,A3,2000,8000),sensorBeco(A4,A5,2000,8000);

uint32_t branco= strip.Color(90,65,65);
uint32_t red= strip.Color(240,40,40);
uint32_t blue= strip.Color(40,40,240);
uint32_t green= strip.Color(40,240,40);


void setup() {
  startAll(12,branco,&strip);
  delay(1000);
}

void flash(uint32_t color){
    fillAll(12,color,&strip);
    delay(1000);
    fillAll(12,branco,&strip);
    delay(1000);
}

void loop() {
  if (sensorTelma.checkSensor())flash(red);
  if (sensorBeco.checkSensor()) flash(blue);
  if (sensorEntrada.checkSensor())flash(green);
  delay(100);

}
