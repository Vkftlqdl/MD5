#include<stdio.h>
#include<string.h>
#include "md5.h"
char* MDhexi(unsigned char digest[16]);
int DecValgenerator(int unit, char *DecVal, char *hash);
char* List= {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
void main()
{
	char DecVal5[5] = {0,};
	char DecVal6[6] = {0,};
	char DecVal7[7] = {0,};
	char hash[33] = {0,};
	printf("해쉬값을 입력하세요 >> ");
	scanf("%s",hash);
	printf("%s에대한 디코딩 시작합니다.\n", hash);
	printf("************************************\n");
	if(DecValgenerator(5, DecVal5,hash))
		if(DecValgenerator(6, DecVal6,hash))
			DecValgenerator(7, DecVal7,hash);
}
char* MDhexi(unsigned char digest[16])
{
	/*16자리 output결과를 16진수로 바꿔서
	문자열로 반환해주는 함수*/

	unsigned int i;
	char digested[33]= {0,};
	
	for (i = 0; i < 16; i++){
			sprintf (&digested[2*i],"%02x", digest[i]);}

	return digested;
}

int DecValgenerator(int unit, char *DecVal,char *hash)
{
	unsigned char DecValMD5[16] = {0,};
	//재귀함수보다 for문이 빠르다
	if(unit == 5)
	{
		for (int i = 0; i < 62; i++)
		{
			DecVal[0] = List[i];
			for (int j = 0; j < 62; j++)
			{
				DecVal[1] = List[j];
				for (int k = 0; k < 62; k++)
				{
					DecVal[2] = List[k];
					for (int m = 0; m < 62; m++)
					{
						DecVal[3] = List[m];
						for (int l = 0; l < 62; l++)
						{
							DecVal[4] = List[l];
							MD5Simple(DecVal,5,DecValMD5);
							if(!strcmp(MDhexi(DecValMD5),hash)){
								printf("password : %.5s\n",DecVal); 
								return 0;}
						}
					}
				}
			}
		printf("%d의 %d단 완료\n",unit, i);
		}
	}
	else if(unit == 6)
	{
		for (int i = 0; i < 62; i++)
		{
			DecVal[0] = List[i];
			for (int j = 0; j < 62; j++)
			{
				DecVal[1] = List[j];
				for (int k = 0; k < 62; k++)
				{
					DecVal[2] = List[k];
					for (int m = 0; m < 62; m++)
					{
						DecVal[3] = List[m];
						for (int l = 0; l < 62; l++)
						{
								DecVal[4] = List[l];
								for (int n = 0; n < 62; n++)
								{
									DecVal[5] = List[n];
									MD5Simple(DecVal,6,DecValMD5);
									if(!strcmp(MDhexi(DecValMD5),hash)){
										printf("password : %.6s\n",DecVal); 
										return 0;}
								}
						}
					}
				}
			}
			printf("%d의 %d단 완료\n",unit, i);
		}
	}
	else if(unit == 7)
	{
		for (int i = 0; i < 62; i++)
		{
			DecVal[0] = List[i];
			for (int j = 0; j < 62; j++)
			{
				DecVal[1] = List[j];
				for (int k = 0; k < 62; k++)
				{
					DecVal[2] = List[k];
					for (int m = 0; m < 62; m++)
					{
						DecVal[3] = List[m];
						for (int l = 0; l < 62; l++)
						{
								DecVal[4] = List[l];
								for (int n = 0; n < 62; n++)
								{
									DecVal[5] = List[n];
									for (int v = 0; v < 62; v++)
									{
										DecVal[6] = List[v];
										MD5Simple(DecVal,7,DecValMD5);
										if(!strcmp(MDhexi(DecValMD5),hash)){
											printf("password : %.7s\n",DecVal); 
											return 0;}
									}
								}
						}
					}
				}
			}
			printf("%d의 %d단 완료\n",unit, i);
		}
	}

	return 1;
}