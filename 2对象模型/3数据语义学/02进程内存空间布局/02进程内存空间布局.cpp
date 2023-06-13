#include <iostream>
#include <time.h>

using namespace std;

int* ptest = new int(120);
int g1;
int g2;

int g3 = 12;
int g4 = 32;
int g5;
int g6 = 0;
static int g7;
static int g8 = 0;
static int g9 = 10;
void mygfunc() {
	return;
}
//定义一个类
class MYACLS{
public:
	int m_i;
	static int m_si; //这是声明不是定义
	int m_j;
	static int m_sj;
	int m_k;
	static int m_sk;
};
int MYACLS::m_sj = 12; //这才是定义

int main() {

	int e_mytest;  //该变量在程序运行时临时放在栈中
	e_mytest = 9;

	printf("ptest地址=%p\n", &ptest);
	printf("g1地址=%p\n", &g1);
	printf("g2地址=%p\n", &g2);
	printf("g3地址=%p\n", &g3);
	printf("g4地址=%p\n", &g4);
	printf("g5地址=%p\n", &g5);
	printf("g6地址=%p\n", &g6);
	printf("g7地址=%p\n", &g7);
	printf("g8地址=%p\n", &g8);
	printf("g9地址=%p\n", &g9);
	printf("MYACLS::m_sj地址=%p\n", &(MYACLS::m_sj));
	printf("mygfunc()地址=%p\n", mygfunc);
	printf("main()地址=%p\n", main);

	int i = 7;
	printf("i地址=%p\n", &i);

	return 0;
}
