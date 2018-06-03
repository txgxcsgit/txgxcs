
#include "stdafx.h"


#ifndef DES_CPP
#define DES_CPP

#include "des.h"
#include "Bit.h"

#include "iostream"
using namespace std;

//#define  ceShi

Des::Des(char * strkey)
{

	/* 密钥 */
	for (int j = 0; j < MAN; j++)
	{
		g_szkey[j]=strkey[j];
	}

	/*16个 子秘钥 */
	for (int k = 0; k < ROUNDNUM; k++)
	{
		for (int J = 0; J < ROUNDKEY; J++)
		{
			g_roundKey[k][J]=0;
		}
	}

	//R0,L0
	for (int i = 0; i < MAN/2; i++)
	{
		g_szL0[i]=0;
		g_szR0[i]=0;
	}


	/* 8个 s盒 */
	for (int m = 0; m < MAN; m++)
	{
		for (int n = 0; n < SROW; n++)
		{
			for (int v= 0; v < MAN*2; v++)
			{
				g_s_8[m][n][v]=0;
			}

		}
	}

	/* 初始化 各种表 */
	initTable();

	/* 产生 16个 子秘钥 */

	if (!WheelKeyGeneration(g_szkey,g_extendKeyTable,g_subKeyTable1,g_subKeyTable2,g_dieDaiTab,&g_roundKey[0][0]))
	{
		cout<<"16个 子秘钥 产生过程，出现错误 "<<endl;

		exit(1) ;
	}


}

Des::~Des(){};

void Des::initTable(){

	char ini[MAN*MAN]=
	{
		58,50,42,34,26,18,10,2,
		60,52,44,36,28,20,12,4,
		62,54,46,38,30,22,14,6,
		64,56,48,40,32,24,16,8,
		57,49,41,33,25,17,9,1,
		59,51,43,35,27,19,11,3,
		61,53,45,37,29,21,13,5,
		63,55,47,39,31,23,15,7

	};
	for (int i = 0; i < MAN*MAN; i++)
	{

		g_inisubstituteTab[i]=ini[i];

	}

	/********************************************************************************/

	char ini2[MAN*MAN]=
	{
		40,8,48,16,56,24,64,32,
		39,7,47,15,55,23,63,31,
		38,6,46,14,54,22,62,30,
		37,5,45,13,53,21,61,29,
		36,4,44,12,52,20,60,28,
		35,3,43,11,51,19,59,27,
		34,2,42,10,50,18,58,26,
		33,1,41,9,49,17,57,25

	};

	for (int i = 0; i < MAN*MAN; i++)
	{
		g_uninisubstituteTab[i]=ini2[i];
	}

	/********************************************************************************/

	char ini3ex[EXTENDROW*EXTENDCOLO]=
	{
		32,1,2,3,4,5,
		4,5,6,7,8,9,
		8,9,10,11,12,13,
		12,13,14,15,16,17,
		16,17,18,19,20,21,
		20,21,22,23,24,25,
		24,25,26,27,28,29,
		28,29,30,31,32,1

	};
	for (int i = 0; i < EXTENDROW*EXTENDCOLO; i++)
	{

		g_extendTab[i]=ini3ex[i];

	}

	/********************************************************************************/



	char ini3extedKeyTab[MAN*7]=
	{
		1,2,3,4,5,6,7,
		9,10,11,12,13,14,15,
		17,18,19,20,21,22,23,
		25,26,27,28,29,30,31,
		33,34,35,36,37,38,39,
		41,42,43,44,45,46,47,
		49,50,51,52,53,54,55,
		57,58,59,60,61,62,63

	};
	for (int i = 0; i < MAN*7; i++)
	{

		g_extendKeyTable[i]=ini3extedKeyTab[i];

	}

	/********************************************************************************/

	char ini3_1[SROW][SCOLO]=
	{
		14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
		0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
		4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
		15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13

	};
	Assignment(ini3_1[0],g_s_8[0][0]);

	/********************************************************************************/

	char ini3_2[SROW][SCOLO]=
	{
		15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
		3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
		0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
		13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,



	};
	Assignment(ini3_2[0],g_s_8[1][0]);

	/********************************************************************************/

	char ini3_3[SROW][SCOLO]=
	{
		10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
		13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
		13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
		1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,

	};
	Assignment(ini3_3[0],g_s_8[2][0]);

	/********************************************************************************/



	char ini3_4[SROW][SCOLO]=
	{
		7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
		13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
		10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
		3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14

	};
	Assignment(ini3_4[0],g_s_8[3][0]);

	/********************************************************************************/



	char ini3_5[SROW][SCOLO]=
	{
		2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
		14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
		4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
		11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3

	};
	Assignment(ini3_5[0],g_s_8[4][0]);

	/********************************************************************************/

	char ini3_6[SROW][SCOLO]=
	{
		12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
		10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
		9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
		4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13

	};
	Assignment(ini3_6[0],g_s_8[5][0]);

	/********************************************************************************/

	char ini3_7[SROW][SCOLO]=
	{
		4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
		13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
		1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
		6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12

	};
	Assignment(ini3_7[0],g_s_8[6][0]);

	/********************************************************************************/

	char ini3_8[SROW][SCOLO]=
	{
		13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
		1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
		7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
		2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11

	};
	Assignment(ini3_8[0],g_s_8[7][0]);

	/********************************************************************************/

	char ini4[PROW][PCOLO]=
	{
		16,7,20,21,
		29,12,28,17,
		1,15,23,26,
		5,18,31,10,
		2,8,24,14,
		32,27,3,9,
		19,13,30,6,
		22,11,4,25

	};
	for (int i = 0; i < PROW; i++)
	{
		for (int j= 0; j < PCOLO; j++)
		{
			g_p[i][j]=ini4[i][j];
		}
	}

	/********************************************************************************/

	const int tabLen=SUBROW1*SNBCOLO1;
	char ini5[tabLen]=
	{
		57,49,41,33,25,17,9,
		1,58,50,42,34,26,18,
		10,2,59,51,43,35,27,
		19,11,3,60,52,44,36,
		63,55,47,39,31,23,15,
		7,62,54,46,38,30,22,
		14,6,61,53,45,37,29,
		21,13,5,28,20,12,4


	};
	for (int i = 0; i < tabLen; i++)
	{

		g_subKeyTable1[i]=ini5[i];

	}

	///********************************************************************************/
	const int tabLen2=SUBROW1*SNBCOLO1;
	char ini6[tabLen2]=
	{
		14,17,11,24,1, 5, 3, 28,
		15,6, 21,10,23,19,12,4,
		26,8, 16,7, 27,20,13,2,
		41,52,31,37,47,55,30,40,
		51,45,33,48,44,49,39,56,
		34,53,46,42,50,36,29,32

	};
	for (int i = 0; i < tabLen2; i++)
	{

		g_subKeyTable2[i]=ini6[i];

	}

	///********************************************************************************/

	const int dieDaitabLen2=ROUNDNUM;
	char ini7[dieDaitabLen2]=
	{
		1,1,2,2,2,2,2,2,1,2, 2, 2, 2, 2, 2, 1

	};
	for (int i = 0; i < dieDaitabLen2; i++)
	{

		g_dieDaiTab[i]=ini7[i];

	}

	///********************************************************************************/


}

