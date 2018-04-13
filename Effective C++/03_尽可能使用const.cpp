#include <iostream>
using namespace std;

class TClass
{
public:
	TClass() { memset(m_list, 0, sizeof(m_list)); }

	size_t &operator[](int i) { return ++m_list[i]; }	// ��const�汾�ı�ֵ
	const size_t &operator[](int i) const				// const�汾���÷�const���ƻ�logical constness
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