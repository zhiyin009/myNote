#include "iostream"

class Base {};
class Derived: public Base {};

int main() {
    // 此类情有可能地址不同，我的osx中是一样的。这种情况下会有个偏移量（offset）在运行期被施行于Derived*指针身上，
    // 用以取得正确的Base*指针值。而多重继承时，这类事情经常发生。
    Derived d;
    Derived *pd = &d;
    Base *pb = &d;
    const Base *cpb = &d;

    pb = const_cast<Base*>(cpb);
    pb = dynamic_cast<Base*>(pd);
    int *pi = reinterpret_cast<int*>(pb); // 实际动作取决于编译器，意味着它不可移植。
    void *vp = static_cast<void*>(pb);

    return 0;
}

/* 
    要点：
    1.转型操作：
    const_cast<T>(expression)：通常用来将对象的常量性转除（cast away the constness）。
    dynamic_cast<T>(expression)：主要用来执行“安全向下转型”（safe downcasting）。
    reinterpret_cast<T>(expression)：意图执行低级转型。
    static_cast<T>(expression)：强迫隐式转换。
    2.避免做出“对象在c++中如何布局”的假设，更不应该以此假设为基础执行转型动作。
    例如将对象地址转型为char*指针然后在它们身上进行指针算数。
    3.如果转型是必要的，试着将它隐藏于某个函数背后。客户随后调用该函数，而不需要将转型放在他们的代码里。
    4.dynamic转型效率较低，可以使用容器存储指向derived class对象的指针或者使用virtual函数。
    
    注意：子类调用父类函数，错误写法：static_cast<*Base>(this).fun()；正确写法：Base::fun()。

    补充：
    linux内核链表实现中，依据struct结构相对位置获取struct指针。可见c++对象地址在布局上与c的差异。
 */