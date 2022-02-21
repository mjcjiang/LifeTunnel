#include <iostream>
#include "message_packing.h"

using namespace std;

// various bits for floating point types--
// varies for different architectures
typedef float float32_t;
typedef double float64_t;

int main(int argc, char **argv) {
    /*
    float f = 3.1415926, f2;
    double d = 3.14159265358979323, d2;
    uint32_t fi;
    uint64_t di;

    fi = pack754_32(f);
    f2 = unpack754_32(fi);

    di = pack754_64(d);
    d2 = unpack754_64(di);

    printf("float before : %.7f\n", f);
    printf("float encoded: 0x%08" PRIx32 "\n", fi);
    printf("float after : %.7f\n\n", f2);

    printf("double before : %.20lf\n", d);
    printf("double encoded: 0x%016" PRIx64 "\n", di);
    printf("double after : %.20lf\n", d2);
    */
    
    unsigned char buf[1024];
    unsigned char *buf_index = buf;
    int8_t magic;
    int16_t monkeycount;
    int16_t packetsize;

    packetsize = pack(buf_index, "ch", (int8_t)'g', (int16_t)-12);
    printf("packet is %" PRId32 " bytes\n", packetsize);
    unpack(buf, "ch", &magic, &monkeycount);
    printf("%d\n", magic);
    printf("%d\n", monkeycount);
    return 0;
}