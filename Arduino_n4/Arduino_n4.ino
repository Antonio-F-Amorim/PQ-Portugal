#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

byte SINGLE_CYCLE_PLAY[8]={ 0x7E,0xFF,0x06,0x08,0x00,0x00,0x01,0xEF};
byte SELECT_SD[8] = {0x7E, 0xFF ,0x06, 0x09 ,0x00, 0x00, 0x02, 0xEF};
byte SET_VOLUME[8] = {0x7E,0xFF,0x06,0x06,0x00,0x00,0x1E,0xEF};
byte PLAY_FIRST[8] = {0x7E, 0xFF, 0x06, 0x03, 0x00, 0x00, 0x01, 0xEF};

SoftwareSerial  SoftSerial(12,13);
//rx -> 12 tx -> 13


Adafruit_NeoPixel strip(150,0, NEO_GRB + NEO_KHZ800);



void setup() {
  for(int i=1;i<12;i++){
  pinMode(i,OUTPUT);
  }
  delay(1000);
  strip.begin();
  strip.clear();
  strip.show();

  delay(100);
  SoftSerial.begin(9600);
  delay(100);
  SoftSerial.write(SELECT_SD,sizeof(SELECT_SD));
  
delay(100);
  SoftSerial.write(SET_VOLUME,sizeof(SET_VOLUME));

  delay(100);
 // SoftSerial.write(PLAY_FIRST,sizeof(PLAY_FIRST));
  SoftSerial.write(SINGLE_CYCLE_PLAY,sizeof(PLAY_FIRST));
  delay(100);

}

uint32_t cor= strip.Color(75,52,52);
uint32_t preto= strip.Color(80,80,80);

void loop() {
  strip.fill(cor,0,149);
  
  for (uint16_t i=0;i<12;i++){
  strip.setPinTony(i);
  strip.show();
  }
delay(1000);
}
