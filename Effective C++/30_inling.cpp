#include <iostream>

class Person {
    public:
        int age() const { return theAge; }

    private:
        int theAge;
};

namespace InlineDemo
{
/* 
  "max 是个 template"带出了一项观察结果，我们发现 inline 函数和 templates 两者通常被定义于头文件内。
  这使得某些程序员以为 function templates 一定必须是 inline。
*/
template<typename T>
inline const T& std::max(const T& a, const T& b)
{ return a < b ? b : a; }
}
