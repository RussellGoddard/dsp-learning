//  main.cpp


#include <iostream>
#include "wave/decoder.hpp"

int main(int argc, const char * argv[]) {
    wave::decoderMain();
    std::cout << "Nothing crashed this time, remember to turn down the volume";
    return 0;
}
