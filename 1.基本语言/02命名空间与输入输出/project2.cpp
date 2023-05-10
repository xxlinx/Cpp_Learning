#include <iostream>

//李四编写
namespace lisi {
	void radius() {
		std::cout << "李四radius的函数" << std::endl;
	}
}
//定义过相当于打开了已经存在的命名空间为其添加新的成员
//之前没有定义，就相当于定义了新的命名空间
namespace lisi {
	void radius2() {
		std::cout << "李四radius2的函数" << std::endl;
	}
}