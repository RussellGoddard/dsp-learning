//  decoder.cpp
//  lesson from: https://mu.krj.st/wave/

#include "decoder.hpp"

static FILE *fileStream;
static bitDepth buffer[NSAMPLES];

int wave_init()
{
    struct wave::wavHeader header = {0};
    fileStream = fopen("output.wav", "wb");
    if (!fileStream) {
        return 0;
    }
    
    /* RIFF header */
    memcpy(&header.riff.id, "RIFF", 4);
    header.riff.size = 36 + NSAMPLES*sizeof(bitDepth);
    memcpy(&header.riff.type, "WAVE", 4);

    /* FMT chunk */
    memcpy(&header.fmt.id, "fmt ", 4);
    header.fmt.size = 16;
    header.fmt.fmt_tag = 1;  /* linear PCM */
    header.fmt.channels = NCHANNELS;
    header.fmt.samples_per_sec = SR;
    header.fmt.bytes_per_sec = NCHANNELS*SR*sizeof(bitDepth);
    header.fmt.block_align = NCHANNELS*sizeof(bitDepth);
    header.fmt.bits_per_sample = 8*sizeof(bitDepth);

    /* DATA header */
    memcpy(&header.data.id, "data", 4);
    header.data.size = NSAMPLES*sizeof(bitDepth);

    if (fwrite(&header, sizeof(struct wave::wavHeader), 1, fileStream) != 1) {
        fclose(fileStream);
        return 0;
    }
    return 1;
}

void wave_finish()
{
    fwrite(buffer, sizeof(buffer), 1, fileStream);
    /* 1 byte padding if buffer size is odd */
    if (sizeof(buffer) % 2 == 1) {
        char nil = 0;
        fwrite(&nil, 1, 1, fileStream);
    }
    fclose(fileStream);
}

int wave::decoderMain()
{
    size_t i;
    if (!wave_init())
    return 1;

    for (i = 0; i < NSAMPLES; ++i)
    buffer[i] = lrint(SAMPLE_MAX*sin(2*M_PI * 440 * i/SR));

    wave_finish();
    return 0;
}
