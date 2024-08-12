//  decoder.cpp
//  lesson from: https://mu.krj.st/assignments/wave_s.html

#include "decoder.hpp"


std::string fileName = "testFile.wav";

int wave::decoderMain() {
    struct wave::wavHeader input;
    std::ifstream inputFile(fileName, std::ios::in|std::ios::binary);
    std::vector<char> buffer(4);
//    std::streampos size;
    if (inputFile.is_open()) {
//        inputFile.seekg(0, inputFile.end); // set cursor at end of file
//        size = inputFile.tellg(); // return number of bytes into the file the cursor is aka the filesize.
//        inputFile.seekg(0, inputFile.beg); // return cursor to beginning of file
//        
//        buffer.resize(size); // now that we know the file size, resize our buffer
        
        // read the header check to see what the format is and file size
        inputFile.read(buffer.data(), 4);
        if (std::string(buffer.begin(), buffer.begin() + 4) != "RIFF") {
            return -1;
        }
        std::copy(buffer.begin(), buffer.begin() + 4, input.riff.id);
        buffer.clear();
        
        inputFile.read(buffer.data(), 4);
        input.riff.size = std::stoi(buffer.data());
        buffer.clear();
        
        inputFile.read(buffer.data(), 4);
        if (std::string(buffer.begin(), buffer.begin() + 4) != "WAVE") {
            return -2;
        }
        std::copy(buffer.begin(), buffer.begin() + 4, input.riff.type);
        buffer.clear();
        
        // read the format chunk
        inputFile.read(buffer.data(), 4);
        if (std::string(buffer.begin(), buffer.begin() + 4) != "fmt ") {
            return -3;
        }
        std::copy(buffer.begin(), buffer.begin() + 4, input.fmt.id);
        buffer.clear();
        
        inputFile.read(buffer.data(), 4);
        input.fmt.size = std::stoi(buffer.data());
        buffer.clear();
        
        inputFile.read(buffer.data(), 2);
        input.fmt.fmt_tag = std::stoi(buffer.data());
        buffer.clear();
        
        inputFile.read(buffer.data(), 2);
        input.fmt.channels = std::stoi(buffer.data());
        buffer.clear();
        
        inputFile.read(buffer.data(), 4);
        input.fmt.samples_per_sec = std::stoi(buffer.data());
        buffer.clear();
        
        inputFile.read(buffer.data(), 4);
        input.fmt.bytes_per_sec = std::stoi(buffer.data());
        buffer.clear();
        
        inputFile.read(buffer.data(), 2);
        input.fmt.block_align = std::stoi(buffer.data());
        buffer.clear();
        
        inputFile.read(buffer.data(), 2);
        input.fmt.bits_per_sample = std::stoi(buffer.data());
        buffer.clear();
        
        // read the data
        inputFile.read(buffer.data(), 4);
        if (std::string(buffer.begin(), buffer.begin() + 4) != "data") {
            return -4;
        }
        std::copy(buffer.begin(), buffer.begin() + 4, input.data.id);
        buffer.clear();
        
        inputFile.read(buffer.data(), 4);
        input.data.size = std::stoi(buffer.data());
        
        buffer.resize(input.data.size);
        inputFile.read(buffer.data(), buffer.size()); // buffer now contains the audio
        
        // handle padding
        
        inputFile.close();
    }
    
    return 0;
}
