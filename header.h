#include <stdint.h>
#include <stdio.h>

typedef uint16_t uint12_t;  // Tipo base a 16 bit, limitato a 12 bit
typedef uint8_t uint4_t;
typedef uint8_t bit;

#define UINT12_MAX 0xFFF  // Massimo valore a 12 bit
#define UINT4_MAX 0xF  // Massimo valore a 4 bit
#define BIT_MAX 0x1  // Massimo valore a un bit


#define UINT12(value) ((value) & UINT12_MAX)  // Maschera automatica


#define UINT4(value) ((value) & UINT4_MAX)  // Maschera automatica


#define BIT(value) ((value) & BIT_MAX)  // Maschera automatica

