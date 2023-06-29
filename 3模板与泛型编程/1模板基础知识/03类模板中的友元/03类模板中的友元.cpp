#include <iostream>
#include <map>
#include <vector>
#include <list>

using namespace std;

namespace _nmsp1 {
	template <typename U> class B; //类模板B声明

	template <typename T>
	class A{
		//友元类
		friend class B<long>; //不需要任何public、private等修饰符修饰

	private:
		int data;
	};

	template <typename U>
	class B{
	public:
		void callBAF(){
			A<int> atmpobj;
			atmpobj.data = 5;
			std::cout << atmpobj.data << std::endl;
		}
	};
}
namespace _nmsp2 {
	template <typename T>
	class A {
		//friend class B<long>;
		template<typename> friend class B; //友元类模板
	private:
		int data;
	};

	template <typename U>
	class B {
	public:
		void callBAF() {
			A<int> atmpobj;
			atmpobj.data = 5;
			std::cout << atmpobj.data << std::endl;
		}
	};
}
namespace _nmsp3 {
	template <typename T>
	class A2 {
		friend  T;
		//friend class CF;
	private:
		int data;
	};

	class CF {
	public:
		void callCFAF() {
			A2<CF> aobj1;
			aobj1.data = 12;
			std::cout << aobj1.data << std::endl;

			/*A2<int> aobj2;
			aobj2.data = 12;*/
		}
	};
}

namespace _nmsp4 {
	//template<typename U, typename V> void func(U val1, V val2);
	template<typename Z>
	class Men {
		friend void func2(Men<Z>& tmpmen) {
			for (int i = 0; i < 1; ++i)
				tmpmen.funcmen();
		}

		//friend void func<int, int>(int, int);
		//friend void func<int>(int, int);
	/*	friend void func<>(int, int);
		friend void func<>(float, int);
		friend void func<>(int, float);*/

		template<typename U, typename V>friend void func(U val1, V val2);

	private:
		void funcmen() const {
			std::cout << "Men:funcmen被调用了" << std::endl;
		};
	};


	template<typename U, typename V>
	void func(U val1, V val2) {
		/*cout << "val1 = " << val1 << endl;
		cout << "val2 = " << val2 << endl;*/
		//Men mymen;
		Men<int> mymen;
		mymen.funcmen(); //这行报错
	};

	template<>
	void func(int val1, double val2) {
		Men<int> mymen;
		mymen.funcmen();
	}
}

int main() {
	/*****   友元类   *****/
	//让类模板的某个实例成为友元类
	/*_nmsp1::B<long> bobj;
	bobj.callBAF();*/

	//让类模板成为友元类模板
	/*_nmsp2::B<long> bobj;
	bobj.callBAF();*/

	//让类型模板参数成为友元类
	_nmsp3::CF mycfobj;
	mycfobj.callCFAF();
	
	//_nmsp3::A2<_nmsp3::CF> aobj1;
	//aobj1.data = 12;   无法访问

	/*****   友元函数   *****/
	//让函数模板的某个实例成为友元函数
	_nmsp4::Men<double> mymen2;
	func2(mymen2);  //直接调用Men类模板中定义的友元函数func2
	_nmsp4::Men<int> mymen3;
	func2(mymen3);

	return 0;
}
