//  main.cpp


#include <iostream>
#include "wave/decoder.hpp"
#include "wave/encoder.hpp"

int main(int argc, const char * argv[]) {
    wave::encoderMain();
    std::cout << "Nothing crashed this time, remember to turn down the volume";
    return 0;
}
