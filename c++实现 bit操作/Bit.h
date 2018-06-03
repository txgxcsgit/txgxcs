#pragma once

#ifndef BIT_H
#define BIT_H


/*************************************************

classname:Bit

实现字节中 8 个 bit 的操作

主要功能如下：

1.设定 bit的 值 
2.获取 bit的 值
3.打印 bit的 值

*************************************************/

class Bit
{
public:
	Bit();
	Bit(char &str);
	~Bit(void);


	/*************************************************
	Function:       // SetChar
	Description:    // 设置新的字符
	Calls:          // 被本函数调用的函数清单
	Called By:      // 调用本函数的函数清单
	Input:          // str 新字符
	// 用、取值说明及参数间关系。
	Output:         // 对输出参数的说明。
	Return:         // 函数返回值的说明
	Others:         // 其它说明
	Performance：		//说明函数的处理速度。通常是表明函数的算法复杂度、空间复杂度。也可以简单的描述次/秒。对于简单计算函数可以不描述。
	*************************************************/

	void SetChar(char &str);


	/*************************************************
	Function:       // GetChar
	Description:    // 返回字符
	Calls:          // 被本函数调用的函数清单
	Called By:      // 调用本函数的函数清单
	Input:          // 输入参数说明，包括每个参数的作
	// 用、取值说明及参数间关系。
	Output:         // 对输出参数的说明。
	Return:         // 函数返回值的说明
	Others:         // 其它说明
	Performance：		//说明函数的处理速度。通常是表明函数的算法复杂度、空间复杂度。也可以简单的描述次/秒。对于简单计算函数可以不描述。
	*************************************************/

	unsigned char* GetChar()const;


	/*************************************************
	Function:       // GetBitValude
	Description:    // 获取字节指定下标bit的值
	Calls:          // 被本函数调用的函数清单
	Called By:      // 调用本函数的函数清单
	Input:          // iddex 字节指定下标的bit值, isRtoL: iddex 是否是 从右往左 数
	// 用、取值说明及参数间关系。
	Output:         // 对输出参数的说明。
	Return:         // 返回bit值
	Others:         // 其它说明
	Performance：		//说明函数的处理速度。通常是表明函数的算法复杂度、空间复杂度。也可以简单的描述次/秒。对于简单计算函数可以不描述。
	*************************************************/

	unsigned int GetBitValude(int index,bool isRtoL=true);


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

	void CharToBit();

	/*************************************************
	Function:       // CharToSetBit
	Description:    // 实现 字符 指定 bit 的值  设定
	Calls:          // GetNum
	Called By:      // 调用本函数的函数清单
	Input:          // count指定的bit 位置（从右往左数 ，setValude bit被设定的值）isRtoL:位置是否为从 右往左数 ，
	// 用、取值说明及参数间关系。
	Output:         // 对输出参数的说明。
	Return:         // 函数返回值的说明
	Others:         // 其它说明
	Performance：		//说明函数的处理速度。通常是表明函数的算法复杂度、空间复杂度。也可以简单的描述次/秒。对于简单计算函数可以不描述。
	*************************************************/

	void CharToSetBit(int count,int setValude,bool isRtoL=true);




private:

	/*************************************************
	Function:       // GetNum
	Description:    // 获取CharToSetBit函数设定值时，用到的 与或异或 用到的值
	Calls:          // 被本函数调用的函数清单
	Called By:      // CharToSetBit
	Input:          // index 字节种 8位bit中的 第几位,isRtoL:index是否是 从右往左数
	// 用、取值说明及参数间关系。
	Output:         // 对输出参数的说明。
	Return:         // 函数返回值的说明
	Others:         // 其它说明
	Performance：		//说明函数的处理速度。通常是表明函数的算法复杂度、空间复杂度。也可以简单的描述次/秒。对于简单计算函数可以不描述。
	*************************************************/

	unsigned int GetNum(unsigned int index,bool isRtoL=true);

	


private:


	unsigned char *ss;                /* 字符 */
	bool isQuote;                     /* 字符 是否 引用过 */

};

#endif