#include "iostream"
#include "vector"

// swap原本是STL的一部分，而后成为异常安全性变成的脊柱，以及用来处理自我复制可能性的一种常见机制。

// 缺省情况下swap操作可由程序库提供的swap算法完成,其典型实现：
namespace std {
    template <typename T>
    void swap(T& a, T& b) {
        T temp(a);
        a = b;
        b = temp;
    }
}

// pimpl（pointer to implementation）类型数据，如果以Widget class，实现起来：
class WidgetImpl {                  // 针对Widget数据设计的类
    private:
        int a, b, c;                // 可能有很多数据
        std::vector<double> v;      // 意味着复制时间很长
};

class Widget {                      // 使用pimpl
    public:
        Widget(const Widget& rhs);
        Widget& operator=(const Widget& rhs) {
            *pImpl = *(rhs.pImpl);  // 仅复制指针
        }

    private:
        WidgetImpl* pImpl;          // 指针，指向对象Widget数据。
};

    // 我们希望std::swap当Widget被置换时真正做到置换其内部的pImpl指针。这个思路的做法之一是：将std::swap
    // 针对Widget特化。下面是基本构想：

namespace std {
    template<>
    void swap<Widget>(Widget& lhs, Widget& rhs) {
        swap(a.pImpl, b.pImpl);
    }
}

    // 函数一开始“template<>”表示它是std::swap的一个全特化版本，函数名之后的“<Widget>”表示这一特化版本系
    // 针对“T是Widget”而设计的。换句话说一般性的swap template施行于Widgets身上就会启用这个版本。
    // 通常我们不能改变std命名空间内的任何东西，但可以为标准templates制造特化版本。
    // 尽管如此，这个函数仍然不能通过编译，因为它企图访问a和b的pImpl指针，而那是private。


// =================================================================

class Widget {
    public:
        void swap(Widget& other) {
            using std::swap;
            swap(pImpl, other.pImpl);
        }

    private:
        WidgetImpl *pImpl; // 指针，指向对象Widget数据。
};

namespace std {
    template<>
    void swap<Widget>(Widget& lhs, Widget& rhs) {
        lhs.swap(rhs);
    }
}

// =================================================================


    // 然而假设Widget和WidgetImpl都是class template而非class，将WidgetImpl内的数据类型
    // 加以参数化：

    template<typename T>
    class WidgetImpl {};

    template<typename T>
    class Widget {};

    namespace std {
        template<typename T>
        void swap< Widget<T> >(Widget<T>& a, Widget<T>& b) {
            a.swap(b);
        }
    }

    // 这样做，我们将试图偏特化一个function template，但c++只允许对class template偏特化，无法通过编译,
    // 试图改为添加重载版本
    namespace std {
        template<typename T>
        void swap(Widget<T>& a, Widget<T>& b) {
            a.swap(b);
        }
    }

    // 然而std是个特殊的命名空间，客户可以全特化std内的templates，但不可以添加新的templates到std里头。
    
    // 如何在他人调用swap时能够取得我们提供的高效template特定版本。我们可以声明一个non-member swap让
    // 它调用member swap，但不再将non-member swap声明为std::swap的特化版本或重载版本。假设Widget的
    // 所有相关技能都被置于命名空间WidgetStuff内：


// =================================================================

namespace WidgetStuff {
    template<typename T>
    class WidgetImpl {
        public:
        // private:
            std::vector<T> vec;
    };

    template<typename T>
    class Widget{
        public:
            Widget(T *impl) {
                pImpl = impl;
            }
        // private:
            T *pImpl;
    };

    template<typename T>
    void swap(Widget<T>& a, Widget<T>& b) {
        a.swap(b);
    }
}

int main() {
    using namespace WidgetStuff;
    WidgetImpl<int> *impl = new WidgetImpl<int>;
    impl->vec.push_back(6);
    Widget< WidgetImpl<int> > wid(impl);
    auto a = wid.pImpl->vec[0];
    std::cout << a;
}

/* 
    **成员版swap绝不可抛出异常**
    这一约束只施行于成员版！不可施行于非成员版，因为swap缺省版本是以copy构造函数和copy assignment操作符
    为基础，而一般情况下两者都允许抛出异常。因此自定义版本的swap往往不仅仅提供高效置换，而且不抛出异常。
    一般而言这两个swap特性是连在一起的，因为高效的swaps几乎是基于对内置类型的操作，而内置类型绝不会抛出异常。
 */

/* 
    要点：
    1.当std::swap对你的类型效率不高，提供一个swap成员函数，并确定这个函数不抛出异常。
    2.如果提供一个member swap，也应该提供一个non-member swap来调用前者，对于classes，请特化std::swap。
    3.调用swap时针对std::swap使用using声明式，然后调用swap并且不带任何“命名空间资格修饰”。
    4.为“用户定义类型”进行std template全特化是好的，但千万不要尝试在std内加入某些对std而言全新的东西。

    补充：
    1.template class支持全特化，偏特化；template func仅支持全特化。
 */