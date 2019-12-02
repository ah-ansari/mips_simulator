#include <stdio.h>

void getFromInstructionMemory(int *pc,int *instruction);
void getFromInstructionMemory(int *pc);
int initialInstructionMemory(char fileName[]);
void intialPc(int value);
void registerFileWrite(int *writeRegister, int *writeData);
void registerFileRead(int *readRegister1, int *readRegister2, int *readData1, int *readData2);
int binToDecUnsigned(int *binArray,int len);
void binCopy(int * ref,int* dest,int len);
void signExtend(int *bits_16,int * bits_32);
void decToBin(int dec,int* bin);
int *Mux(int *value1,int *value2,int select);
int binToDecSigned(int *binArray,int len);
int isEqualToZero(int *array,int len);
int* incrementPc(int *pointer,int value);
void generateControlSignals(int *opcode,  int* executionStageSignal, int* memStageSignal, int* wbStageSignal);
void shiftLeftTwo(int* inArray);
void addTwo_32bit(int* value1, int* value2, int* result);
void generateAluControlSignals(int *function, int *aluOp, int *select);
int aluExecution(int *reg1, int* reg2,int *result, int* control);
void memoryFunction(int* address, int* writeData, int memRead, int memWrite, int *readData);
void initialDataMemory(char fileName[]);
void printIntArray(int * array, int size);
void refreshExMemReg(struct exMem * exMemReg);
void refreshIdExReg(struct idEx * idExReg);
void refreshIfReg(struct ifId * ifReg);
void refreshMemWbReg(struct memWb* reg);
int isEqual(int *a1, int *a2, int len);
void ifIdNewFlush(struct ifId *ifReg);
int* Mux4_1(int *value1, int *value2, int *value3, int *value4, int *select);
void forwardingUnit(struct exMem exMemReg, struct idEx idExReg, struct memWb memWbReg, int *outputRs, int *outputRt);
void hazardDetect(struct idEx idExReg, int *instruction, int *hazardDetectionOut);
void initialRegFile(char fileName[]);
void printDataMemory();
void printRegFile();
void decToBinSigned(int dec, int *bin);

struct ifId{
	int instructionNew[32];
	int instructionOld[32];
	int pcNew[32];
	int pcOld[32];
};

struct idEx{
	int newJalAddress[32];
	int oldJalAddress[32];
	int	newCtlWb[2];
	int	oldCtlWb[2];
	int newCtlM[3];
	int oldCtlM[3];
	int newCtlEx[4];
	int oldCtlEx[4];
	int newPc[32];
	int oldPc[32];
	int newReadData1[32];
	int oldReadData1[32];
	int newReadData2[32];
	int oldReadData2[32];
	int newSignExtend[32];
	int oldSignExtend[32];
	int newInstruction_2016[5];
	int oldInstruction_2016[5];
	int newInstruction_1511[5];
	int oldInstruction_1511[5];
	int newRegRead1[5];
	int oldRegRead1[5];
	int newRegRead2[5];
	int oldRegRead2[5];
};
struct exMem{
	int newJalAddress[32];
	int oldJalAddress[32];
	int	newCtlWb[2];
	int	oldCtlWb[2];
	int newCtlM[3];
	int oldCtlM[3];
	int newAdder[32];
	int oldAdder[32];
	int newAluZero;
	int oldAluZero;
	int newAluResult[32];
	int oldAluResult[32];
	int newReadData2[32];
	int oldReadData2[32];
	int newMuxOut[5];
	int oldMuxOut[5];
};


struct memWb{
	int newJalAddress[32];
	int oldJalAddress[32];
	int newWb[2];
	int oldWb[2];
	int newReadData[32];
	int oldReadData[32];
	int newAluResult[32];
	int oldAluResult[32];
	int newWriteRegister[5];
	int oldWriteRegister[5];
};