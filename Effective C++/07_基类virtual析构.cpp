#include <iostream>
#include <string>
using namespace std;

// 我只是用来打印的
class PrintClass
{
public:
	PrintClass(string& func) {
		m_func = func;
		cout << m_func << "构造PrintClass" << endl; 
	}
	~PrintClass() { 
		cout << m_func << "析构PrintClass" << endl;
	}

private:
	string m_func;
};

/*
	析构函数的运作方式是从最深层派生的class开始析构
	其次是每一个base class
	编译器会在子类中创建一个对父类析构的调用，所以函数必须提供定义
	如果遗漏，链接器将会抱怨
*/
class BaseClass
{
public:
	BaseClass() { pp = new PrintClass(string(__FUNCTION__)); }
	~BaseClass() { delete(pp); }

private:
	PrintClass* pp;
};

class Subclass: public BaseClass
{
public:
	Subclass() { 
		pp1 = new PrintClass(string(__FUNCTION__)); 
	}
	~Subclass() { delete(pp1); }

private:
	PrintClass* pp1;
};

int main()
{
	auto test = new Subclass;
	BaseClass *test_base = dynamic_cast<BaseClass*>(test);
	delete(test_base);
	system("pause");
}