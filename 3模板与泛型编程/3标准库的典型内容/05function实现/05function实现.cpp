#include <iostream>
#include <vector>
#include <functional>

using namespace std;
//#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 

void myfunc(int tmpvalue) //一个普通函数
{
	std::cout << "myfunc执行了：tmpvalue = " << tmpvalue << endl;
}
void callObjFunc(std::function<void(int)> cobj)
{
	cobj(120);
}
/***   实现类似std::function的功能   ***/

//可调用对象处理器
template<typename T, typename... Args>
class CFObjHandler
{
public:
	virtual T invoke(Args... args) const {}; //虚函数，因为后续要创建子类
};
//子类模板
template<typename U, typename T, typename... Args>
class CFObjHandlerChild :public CFObjHandler<T, Args...> {
public:
	//构造函数	
	CFObjHandlerChild(U&& tmpfuncobj) :functor(std::forward<U>(tmpfuncobj)) {
		/*cout << "-------------------" << endl;
		using boost::typeindex::type_id_with_cvr;
		cout << "U1111=" << type_id_with_cvr<U>().pretty_name() << endl;
		cout << "tmprv11111=" << type_id_with_cvr<decltype(tmpfuncobj)>().pretty_name() << endl;*/
	}

	virtual T invoke(Args... args) const {
		return functor(std::forward<Args>(args)...);
	}

private:
	U functor;  //U是一个可调用对象类型，functor用于保存可调用对象的一个拷贝
};


//泛化版本
template<typename T>
class CallFuncObj;
//特化版本
template<typename T, typename... Args>
class CallFuncObj<T(Args...)> {
public:
	//构造函数模板
	template<typename U>
	CallFuncObj(U&& acobj) { //可以接收各种可调用对象（函数对象、lambda表达式等等）
		handler = new CFObjHandlerChild<U, T, Args...>(std::forward<U>(acobj));
	}
	~CallFuncObj() {
		delete handler;
	}

	//重载()，实现该类对象的可调用
	T operator()(Args... args) const {
		return handler->invoke(std::forward<Args>(args)...);  //使用std::forward实现参数的完美转发，保持原始实参的左值或者右值性
	}

private:
	CFObjHandler<T, Args...>* handler;   //可调用对象处理器

};



void callObjFunc2(CallFuncObj<void(int)> cobj) {
	cobj(120);   //这里会调用类模板的 operator() 成员函数
}


int main() {
	/*
	callObjFunc(myfunc);				//myfunc执行了：tmpvalue = 120
	callObjFunc([](int tmpvalue) {      //形参可以是一个lambda表达式
		std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl;
		});   //lambda表达式执行了，tmpvalue = 120
	*/

	//效果实现
	callObjFunc2(myfunc);
	callObjFunc2([](int tmpvalue) {
		std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl;
		});

	CallFuncObj<void(int)> f1 = myfunc;
	f1(1200);

	CallFuncObj<void(int)> f2 = [](int tmpvalue) {
		std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl;
	};
	f2(1200);

	auto ftest = [](int tmpvalue) {std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl; };
	CallFuncObj<void(int)> f3 = ftest;
	f3(1200);

	return 0;
}