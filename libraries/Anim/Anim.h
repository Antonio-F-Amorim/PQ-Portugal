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

Cor White(75,52,52);
Cor corTelma(247,32,9);
Cor corDiogo(12,201,172);
Cor corBeco(100,0,166);
Cor corCoracao(240,40,0); 

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
	
	uint8_t numsteps,totalsteps;
	Adafruit_NeoPixel* fita;
	uint8_t currentStep=255;
	bool justFinished=0;
	
	void setColorDiff(){
		Diff[0]=(corEnd.red-corStart.red);
		Diff[1]=(corEnd.green-corStart.green);
		Diff[2]=(corEnd.blue-corStart.blue);
	}

	virtual uint32_t frameColor(){
		float factor;
		if(currentStep<=numsteps){
			factor = (float)currentStep/numsteps;
		} else factor=1;
		
		uint8_t vermelho =(uint8_t)((float)corStart.red+(Diff[0]*factor));
		uint8_t verde =(uint8_t)((float)corStart.green+(Diff[1]*factor));
		uint8_t azul =(uint8_t)((float)corStart.blue+(Diff[2]*factor));
   		
		if(currentStep>=253) currentStep=253;
		return Cor(vermelho,verde,azul).toUint32();
	}
	

	Anim(Masc* masc,uint16_t intreval,Cor cordebase,Cor corInicial,Cor corFinal,uint8_t numerodesteps,uint8_t numerototalsteps,Adafruit_NeoPixel* strips){
		mascara=masc;
		intrevalo=intreval;
		corBase=cordebase;
		corStart=corInicial;
		corEnd=corFinal;
		numsteps = numerodesteps;
		totalsteps=numerototalsteps;
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
		if(currentStep<=totalsteps){
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

class AnimWithBeat : public Anim{
public:


	AnimWithBeat(Masc* masc,uint16_t intreval,Cor cordebase,Cor corInicial,Cor corFinal
			,uint8_t numerodesteps,uint8_t numerototalsteps
			,Adafruit_NeoPixel* strips):Anim (masc,intreval,cordebase,corInicial
			,corFinal,numerodesteps,numerototalsteps,strips){}


	uint32_t frameColor() {
		if(currentStep>=253) currentStep=253;
		float factor;
		if(currentStep<=numsteps){
			factor = (float)currentStep/numsteps;
		} else if(currentStep<=(2*numsteps)){
			factor = 1.0;
		} else {
			factor= ( 1.0- ((float)(currentStep-numsteps*2))/numsteps);
		}
		
		uint8_t vermelho =(uint8_t)((float)corStart.red+(Diff[0]*factor));
		uint8_t verde =(uint8_t)((float)corStart.green+(Diff[1]*factor));
		uint8_t azul =(uint8_t)((float)corStart.blue+(Diff[2]*factor));
   		
		if(currentStep>=3*numsteps) currentStep=0;
		
		return Cor(vermelho,verde,azul).toUint32();
	}

};





class Anim2{
public:
Anim* first;
Anim* second;
bool justFinished=0;
bool isRunning=0;
	
	Anim2(Anim* primeiro,Anim* segundo){
		first=primeiro;
		second=segundo;
	}

	byte indexSamePin(uint16_t pin){
		for(uint16_t i=0;i<second->mascara->numPin;i++){
		if (second->mascara->pin[i]==pin) return i;
		}
		return 255;
	}

	void applyMasks(){
		for(uint16_t i=0;i<first->mascara->numPin;i++){
			uint16_t currentFirstPin =first->mascara->pin[i];
			uint32_t firstColor= first->frameColor();
			first->fita->setPinTony(currentFirstPin);
			first->fita->fill(first->corBase.toUint32(),0,149);

			if(first->mascara->pos[i][0]==255) first->fita->fill(firstColor,0,149);			
			else for(byte j=0;j<first->mascara->size[i];j++){
				first->fita->setPixelColor((uint16_t)first->mascara->pos[i][j],firstColor);
			}
			
			byte coincidentPin = indexSamePin(currentFirstPin);
			if(coincidentPin!=255){
				for(byte j=0;j<second->mascara->size[coincidentPin];j++){
					first->fita->setPixelColor((uint16_t)second->mascara->pos[coincidentPin][j],second->frameColor());
				}
			}


		first->fita->show();
		}
	}

	bool runStepNonStop(){
			if(isRunning){
				applyMasks();
				first->currentStep++;
				second->currentStep++;
				if(first->currentStep >= first->totalsteps) return false;
				return true;
			} else return false;
	}

	bool runStep(){
			if(first->currentStep<= first->totalsteps){
				applyMasks();
				first->currentStep++;
				second->currentStep++;
				return true;

			}else return false;
	}


	void begin(){
		isRunning=true;
		first->currentStep=0;
		second->currentStep=0;
		runStep();
	}
	
	void run(){
		begin();
		while(runStep()){
			delay(first->intrevalo);	
		}
	}



};

void startAll(uint16_t numPins,uint32_t cordebase,Adafruit_NeoPixel* strips){
  for(uint16_t i=0;i<numPins;i++){
    pinMode(i,OUTPUT);
  }
  strips->fill(cordebase,0,149);
    delay(500);
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

class tempo{
public:
unsigned long begining=0;
unsigned long finish=0;
unsigned long duration=0;

	tempo(unsigned long durac){
	duration=durac;
	}
	
	void start(){
	begining=millis();	
	}
		
	void correctedDelay(){
		finish=millis();
		unsigned long diff=finish-begining;
		if(diff>duration) return;
		delay(duration-(diff));
	}
	
};







