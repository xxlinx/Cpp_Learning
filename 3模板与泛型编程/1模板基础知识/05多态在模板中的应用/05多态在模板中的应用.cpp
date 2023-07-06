#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <deque>

using namespace std;

/*****  一个简单的多态演示  ******/
namespace _nmsp1 {
	class Human {
	public:
		virtual void eat(){
			cout << "人类以米饭和面食为主!" << endl;
		}
		virtual ~Human() {} //作为父类存在时一般应该书写虚析构函数
	};

	class Men :public Human{
	public:
		virtual void eat(){
			cout << "男人喜欢吃面食!" << endl;
		}
	};

	class Women :public Human{
	public:
		virtual void eat(){
			cout << "女人喜欢吃米饭!" << endl;
		}
	};
}

/*****  模板中的多态  ******/
namespace _nmsp2{
	class Men{
	public:
		void eat(){
			cout << "男人喜欢吃面食!" << endl;
		}
	};
	class Women{
	public:
		void eat(){
			cout << "女人喜欢吃米饭!" << endl;
		}
	};

	//函数模板
	template<typename T>
	void eatTmpl(T& obj){
		obj.eat();
	}
}

int main() {

	/*
	_nmsp1::Men objmen;
	_nmsp1::Women objwomen;
	//父类引用绑定（指向）子类对象，以表现多态
	_nmsp1::Human& yinbase1 = objmen;
	_nmsp1::Human& yinbase2 = objwomen;
	yinbase1.eat();   //男人喜欢吃面食!
	yinbase2.eat();   //女人喜欢吃米饭!
	*/

	_nmsp2::Men objmen;
	_nmsp2::Women objwomen;
	_nmsp2::eatTmpl(objmen);
	_nmsp2::eatTmpl(objwomen);


	return 0;
}