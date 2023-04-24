
class remRead2 {
  
public:
  bool status[3]={0,0,0};
  remRead2(){
    pinMode(A0,INPUT);
    pinMode(A1,OUTPUT);
    digitalWrite(A1,LOW);
  }
  
  bool isMessageAvailable(){
     if(digitalRead(A0)==HIGH) return true;
     return false;
  }
  
  

  void recieve(){
	digitalWrite(A1,HIGH);
        delayMicroseconds(500);
        for(byte i=0;i<3;i++){
		status[i]=digitalRead(A0);
		delayMicroseconds(1000);
	}
	digitalWrite(A1,LOW);
  }

	bool update(){
		if(isMessageAvailable()) {
			recieve();
			return true;
		}
		else return false;
	}

  bool read(byte val){
	if(val==0) return (!status[0]&&!status[1]&&!status[2]);
	return status[val-1];
  }  

/*  void printStatus(){
	Serial.print(" ");
	for(byte i=0;i<3;i++){
			
			Serial.print(status[i]);
	}
	Serial.println();
  }*/

};

class remWrite2 {
public:
  bool status[3]={0,0,0};

  remWrite2(){
    pinMode(12,OUTPUT);
    pinMode(13,INPUT);
    digitalWrite(12,LOW);
  }

  void handShake(){
	digitalWrite(12,HIGH);
	while(digitalRead(13)==LOW){}
	return;
   }

   void write(byte val){
	if(val==0){
	        status[0]=true;
		status[1]=true;
		status[2]=true;
		send();
		return;
        }
	if(status[val-1]==true) return;
	status[val-1]=true;
	send();
   }

   void clear (byte val){
	if(val==0){
	        status[0]=false;
		status[1]=false;
		status[2]=false;
		send();
		return;
        }
	if(status[val-1]==false) return;
	status[val-1]=false;
	send();
   }

  void send(){
    handShake();
    for(byte i=0;i<3;i++){
	digitalWrite(12,status[i]);
	delayMicroseconds(1000);
    }
    digitalWrite(12,LOW);
	delay(1);
  }
};

