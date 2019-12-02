#include"headers.h"
int dataMemory[64][8]= { 0 };

void memoryFunction(int* address,int* writeData,int memRead,int memWrite,int *readData)
{
	if(memWrite==1){
		binCopy(writeData,dataMemory[binToDecUnsigned(address,32)],8);
		binCopy(writeData+8, dataMemory[binToDecUnsigned(address, 32)+1], 8);
		binCopy(writeData+16, dataMemory[binToDecUnsigned(address, 32)+2], 8);
		binCopy(writeData+24, dataMemory[binToDecUnsigned(address, 32)+3], 8);
	}
	if(memRead==1){
			binCopy(dataMemory[binToDecUnsigned(address,32)],readData,32);
	}
}

int and_1Bit(int s1, int s2)
{
	return s1 & s2;
}

void initialDataMemory(char fileName[]){
	FILE *input = fopen(fileName, "r");
	char c;
	int i=0;
	int j=0;
	while ((c = getc(input)) != EOF){
		if (c != '\n'){
				dataMemory[i][j] = c-'0';
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

void printDataMemory(){
	FILE *file = fopen("memoryFileDisplay.txt", "w");
	int i, j;

	for (int i = 0; i <64 ; i++){
		for (int j = 0; j < 8; j++)
			fprintf(file, "%d", dataMemory[i][j]);
		fprintf(file, "\n");
	}

	fclose(file);

	return;
}

