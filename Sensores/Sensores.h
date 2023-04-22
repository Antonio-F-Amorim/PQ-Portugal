#include "Comms2.h";



class sensorPos {
public:
  void Blink(){
    digitalWrite(LED_BUILTIN,HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN,LOW);
  }
  virtual bool checkSensor();
  byte id;

};

class sensorLocal: sensorPos{
  uint16_t TriggerPin,EchoPin;
  long min,max;

  public:
  sensorLocal(uint16_t trigger, uint16_t echo,long minimum, long maximum){
    TriggerPin=trigger;
    EchoPin=echo;
    min=minimum;
    max=maximum;
    pinMode(TriggerPin,OUTPUT);
    pinMode(EchoPin,INPUT);
   // #ifndef  built
    pinMode(LED_BUILTIN,OUTPUT);
   // #endif
    //#define Built;
  }

  bool checkSensor(){
    digitalWrite(TriggerPin,HIGH);
    delayMicroseconds(10);
    
    digitalWrite(TriggerPin,LOW);
    long time = pulseIn(EchoPin,HIGH,18000);
    delayMicroseconds(200);
      
    if( time >min && time <max ) {
      Blink();
      return true;
    }
    else return false;

  }

  bool checkSenorAverage(){
    for(byte i=0;i<3;i++){
       if (checkSensor()) return true;
       delay(10);
    }
    return false;
  }
};

class sensorParteLocal : sensorPos{
  uint16_t TriggerPin,EchoPin;
  long min,max;
  remWrite2* sensorRemoto;
  bool estado=false;

  public:
  sensorParteLocal(uint16_t trigger, uint16_t echo,long minimum, long maximum,remWrite2* rem,byte qual){
    TriggerPin=trigger;
    EchoPin=echo;
    min=minimum;
    max=maximum;
    id=qual;
    sensorRemoto=rem;
    pinMode(TriggerPin,OUTPUT);
    pinMode(EchoPin,INPUT);
   // #ifndef  built
    pinMode(LED_BUILTIN,OUTPUT);
   // #endif
    //#define Built;
  }

  bool checkSensor(){
    digitalWrite(TriggerPin,HIGH);
    delayMicroseconds(10);
    
    digitalWrite(TriggerPin,LOW);
    long time = pulseIn(EchoPin,HIGH,16000);
    delayMicroseconds(200);
      
    if( time >min && time <max ) {
      Blink();
      if(!estado) sensorRemoto->write(id);
      return true;
    }
    else { 
	estado=0;
	if(estado) sensorRemoto->write(id);
	return false;
	}
  }
};


class sensorRemoto : sensorPos{
  public:
remRead2 sensor;
 sensorRemoto(byte qual){
   id=qual;
   remRead2 sensor();
 }

 bool checkSensor(){
   if(sensor.read()==id){ 
    for(byte i=0;i<id+1;i++){
      Blink();
    }
    return true;
   }

   else return false;
 }

};



    





