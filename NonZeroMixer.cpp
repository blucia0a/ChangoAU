//
//  NonZeroMixer.cpp
//  PhotoChango
//
//  Created by Brandon Lucia on 6/25/14.
//  Copyright (c) 2014 Brandon Lucia. All rights reserved.
//

#include "NonZeroMixer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
NonZeroMixer::NonZeroMixer() : SampleMixer(){
  
}

void NonZeroMixer::Mix(int numSources, SampleSource **srcs, float *out){
	
  unsigned numNonZero = 0;
	out[0] = 0.0f; //left
	out[1] = 0.0f; //right

  
	for(int i = 0; i < numSources; i++){


    float precision = 32767.;
		float o[2];
    srcs[i]->getNextSample(o);

    int sampL = o[0] * precision;
    int sampR = o[1] * precision;
    int aggL = out[0] * precision;
    int aggR = out[1] * precision;

    

    if( sampL < 0 && aggL < 0 ){
      
      aggL = aggL + sampL - ( (aggL * sampL) / -precision );
      
    }else if( aggL > 0 && sampL > 0 ){

      aggL = aggL + sampL - ( (aggL * sampL) / precision );
      
    }else{

      aggL = aggL + sampL;
      
    }
    
    out[0] = ((float)aggL) / precision;

    if( sampR < 0 && aggR < 0 ){
      
      aggR = aggR + sampR - ( (aggR * sampR) / -precision );
      
    }else if( aggR > 0 && sampR > 0 ){
      
      aggR = aggR + sampR - ( (aggR * sampR) / precision );
      
    }else{
      
      aggR = aggR + sampR;
      
    }
    
    out[1] = ((float)aggR) / precision;

    
    
  }
  
  //fprintf(stderr,"%f %f\n",out[0],out[1]);
	
  out[0] *= this->amp;
  out[1] *= this->amp;
  
  
}

void NonZeroMixer::getNextSample(float *out){
  this->Mix(this->numSources,this->srcs,out);
}

void NonZeroMixer::setAmpVal(float newamp){
  this->amp = newamp;
}

bool NonZeroMixer::Add(SampleSource *s){
  for(int i = 0; i < MIXER_MAX_SRCS; i++){
    if(this->srcs[i] == NULL){
      this->srcs[this->numSources++] = s;
      return true;
    }
  }
  return false;
}


SampleSource *NonZeroMixer::Remove(unsigned i){
  SampleSource *r = NULL;
  if(this->srcs[i] == NULL){
    r = this->srcs[i];
    this->srcs[i] = NULL;
  }
  return r;
}
