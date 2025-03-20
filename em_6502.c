#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEMORY 65535
/*
stack-> 0x0100 a 0x1FF
zero page -> 0x0000 a 0x00FF
vettore di reset -> 0xFFFC e 0xFFFD
*/

struct CPU {
	uint8_t AC;//accumulatore
	uint8_t X;
	uint8_t Y;// X e Y usati per scorrere memoria
	uint16_t PC;// tiene indirizzo della prossima istruzione
	uint8_t P;//status register ogni bit è un flag
	uint8_t SP;// punta allo stack (infatti si chiama stack pointer) che sta tra  $0100 e $01FF.
};

uint8_t memoria[0x10000];

uint8_t read(uint16_t address) {//leggo la memoria
	return memoria[address];
}

void write(uint16_t address, uint8_t value) {
	 memoria[address] = value;
}

void set_zn_flags(struct CPU* cpu, uint8_t value) {
	if (value == 0)
		cpu->P |= (uint8_t)0x02; // flag che controllo che il numero sia 0 
	else
		cpu->P &= (uint8_t)~0x02; //se non è zero il flag rimane a zero faccio il not  bit a bit

	if (value & 0x80)//l'ultimo bit controlla se il numero è negativo
		cpu->P |= (uint8_t)0x80; // Set Negative flag 
	else
		cpu->P &= (uint8_t)~0x80; // Clear Negative flag
}

void cpu_execute(struct CPU* cpu) {
	uint8_t opcode = memoria[cpu->PC];//leggi opcode
	cpu->PC++;//incrementa program counter
    uint8_t value = 0x00;
	
	switch (opcode) {
	case 0xA9://LDA immediato carica valore in AC, immediato cioè che viene fatto subito utlizza lo stack mi pare(?)
        value = read(cpu->PC);
		cpu->PC++;
		cpu->AC = value;
		printf("LDA #$%02X\n", value);
		set_zn_flags(cpu, cpu->AC);
		break;
	case 0x00://BRK
		printf("emulatore fermato");
		exit(0);
		break;
    case 0x69://ADD immediato
        value = read(cpu->PC);
        cpu->PC++;
		cpu->AC += value;
       // cpu->AC = cpu->AC + (uint8_t)value;
        set_zn_flags(cpu, cpu->AC);
        break;
	default:
		printf("opcode sconosciuto");
		break;
	}
    
}



void reset(struct CPU* cpu) {
	cpu->X = 0;
	cpu->Y = 0;
	cpu->AC = 0;
	cpu->SP = 0xFD;
	cpu->P = 0x24;
	uint16_t lo = read(0xFFFC);//LSB low significat byte
	uint16_t hi = read(0xFFFD);//MSB most "         "
	cpu->PC = (uint16_t) (hi << 8) | lo;
}



int main() {
	struct CPU cpu;

	// Inizializza tutta la memoria a zero
	for (int i = 0; i < 65536; i++) {
		memoria[i] = 0;
	}


	// 0x8000: LDA #$01
	// 0x8002: BRK
	memoria[0x8000] = 0xA9; // LDA Immediate
	memoria[0x8001] = 0x01; // Valore immediato
    memoria[0x8002] = 0x69; // ADD immediato
    memoria[0x8003] = 0x05; // valore immediato
	memoria[0x8004] = 0x00; // BRK

	// Imposta il vettore di reset per partire da 0x8000
	memoria[0xFFFC] = 0x00;
	memoria[0xFFFD] = 0x80;

	// Resetta la CPU e inizia
	reset(&cpu);

	// Ciclo principale
	while (1) {
		cpu_execute(&cpu);
		printf("AC:%d\n", cpu.AC);
	}
	return 0;
}