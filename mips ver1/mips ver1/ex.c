#include"headers.h"

void generateAluControlSignals(int *function, int *aluOp, int *select)
{
	if(aluOp[0]==0 && aluOp[1]==0){   // SW , LW
		select[0]=0;
		select[1]=1;
		select[2]=0;
		return;
	}
	if(aluOp[0]==1 && aluOp[1]==0){  //branch
		select[0]=1;
		select[1]=1;
		select[2]=0;
		return;
	}
	if(aluOp[0]==0 && aluOp[1]==1){
		if (function[5] == 0 && function[4] == 0 && function[3] == 0 && function[2] == 0)
		{ 	// ADD -> 010
			select[0] = 0;
			select[1] = 1;
			select[2] = 0;
			return;
		}
		if (function[5] == 0 && function[4] == 1 && function[3] == 0 && function[2] == 0)
		{	// AND -> 000
			select[0] = 0;
			select[1] = 0;
			select[2] = 0;
		
		}
		if (function[5] == 0 && function[4] == 1 && function[3] == 0 && function[2] == 1)
		{	// OR -> 001
			select[0] = 0;
			select[1] = 0;
			select[2] = 1;
			return;
		}
	}
	if (aluOp[1] == 1)
	{
		if (function[5] == 0 && function[4] == 1 && function[3] == 0 &&function[2]==0&& function[1] == 0 && function[0]==1)
		{  // SUBTRACT -> 110
			select[0] = 1;
			select[1] = 1;
			select[2] = 0;
			return;
		}
		if (function[5] == 1 && function[4] == 0 && function[3] == 1 && function[2] == 0)
		{	// SET ON LESS THAN   -> 111
			select[0] = 1;
			select[1] = 1;
			select[2] = 1;
			return;
		}
	}
	printf("hehehehhehheheheh\n");
	return;
}

int aluExecution(int *reg1, int* reg2,int *result, int* control)
{	
	// ADD -> 010
	if(control[0]==0 && control[1]==1 && control[2]==0){  
		decToBinSigned(binToDecSigned(reg1,32)+binToDecSigned(reg2,32),result);
		return (isEqualToZero(result,32));
	}
	// SUBTRACT -> 110
	if(control[0]==1 && control[1]==1 && control[2]==0){
		decToBinSigned(binToDecSigned(reg1,32)-binToDecSigned(reg2,32),result);
		return (isEqualToZero(result,32));
	}
	// AND -> 000
	if(control[0]==0 && control[1]==0 && control[2]==0){
		int i;
		for(i=0; i<32; i++)		
			result[i]=reg1[i]&reg2[i];	
		return (isEqualToZero(result,32));
	}
	// OR -> 001
	if(control[0]==0 && control[1]==0 && control[2]==1){
		int i;
		for(i=0; i<32; i++)		
			result[i]=reg1[i] | reg2[i];	
		return (isEqualToZero(result,32));
	}
	// SET ON LESS THAN   -> 111
	if(control[0]==1 && control[1]==1 && control[2]==1){
		if(binToDecSigned(reg1,32) < binToDecSigned(reg2,32))
			return 1;
		else 
			return 0;		
	}
	return 0;
}

void shiftLeftTwo(int* inArray)
{
	int i;
	for(i=0 ; i < 30 ; i++)
		inArray[i]=inArray[i+2];
	inArray[30]=0;
	inArray[31]=0;
}

void updatePc(int* pc,int* branchAmount , int* branchAddress)
{
	decToBin(binToDecUnsigned(pc,32)+binToDecUnsigned(branchAmount,32),branchAddress);
}

void addTwo_32bit(int* value1, int* value2, int* result)
{
	decToBinSigned(binToDecSigned(value1,32)+binToDecSigned(value2,32),result);
}


