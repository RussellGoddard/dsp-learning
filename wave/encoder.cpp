//  encoder.cpp
//  dsp-learning
//  lesson from: https://mu.krj.st/wave/


#include "encoder.hpp"

struct riff_hdr {
    int8_t   id[4];
    uint32_t size;
    int8_t   type[4];
};

struct fmt_ck {
    int8_t   id[4];
    uint32_t size;
    uint16_t fmt_tag;
    uint16_t channels;
    uint32_t samples_per_sec;
    uint32_t bytes_per_sec;
    uint16_t block_align;
    uint16_t bits_per_sample;
};

struct data_hdr {
    int8_t   id[4];
    uint32_t size;
};

struct wav_hdr {
    struct riff_hdr riff;
    struct fmt_ck   fmt;
    struct data_hdr data;
};

static FILE *fp;
static bitDepth buf[NSAMPLES];

int wave_init()
{
    struct wav_hdr hdr = {0};
    fp = fopen("output.wav", "wb");
    if (!fp) {
        return 0;
    }
    
    /* RIFF header */
    memcpy(&hdr.riff.id, "RIFF", 4);
    hdr.riff.size = 36 + NSAMPLES*sizeof(bitDepth);
    memcpy(&hdr.riff.type, "WAVE", 4);

    /* FMT chunk */
    memcpy(&hdr.fmt.id, "fmt ", 4);
    hdr.fmt.size = 16;
    hdr.fmt.fmt_tag = 1;  /* linear PCM */
    hdr.fmt.channels = NCHANNELS;
    hdr.fmt.samples_per_sec = SR;
    hdr.fmt.bytes_per_sec = NCHANNELS*SR*sizeof(bitDepth);
    hdr.fmt.block_align = NCHANNELS*sizeof(bitDepth);
    hdr.fmt.bits_per_sample = 8*sizeof(bitDepth);

    /* DATA header */
    memcpy(&hdr.data.id, "data", 4);
    hdr.data.size = NSAMPLES*sizeof(bitDepth);

    if (fwrite(&hdr, sizeof(struct wav_hdr), 1, fp) != 1) {
        fclose(fp);
        return 0;
    }
    return 1;
}

void wave_finish()
{
    fwrite(buf, sizeof(buf), 1, fp);
    /* 1 byte padding if buf size is odd */
    if (sizeof(buf) % 2 == 1) {
        char nil = 0;
        fwrite(&nil, 1, 1, fp);
    }
    fclose(fp);
}

int wave::encoderMain()
{
    size_t i;
    if (!wave_init())
    return 1;

    for (i = 0; i < NSAMPLES; ++i)
    buf[i] = lrint(SAMPLE_MAX*sin(2*M_PI * 440 * i/SR));

    wave_finish();
    return 0;
}
