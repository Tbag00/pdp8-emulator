#include <stdint.h>
#include <stdio.h>

typedef uint16_t uint12_t;  // Tipo base a 16 bit, limitato a 12 bit

#define UINT12_MAX 0xFFF  // Massimo valore a 12 bit
#define UINT12(value) ((value) & UINT12_MAX)  // Maschera automatica