bool Des::Assignment(char * strIn,char *strS)
{
	for (int i = 0; i < SROW; i++)
	{
		for (int j= 0; j < SCOLO; j++)
		{
			strIn[i*SROW+j]=strIn[i*SROW+j];
		}
	}
	return true;
}


bool Des::StartSecret(char *strIn,char *strOut)
{
	/**************************************************
	总共三步：
	1.初始置换IP
	2.16轮迭代
	3.逆初始置换IP
	*****************************************************/
	bool isVtemp=false;


	do
	{
#ifdef ceShi
		/**********测试用 可删除************************/
		cout<<"打印 明文 64位 "<<endl;
		for (int i = 0; i < MAN; i++)
		{
			Bit bit(strIn[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;

		/*************测试用 end************************/
#endif

		if(!IniSubstitutionIP(strIn[0],g_inisubstituteTab,g_szL0[0],g_szR0[0]))                                         /* 1.   初始置换IP   */
			break;

#ifdef ceShi
		/**********测试用 可删除************************/
		cout<<"打印 明文 64位 初始置换IP后 "<<endl;
		for (int i = 0; i < MAN/2; i++)
		{
			Bit bit(g_szL0[i]);
			bit.CharToBit();
		}
		for (int i = 0; i < MAN/2; i++)
		{
			Bit bit(g_szR0[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;

		/*************测试用 end************************/
#endif

		for (int i = 0; i < DIEDAICOLOC; i++)                                                                           /*  2.  16轮迭代  */
		{

			if(!SingleIterationOperation(g_szL0,g_szR0,g_roundKey[i]))
				break;
		}

		if(!UnIniSubstitutionIP(g_szR0,g_szL0,strOut))                                                                  /* 3.   逆初始置换IP   */
			break; 

		isVtemp=true;

	} while (false);

	return isVtemp;

}

bool Des::unStartSecret(char *strIn,char *strOut)
{
	/**************************************************
	总共三步：
	1.初始置换IP
	2.16轮迭代                  注意：秘钥顺序同加密相反
	3.逆初始置换IP
	*****************************************************/
	bool isVtemp=false;

	do
	{
		if(!IniSubstitutionIP(strIn[0],g_inisubstituteTab,g_szL0[0],g_szR0[0]))                                         /* 1.   初始置换IP   */
			break;

		for (int i = 15; i >-1; i--)                                                                                    /*  2.  16轮迭代  */
		{
			if(!SingleIterationOperation(g_szL0,g_szR0,g_roundKey[i]))
				return false;
		}

		if(!UnIniSubstitutionIP(g_szR0,g_szL0,strOut))                                                                  /* 3.   逆初始置换IP   */
			break; 

		isVtemp=true;

	} while (false);

	return isVtemp;
}

bool Des::IniSubstitutionIP(char &szin,char *inisubStitute,char &L0,char &R0)
{

	bool vbtemp=false;                                                            /* 返回值 */


	do
	{

		if (!Displace(szin,inisubStitute,MAN))
			break;

#ifndef ceShi
		cout<<"打印 明文64 位      初始置换后  "<<endl;
		for (int k = 0; k < 8; k++)
		{
			Bit bit((&L0)[k]);
			bit.CharToBit();
		}

		cout<<endl<<endl;

#endif 
		for (int i = 0; i < MAN/2; i++)
		{
			(&L0)[i]=(&szin)[i];
			(&R0)[i]=(&szin)[i+4];
		}

#ifndef ceShi
		cout<<"打印 L0 32 位  L0 32 位 "<<endl;
		for (int j = 0; j < 4; j++)
		{
			Bit bit((&L0)[j]);
			bit.CharToBit();
		}
		cout<<endl;
		for (int j = 0; j < 4; j++)
		{
			Bit bit((&R0)[j]);
			bit.CharToBit();
		}
		cout<<endl<<endl;

#endif 

		vbtemp=true;

	} while (false);


	/* 测试用 可删除 */
	/*for (int i = 0; i < MAN; i++)
	{
	Bit bit;
	bit.SetChar(vctemp[i]);
	bit.CharToBit();
	cout<<endl;	
	}
	cout<<"g_szin"<<endl<<endl;

	for (int i = 0; i < MAN; i++)
	{
	Bit bit;
	bit.SetChar(g_szin[i]);
	bit.CharToBit();
	cout<<endl;	
	}*/



	return vbtemp;
}

bool Des::SingleIterationOperation(char *L0,char *R0,char *subKey)
{
	/******************************
	此是 F 函数：由四步构成
	1.R0扩展置换E
	2.与轮子秘钥Ki异或
	3.S盒代换
	4.P盒置换
	5.R0与L0 异或
	6.最先的 R0 赋值给 L0 
	*******************************/

	bool vbtemp=false;                                                            /* 返回值 */
	char vextendedR0[6];                                                          /* 扩展后48位 */


	do
	{
		char sz_r0[6]={};
		for (int j = 0; j < 6; j++)
		{
			sz_r0[j]=R0[j];                                                       /* 保存 R0的值，留待最后一步 赋值给 L0 */
		}

#ifdef ceShi
		/**********测试用 可删除************************/
		cout<<"打印  R0   在函数 SingleIterationOperation 551 行 "<<endl;
		for (int i = 0; i < MAN/2; i++)
		{
			Bit bit(R0[i]);
			bit.CharToBit();
		}

		cout<<endl<<endl;

		/*************测试用 end************************/
#endif

		if(!Extended(R0,g_extendTab,vextendedR0[0]))                              /* 1. 32位扩展到48位 置换的 实现 */
			break;

#ifdef ceShi
		/**********测试用 可删除************************/
		cout<<"打印  vextendedR0   R0 32位扩展到48位后 "<<endl;
		for (int i = 0; i < MAN-2; i++)
		{
			Bit bit(vextendedR0[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;
		/*************测试用 end************************/
#endif

		for (int i = 0; i < 6; i++)                                               /* 2. 与轮子秘钥Ki异或  */
		{
			vextendedR0[i]^=subKey[i];
		}

#ifdef ceShi
		/**********测试用 可删除************************/
		cout<<"打印  vextendedR0 48位  vextendedR0 与 子秘钥Ki异或 后 "<<endl;
		for (int i = 0; i < MAN-2; i++)
		{
			Bit bit(vextendedR0[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;
		/*************测试用 end************************/
#endif

		if(!SBoxFan(vextendedR0,R0))                                              /* 3.  S盒压缩 */
			break;

#ifdef ceShi
		/**********测试用 可删除************************/
		cout<<"打印  R0 32位  vextendedR0 与 s盒压缩后 "<<endl;
		for (int i = 0; i < MAN/2; i++)
		{
			Bit bit(R0[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;
		/*************测试用 end************************/
#endif

		if(!Displace(*R0,&g_p[0][0],4))                                           /* 4. P盒 置换 */
			break;

#ifdef ceShi
		/**********测试用 可删除************************/
		cout<<"打印  R0 32位  R0 与 P盒置换 后 "<<endl;
		for (int i = 0; i < MAN/2; i++)
		{
			Bit bit(R0[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;
		/*************测试用 end************************/
#endif

		for (int i = 0; i < 4; i++)                                               /* 5. R0 与 L0 异或  */
		{
			R0[i]^=L0[i];
		}

		for (int i = 0; i < 4; i++)                                               /* 6. L0 赋值，sz_r0 赋值给 L0  */
		{

			L0[i]=sz_r0[i];

		}

		vbtemp=true;
	} while (false);


	return vbtemp;
}

bool Des::Extended(char *R0,char *extendedTable, char &g_extendedR0)
{
	bool value=false;



	do
	{

		//#define ceShi1
#ifdef ceShi
		/**********测试用 可删除************************/
		cout<<"打印  R0   32位 在Extended 函数中 "<<endl;
		for (int i = 0; i < MAN/2; i++)
		{
			Bit bit(R0[i]);
			bit.CharToBit();
		}

		cout<<endl<<endl;

		/*************测试用 end************************/
#endif
		if(!Displace(&g_extendedR0,R0,extendedTable,6))
			break;

		value=true;

	} while (false);

	return value;


}

bool Des::SBoxFan(char *strIn,char *strOut)
{
	/*******************************************
	1.取出6位
	2.1+6=row
	3.2345=column
	4.valude=查表（row，column）
	5.4位的值valude 写入6位 的位置
	********************************************/

	bool vbtemp=false;                                                             /* 返回值 */

	char bitValude=0;                                                              /* 根据 row和column 查表 的 值 */
	char vtempVal[2]={0};                                                          /* 存储row 和 colu 临时值 */


	do
	{
		for (int i = 0; i < 8; i++)                                            
		{

			if(!GetBitVal(strIn,i*6,vtempVal))                                     /* 返回 6个bit 的值 到vtemVal */
				return false;

			bitValude=g_s_8[i][vtempVal[0]][vtempVal[1]];                          /* 取出表的值 */

			if (!SetBitVal(&bitValude,strOut,i*4))                                 /* 把 值 写入 4位 bit */
				break;

			vtempVal[0]=0;                                                         /* 必须清零 ，否则下次循环 会 不准确 */
			vtempVal[1]=0;

		}

		vbtemp=true;
	} while (false);


	return vbtemp;

}

bool Des::UnIniSubstitutionIP(char *R0,char *L0,char *ciphertext)
{
	bool vbtemp=false;                                                                               /* 返回值 */

	do
	{
		for (int i = 0; i < 8; i++)                                                                  /* L0 R0合并到 ciphertext */
		{
			if (i<4)
			{
				ciphertext[i]=L0[i];
			}
			else
			{
				ciphertext[i]=R0[i-4];
			}

		}


		if (!Displace(*ciphertext,g_uninisubstituteTab,8))                                           /* 用 逆初始置换表 置换 ciphertext */
			break;



		vbtemp=true;

	} while (false);


	return vbtemp;
}

bool Des::WheelKeyGeneration(char *key,char *exdTab,char *subKeyTable1,char *subKeyTable2,char *dieDaiTab,char *roundKey)
{
	//轮密钥产生需要 三步

	//一：DES的密钥由64位减至56位，每个字节的第8位作为奇偶校验位。产生的56位密钥由表生成（注意表中没有8,16,24，32,40,48,56和64这8位）
	//二：将56位的密钥分成两部分，每部分28位。根据轮数，这两部分分别循环左移1位或2位
	//三：移动后，从56位中选出48位。这个过程中，既置换了每位的顺序，又选择了子密钥，因此称为压缩置换

	bool vbtemp=false;                                                                              /* 返回值 */

	char rundKey56[MAN-1]={0};                                                                      /* 存储 56 bit 秘钥 */ 
	char roundKeyC[MAN/2]={0};                                                                      /* 存储 28 bit C半秘钥 用四个字节 ，长度过大，没想到更好的办法 */
	char roundKeyD[MAN/2]={0};                                                                      /* 存储 28 bit D半秘钥 用四个字节 ，长度过大，没想到更好的办法 */
	char subKey[ROUNDKEY]={0};                                                                      /* 存储 48 bit 子秘钥*/

	do
	{
#ifndef ceShi
		/**********测试用 可删除************************/
		cout<<"打印 DES的密钥由64位 "<<endl;
		for (int i = 0; i < MAN; i++)
		{
			Bit bit(key[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;

		/*************测试用 end************************/
#endif


		if(!ProducKeyOne(rundKey56,key,exdTab,subKeyTable1,roundKeyC,roundKeyD))                     /* 产生秘钥 第一步：1.64位秘钥，按照exdTab表压缩到56位，2.按照subKeyTable1表 置换，3.输出2个 半秘钥C0，D0 */
			break;

#ifndef ceShi
		/**********测试用 可删除************************/
		cout<<"打印 半密钥 28 位 "<<endl;
		for (int i = 0; i < 4; i++)
		{
			Bit bit(roundKeyC[i]);
			bit.CharToBit();
		}

		for (int i = 0; i < 4; i++)
		{
			Bit bit(roundKeyD[i]);
			bit.CharToBit();
		}

		cout<<endl<<endl;

		/*************测试用 end************************/
#endif

		for (int n = 0; n < MAN*2; n++)                                                              
		{

			//char C0[4]={0};
			//char D0[4]={0};
			//for (int i = 0; i < 4; i++)
			//{
			//	C0[i]=roundKeyC[i];
			//	D0[i]=roundKeyD[i];
			//}

			//if(!ProducKeyTwo(C0,D0,n,dieDaiTab,rundKey56))                                         /* 此注释 测试 用 产生秘钥 第二步：1.循环左移动 半秘钥，2.合并 半秘钥 并输出56位秘钥 */


			if(!ProducKeyTwo(roundKeyC,roundKeyD,n,dieDaiTab,rundKey56))                             /* 产生秘钥 第二步：1.循环左移动 半秘钥，2.合并 半秘钥 并输出56位秘钥 */
				break;
#ifndef ceShi
			/**********测试用 可删除************************/
			cout<<"打印 半密钥 28 位 左移动 后"<<endl;
			for (int i = 0; i < 4; i++)
			{
				Bit bit(roundKeyC[i]);
				bit.CharToBit();
			}

			for (int i = 0; i < 4; i++)
			{
				Bit bit(roundKeyD[i]);
				bit.CharToBit();
			}

			cout<<endl<<endl;
			/*************测试用 end************************/
#endif
#ifndef ceShi
			/**********测试用 可删除************************/
			cout<<"打印 密钥 56 位 合并两个 半秘钥 后"<<endl;
			for (int i = 0; i < 7; i++)
			{
				Bit bit(rundKey56[i]);
				bit.CharToBit();
			}
			cout<<endl<<endl;
			/*************测试用 end************************/
#endif


			if(!ProducKeyThree(subKey, rundKey56,subKeyTable2))                                      /* 产生秘钥 第三步：56位秘钥压缩并置换，输出 48位 子秘钥  */
				break;

#ifndef ceShi
			/**********测试用 可删除************************/
			cout<<"打印 密钥 48 位 压缩置换2 后  即新秘钥产生  "<<endl;
			for (int i = 0; i < 6; i++)
			{
				Bit bit(subKey[i]);
				bit.CharToBit();
			}
			cout<<endl<<endl;

			/*************测试用 end************************/
#endif

			for (int j = 0; j < ROUNDKEY; j++)                                                       /* 新子秘钥 存储 */
			{
				roundKey[n*6+j]=subKey[j];
			}

		}


		vbtemp=true;

	} while (false);


	return vbtemp;
}

bool Des::GetCharAndBit(int in,int &chIndex,int &bitIndex)
{
	bool val=true;

	do
	{
		chIndex=in/8;
		bitIndex=in%8;

		if (bitIndex==0)
		{
			chIndex--;
			bitIndex=8;
		}


	} while (false);

	return val;

}

bool Des::Displace(char &displace,char *displaceTable,int count)
{

	bool value=true;
	int cou=(count);

	char *vsztemp=new char[cou];

	for (int c = 0; c < cou; c++)
	{
		vsztemp[c]=((&displace)[c]);
	}
#ifdef ceShi
	/**********测试用 可删除************************/
	cout<<"打印  Displace：：vsztemp   R0   32位扩展到48位后 赋值给 vsztemp "<<endl;
	for (int i = 0; i < MAN-2; i++)
	{
		Bit bit(vsztemp[i]);
		bit.CharToBit();
	}

	cout<<endl<<endl;

	/*************测试用 end************************/
#endif

	do
	{
		for (int i = 0; i <cou ; i++)
		{

			Bit bit((&displace)[i]);

			for (int j = 0; j < MAN; j++)
			{
				int tabVal=(displaceTable[i*8+j]);                                                       /* 获取 z置换表 的 值 */

				int chInd=0,biInd=0;
				bool  get=GetCharAndBit(tabVal,chInd,biInd);                                             /* 获取R0 字符下标和 bit下标  */
				if (get)
				{
					Bit biOut(vsztemp[chInd]);
					int biVal=biOut.GetBitValude(biInd,false);                                           /* 取出 R0 字符下标和 bit下标  的值 */

					bit.CharToSetBit(j+1,biVal,false);    /*  赋值 */
					//cout<<biVal;
				}
				else
				{
					delete []vsztemp;
					cout<<"Displace  函数错误 "<<endl;
					return false;
				}

			}
			//cout<<endl;
#ifdef ceShi
			cout<<"in  情况："<<endl;
			bit.CharToBit();
			cout<<endl;
#endif
		}
		//cout<<endl;
#ifdef ceShi

		/* *************测试用 可删除******** */

		for (int c = 0; c < cou/MAN; c++)
		{
			Bit bit(vsztemp[c]);
			bit.CharToBit();

		}

		cout<<endl<<endl;

		for (int i = 0; i < 6; i++)
		{

			Bit bit((&displace)[i]);
			bit.CharToBit();


		}
		cout<<endl<<endl;

		/********测试 end***************************/
#endif

		delete []vsztemp;


	} while (false);

	return value;
}

bool Des::Displace(char *displace1,char * displace2,char *exideTab,int count)
{
	bool val=true;
#ifdef ceShi1

	/* *************测试用 可删除******** */
	cout<<"打印 displace2    是否 等于 R0 "<<endl;
	for (int i = 0; i < 4; i++)
	{
		Bit bit(displace2[i]);
		bit.CharToBit();
	}
	cout<<endl<<endl;

	/********测试 end***************************/
#endif

	for (int i = 0; i <count ; i++)
	{

		Bit bit(displace1[i]);

		for (int j = 0; j < MAN; j++)
		{
			int tabVal=(exideTab[i*8+j]);                                                     /* 获取 置换表 的 值 */

			int chInd=0,biInd=0;
			bool  get=GetCharAndBit(tabVal,chInd,biInd);                                      /* 获取 字符下标和 bit下标  */
			if (get)
			{
				Bit biOut(displace2[chInd]);
				int biVal=biOut.GetBitValude(biInd,false);                                    /* 取出 key 字符下标和 bit下标  的值 */

				bit.CharToSetBit(j+1,biVal,false);                                            /* 赋值 */
				//cout<<biVal;
			}
			else
			{
				return false;
			}

		}
		//cout<<endl;
	}

	//cout<<endl<<endl;
	return val;

}

bool Des::HaldKeyAss(char *C0,char *D0,char *rounKey56)
{
	bool val=true;

	do
	{

		{
			for (int i = 0; i < 3; i++)                                                            /* C0半秘钥28 bit  赋值 */
			{
				C0[i]=rounKey56[i];
			}
			Bit bit1(C0[3]);
			Bit bit2(rounKey56[3]);
			for (int j = 0; j < 4; j++)
			{
				int vv=bit2.GetBitValude(j+1,false);
				bit1.CharToSetBit(j+1,vv,false);                                    
			}
		}                                                                                         /* C0半秘钥 赋值 完成 */



		{                                                                                         /* D0半秘钥28 bit  赋值  */

			for (int i = 0; i < 4; i++)
			{
				Bit bit(D0[i]);

				Bit bit2(rounKey56[i+3]);
				for (int j = 0; j < 4; j++)
				{
					bit.CharToSetBit(j+1,bit2.GetBitValude(j+5,false),false);	
				}

				if (i==3)
					break;                                                                        /* 此时，28 bit秘钥 已经完成 */

				Bit bit3(rounKey56[i+4]);
				for (int k = 0; k < 4; k++)
				{
					bit.CharToSetBit(k+5,bit3.GetBitValude(k+1,false),false);
				}

			}                                                                                     

		}                                                                                         /* D0半秘钥 赋值  完成 */



	} while (false);

	return val;


}

bool Des::CharArrayMoveBit(char *str,int len,int moveLen,bool isRightMove)
{
	bool val = true;

	char *vtemp=new char[len];
	for (int i = 0; i < len; i++)
	{
		vtemp[i]=str[i];
	}


	do
	{
		if(!isRightMove)                                                                                                          /* 左 移动 */
		{
			for (int i = 0; i < len; i++)
			{
				Bit bit(str[i]);
				int vBit=0;

				Bit bitVtemp(vtemp[i]);
				for (int j = 0; j <8- moveLen; j++)
				{
					vBit=bitVtemp.GetBitValude(moveLen+j+1,false);
					bit.CharToSetBit(j+1,vBit,false);
				}

				if (i==(len-1))
				{
					for (int k = 0; k < moveLen; k++)
					{
						vBit=0;
						bit.CharToSetBit(k+8-moveLen+1,vBit,false);
					}
				}
				else
				{
					Bit bitVtemp2(vtemp[i+1]);
					for (int k = 0; k < moveLen; k++)
					{
						vBit=bitVtemp2.GetBitValude(k+1,false);
						bit.CharToSetBit(k+8-moveLen+1,vBit,false);
					}
				}

			}
		}
		else
		{                                                                                                                        /* 右 移动 */
			for (int i = len; i >0; i--)
			{
				Bit bit(str[i]);
				int vBit=0;

				Bit bitVtemp(vtemp[i]);
				for (int j = 0; j <8- moveLen; j++)
				{
					vBit=bitVtemp.GetBitValude(moveLen+j+1);
					bit.CharToSetBit(j+1,vBit);
				}

				if (i==(1))
				{
					for (int k = 0; k < moveLen; k++)
					{
						vBit=0;
						bit.CharToSetBit(k+8-moveLen+1,vBit);
					}
				}
				else
				{
					Bit bitVtemp2(vtemp[i-1]);
					for (int k = 0; k < moveLen; k++)
					{
						vBit=bitVtemp2.GetBitValude(k+1);
						bit.CharToSetBit(k+8-moveLen+1,vBit);
					}
				}

			}
		}


	} while (false);

	delete []vtemp;


	return val;
}

bool Des::HaldMergeAndNewKey(char *C0,char *D0,char *outKey)
{
	bool val=false;

	do
	{
		for (int i = 0; i < 3; i++)                                                              /* C0 秘钥 合并*/  
		{
			outKey[i]=C0[i];
		}

		Bit bitOut(outKey[3]);                                                                   /* 还差 4 bit 没 合并 */
		Bit bit(C0[3]);
		for (int j = 0; j < 4; j++)                                                             
		{
			int valBit=bit.GetBitValude(j+1,false);
			bitOut.CharToSetBit(j+1,valBit,false);
		}                                                                                       /* C0 秘钥 合并 完成 */

		for (int m = 0; m < 4; m++)                                                             /* D0 秘钥 合并  */
		{
			Bit bit(D0[m]);

			Bit bitOut(outKey[m+3]);
			for (int k = 0; k < 4; k++)
			{
				int valBit=bit.GetBitValude(k+1,false);
				bitOut.CharToSetBit(k+5,valBit,false);
			}

			if (3==m)                                                                          /* 此时，合并已经 完成 */
			{
				break;
			}

			Bit bitOut2(outKey[m+3+1]);
			for (int k = 0; k < 4; k++)
			{
				int valBit=bit.GetBitValude(k+5,false);
				bitOut2.CharToSetBit(k+1,valBit,false);
			}
		}                                                                                      /* D0 秘钥 合并  完成 */



		val=true;             

	} while (false);


	return val;
}

bool Des::ProducKeyOne(char *rundKey56,char *key,char *exdTab,char *subKeyTable1,char *roundKeyC,char *roundKeyD)
{
	bool val=false;

	do
	{

		bool isFaid=Displace(rundKey56,key,exdTab,MAN-1);                                           /* DES的密钥由64位压缩至56位 这步 没看出 作用 下步会覆盖掉 */
		if (!isFaid)
			break;

#ifndef ceShi
		/**********测试用 可删除************************/
		cout<<"打印 DES的密钥 56 位 压缩表压缩后 "<<endl;
		for (int i = 0; i < 7; i++)
		{
			Bit bit(rundKey56[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;

		/*************测试用 end************************/
#endif

		if(!Displace(rundKey56,key,subKeyTable1,7))                                                 /* 56 bit 密码 与 表1置换*/
			break;

#ifndef ceShi
		/**********测试用 可删除************************/
		cout<<"打印 DES的 密钥 56 位 表1置换后"<<endl;
		for (int i = 0; i < 7; i++)
		{
			Bit bit(rundKey56[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;

		/*************测试用 end************************/
#endif


		bool ishal=HaldKeyAss(roundKeyC,roundKeyD,rundKey56);                                       /* 半秘钥C0,DO 产生 */
		if (!ishal)
			break;
#ifndef ceShi
		/**********测试用 可删除************************/
		cout<<"半 密钥C0 28 位 "<<endl;
		for (int i = 0; i < 4; i++)
		{
			Bit bit(roundKeyC[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;

		for (int i = 0; i < 4; i++)
		{
			Bit bit(roundKeyD[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;

		/*************测试用 end************************/
#endif

		val=true;

	} while (false);

	return val;

}

bool Des::ProducKeyTwo(char *roundKeyC,char *roundKeyD,int diwDaiCou,char * dieDaiTab,char *rundKey56)
{
	bool val=false;

	do
	{
		int charLen=4;                                                                          /* 半秘钥 用 4 字节 存储 空间大，还没想到好办法 */
		int dieDaiTabVal=dieDaiTab[diwDaiCou];                                                  /* 查表 得到 左移动的 bit 数目  */

		bool isHlfC=CharArrayMoveBit(roundKeyC,charLen,dieDaiTabVal,false);                     /* 半秘钥C0 左 移动 */
		if (!isHlfC)
		{
			break;
		}

		bool isHlfD=CharArrayMoveBit(roundKeyD,charLen,dieDaiTabVal,false);                     /* 半秘钥D0 左 移动 */
		if (!isHlfD)
		{
			break;
		}

#ifdef ceShi
		/**********测试用 可删除************************/
		cout<<"半 密钥C0 28 位移动后  "<<endl;
		for (int i = 0; i < 4; i++)
		{
			Bit bit(roundKeyC[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;

		for (int i = 0; i < 4; i++)
		{
			Bit bit(roundKeyD[i]);
			bit.CharToBit();
		}
		cout<<endl<<endl;

		/*************测试用 end************************/
#endif

		if(!HaldMergeAndNewKey(roundKeyC,roundKeyD,rundKey56))                                  /* 半秘钥合并 */  
		{
			break;
		}
#ifdef ceShi
		/**********测试用 可删除************************/

		cout<<"半 密钥C0, DO合并 后  "<<endl;
		for (int k = 0; k < 7; k++)
		{
			Bit bit(rundKey56[k]);
			bit.CharToBit();
		}
		cout<<endl<<endl;

		/*************测试用 end************************/
#endif



		val=true;
	} while (false);

	return val;

}

bool Des::ProducKeyThree(char *subKey,char *rundKey56,char *subKeyTable2)
{
	bool val=false;

	do
	{
		if(!Displace(subKey, rundKey56,subKeyTable2,6))                                /* 按照置换表2，置换，产生48 bit 子秘钥  */
			break;


		val=true;

	} while (false);

	return val;

}

bool Des::GetBitVal(char *strIn,int index,char *valude)
{
	bool vbtemp=false;                                                                 /* 返回值 */

	int vtempindex=0;
	int vtempbitIndex=0;

#ifdef ceShi
	/**********测试用 可删除************************/
	cout<<"打印  vextendedR0 48位   在GetBitVal  函数中 "<<endl;
	for (int i = 0; i < MAN-2; i++)
	{
		Bit bit(strIn[i]);
		bit.CharToBit();
	}
	cout<<endl<<endl;
	/*************测试用 end************************/

#endif
	do
	{
		Bit bitRow(valude[0]);
		Bit bitCol(valude[1]);

		for (int i = 0; i < 6; i++)
		{
			if(!GetCharAndBit(index+1+i,vtempindex,vtempbitIndex))                        /* 获取所在字节的 下标 和 bit下标 */
				return false;

			Bit bitGet(strIn[vtempindex]);
			int val=bitGet.GetBitValude(vtempbitIndex,false);

			if (0==i)
			{
				bitRow.CharToSetBit(2,val);
			}

			if (1==i)
			{
				bitCol.CharToSetBit(4,val);
			}
			if (2==i)
			{
				bitCol.CharToSetBit(3,val);
			}
			if (3==i)
			{
				bitCol.CharToSetBit(2,val);
			}
			if (4==i)
			{
				bitCol.CharToSetBit(1,val);
			}

			if (5==i)
			{
				bitRow.CharToSetBit(1,val);
			}

		}


		vbtemp=true;

	} while (false);


	return vbtemp;
}

bool Des::SetBitVal(char *chIn,char *chOut,int len)
{
	bool vbtemp=false;                                                            /* 返回值 */
	int vtempindex=0;
	int vtempbitIndex=0;


	do
	{
		if(!GetCharAndBit(len+1,vtempindex,vtempbitIndex))                        /* 获取所在字节的 下标 和 bit下标 */
			break;

		Bit bitSet(chOut[vtempindex]);
		Bit bitGet(*chIn);

		for (int i = 0; i < 4; i++)
		{
			int val=bitGet.GetBitValude(4-i);                                      /* 注意：此处必须是 从右 往左 数 */
			bitSet.CharToSetBit(i+vtempbitIndex,val,false);
		}


		vbtemp=true;

	} while (false);


	return vbtemp;
}



#endif