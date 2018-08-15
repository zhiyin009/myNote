#include "iostream"
#include "vector"

// swap原本是STL的一部分，而后成为异常安全性变成的脊柱，以及用来处理自我复制可能性的一种常见机制。

// 缺省情况下swap操作可由程序库提供的swap算法完成,其典型实现：
// namespace std {
//     template <typename T>
//     void swap(T& a, T& b) {
//         T temp(a);
//         a = b;
//         b = temp;
//     }
// }

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
/* 
    我们希望std::swap当Widget被置换时真正做到置换其内部的pImpl指针。这个思路的做法之一是：将std::swap
    针对Widget特化。下面是基本构想：

    namespace std {
        template<>
        void swap<Widget>(Widget& lhs, Widget& rhs) {
            swap(a.pImpl, b.pImpl);
        }
    }

    函数一开始“template<>”表示它是std::swap的一个全特化版本，函数名之后的“<Widget>”表示这一特化版本系
    针对“T是Widget”而设计的。换句话说一般性的swap template施行于Widgets身上就会启用这个版本。
    通常我们不能改变std命名空间内的任何东西，但可以为标准templates制造特化版本。
    尽管如此，这个函数仍然不能通过编译，因为它企图访问a和b的pImpl指针，而那是private。
*/

// =================================================================

// class Widget {
//     public:
//         void swap(Widget& other) {
//             using std::swap;
//             swap(pImpl, other.pImpl);
//         }

//     private:
//         WidgetImpl *pImpl; // 指针，指向对象Widget数据。
// };

// namespace std {
//     template<>
//     void swap<Widget>(Widget& lhs, Widget& rhs) {
//         lhs.swap(rhs);
//     }
// }

/* 
    
 */
