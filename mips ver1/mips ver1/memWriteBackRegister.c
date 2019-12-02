#include "headers.h"



void refreshMemWbReg(struct memWb* reg)
{
	int tmp[32];

	binCopy(reg->newWb, tmp, 2);
	binCopy(reg->oldWb, reg->newWb, 2);
	binCopy(tmp, reg->oldWb, 2);

	binCopy(reg->newReadData, tmp, 32);
	binCopy(reg->oldReadData, reg->newReadData, 32);
	binCopy(tmp, reg->oldReadData, 32);

	binCopy(reg->newAluResult, tmp, 32);
	binCopy(reg->oldAluResult, reg->newAluResult, 32);
	binCopy(tmp, reg->oldAluResult, 32);

	binCopy(reg->newWriteRegister, tmp, 5);
	binCopy(reg->oldWriteRegister, reg->newWriteRegister, 5);
	binCopy(tmp, reg->oldWriteRegister, 5);

}
