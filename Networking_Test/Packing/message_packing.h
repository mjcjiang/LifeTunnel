#include <stdint.h> // defines uintN_t types
#include <inttypes.h> // defines PRIx macros
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>

// various bits for floating point types--
// varies for different architectures
typedef float float32_t;
typedef double float64_t;

#define pack754_16(f) (pack754((f), 16, 5))
#define pack754_32(f) (pack754((f), 32, 8))
#define pack754_64(f) (pack754((f), 64, 11))
#define unpack754_16(i) (unpack754((i), 16, 5))
#define unpack754_32(i) (unpack754((i), 32, 8))
#define unpack754_64(i) (unpack754((i), 64, 11))

uint64_t pack754(long double f, unsigned bits, unsigned expbits);
long double unpack754(uint64_t i, unsigned bits, unsigned expbits);

void packi16(unsigned char *buf, unsigned int i);
void packi32(unsigned char *buf, unsigned long int i);
void packi64(unsigned char *buf, unsigned long long int i);

int unpacki16(unsigned char *buf);
unsigned int unpacku16(unsigned char *buf);

long int unpacki32(unsigned char *buf);
unsigned long int unpacku32(unsigned char *buf);

long long int unpacki64(unsigned char *buf);
unsigned long long int unpacku64(unsigned char *buf);

unsigned int pack(unsigned char *buf, const char *format, ...);
void unpack(unsigned char *buf, const char *format, ...);