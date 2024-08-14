//  decoder.cpp
//  lesson from: https://mu.krj.st/assignments/wave_s.html

#include "decoder.hpp"

std::string testFileName = "output.wav";

int getAudio(std::string fileName, std::vector<char> &buffer, wave::wavHeader &wavInfo) {
    std::ifstream inputFile(fileName, std::ios::in | std::ios::binary);
    buffer.resize(4);
    if (inputFile.is_open()) {
        // read the header check to see what the format is and file size
        inputFile.read(buffer.data(), 4);
        if (std::string(buffer.begin(), buffer.begin() + 4) != "RIFF") {
            return -1;
        }
        std::copy(buffer.begin(), buffer.begin() + 4, wavInfo.riff.id);
        buffer.clear();
        
        inputFile.read(buffer.data(), 4);
        wavInfo.riff.size = (uint32_t)(buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24);
        buffer.clear();
        
        inputFile.read(buffer.data(), 4);
        if (std::string(buffer.begin(), buffer.begin() + 4) != "WAVE") {
            return -2;
        }
        std::copy(buffer.begin(), buffer.begin() + 4, wavInfo.riff.type);
        buffer.clear();
        
        // read the format chunk
        inputFile.read(buffer.data(), 4);
        if (std::string(buffer.begin(), buffer.begin() + 4) != "fmt ") {
            return -3;
        }
        std::copy(buffer.begin(), buffer.begin() + 4, wavInfo.fmt.id);
        buffer.clear();
        
        inputFile.read(buffer.data(), 4);
        wavInfo.fmt.size = (uint32_t)(buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24);
        buffer.clear();
        
        inputFile.read(buffer.data(), 2);
        wavInfo.fmt.fmt_tag = (uint16_t)(buffer[0] | buffer[1] << 8);
        buffer.clear();
        
        inputFile.read(buffer.data(), 2);
        wavInfo.fmt.channels = (uint16_t)(buffer[0] | buffer[1] << 8);
        buffer.clear();
        
        inputFile.read(buffer.data(), 4);
        wavInfo.fmt.samples_per_sec = (uint32_t)(buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24);
        buffer.clear();
        
        inputFile.read(buffer.data(), 4);
        wavInfo.fmt.bytes_per_sec = (uint32_t)(buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24);
        buffer.clear();
        
        inputFile.read(buffer.data(), 2);
        wavInfo.fmt.block_align = (uint16_t)(buffer[0] | buffer[1] << 8);
        buffer.clear();
        
        inputFile.read(buffer.data(), 2);
        wavInfo.fmt.bits_per_sample = (uint16_t)(buffer[0] | buffer[1] << 8);
        buffer.clear();
        
        // read the data
        inputFile.read(buffer.data(), 4);
        if (std::string(buffer.begin(), buffer.begin() + 4) != "data") {
            return -4;
        }
        std::copy(buffer.begin(), buffer.begin() + 4, wavInfo.data.id);
        buffer.clear();
        
        inputFile.read(buffer.data(), 4);
        wavInfo.data.size = (uint32_t)(buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24);
        std::cout << "data size" << std::endl;
        buffer.resize(wavInfo.data.size);
        inputFile.read(buffer.data(), buffer.size()); // buffer now contains the audio
        std::cout << "post data size" << std::endl;
        inputFile.close();
    }
    
    return 0;
}

int getFrequency(const std::vector<char> &audioBuffer, const wave::wavHeader &wavInfo) {
    // calculate 50ms of samples
    int sampleLength = wavInfo.fmt.samples_per_sec * 0.005;
    
    if (sampleLength == 0) {
        std::cerr << "Audio file not long enough" << std::endl;
        return -1;
    }
    
    std::vector<char> audioSample;
    std::vector<int> offsetDiff;
    
    // get 50ms of samples or the whole buffer if 50 ms doesn't exist
    if (wavInfo.data.size < sampleLength) {
        audioSample.resize(wavInfo.data.size);
        offsetDiff.resize(wavInfo.data.size);
        std::copy(audioBuffer.begin(), audioBuffer.begin() + wavInfo.data.size, audioSample.begin());
    } else {
        audioSample.resize(sampleLength);
        offsetDiff.resize(sampleLength);
        std::copy(audioBuffer.begin(), audioBuffer.begin() + sampleLength, audioSample.begin());
    }
    
    // offset by X samples
    int offset = 5;
    // find local minimum between normal audio and offset audio
    
    
    // once you find second local minimum calculate the frequency
    
    
    return -1;
}

int wave::decoderMain() {
    std::vector<char> buffer;
    struct wave::wavHeader wavInfo;
    
    int success = getAudio(testFileName, buffer, wavInfo);
    
    if (success != 0) {
        std::cerr << "Get Audio returned error: " + std::to_string(success) << std::endl;
    }
    

    // calculate period
    
    return 0;
}
