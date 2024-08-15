//  encoder.cpp
//  lesson from: https://mu.krj.st/wave/

#include "encoder.hpp"

// TODO: Replace this
std::string testOutputFileName = "output.wav";

void buildWavHeader(wave::wavHeader &header) {
    header = {
        /* RIFF header */
        .riff.id = {'R', 'I', 'F', 'F'},
        .riff.size = (36 + NSAMPLES * sizeof(bitDepth)),
        .riff.type = {'W', 'A', 'V', 'E'},
        
        /* FMT chunk */
        .fmt.id = {'f', 'm', 't', ' '},
        .fmt.size = 16,
        .fmt.fmt_tag = 1,  /* linear PCM */
        .fmt.channels = NCHANNELS,
        .fmt.samples_per_sec = SR,
        .fmt.bytes_per_sec = (NCHANNELS * SR * sizeof(bitDepth)),
        .fmt.block_align = (NCHANNELS * sizeof(bitDepth)),
        .fmt.bits_per_sample = (8 * sizeof(bitDepth)),
        
        /* DATA header */
        .data.id = {'d', 'a', 't', 'a'},
        .data.size = NSAMPLES * sizeof(bitDepth)
    };
}

void buildAudio(std::vector<bitDepth> &audio) {
    for (size_t i = 0; i < audio.size(); ++i) {
        audio[i] = lrint(SAMPLE_MAX*sin(2*M_PI * 440 * i/SR));
    }
}

int wave::encoderMain() {
    wave::wavHeader wavHeader;
    std::vector<bitDepth> audio(NSAMPLES);
    
    buildWavHeader(wavHeader);
    buildAudio(audio);
    
    std::ofstream outputFile(testOutputFileName, std::ios::out | std::ios::binary);
    if (outputFile.is_open()) {
        if (!outputFile.write(reinterpret_cast<char*>(&wavHeader), sizeof(struct wave::wavHeader))) {
            return -1;
        }
        
        if (!outputFile.write(reinterpret_cast<char*>(&audio[0]), sizeof(bitDepth) * audio.size())) {
            return -1;
        }
        
        /* 1 byte padding if buffer size is odd */
        if (sizeof(audio) % 2 == 1) {
            outputFile << '0';
        }
        
        outputFile.close();
    }

    return 0;
}
