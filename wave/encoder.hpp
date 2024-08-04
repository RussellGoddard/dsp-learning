//
//  encoder.hpp
//  dsp-learning
//
//  Created by Frobu on 8/4/24.
//

#ifndef encoder_hpp
#define encoder_hpp

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// TODO: these defines should be put into a common header file
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

namespace wave {
    int encoderMain();
}

#endif /* encoder_hpp */
