//
//  NonZeroMixer.h
//  PhotoChango
//
//  Created by Brandon Lucia on 6/25/14.
//  Copyright (c) 2014 Brandon Lucia. All rights reserved.
//

#ifndef PhotoChango_NonZeroMixer_h
#define PhotoChango_NonZeroMixer_h

#include "SampleSource.h"
#include "SampleMixer.h"

class NonZeroMixer : public SampleMixer{
  
  
public:
  NonZeroMixer();
  virtual bool Add(SampleSource *s);
  virtual SampleSource *Remove(unsigned i);
	virtual void Mix(int numSources, SampleSource **srcs, float *out);
  virtual void getNextSample(float *out);
  virtual void setAmpVal(float newamp);

  
};
#endif
