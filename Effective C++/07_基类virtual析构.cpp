#include <iostream>
#include <string>
using namespace std;

// ��ֻ��������ӡ��
class PrintClass
{
public:
	PrintClass(string& func) {
		m_func = func;
		cout << m_func << "����PrintClass" << endl; 
	}
	~PrintClass() { 
		cout << m_func << "����PrintClass" << endl;
	}

private:
	string m_func;
};

/*
	����������������ʽ�Ǵ������������class��ʼ����
	�����ÿһ��base class
	���������������д���һ���Ը��������ĵ��ã����Ժ��������ṩ����
	�����©�����������ᱧԹ
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