#ifndef _WAVECHANGO_H_
#define _WAVECHANGO_H_
#include "ChangoGenerator.h"
#include "Wave.h"
class WaveChango : public ChangoGenerator{

  public:

    WaveChango(float rate);
    /*Will have NUM_SRCS entries*/
    virtual float render(float scale);
    virtual void update(float vals[]);
    virtual void tune(long which, float freq);
    virtual ~WaveChango();
};
#endif
