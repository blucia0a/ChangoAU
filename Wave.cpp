/*
 *  Wave.cpp
 *  Sin
 *
 *  Created by blucia0a on 8/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Wave.h"
#include <math.h>
#include <stdlib.h>
Wave::Wave(double frq, double srate, double amp = 1.0){
	
    //Sample rate is passed in from the HAL deviceInfo structure
    this->srate = srate;
	
    // initialize phase and de-zipper filters.
    phase = 0.0;
    //With 1Hz, we move by 2PI / srate radians per sample.  Every
    //srate samples, we've completed 1 second. Every srate
    //samples, we've completed 2PI/srate*srate = 2PI radians ==
    //a full cycle.
    //
    //With 440Hz, we move 440*2PI/srate radians per sample.  Every
    //srate samples, we've completed 1 second.  Every srate
    //samples, we've completed 440*2PI/srate*srate == 440*2PI radians
    //== 440 full cycles
    
    this->freqz = this->freq = frq * 2. * 3.14159265459 / srate; 
    this->ampz = this->amp = amp;
    this->callback = NULL;

}

void Wave::setCallback(void (*f)(Wave *, void *), void *cbd){

  this->callback = f;
  this->cbdata = cbd;

}

double Wave::getRate(){
  return this->srate;
}

void Wave::getNextSample(float *out){
	
  float wave = (float)sin(this->phase) * (float)this->ampz;  // generate sine wave
  this->phase = this->phase + this->freq;  // increment phase
  
  // write output
  out[0] = wave;	// left channel
  out[1] = wave;	// right channel
  
  // de-zipper controls
  this->ampz  = 0.001 * this->amp  + 0.999 * this->ampz;
  this->freqz = 0.001 * this->freq + 0.999 * this->freqz;

  if(this->callback != NULL){
    this->callback(this, this->cbdata);
  }

}

void Wave::setAmpVal(float val){
    this->amp = val;
}

void Wave::setFreqVal(double val){
    this->freq = val * 2. * 3.14159265359 / this->srate;
}

double Wave::getAmpVal(){
    return this->amp;
}

double Wave::getFreqVal(){
    return this->freq / 2. / 3.141592653589 * this->srate;
}
