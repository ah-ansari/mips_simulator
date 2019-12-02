#include"headers.h"


void refreshIdExReg(struct idEx * idExReg)
{
	int tmp[32];
	binCopy(idExReg->newInstruction_2016,tmp,5);
	binCopy(idExReg->oldInstruction_2016,idExReg->newInstruction_2016,5);
	binCopy(tmp,idExReg->oldInstruction_2016,5);
	
	binCopy(idExReg->newInstruction_1511,tmp,5);
	binCopy(idExReg->oldInstruction_1511,idExReg->newInstruction_1511,5);
	binCopy(tmp,idExReg->oldInstruction_1511,5);
	
	binCopy(idExReg->newPc,tmp,32);
	binCopy(idExReg->oldPc,idExReg->newPc,32);
	binCopy(tmp,idExReg->oldPc,32);
	
	binCopy(idExReg->newSignExtend,tmp,32);
	binCopy(idExReg->oldSignExtend,idExReg->newSignExtend,32);
	binCopy(tmp,idExReg->oldSignExtend,32);

	binCopy(idExReg->newReadData1,tmp,32);
	binCopy(idExReg->oldReadData1,idExReg->newReadData1,32);
	binCopy(tmp,idExReg->oldReadData1,32);

	binCopy(idExReg->newReadData2,tmp,32);
	binCopy(idExReg->oldReadData2,idExReg->newReadData2,32);
	binCopy(tmp,idExReg->oldReadData2,32);
	
	binCopy(idExReg->newCtlWb,tmp,2);
	binCopy(idExReg->oldCtlWb,idExReg->newCtlWb,2);
	binCopy(tmp,idExReg->oldCtlWb,2);

	binCopy(idExReg->newCtlM,tmp,3);
	binCopy(idExReg->oldCtlM,idExReg->newCtlM,3);
	binCopy(tmp,idExReg->oldCtlM,3);
	
	binCopy(idExReg->newCtlEx,tmp,4);
	binCopy(idExReg->oldCtlEx,idExReg->newCtlEx,4);
	binCopy(tmp,idExReg->oldCtlEx,4);

	binCopy(idExReg->newRegRead1, tmp, 5);
	binCopy(idExReg->oldRegRead1, idExReg->newRegRead1, 5);
	binCopy(tmp, idExReg->oldRegRead1, 5);

	binCopy(idExReg->newRegRead2, tmp, 5);
	binCopy(idExReg->oldRegRead2, idExReg->newRegRead2, 5);
	binCopy(tmp, idExReg->oldRegRead2, 5);

}