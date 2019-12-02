
/*
	Mips Simulator Ver : 1.00

		Written By:
			Ahmad Reza Ranjbar
			Hojjat Tabkhi
			Amir Hossein Ansari

		End Date:
			Tuesday 10 June 2014

		
*/



#include <stdio.h>
#include <math.h>
#include "windows.h"
#include"headers.h"

#define COLOR_RED 0xc
#define COLOR_BLUE 0x9
#define COLOR_AQUA 0xb
#define COLOR_YELLOW 0xe
#define COLOR_PURPLE 0xd
#define COLOR_WHITE 0xf

void refresh(struct ifId *ifIdReg, struct idEx *idExReg, struct exMem *exMemReg, struct memWb* memWbReg);
void startMenu();

int main()
{
	//	temp input
	char c; 
	//	stores clk
	int clk = 1;
	//	sotores the out put of the hazard detection unit 
	int hazardDetectOut[3] = { 1, 1, 0 };


	//	if var

	//	stores pc
	int pc[32] = { 0 }; // holds the address of coming instruction
	//	pc update mux select
	int pcSrc = 0;
	//	pc new result from mux
	int *pcUpdate = NULL;
	//	struct IfIdReg
	struct ifId ifIdReg = { 0 };
	//	the result of branch
	int  pcBranch[32];
	//decode var
	struct idEx idExReg = { 0 };
	int jalAdress[32];
	
	// execution var
	
	int aluInput1Select[2];
	int aluInput2Select[2];
	struct exMem exMemReg = { 0 };
	int shiftInput[32];
	int aluSelect[3];
	int  aluInput2[32];
	

	int writeBackData[32];

	// mem var
	struct memWb memWbReg = { 0 };

	//	get the handle to use SetConSoleStdHandle
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// initialize instruction memory
	initialInstructionMemory("instructions.txt");

	// initialize data memory
	initialDataMemory("dataMemory.txt");

	//initial regFile
	initialRegFile("regFile.txt");
	system("title MIPS SIMULATOR");
	startMenu();

	//an infinite loop
	while (1){
		printf("   * clock : %d\n\n", clk);
		//Hazard detection unit
		if (clk > 1){
			hazardDetect(idExReg, ifIdReg.instructionOld, hazardDetectOut);
		}
		// first stage
		//    Instruction fetch
		if (clk > 0){
			SetConsoleTextAttribute(handle,COLOR_YELLOW );
			printf("\n.......................... instruction fetch ..........................\n\n");
			if (hazardDetectOut[0] == 1 && hazardDetectOut[1] == 1){
				getFromInstructionMemory(pc, ifIdReg.instructionNew);
				printf("	pc          : "); printIntArray(pc, 32);
				binCopy(incrementPc(pc, 4), pc, 32);
				binCopy(pc, ifIdReg.pcNew, 32);
			}
			else{
				SetConsoleTextAttribute(handle, COLOR_RED);
				printf("	hazard detected. so pc and IF/ID is not updated .\n");
				SetConsoleTextAttribute(handle, COLOR_YELLOW);
			}
			printf("	new instruction comes into pipeline  .\n ");
			
			printf("	instruction : "); printIntArray(ifIdReg.instructionNew, 32);
			printf("	updating pc ....\n ");
			printf("	new pc      : "); printIntArray(pc, 32);
		}

		//	  Write Back
		if (clk > 4){
			//	write back mux
			if (memWbReg.oldWb[0])
			{			
				
				if (memWbReg.oldWb[1] == 0)
					binCopy(memWbReg.oldReadData,writeBackData,32);					
				else
					binCopy(memWbReg.oldAluResult,writeBackData,32);					

				registerFileWrite(memWbReg.oldWriteRegister, writeBackData); 
			}
		}

		//		Instruction decode
		if (clk > 1){
			SetConsoleTextAttribute(handle, COLOR_AQUA);
			
			printf("\n.......................... instruction decode ..........................\n\n");
			binCopy(ifIdReg.pcOld, idExReg.newPc, 32);
			registerFileRead(ifIdReg.instructionOld + 6, ifIdReg.instructionOld + 11, idExReg.newReadData1, idExReg.newReadData2);
			printf("	reading from register file ... \n");
			printf("	address 1 : "); printIntArray(ifIdReg.instructionOld + 6, 5);
			printf("	data 1    : "); printIntArray(idExReg.newReadData1, 32);
			printf("	address 2 : "); printIntArray(ifIdReg.instructionOld + 11, 5);
			printf("	data 2    : "); printIntArray(idExReg.newReadData2, 32);
			signExtend(ifIdReg.instructionOld + 16, idExReg.newSignExtend);
			printf("	sign extending ...");
			printf("	sign extending input : "); printIntArray(ifIdReg.instructionOld + 16, 16);
			printf("	sign extending output : "); printIntArray(idExReg.newSignExtend, 32);
			binCopy(ifIdReg.instructionOld + 11, idExReg.newInstruction_2016, 5);
			binCopy(ifIdReg.instructionOld + 16, idExReg.newInstruction_1511, 5);
			binCopy(ifIdReg.instructionOld + 6, idExReg.newRegRead1, 5);
			binCopy(ifIdReg.instructionOld + 11, idExReg.newRegRead2, 5);

			generateControlSignals(ifIdReg.instructionOld, idExReg.newCtlEx, idExReg.newCtlM, idExReg.newCtlWb);
			if (hazardDetectOut[2] == 1){
				//	hazard detected 
				idExReg.newCtlEx[0] = 0;
				idExReg.newCtlEx[1] = 0;
				idExReg.newCtlEx[2] = 0;
				idExReg.newCtlEx[3] = 0;

				idExReg.newCtlM[0] = 0;
				idExReg.newCtlM[1] = 0;
				idExReg.newCtlM[2] = 0;

				idExReg.newCtlWb[0] = 0;
				idExReg.newCtlWb[1] = 0;
				SetConsoleTextAttribute(handle, COLOR_RED);
				printf("	hazard is detected .\n");
				printf("	set the control signals to zero\n");
				SetConsoleTextAttribute(handle, COLOR_AQUA);
			}
			printf("	control signals generated ...\n");
			printf("	cltEx : "); printIntArray(idExReg.newCtlEx, 4);
			printf("	cltM  : "); printIntArray(idExReg.newCtlM, 3);
			printf("	cltWb : "); printIntArray(idExReg.newCtlWb, 2);

			// predicting branch
			binCopy(idExReg.newSignExtend, shiftInput, 32);
			shiftLeftTwo(shiftInput);
			printf("	shifting ...\n");
			printf("	shift input  : "); printIntArray(idExReg.oldSignExtend, 32);
			printf("	shift output : "); printIntArray(shiftInput, 32);
			addTwo_32bit(shiftInput, ifIdReg.pcOld, pcBranch);
			printf("	adder input1 : "); printIntArray(idExReg.oldPc, 32);
			printf("	adder input2 : "); printIntArray(shiftInput, 32);
			printf("	adder output : "); printIntArray(exMemReg.newAdder, 32);

			if (isEqual(idExReg.newReadData1, idExReg.newReadData2, 32) && idExReg.newCtlM[0])
			{
				SetConsoleTextAttribute(handle, COLOR_RED);
				printf("	branch happens...\n");
				// branch happens
				binCopy(pcBranch, pc, 32);
				// flushing the IfId
				ifIdNewFlush(&ifIdReg);
				printf("	IFIdreg Flushed\n");
			}
			/*
			//JAL
			if (ifIdReg.instructionOld[0] == 1 && ifIdReg.instructionOld[1] == 1 && ifIdReg.instructionOld[2] == 1 && ifIdReg.instructionOld[3] == 1 && ifIdReg.instructionOld[4] == 1 && ifIdReg.instructionOld[5] == 1){
				binCopy(ifIdReg.pcOld, jalAdress, 4);
				binCopy(ifIdReg.instructionOld + 6, jalAdress + 4, 26);
				jalAdress[30] = jalAdress[31] = 0;
				binCopy(jalAdress, idExReg.newJalAddress, 32);
			}
			*/
		}

		//   Instruction Execution
		if (clk > 2){
			SetConsoleTextAttribute(handle, COLOR_BLUE);
			printf("\n..........................  instruction execution ..........................\n\n");
			binCopy(idExReg.oldCtlWb, exMemReg.newCtlWb, 2);
			binCopy(idExReg.oldCtlM, exMemReg.newCtlM, 3);
			generateAluControlSignals(idExReg.oldSignExtend + 26, idExReg.oldCtlEx + 1, aluSelect);
			printf("	generateing alu control signals ... \n");
			printf("	alu control function  : "); printIntArray(idExReg.oldSignExtend + 26, 6);
			printf("	alu control operation : "); printIntArray(idExReg.oldCtlEx + 1, 2);
			printf("	alu control output    : "); printIntArray(aluSelect, 3);
			binCopy(Mux(idExReg.oldReadData2, idExReg.oldSignExtend, idExReg.oldCtlEx[3]), aluInput2, 32); // Mux 2_1
			//	forwarding unit is operating
			forwardingUnit(exMemReg,idExReg, memWbReg, aluInput1Select, aluInput2Select);
			printf("	forwarding unit is operating ...\n");
			printf("	EX/MEM.RegWrite   : %d\n",exMemReg.oldCtlWb[0]);
			printf("	EX/MEM.RegisterRd : "); printIntArray(exMemReg.oldMuxOut,5);
			printf("	ID/EX.RegisterRs  : "); printIntArray(idExReg.oldRegRead1, 5); 
			printf("	ID/EX.RegisterRt  : "); printIntArray(idExReg.oldRegRead2, 5);
			printf("	Forward A         : "); printIntArray(aluInput1Select, 2);

			printf("	MEM/WB.RegWrite   : %d\n", memWbReg.newWb[0] );
			printf("	MEM/WB.RegisterRd : "); printIntArray(memWbReg.oldWriteRegister, 5);
			printf("	ID/EX.RegisterRs  : "); printIntArray(idExReg.oldRegRead1, 5);
			printf("	ID/EX.RegisterRt  : "); printIntArray(idExReg.oldRegRead2, 5);

			printf("	Forward B         : "); printIntArray(aluInput2Select, 2);

			exMemReg.newAluZero = aluExecution( Mux4_1(idExReg.oldReadData1, writeBackData, exMemReg.oldAluResult, NULL, aluInput1Select), 
				Mux4_1(aluInput2, writeBackData, exMemReg.oldAluResult, NULL, aluInput2Select), exMemReg.newAluResult, aluSelect);
			
			printf("	alu is executing ... \n");
			printf("	alu input 1	: "); printIntArray(Mux4_1(idExReg.oldReadData1, writeBackData, exMemReg.oldAluResult, NULL, aluInput1Select), 32);
			printf("	alu input 2	: "); printIntArray(Mux4_1(aluInput2, writeBackData, exMemReg.oldAluResult, NULL, aluInput2Select), 32);
			printf("	alu result  : "); printIntArray(exMemReg.newAluResult, 32);
			printf("	alu zero    : %d\n", exMemReg.newAluZero);
			binCopy(Mux(idExReg.oldInstruction_2016, idExReg.oldInstruction_1511, idExReg.oldCtlEx[0]), exMemReg.newMuxOut, 5);
			printf("	select register file writing address : %d\n", idExReg.oldCtlEx[0]);
			printf("	destination address : "); printIntArray(exMemReg.newMuxOut, 5);

			binCopy(idExReg.oldReadData2, exMemReg.newReadData2, 32);
			printf("	read data 2 copied from Id/Ex to EX/Mem\n");

			binCopy(idExReg.oldJalAddress, exMemReg.newJalAddress, 32);/////////////////////////////////////////
		}

		//    Memory
		if (clk > 3){
			SetConsoleTextAttribute(handle, COLOR_WHITE);
			printf("\n.......................... Memory access ..........................\n\n");
			memoryFunction(exMemReg.oldAluResult, exMemReg.oldReadData2, exMemReg.oldCtlM[1], exMemReg.oldCtlM[2], memWbReg.newReadData);
			binCopy(exMemReg.oldAluResult, memWbReg.newAluResult, 32);
			binCopy(exMemReg.oldMuxOut, memWbReg.newWriteRegister, 5);
			binCopy(exMemReg.oldCtlWb, memWbReg.newWb, 2);
			printf("	memory is functioning ...\n");
			printf("	memory address      : "); printIntArray(exMemReg.oldAluResult, 32);
			printf("	memory write data   : "); printIntArray(exMemReg.oldReadData2, 32);
			printf("	memory read enable  : %d \n", exMemReg.oldCtlM[1]);
			printf("	memory write enable : %d \n", exMemReg.oldCtlM[2]);
			printf("	memory read data    : "); printIntArray(memWbReg.newReadData, 32);


			binCopy(exMemReg.oldJalAddress, memWbReg.newJalAddress, 32);/////////////////////////////////////////
			}
		if (clk > 4){
			SetConsoleTextAttribute(handle, COLOR_PURPLE);
			printf("\n.......................... Write Back ..........................\n\n");
			printf("	write back or not : %d\n", memWbReg.oldWb[0]);
			printf("	mux select        : %d\n", memWbReg.oldWb[1]);
			printf("	mux input 0 (write data0) : "); printIntArray(memWbReg.oldReadData, 32);
			printf("	mux input 1 (write data1) : "); printIntArray(memWbReg.oldAluResult, 32);
			printf("	write address     : "); printIntArray(memWbReg.oldWriteRegister, 5);
		}

		printDataMemory();
		printRegFile();

		while ((c = getchar()) != '\n')
			;
		clk++;
		system("cls");
		refresh(&ifIdReg, &idExReg, &exMemReg, &memWbReg);
	}
	return 0;
}

