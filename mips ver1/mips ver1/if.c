#include <stdio.h>
#include "headers.h"

#define INSTRUCTION_MEMORY_SIZE 128 
int instructionMemory[INSTRUCTION_MEMORY_SIZE * 4][8]; // holds the instructions

void getFromInstructionMemory(int *pc,int *instruction)
{
	binCopy(instructionMemory[binToDecUnsigned(pc, 32)],instruction, 8);
	binCopy(instructionMemory[binToDecUnsigned(pc, 32) + 1],instruction + 8, 8);
	binCopy(instructionMemory[binToDecUnsigned(pc, 32) + 2],instruction + 16, 8);
	binCopy(instructionMemory[binToDecUnsigned(pc, 32) + 3],instruction + 24, 8);

	return ;
}

int initialInstructionMemory(char fileName[])
{
	FILE *file = fopen(fileName, "r");
	int i, j, k, m;
	i = j = k = m = 0;
	char c;
	while ((c = getc(file)) != EOF){
		if (c != '\n'){
			instructionMemory[i][j] = c - '0';
			j++;
		}
		else{
			j = 0;
			i++;
		}
	}

	fclose(file);

	return 0;
}

int*  incrementPc(int *pointer,int value){
	int tmp=binToDecUnsigned(pointer,32);
	tmp+=value;
	decToBin(tmp,pointer);
	return pointer;
}
