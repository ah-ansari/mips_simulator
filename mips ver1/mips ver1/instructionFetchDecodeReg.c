#include "headers.h"


void refreshIfReg(struct ifId * ifReg)
{	
	binCopy(ifReg->instructionNew,ifReg->instructionOld,32);
	binCopy(ifReg->pcNew,ifReg->pcOld,32);
}

//	assigning noOP to Ifid.newInstruction
void ifIdNewFlush(struct ifId *ifReg)
{
	int noOp[] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	binCopy(noOp, ifReg->instructionNew, 32);
	
	return;
}
