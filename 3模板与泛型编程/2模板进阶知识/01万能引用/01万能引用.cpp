#include <iostream>
#include <vector>

using namespace std;

/*   基本认识   
	 万能引用资格的剥夺与辨认   
*/
namespace _nmsp1 {
	//void func(const int& abc) {}

	//template <typename T>
	//void func(const T& abc) { }

	//void myfunc(int&& tmprv) //参数tmprv是个右值引用类型
	template <typename T>
	//void myfunc(T&& tmprv) //万能引用，注意 &&是属于tmprv类型的一部分，不是T类型的一部分（&&和T类型没有关系）
	void myfunc(const T&& tmprv) {//有const修饰，因此万能引用资格被剥夺，因为是&&所以只能是个右值引用
	
		//tmprv = 12;  //不管tmprv的类型是左值引用还是右值引用，都可以给tmprv赋值，因为tmprv本身是个左值
		cout << tmprv << endl;
		return;
	}

	template<typename T>
	void func(std::vector<T>&& param) {}

	template <typename T>
	class mytestc {

	public:
		void testfunc(T&& x) {}; //这个不是万能引用，这个是右值引用

		template <typename T2>
		void testfunc2(T2&& x) {} 
		//T2类型是独立的，和T没任何关系，而且x是函数模板形参，类型是推导来的，所以这是个万能 引用
	};
}




int main() {
	/*
	//_nmsp1::func(10);
	_nmsp1::myfunc(10); //正确，右值做实参  右值绑定在右值引用上
	int i = 100;
	//_nmsp1::myfunc(i); //错，右值引用不能接(绑)左值
	vector<int>aa = { 1 };
	_nmsp1::func(std::move(aa)); //不用std::move不行。也就是说，用左值当参数传递是不行的
	*/

	




	return 0;
}