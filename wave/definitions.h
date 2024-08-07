//
//  definitions.h
//  dsp-learning


#ifndef definitions_h
#define definitions_h

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* change output format here */
typedef int16_t bitDepth; // bit depth
#define SAMPLE_MAX 32767

#define DURATION 5
#define SR 44100
#define NCHANNELS 1
#define NSAMPLES (NCHANNELS*DURATION*SR)


#endif /* definitions_h */
