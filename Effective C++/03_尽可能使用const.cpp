#include <iostream>
using namespace std;

class TClass
{
public:
    TClass() { memset(m_list, 0, sizeof(m_list)); }

	size_t &operator[](int i) { return ++m_list[i]; }   // 非const版本改变值
	const size_t &operator[](int i) const               // const版本调用非const，破坏logical constness
	{
		return static_cast<const size_t&>(
			const_cast<TClass&>(*this)[i]);
	}

private:
	size_t m_list[20];
};

int main()
{
	const TClass tc;
	cout << tc[3] << endl;
	cout << tc[3];
	system("pause");
}