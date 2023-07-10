#include <iostream>
#include <vector>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 

namespace _nmsp1 {
	template <bool val>
	struct BoolConstant {
		using type = BoolConstant;  //写成using type = BoolConstant<val>;也行
		static constexpr bool value = val;
	};
	using TrueType = BoolConstant<true>;
	using FalseType = BoolConstant<false>;

	//1.TrueType  FalseType 代表一种类类型
	//2.一般是被当作基类被继承


	//一个类型模板参数，一个非类型模板参数
	template <typename T, bool val>  
	struct AClass {
		AClass() {//构造函数
			cout << "AClass::AClass()执行了" << endl;
			/*if constexpr (val){
				T tmpa = 15;
			}
			else{
				T tmpa = "abc";   // if constexpr : 编译期间if 语句 可以解决这个bug
			}*/
			AClassEx(BoolConstant<val>()); //创建一临时对象
		}

		void AClassEx(TrueType) {
			T tmpa = 15;
		}
		void AClassEx(FalseType) {
			T tmpa = "abc";
		}
	};
}


int main() {

	_nmsp1::AClass<int, true> tmpobj1;
	_nmsp1::AClass<string, false> tmpobj2;

	return 0;
}