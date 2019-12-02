#include<math.h>
#include <stdio.h>

int binToDecUnsigned(int *binArray,int len){
	int i;
	int num=0;
	for(i=len-1; i >= 0; i--)
		num+=binArray[i]*pow(2.0,len-i-1);
	return num;
}

int binToDecSigned(int *binArray,int len){
	int num;
	int i;
	if(binArray[0]==1){
		num=-1*pow(2.0,len-1);
		for(i=1;i<len;i++)
			num+=binArray[i]*pow(2.0,len-i-1);
		return num;
	}else{
		return binToDecUnsigned(binArray,len);
	}
}

void decToBin(int dec,int* bin)
{
	int i;
	for(i=31; i>=0; i--)
	{
		if(dec & 1)
			{
				bin[i]=1;
			}
		else
			bin[i]=0;
		dec=dec >> 1;
	}
}

void binCopy(int * ref,int* dest,int len){
	int i;
	for(i=0;i<len;i++)
		dest[i]=ref[i];
}

int *Mux(int *value1,int *value2,int select)
{
	if(select == 1)
		return value2;
	else if(select == 0)
		return value1;
}

int* Mux4_1(int *value1, int *value2, int *value3, int *value4, int *select)
{
	int decSelect = binToDecUnsigned(select,2);

	if (decSelect == 0)
		return value1;
	else if (decSelect == 1)
		return value2;
	else if (decSelect == 2)
		return value3;
	else if (decSelect == 3)
		return value4;
}

int isEqualToZero(int *array,int len)
{
	int i;
	for(i=0; i<len; i++)
		if(array[i] == 1)
			return 0;
	return 1;
}

void printIntArray(int * array, int size){
	int i;
	for (i = 0; i < size; i++){
		printf("%d", array[i]);
	}
	printf("\n");
	return;
}

int isEqual(int *a1, int *a2, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		if (a1[i] != a2[i])
			return 0;
	}
	return 1;
}

void decToBinSigned(int dec, int *bin){
	int i=31;
	if (dec < 0){
		dec = -dec;
		decToBin(dec, bin);
		while (bin[i] != 1)
			i--;
		i--;
		for (i ; i>-1; i--){
			if (bin[i] == 0)
				bin[i] = 1;
			else
				bin[i] = 0;
		}
	}
	else{
		decToBin(dec, bin);
	}
}
