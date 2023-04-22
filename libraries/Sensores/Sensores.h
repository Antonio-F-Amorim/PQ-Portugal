#include "Comms2.h"

class sensorPos {
public:
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
  }

  bool checkSensor(){
    digitalWrite(TriggerPin,HIGH);
    delayMicroseconds(10);
    
    digitalWrite(TriggerPin,LOW);
    long time = pulseIn(EchoPin,HIGH,18000);
    delayMicroseconds(200);
      
    if( time >min && time <max ) {
      return true;
    }
    else return false;

  }

  bool checkSensorAverage(){
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
  remWrite2* sender;

  public:
  sensorParteLocal(uint16_t trigger, uint16_t echo,long minimum, long maximum,remWrite2* writer,byte qual){
    TriggerPin=trigger;
    EchoPin=echo;
    min=minimum;
    max=maximum;
    id=qual;
    sender=writer;
    pinMode(TriggerPin,OUTPUT);
    pinMode(EchoPin,INPUT);
  }

  bool checkSensor(){
    digitalWrite(TriggerPin,HIGH);
    delayMicroseconds(10);
    
    digitalWrite(TriggerPin,LOW);
    long time = pulseIn(EchoPin,HIGH,16000);
    delayMicroseconds(200);
      
    if( time >min && time <max ) {
      sender->write(id);
      return true;
    } else {
	sender->clear(id);
	return false;
	}
  }
};


class sensorRemoto : sensorPos{
  public:
remRead2* reciever;

 sensorRemoto(remRead2* reader,byte qual){
   id=qual;
   reciever=reader;
 }

 bool checkSensor(){
   if(reciever->read(id)){ 
    return true;
   }

   else return false;
 }

};



    





