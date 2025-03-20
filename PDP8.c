#include <stdlib.h>
#include <stdint.h>
#include "header.h"
#include <stdbool.h>

#define PDP8E


typedef struct MAJOR_REGISTER
{
    uint12_t AC;//accumulatore
    #ifdef PDP8E    
        uint12_t MQ;// solo per le moltiplicazioni
    #endif
    uint12_t MB;
    uint12_t CPMA;
    uint12_t PC;//program counter
    uint12_t MA;
    uint12_t DF;
    
}MJ;
 typedef struct REGISTER_CONTROL{
    bool LINK;//carry register (sugli shift e varie operazioni sull'AC viene incluso anche lui ) [?]
    uint8_t IR;//legge opcode, TODO: il registro è a 3 bit
    uint8_t MJR;//gestisce i processi di fetch,execute... etc
} REG_C;



int main(){
    return 0;
}