void refresh(struct ifId *ifIdReg, struct idEx *idExReg, struct exMem *exMemReg, struct memWb* memWbReg)
{
	refreshIfReg(ifIdReg);
	refreshIdExReg(idExReg);
	refreshExMemReg(exMemReg);
	refreshMemWbReg(memWbReg);

	return;
}


void startMenu()
{

	printf("\n\n");
	printf("              In the Name Of the first Architect   \n\n\n\n");
	system("color 0d");
	printf("	88b           d88 88                            \n");
	printf("	888b         d888 ""                            \n");
	printf("	88`8b       d8'88                               \n");
	printf("	88 `8b     d8' 88 88 8b,dPPYba,  ,adPPYba,      \n");
	printf("	88  `8b   d8'  88 88 88P'    \"8a I8[""		    \n");
	printf("	88   `8b d8'   88 88 88       d8  `\"Y8baa,     \n");
	printf("	88    `888'    88 88 88b, , a8\"   aaa]8Ia      \n");
	printf("	88     `8'     88 88 88`YbbdP\"'  `\"YbbdP\"'   \n");
	printf("			     88                         \n");
	printf("			     88                         \n");


	printf("\n\n\t\t Mips Simulator ver: 1.00 \n");
	printf("\t\t        Written By : \n");
	printf("\t\t                   Ahmad Reza Ranjbar\n");
	printf("\t\t                   Hojjat Tabkhi\n");
	printf("\t\t                   Amir Hossein Ansari\n");
	
	printf("\n\n   press enter to start ...");
	getchar();
	system("cls");
	return;
}