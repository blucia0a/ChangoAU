#include "WaveChango.h"
#include "Wave.h"
#include "tones.h"

static double tones[NUM_WAVES] = { C2, D2, E2, F2, G2,
                                   A2, B2, C3, D3, E3,
                                   F3, G3, A3, B3, C4,
                                   D4, E4, F4, G4, A4,
                                   B4, C5, D5, E5, F5};


WaveChango::WaveChango(float rate){


  //NonZeroMixer *s = new NonZeroMixer();
  mixer = new SampleMixer();
  for ( int i = 0; i < NUM_WAVES; i++ ){

    Wave *b = new Wave(tones[i], rate, 0.5);

    this->srcs[i] = b;
    mixer->Add(b);

  }
  
  

}

WaveChango::~WaveChango(){
    
}

float WaveChango::render(float scale){

    float ret[2];
    this->mixer->getNextSample(ret);
    return scale * ret[0];

}

void WaveChango::tune(long which, float freq){

    ((Wave*)this->srcs[which])->setFreqVal( freq );
    
}

void WaveChango::update(float *vals){

  for( int i = 0; i < NUM_WAVES; i++ ){
   
      this->srcs[i]->setAmpVal( vals[i] );
    
  }
  
}
