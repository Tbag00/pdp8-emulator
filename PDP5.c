#include <stdlib.h>
#include <stdint.h>
#include "header.h"
#include <stdbool.h>

//#define BIG_MEMORY

typedef struct 
{
    uint12_t AC; //accumulatore
    //int MQ;
    uint12_t MB; //memory buffer (tiene i contenuti)
    uint12_t MA; //memory address
    uint12_t PC; //program counter
    uint4_t IR; //3 bit per indirizzo 1 per diretto/indiretto (instruction register)

    bit L; //link vedere se cambiare il tipo
}CPU;



#ifdef BIG_MEMORY
    uint12_t memoria[4096]; 
#else
    uint12_t memoria[1024]; 
#endif
//memoria[0] usata come program counter
//memoria[1] copia il PC dopo interrupt
//memoria[2] salva la prima istruzione da eseguire dop interrupt 
//memoria[10]->memoria[17] autoindexing (da vedere cos'è,nel dubbio non si deve usare)

void p(CPU *pCpu){
    pCpu->MB = memoria[0];
    //aggiungi di due se c'è l'istruzione di skip (DA IMPLEMENTARE)
    pCpu->MB++;
    memoria[0] = pCpu -> MB;

}
void fetch(CPU *pCpu, uint12_t* memoria ){
    pCpu->MA = pCpu->PC;//salvi indirizzo dal PC
    pCpu->MB = memoria[pCpu->MA];//metti nel memory buffer 
}
void cpu_execute(CPU *pCpu){
    
}

int main(){
    
    return 0;
}