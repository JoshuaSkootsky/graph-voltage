// Joshua Skootsky 
// May 6,2015
// random64.c
// returns: a 64-bit random number in c
#include <stdint.h>

// Choices must conform with Hull-Dobell Theorem
// Specifically:
// rand_new = (mult * rand_old + add) mod m
// 1.  "add" cannot be zero
// 2.  "add" and "mult" must be relatively prime
// 3.  "add" - 1 must be divisible by all prime factors of "mult"
// 4.  "add"  must be a multiple of 4, if "mult" is a multiple of 4

static uint64_t rand64 = 2395040858963409; // seed for my RNG routine
static uint64_t add  = 1442695040888963407; // Knuth MMIX
static uint64_t mult =  6364136223846793005; // Knuth MMIX
static uint64_t MAXINT_U64 = 0xFFFFFFFFFFFFFFFF; // 16 Fs

// notes:
// 0xFFFFFFFFFFFFFFC5 = largest 64 bit prime
// 0xFFFFFFFFFFFFFFFF = largest 64 bit number (unsigned)

double random64() {
    // implictly  m = 64 bits by using uint64_t
    rand64 = mult * rand64 + add;
    return (double) rand64/ MAXINT_U64;
    // result should be between 0 and 1
}
