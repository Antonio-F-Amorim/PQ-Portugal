 
class Masc {
	public:
  byte numPin;	
	uint16_t *pin;
	byte* (*pos);
	byte *size;
	
	Masc(byte numpins,uint16_t *pins, byte **posic,byte * tamanho){
		numPin=numpins;
		pin=pins;
		pos=posic;
		size=tamanho;
	}
};

class Anim {
  public:
	Masc* mascara;
	uint16_t intrevalo;
	uint32_t corBase;
	uint32_t (*cor)(uint8_t step);
	uint8_t numsteps;
	Adafruit_NeoPixel* fita;
	byte currentStep=0;
	bool running=false;
	
	

	Anim(Masc* masc,uint16_t intreval,uint32_t cordebase,uint32_t (*funccores)(uint8_t),uint8_t numerodesteps,Adafruit_NeoPixel* strips){
		mascara=masc;
		intrevalo=intreval;
		corBase=cordebase;
		cor=funccores;
		numsteps = numerodesteps;
		fita=strips;
	}

	void ApplyMask(uint32_t color){
		for(uint16_t i=0;i<mascara->numPin;i++){
			fita->setPinTony(mascara->pin[i]);
			fita->fill(corBase,0,149);

			if(mascara->pos[i][0]==255) fita->fill(color,0,149);			
			else for(byte j=0;j<mascara->size[i];j++){
				fita->setPixelColor((uint16_t)mascara->pos[i][j],color);
			}
			fita->show();
		}
	}

	bool runStep(){
		if(running && currentStep<numsteps){
			this->ApplyMask(cor(currentStep));
			currentStep++;
			return 1;
		} else {
			running=0;
			currentStep=0;
			return 0;
		}
	}

	void run(){
		begin();
		while(runStep()){
			delay(intrevalo);	
		}
	}
	
	void begin(){
		running=true;
		runStep();
	}


};

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

void fillAll(uint16_t numPins,uint32_t cordebase,Adafruit_NeoPixel* strips){
  strips->fill(cordebase,0,149);

  for(uint16_t i=0; i<numPins; i++){
    strips->setPinTony(i);
    delay(10);
    strips->show();
    delay(10);
  }

}









