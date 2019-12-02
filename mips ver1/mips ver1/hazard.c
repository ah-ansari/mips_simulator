#include"headers.h"

void forwardingUnit(struct exMem exMemReg, struct idEx idExReg, struct memWb memWbReg, int *outputRs, int *outputRt)
{
	// ex hazard
	if ((exMemReg.oldCtlWb[0]) && (binToDecUnsigned(exMemReg.oldMuxOut, 5) != 0) && (binToDecUnsigned(exMemReg.oldMuxOut, 5) == (binToDecUnsigned(idExReg.oldRegRead1, 5)))){
		outputRs[0] = 1;
		outputRs[1] = 0;
	}
	// mem Hazard
	else if ((memWbReg.oldWb[0]) && (binToDecUnsigned(memWbReg.oldWriteRegister, 5) != 0) && (binToDecUnsigned(memWbReg.oldWriteRegister, 5) == binToDecUnsigned(idExReg.oldRegRead1, 5)) &&
		!((exMemReg.oldCtlWb[0]) && (binToDecUnsigned(exMemReg.oldMuxOut, 5) != 0) && (binToDecUnsigned(exMemReg.oldMuxOut, 5) == (binToDecUnsigned(idExReg.oldRegRead1, 5))))){
		outputRs[0] = 0;
		outputRs[1] = 1;
	}
	else{
		outputRs[0] = 0;
		outputRs[1] = 0;
	}

	//	Ex hazard
	if ((exMemReg.oldCtlWb[0]) && (binToDecUnsigned(exMemReg.oldMuxOut, 5) != 0) && (binToDecUnsigned(exMemReg.oldMuxOut, 5) == (binToDecUnsigned(idExReg.oldRegRead2, 5)))){
		outputRt[0] = 1;
		outputRt[1] = 0;
	}
	//	mem hazard
	else if ((memWbReg.oldWb[0]) && (binToDecUnsigned(memWbReg.oldWriteRegister, 5) != 0) && (binToDecUnsigned(memWbReg.oldWriteRegister, 5) == binToDecUnsigned(idExReg.oldRegRead2, 5)) &&
		!((exMemReg.oldCtlWb[0]) && (binToDecUnsigned(exMemReg.oldMuxOut, 5) != 0) && (binToDecUnsigned(exMemReg.oldMuxOut, 5) == (binToDecUnsigned(idExReg.oldRegRead2, 5))))){
		outputRt[0] = 0;
		outputRt[1] = 1;
	}
	else{
		outputRt[0] = 0;
		outputRt[1] = 0;
	}

	return;
}

//hazardDetectionOut-->pcWrite,IF/DWrite,muxSelect
void hazardDetect(struct idEx idExReg, int *instruction, int *hazardDetectionOut){
	int lw[] = { 1, 0, 0, 0, 1, 1 };
	if (idExReg.oldCtlM[1] == 1){
		//the instruction in ex is lw
		if (isEqual(instruction, lw, 6)){
			if (isEqual(idExReg.oldInstruction_2016, instruction + 6, 5)){
				//	lw with hazard
				hazardDetectionOut[0] = 0;
				hazardDetectionOut[1] = 0;
				hazardDetectionOut[2] = 1;
				return;
			}
		}
		else if (isEqual(idExReg.oldInstruction_2016, instruction + 6, 5) || isEqual(idExReg.oldInstruction_2016, instruction + 11, 5)){
			// sw or rtype with hazard
			hazardDetectionOut[0] = 0;
			hazardDetectionOut[1] = 0;
			hazardDetectionOut[2] = 1;
			return;
		}
	}
	// normal insttruction (without hazard)
	hazardDetectionOut[0] = 1;
	hazardDetectionOut[1] = 1;
	hazardDetectionOut[2] = 0;
	return;
}


