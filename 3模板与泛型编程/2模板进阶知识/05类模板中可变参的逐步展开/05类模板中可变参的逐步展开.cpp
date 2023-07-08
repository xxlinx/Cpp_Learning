#include <iostream>
#include <vector>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 

namespace _nmsp1 {
	template<typename... Args>
	class myclasst {
	public:
		myclasst() {
			cout << "myclasst::myclasst()执行了，可变参个数=" << sizeof...(Args) << endl;
		}
	};

	template<typename... Args>
	//class myclasst2 : public myclasst<Args...>
	//class myclasst2 : public myclasst <Args>...
	//class myclasst2 : public myclasst <Args,char>...
	class myclasst2 : public myclasst <Args, Args...>... {
	public:
		myclasst2() {
			cout << "myclasst2::myclasst2()执行了，可变参个数=" << sizeof...(Args) << endl;
		}
	};

}

int main() {
	_nmsp1::myclasst2<double, float, int> tmpobj;

	return 0;
}