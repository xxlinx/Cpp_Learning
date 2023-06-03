#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <map>
#include <set>
#include <forward_list>
#include <algorithm>
#include <unordered_set>
#include <functional>
#include <queue>
#include <boost/type_index.hpp>

using namespace std;


void testFunc() {}


//函数模板
template <typename T>
//void myfunc(const T& tmprv) 
void myfunc(T& tmprv)
{
	cout << "---------------------begin------------------------" << endl;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv类型
	cout << "----------------------end-------------------------" << endl;
}



int main() {

	//myfunc(100);  需要函数模板有const

	/*
	//函数模板没有const
	int i = 18;
	const int j = i;
	const int& k = i;
	myfunc(i); //T=int,tmprv=int &。
	myfunc(j); //因为j的类型中带个const，结果：T=int const, tmprev=int const &
	myfunc(k); //执行结果：T=int const, tmprev=int const &
	*/

	/*
	//函数模板有const   const T& tmprv
	int i = 18;        //一眼看得出来i的类型为int
	const int j = i;   //一眼看得出来j的类型为const int
	const int& k = i;  //一眼看得出来k的类型为const int &
	myfunc(i);   //执行结果：T=int, tmprev=int const & ，tmprev这里多了个const
	myfunc(j);   //执行结果：T=int, tmprev=int const & ，T类型原来的const变没了
	myfunc(k);   //执行结果：T=int, tmprev=int const & ，T类型原来的const变没了
	*/


	//	//(T * tmprv)
	//	int i = 18;
	//	const int* pi = &i;
	//	myfunc(&i);            //看实际执行结果：T=int,tmprev=int *
	//	myfunc(pi);            //看实际执行结果：T=int const, tmprev =int const *



	//	//T&& tmprv
	//	int i = 18;           //一眼看得出来i的类型为int
	//	const int j = i;      //一眼看得出来j的类型为const int
	//	const int& k = i;     //一眼看得出来k的类型为const int &
	//	myfunc(i);            //i是左值，看实际执行结果：T=int &，tmprv=int &
	//	myfunc(j);            //j是左值，看实际执行结果：T=int const &，tmprv=int const &
	//	myfunc(k);            //k是左值(只要能往等号左边放的都是左值，就是算是右值引用，也是个左值）,看实际执行结果：T=int const &，tmprv=int const &
	//	myfunc(100);          //100是右值，看实际执行结果：T=int，tmprv=int &&


	//T tmprv
	//int i = 18;           //一眼看得出来i的类型为int
	//const int j = i;      //一眼看得出来j的类型为const int
	//const int& k = i;     //一眼看得出来k的类型为const int &
	//myfunc(i);            //看实际执行结果：T=int,tmprev=int
	//myfunc(j);            //看实际执行结果：T=int,tmprev=int，const属性没传递，因为对方是新副本
	//myfunc(k);            //看实际执行结果：T=int,tmprev=int，const属性没传递，因为对方是新副本

	//char mystr[] = "I Love China!";
	//const char* const point = mystr;
	//myfunc(point);        //看实际执行结果：T=char const *,tmprev=char const *



	//	//T tmprv
	//	const char mystr[] = "I Love China!";
	//	myfunc(mystr);          //看实际执行结果：T=char const *,tmprev=char const *，按指针方式处理数组了
	//}

	//{
	//	//T& tmprv
	//	const char mystr[] = "I Love China!";
	//	myfunc(mystr);          //看实际执行结果：T=T=char const [14],tmprv=char const (&)[14]，按指针方式处理数组了
	//}

	//{
	//	//T(&tmprv)[L1]
	//	const char mystr[] = "I Love China!";
	//	myfunc(mystr);          //看实际执行结果：T=char const [14], tmprv =char const (&)[14]
	//}


		//T tmprv 
		//myfunc(testFunc); //看实际执行结果：T=void (__cdecl*)(void)，tmprv=void (__cdecl*)(void)



		//T& tmprv 
		myfunc(testFunc); //看实际执行结果：T=void __cdecl(void)，tmprv=void (__cdecl&)(void)

	return 0;
}