#include <iostream>
#include <vector>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996)

namespace _nmsp1 {
	template <typename T>
	void myfunc(const T& t) {
		cout << "myfunc函数模板执行了" << endl;
	}

	//void myfunc(int tmpvalue)
	void myfunc(unsigned int tmpvalue) {
		cout << "myfunc函数执行了" << endl;
	}
}
/***   替换失败并不是一个错误 SFINAE   ***/
namespace _nmsp2 {
	template <typename T>
	typename T::size_type mydouble(const T& t) {
		return t[0] * 2;
	}

	int mydouble(int i) {
		return i * 2;
	}
}
/***   enable_if   ***/
namespace _nmsp3 {
	template <typename T>
	struct MEB {
		using type = T;
	};

	//// STRUCT TEMPLATE enable_if
	//template <bool _Test, class _Ty = void> //泛化版本
	//struct enable_if {};

	//template <class _Ty>     //偏特化版本
	//struct enable_if<true, _Ty> {
	//	using type = _Ty;
	//};
}
//enable_if 用于函数模板中
namespace _nmsp4 {
	template<typename T>
	//typename std::enable_if< (sizeof(T) > 2) >::type  funceb()
	//std::enable_if_t< (sizeof(T) > 2) >  funceb()
	std::enable_if_t< (sizeof(T) > 2), T >  funceb() {
		//......
		T myt = {};
		return myt;
	}

	//template <bool _Test, class _Ty = void>
	//using enable_if_t = typename enable_if<_Test, _Ty>::type;
}
//enable_if 用于类模板中
namespace _nmsp5 {
	template<typename T>
	//给类型模板定义一个别名
	using StrProcType = std::enable_if_t< std::is_convertible<T, std::string>::value >;

	class Human {
	public:

		//template<typename T>
		template<
			typename T,
			/*typename = std::enable_if_t<
										std::is_convertible<T, std::string>::value
										>*/
			typename = StrProcType<T>
		>

		Human(T&& tmpname) :m_sname(std::forward<T>(tmpname)) {
			cout << "Human(T&& tmpname)执行" << endl;
		}

		Human(const Human& th) : m_sname(th.m_sname) {
			cout << "Human(Human const& th)拷贝构造函数执行" << endl;
		}
		Human(Human&& th) : m_sname(std::move(th.m_sname)) {
			cout << "Human(Human const& th)移动构造函数执行" << endl;
		}

	private:
		string m_sname;  //姓名	

	};
}

int main() {

	//_nmsp1::myfunc(15u);

	/*
	_nmsp2::mydouble(15);	//这里是调用函数

	vector<int> myvec;
	myvec.push_back(15);
	cout << _nmsp2::mydouble(myvec) << endl;   //这里就是调用函数模板
	*/
	/*
	//_nmsp3::MEB<int>::type  abc = 15;
	std::enable_if< (3 > 2) >::type* mypoint1 = nullptr; //等价于void *mypoint1=nullptr;
	//std::enable_if< (3 < 2) >::type* mypoint2 = nullptr;
	*/

	/*
	_nmsp4::funceb<int>();
	//_nmsp4::funceb<char>();
	*/

	//std::is_convertible  用于判读能否从某个类型隐式地转换到另一个类型
	//cout << "string => float: " << std::is_convertible<string, float>::value << endl;   //0  表示false
	//cout << "float => int: " << std::is_convertible<float, int>::value << endl;         //1  表示true

	string sname = "ZhangSan";
	_nmsp5::Human myhuman1(sname);
	_nmsp5::Human myhuman3(myhuman1);   //修改后，这里调用的就是拷贝构造

	return 0;
}
