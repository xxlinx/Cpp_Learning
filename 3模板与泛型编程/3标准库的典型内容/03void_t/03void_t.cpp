#include <iostream>
#include <vector>

using namespace std;
#include <boost/type_index.hpp>

#pragma warning(disable : 4996) 


/***   编译器如何选择泛化版本还是特化版本    ***/
namespace _nmsp1 {
	//template<typename...Args>
	//using void_t = void;

	struct NoInnerType {
		int m_i;
	};
	struct HaveInnerType {
		using type = int;
		void myfunc() {}
	};


	//泛化版本
	template<typename T, typename U = std::void_t<> >
	struct HasTypeMem : std::false_type  //struct默认是public继承，class默认是private继承
	{
	};

	//特化版本
	template<typename T>
	struct HasTypeMem<T, std::void_t<typename T::type>> : std::true_type
	{
	};

	//带参数的宏定义，注意“反斜杠”表示下一行接着本行来，是本行的一部分 
#define _HAS_TYPE_MEM_(parMTpNm) \
	template<typename T, typename U = std::void_t<> > \
	struct HTM_##parMTpNm : std::false_type { }; \
	template<typename T> \
	struct HTM_##parMTpNm<T, std::void_t<typename T::parMTpNm>> : std::true_type { };

	_HAS_TYPE_MEM_(type)
	_HAS_TYPE_MEM_(sizetype)

	//------------------------------------------------------
	//泛化版本
	//template<typename T, typename U = std::void_t<> >
	template<typename T, typename U = int >
	struct HasMember : std::false_type{
	};
	//特化版本
	template<typename T>
	struct HasMember<T, std::void_t<decltype(T::m_i)>> : std::true_type
	{
	};

	//------------------------------------------------------
	//泛化版本
	template<typename T, typename U = std::void_t<> >
	struct HasMemFunc : std::false_type {
	};
	//特化版本
	template<typename T>
	struct HasMemFunc<T, std::void_t<decltype(std::declval<T>().myfunc())>> : std::true_type
	{
	};

}
/*****    实现 is_copy_assignable    *****/
namespace _nmsp2 {
	class ACPABL {  //一个空类
	};

	class BCPABL {    //实现一下自己的拷贝运算符
	public:
		BCPABL& operator= (const BCPABL& tmpobj)
		{
			return *this;
		};
	};

	class CCPABL {    //把拷贝运算符设置为私有或者标记为delete
	public:
		CCPABL& operator= (const CCPABL& tmpobj) = delete;
	};

	//-------------------------------------------------
	// 利用 void_t 实现类似功能
	//泛化版本
	template<typename T, typename U = std::void_t<>>
	struct IsCopyAssignable : std::false_type
	{
	};

	//特化版本
	template<typename T>
	struct IsCopyAssignable<T, std::void_t<decltype(std::declval<T&>() = std::declval<const T&>())> > : std::true_type
	{
	};

}

/***    综合范例    ***/
namespace _nmsp3 {
	//泛化版本
	template<typename T, typename U, typename V = std::void_t<>>  //T,U,V都可以省略不写，变成template<typename, typename, typename=std::void_t<>>
	struct IfCanAdd : std::false_type {
	};

	//特化版本
	template<typename T, typename U>
	struct IfCanAdd<T, U, std::void_t<decltype(std::declval<T>() + std::declval<U>())>> : std::true_type
	{
	};

	/*
	template<typename T, typename U>
	struct VecAddResult {
		//using type = decltype(T() + U());
		using type = decltype(std::declval<T>() + std::declval<U>());
	};*/
	//泛化版本
	template<typename T, typename U, bool ifcando = IfCanAdd<T, U>::value>
	struct VecAddResult {
		using type = decltype(std::declval<T>() + std::declval<U>());
	};

	//特化版本
	template<typename T, typename U>
	struct VecAddResult<T, U, false> {
	};


	template<typename T, typename U>
	using VecAddResult_t = typename VecAddResult<T, U>::type;


	template<typename T, typename U>
	//std::vector<T> operator+(std::vector<T> const& vec1, std::vector<U> const& vec2);
	//std::vector< typename VecAddResult<T, U>::type > operator+(std::vector<T> const& vec1, std::vector<U> const& vec2)
	std::vector< VecAddResult_t<T, U> > operator+(std::vector<T> const& vec1, std::vector<U> const& vec2)
	{
		//随便写几句代码
		//std::vector<  typename VecAddResult<T, U>::type  > tmpvec;
		std::vector<  VecAddResult_t<T, U>  > tmpvec;
		return tmpvec;

	}

	//--------------------
	struct elemC {
		elemC(int tmpvalue); //带一个参数的构造函数
		elemC operator+(const elemC& tmppar); //重载加法运算符以支持加法操作,VecAddResult中会用到
	};

}


int main() {

	/*
	//判断类中是否存在某个类型别名
	cout << _nmsp1::HasTypeMem<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HasTypeMem<_nmsp1::HaveInnerType>::value << endl;

	cout << _nmsp1::HTM_type<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HTM_type<_nmsp1::HaveInnerType>::value << endl;
	cout << _nmsp1::HTM_sizetype<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HTM_sizetype<_nmsp1::HaveInnerType>::value << endl;
	//判断类中是否存在某个成员变量
	cout << _nmsp1::HasMember<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HasMember<_nmsp1::HaveInnerType>::value << endl; 
	//判断类中是否存在某个成员函数
	cout << _nmsp1::HasMemFunc<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HasMemFunc<_nmsp1::HaveInnerType>::value << endl; 
	* /

	/*
	_nmsp2::ACPABL aobj1;
	_nmsp2::ACPABL aobj2;
	aobj2 = aobj1;   //可以进行拷贝复制

	_nmsp2::BCPABL bobj1;
	_nmsp2::BCPABL bobj2;
	bobj2 = bobj1;     //可以进行拷贝复制

	//_nmsp2::CCPABL cobj1;
	//_nmsp2::CCPABL cobj2;
	//cobj2 = cobj1;    // 不可以进行拷贝复制
	*/
	/*
	cout << "int: " << std::is_copy_assignable<int>::value << endl;     //int: 1
	cout << "ACPABL: " << std::is_copy_assignable<_nmsp2::ACPABL>::value << endl;      // ACPABL: 1
	cout << "BCPABL: " << std::is_copy_assignable<_nmsp2::BCPABL>::value << endl;   //  BCPABL: 1
	cout << "CCPABL: " << std::is_copy_assignable<_nmsp2::CCPABL>::value << endl;  //  CCPABL: 0

	cout << "int: " << _nmsp2::IsCopyAssignable<int>::value << endl;
	cout << "ACPABL: " << _nmsp2::IsCopyAssignable<_nmsp2::ACPABL>::value << endl;
	cout << "BCPABL: " << _nmsp2::IsCopyAssignable<_nmsp2::BCPABL>::value << endl;
	cout << "CCPABL: " << _nmsp2::IsCopyAssignable<_nmsp2::CCPABL>::value << endl; 
	*/

	int i = int();  //其实就是定义一个int类型变量，而且这种定义方式会把i初值设置为0。
	i = 5;
	double j = double(); //其实就是定义一个double类型变量，而且这种定义方式会把j初值设置为0.0
	j = 13.6;

	std::vector<_nmsp3::elemC> veca;
	std::vector<_nmsp3::elemC> vecb;
	veca + vecb; //会调用全局的operator+(......)函数模板



	return 0;
}