#include <iostream>
using namespace std;

/*
	C++ iostream����������ڷ�ֹcopy��Ϊ
	member������friend����֮�ڿ�����������������������֮���Ǳ���������
*/
class Uncopyable
{
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};

/*
	����������������������������������������
*/
class UncopyableBase
{
protected:
	UncopyableBase() {}
	~UncopyableBase() {}

private:
	UncopyableBase(const UncopyableBase&);
	UncopyableBase& operator=(const UncopyableBase&);
};

class Test :private UncopyableBase
{
public:
	Test() {}
	~Test() {}
};

int main()
{
	Test* a = new Test();
	Test b = Test(*a);

	system("pause");
}