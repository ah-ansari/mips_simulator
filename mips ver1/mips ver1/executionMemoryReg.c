#include "headers.h"



void refreshExMemReg(struct exMem * exMemReg)
{
	int tmp[32];
	binCopy(exMemReg->newCtlWb,tmp,2);
	binCopy(exMemReg->oldCtlWb,exMemReg->newCtlWb,2);
	binCopy(tmp,exMemReg->oldCtlWb,2);
	
	binCopy(exMemReg->newCtlM,tmp,3);
	binCopy(exMemReg->oldCtlM,exMemReg->newCtlM,3);
	binCopy(tmp,exMemReg->oldCtlM,3);

	binCopy(exMemReg->newAdder,tmp,32);
	binCopy(exMemReg->oldAdder,exMemReg->newAdder,32);
	binCopy(tmp,exMemReg->oldAdder,32);

	tmp[0]=exMemReg->newAluZero;
	exMemReg->newAluZero=exMemReg->oldAluZero;
	exMemReg->oldAluZero=tmp[0];

	binCopy(exMemReg->newAluResult,tmp,32);
	binCopy(exMemReg->oldAluResult,exMemReg->newAluResult,32);
	binCopy(tmp,exMemReg->oldAluResult,32);

	binCopy(exMemReg->newReadData2,tmp,32);
	binCopy(exMemReg->oldReadData2,exMemReg->newReadData2,32);
	binCopy(tmp,exMemReg->oldReadData2,32);

	binCopy(exMemReg->newMuxOut,tmp,5);
	binCopy(exMemReg->oldMuxOut,exMemReg->newMuxOut,5);
	binCopy(tmp,exMemReg->oldMuxOut,5);
}

