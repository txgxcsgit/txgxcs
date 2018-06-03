#include "stdafx.h"

#ifndef BIT_CPP
#define BIT_CPP

#include "Bit.h"
#include "iostream"
using namespace std;

Bit::Bit():isQuote(false)
{
}

Bit::Bit( char &str):ss((unsigned char  *)&str),isQuote(true)
{

	
}


Bit::~Bit(void)
{
}


void Bit::SetChar( char &str)
{
	if(isQuote) 
	{
		cout<<"���� ���� ���� ���� ����"<<endl;
		return ;
	}

	ss=(unsigned char*)&str;
	isQuote=true;

}


unsigned char* Bit::GetChar()const
{
	return ss;
}



unsigned int Bit::GetBitValude(int index,bool isRtoL)
{
	int bit=0;
	isRtoL?bit= (((*ss)>>(index-1))&1):bit= (((*ss)>>(8-index))&1);
	return bit;
}



/*************************************************
Function:       // CharToBit
Description:    // ��ӡ���ַ��� 8 ��bit ��ֵ
Calls:          // ��
Called By:      // ���ñ������ĺ����嵥
Input:          // num ����ӡ���ַ�
// �á�ȡֵ˵�����������ϵ��
Output:         // �����������˵����
Return:         // ��������ֵ��˵��
Others:         // ����˵��
Performance��		//˵�������Ĵ����ٶȡ�ͨ���Ǳ����������㷨���Ӷȡ��ռ临�Ӷȡ�Ҳ���Լ򵥵�������/�롣���ڼ򵥼��㺯�����Բ�������
*************************************************/

void Bit::CharToBit()
{
	//cout<<"��������ʾ��";
	for (int i = 0; i < 8; i++)
	{
		cout<<((*ss>>(7-i))&1);                         
	}
	cout<<endl;
}


/*************************************************
Function:       // GetNum
Description:    // ��ȡCharToSetBit�����趨ֵʱ���õ��� ������ �õ���ֵ
Calls:          // �����������õĺ����嵥
Called By:      // CharToSetBit
Input:          // index �ֽ��� 8λbit�е� �ڼ�λ
// �á�ȡֵ˵�����������ϵ��
Output:         // �����������˵����
Return:         // ��������ֵ��˵��
Others:         // ����˵��
Performance��		//˵�������Ĵ����ٶȡ�ͨ���Ǳ����������㷨���Ӷȡ��ռ临�Ӷȡ�Ҳ���Լ򵥵�������/�롣���ڼ򵥼��㺯�����Բ�������
*************************************************/

unsigned int Bit::GetNum(unsigned int index,bool isRtoL)
{

	unsigned int num=0;

	if (isRtoL)
	{

		switch (index)
		{
		case 1:
			{
				num=1;
				break;
			}

		case 2:
			{
				num=2;
				break;
			}

		case 3:
			{
				num=4;
				break;
			}

		case 4:
			{
				num=8;
				break;
			}

		case 5:
			{
				num=16;
				break;
			}

		case 6:
			{
				num=32;
				break;
			}

		case 7:
			{
				num=64;
				break;
			}

		case 8:
			{
				num=128;
				break;
			}
		default:
			{
				num=0;
				break;
			}
		}
	}
	else
	{
		switch (index)
		{
		case 8:
			{
				num=1;
				break;
			}

		case 7:
			{
				num=2;
				break;
			}

		case 6:
			{
				num=4;
				break;
			}

		case 5:
			{
				num=8;
				break;
			}

		case 4:
			{
				num=16;
				break;
			}

		case 3:
			{
				num=32;
				break;
			}

		case 2:
			{
				num=64;
				break;
			}

		case 1:
			{
				num=128;
				break;
			}
		default:
			{
				num=0;
				break;
			}
		}
	}
	return num;

}

/*************************************************
Function:       // CharToSetBit
Description:    // ʵ�� �ַ� ָ�� bit ��ֵ  �趨
Calls:          // GetNum
Called By:      // ���ñ������ĺ����嵥
Input:          // num �ַ���countָ����bit λ�ã����������� ��setValude bit���趨��ֵ����
// �á�ȡֵ˵�����������ϵ��
Output:         // �����������˵����
Return:         // ��������ֵ��˵��
Others:         // ����˵��
Performance��		//˵�������Ĵ����ٶȡ�ͨ���Ǳ����������㷨���Ӷȡ��ռ临�Ӷȡ�Ҳ���Լ򵥵�������/�롣���ڼ򵥼��㺯�����Բ�������
*************************************************/

void Bit::CharToSetBit(int count,int setValude,bool isRtoL)
{
	unsigned char Vitemp=*ss;

	isRtoL?Vitemp=(Vitemp>>(count-1))&1:Vitemp=(Vitemp>>(8-count))&1;

	if(Vitemp==setValude)
	{
		return ;
	}

	unsigned int nm;
	isRtoL?nm=GetNum(count):nm=GetNum(count,false);

	if(Vitemp==0)
	{
		//unsigned int nm=GetNum(count);
		(*ss)|=nm;
		return ;
	}


	if(Vitemp==1)
	{
		//unsigned int nm=GetNum(count);
		(*ss)^=nm;
		return ;
	}

}



#endif 