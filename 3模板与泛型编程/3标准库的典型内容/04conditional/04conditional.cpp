#include <iostream>
#include <vector>

using namespace std;
//#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 

namespace _nmsp1 {
	/*template <bool b, class T, class U>
	struct conditional {
		using type = T;
	};

	template <class T, class U>
	struct conditional<false, T, U> {
		using type = U;
	};*/


}


int main() {

	std::conditional<true, int, double>::type tmp1;
	std::conditional<false, int, double>::type tmp2;

	cout << "tmp1的类型为：" << typeid(decltype(tmp1)).name() << endl;
	cout << "tmp2的类型为：" << typeid(decltype(tmp2)).name() << endl;



	int i = 35;
	if (i > 100) {
		cout << "i > 100" << endl;
	}
	else {
		if (i > 80) {
			cout << "i > 80 并且 <= 100" << endl;
		}
		else {
			if (i > 40) {
				cout << "i > 40 并且 <= 80" << endl;
			}
			else {
				cout << "i <= 40" << endl;
			}
		}
	}

	//模仿上面的逻辑

	constexpr int j = 35; 					   //假设给进去的是35
	std::conditional< (j > 100), double,      //值>100，tsvar是double类型
		std::conditional< (j > 80), float,   //值在80~100之间，tsvar是float类型
		std::conditional< (j > 40), int, //值在40~80之间，tsvar是int类型
		char                  		      //值不超过40，tsvar是char类型
			>::type
		>::type
	>::type tsvar;
	cout << "tsvar的类型为：" << typeid(decltype(tsvar)).name() << endl;

}

