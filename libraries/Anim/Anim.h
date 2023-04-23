// common colors and color animations

class Cor {
public:
uint8_t red;
uint8_t green;
uint8_t blue;

	Cor(uint8_t vermelho,uint8_t verde,uint8_t azul){
		red=vermelho;
		green=verde;
		blue=azul;
	}
	
	uint32_t toUint32(){
		return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
	}

	Cor(uint32_t Color){
		red =(uint8_t)(Color>>16 & 0xff);
		green = (uint8_t)(Color>>8 & 0xff);
		blue = (uint8_t)(Color & 0xff);
	}
	Cor(){
		red=0;
		green=0;
		blue=0;
	}

};

Cor White(90,65,65);
Cor corTelma(240,65,65);
Cor corDiogo(0,40,240);
Cor corBeco(65,240,65);
Cor corcoracao(240,40,0); 

// Class to create a Mask for the affected pins in each strip
 
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

// the final Animation object that recieves colors and Masks to then animate

class Anim {
  public:
	Masc* mascara;
	uint16_t intrevalo;
	Cor corBase,corStart,corEnd;
	int Diff[3];
	
	uint8_t numsteps;
	Adafruit_NeoPixel* fita;
	uint8_t currentStep=0;
	bool justFinished=0;
	
	void setColorDiff(){
		Diff[0]=(corEnd.red-corStart.red);
		Diff[1]=(corEnd.green-corStart.green);
		Diff[2]=(corEnd.blue-corStart.blue);
	}

	uint32_t frameColor(){
		float factor = (float)currentStep/numsteps;
		
		uint8_t vermelho =(uint8_t)((float)corStart.red+(Diff[0]*factor));
		uint8_t verde =(uint8_t)((float)corStart.green+(Diff[1]*factor));
		uint8_t azul =(uint8_t)((float)corStart.blue+(Diff[2]*factor));
   
		return Cor(vermelho,verde,azul).toUint32();
	}
	

	Anim(Masc* masc,uint16_t intreval,Cor cordebase,Cor corInicial,Cor corFinal,uint8_t numerodesteps,Adafruit_NeoPixel* strips){
		mascara=masc;
		intrevalo=intreval;
		corBase=cordebase;
		corStart=corInicial;
		corEnd=corFinal;
		numsteps = numerodesteps;
		fita=strips;
		setColorDiff();
	}

	void ApplyMask(uint32_t color){
		for(uint16_t i=0;i<mascara->numPin;i++){
			fita->setPinTony(mascara->pin[i]);
			fita->fill(corBase.toUint32(),0,149);

			if(mascara->pos[i][0]==255) fita->fill(color,0,149);			
			else for(byte j=0;j<mascara->size[i];j++){
				fita->setPixelColor((uint16_t)mascara->pos[i][j],color);
			}
			fita->show();
		}
	}

	bool runStep(){
		if(currentStep<=numsteps){
			this->ApplyMask(frameColor());
			currentStep++;
			return 1;
		} else return 0;
	}

	void run(){
		begin();
		while(runStep()){
			delay(intrevalo);	
		}
	}
	
	void begin(){
		currentStep=0;
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
    strips->show();
  }

}







