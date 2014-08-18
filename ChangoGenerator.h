#ifndef _CHANGO_H_
#define _CHANGO_H_

#include "mahalo.h"
#include "SampleSource.h"
#include "NonZeroMixer.h"
#include "ChangoGlobal.h"
class ChangoGenerator{

  protected:

    SampleSource *srcs[NUM_WAVES];
    SampleMixer *mixer;

  public:
    /*Will have NUM_SRCS entries*/
    virtual float render(float scale) = 0;
    virtual void update(float *vals) = 0;
    virtual void tune(long which, float freq) = 0;
    virtual ~ChangoGenerator(){};
};
#endif
