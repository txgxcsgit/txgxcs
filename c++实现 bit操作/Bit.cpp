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
		cout<<"引用 不能 二次 更换 对象"<<endl;
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
Description:    // 打印出字符的 8 个bit 的值
Calls:          // 无
Called By:      // 调用本函数的函数清单
Input:          // num 被打印的字符
// 用、取值说明及参数间关系。
Output:         // 对输出参数的说明。
Return:         // 函数返回值的说明
Others:         // 其它说明
Performance：		//说明函数的处理速度。通常是表明函数的算法复杂度、空间复杂度。也可以简单的描述次/秒。对于简单计算函数可以不描述。
*************************************************/

void Bit::CharToBit()
{
	//cout<<"二进制显示：";
	for (int i = 0; i < 8; i++)
	{
		cout<<((*ss>>(7-i))&1);                         
	}
	cout<<endl;
}


/*************************************************
Function:       // GetNum
Description:    // 获取CharToSetBit函数设定值时，用到的 与或异或 用到的值
Calls:          // 被本函数调用的函数清单
Called By:      // CharToSetBit
Input:          // index 字节种 8位bit中的 第几位
// 用、取值说明及参数间关系。
Output:         // 对输出参数的说明。
Return:         // 函数返回值的说明
Others:         // 其它说明
Performance：		//说明函数的处理速度。通常是表明函数的算法复杂度、空间复杂度。也可以简单的描述次/秒。对于简单计算函数可以不描述。
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
Description:    // 实现 字符 指定 bit 的值  设定
Calls:          // GetNum
Called By:      // 调用本函数的函数清单
Input:          // num 字符，count指定的bit 位置（从右往左数 ，setValude bit被设定的值），
// 用、取值说明及参数间关系。
Output:         // 对输出参数的说明。
Return:         // 函数返回值的说明
Others:         // 其它说明
Performance：		//说明函数的处理速度。通常是表明函数的算法复杂度、空间复杂度。也可以简单的描述次/秒。对于简单计算函数可以不描述。
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