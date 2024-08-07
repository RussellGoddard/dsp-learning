// waveFormat.hpp

#ifndef waveFormat_h
#define waveFormat_h

#include <cstdint>
#include <cmath>

namespace wave {
    struct riffHeader {
        int8_t   id[4];
        std::uint32_t size;
        int8_t   type[4];
    };

    struct formatChunk {
        int8_t   id[4];
        std::uint32_t size;
        std::uint16_t fmt_tag;
        std::uint16_t channels;
        std::uint32_t samples_per_sec;
        std::uint32_t bytes_per_sec;
        std::uint16_t block_align;
        std::uint16_t bits_per_sample;
    };

    struct dataHeader {
        int8_t   id[4];
        std::uint32_t size;
    };

    struct wavHeader {
        struct riffHeader riff;
        struct formatChunk fmt;
        struct dataHeader data;
    };
}
#endif /* waveFormat_h */
