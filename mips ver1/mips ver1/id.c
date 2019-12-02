#include <math.h>
#include"headers.h"
int regFile[32][32] = {0};


void registerFileRead(int *readRegister1,int *readRegister2, int *readData1, int *readData2)
{
	binCopy(regFile[binToDecUnsigned(readRegister1,5)],readData1,32);
	binCopy(regFile[binToDecUnsigned(readRegister2,5)],readData2,32);
}

void registerFileWrite( int *writeRegister, int *writeData)
{
	binCopy(writeData, regFile[binToDecUnsigned(writeRegister, 5)], 32);
}


void signExtend(int *bits_16,int * bits_32){
	int i;
	for(i=15;i>=0;i--)
		bits_32[i+16]=bits_16[i];
	for(i=15;i>=0;i--)
		bits_32[i]=bits_16[0];
}

// execution signal = 4 bits ->[0]:regDst [1]:aluOp0 [2]:aluOp1 [3]:aluSrc 
// memStageSignal = 3 bits  -> [0]:branch  [1]:memRead  [2]:memWrite 
// wbStageSignal = 2 bits  -> [0]regWrite [1]:memtoreg 

void generateControlSignals(int *opcode,  int* executionStageSignal, int* memStageSignal, int* wbStageSignal)
{
	if(opcode[5]==0 && opcode[4]==0 && opcode[3]==0 && opcode[2]==0 && opcode[1]==0 && opcode[0]==0) // R_FORMAT Instruction 
	{
		executionStageSignal[0]=1;  //regDst<= 1
		executionStageSignal[1]=0;	//aluOp0 <= 0
		executionStageSignal[2]=1;  //aluOp1 <= 1
		executionStageSignal[3]=0;  //aluSrc <= 0

		memStageSignal[0]=0;  //branch <=0
		memStageSignal[1]=0;  //memRead <= 0
		memStageSignal[2]=0;  //memWrite <= 0

		wbStageSignal[0]=1;   //regWrite <= 1
		wbStageSignal[1]=1;  //memtoreg <= 0
	}
	else if(opcode[5]==1 && opcode[4]==1 && opcode[3]==0 && opcode[2]==0 && opcode[1]==0 && opcode[0]==1) // LW Instruction 
	{
		executionStageSignal[0]=0;  //regDst<= 0
		executionStageSignal[1]=0;	//aluOp0 <= 0
		executionStageSignal[2]=0;  //aluOp1 <= 0
		executionStageSignal[3]=1;  //aluSrc <= 1

		memStageSignal[0]=0;  //branch <=0
		memStageSignal[1]=1;  //memRead <= 1
		memStageSignal[2]=0;  //memWrite <= 0

		wbStageSignal[0]=1;   //regWrite <= 1
		wbStageSignal[1]=0;  //memtoreg <= 0
	}
	else if(opcode[5]==1 && opcode[4]==1 && opcode[3]==0 && opcode[2]==1 && opcode[1]==0 && opcode[0]==1) // SW Instruction 
	{
		executionStageSignal[0]=0;  //regDst<= X
		executionStageSignal[1]=0;	//aluOp0 <= 0
		executionStageSignal[2]=0;  //aluOp1 <= 0
		executionStageSignal[3]=1;  //aluSrc <= 1

		memStageSignal[0]=0;  //branch <=0
		memStageSignal[1]=0;  //memRead <= 0
		memStageSignal[2]=1;  //memWrite <= 1

		wbStageSignal[0]=0;   //regWrite <= 0
		wbStageSignal[1]=0;  //memtoreg <= X
	}
	else if(opcode[5]==0 && opcode[4]==0 && opcode[3]==1 && opcode[2]==0 && opcode[1]==0 && opcode[0]==0) // branch 
	{
		executionStageSignal[0]=0;  //regDst<= X
		executionStageSignal[1]=1;	//aluOp0 <= 1
		executionStageSignal[2]=0;  //aluOp1 <= 0
		executionStageSignal[3]=0;  //aluSrc <= 0

		memStageSignal[0]=1;  //branch <=1
		memStageSignal[1]=0;  //memRead <= 0
		memStageSignal[2]=0;  //memWrite <= 0

		wbStageSignal[0]=0;   //regWrite <= 0
		wbStageSignal[1]=0;  //memtoreg <= X
	}
	if (opcode[5] == 0 && opcode[4] == 0 && opcode[3] == 0 && opcode[2] == 0 && opcode[1] == 0 && opcode[0] == 1) // No Op 
	{
		executionStageSignal[0] = 0;  //regDst<= 0
		executionStageSignal[1] = 0;	//aluOp0 <= 0
		executionStageSignal[2] = 0;  //aluOp1 <= 0
		executionStageSignal[3] = 0;  //aluSrc <= 0

		memStageSignal[0] = 0;  //branch <=0
		memStageSignal[1] = 0;  //memRead <= 0
		memStageSignal[2] = 0;  //memWrite <= 0

		wbStageSignal[0] = 0;   //regWrite <= 0
		wbStageSignal[1] = 0;  //memtoreg <= 0
	}
}

void initialRegFile(char fileName[])
{
	FILE *input = fopen(fileName, "r");
	char c;
	int i = 1;
	int j = 0;
	while ((c = getc(input)) != EOF){
		if (c != '\n'){
			regFile[i][j] = c - '0';
			j++;
		}
		else{
			i++;
			j = 0;
		}
	}

	fclose(input);
	return;
}

void printRegFile(){
	FILE *file = fopen("regFileDispaly.txt", "w");
	int i, j;

	for (int i = 1; i < 32; i++){
		for (int j = 0; j < 32; j++)
			fprintf(file, "%d", regFile[i][j]);
		fprintf(file,"\n");
	}
	fclose(file);

	return;
}


