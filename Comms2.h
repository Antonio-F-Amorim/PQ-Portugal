
class remRead2 {
  
public:

  remRead2(){
    pinMode(A4,INPUT);
    pinMode(A5,INPUT);
  }


  byte read(){
    byte pinStatus=(PINC & B00110000);
    
    if( pinStatus = B00110000 ) {
      return 3;
    } else if (pinStatus = B00100000){
      return 2;
    } else if (pinStatus = B00010000){
      return 1;
    }
    else return 0;
  }  

};

class remWrite2 {
public:

  remWrite2(){
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
  }

  void write(byte val){
    switch(val){
      case 1: { PORTB = PORTB | B00000010;break;}
      case 2: {PORTB | B00000001;break;}
      case 3: {PORTB = PORTB | B00000011;break;}
      default:break;

    }
  }
};

