#include "iostream"

class Rational {
public:
    Rational(int numerator = 0, int denominator = 1);

    // 取分子分母
    int numerator() const;
    int denominator() const;

    // 如果写成成员函数形式，下面运算将会出错
    // const Rational operator* (const Rational& rhs) const;
};


const Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator() * rhs.numerator(),
                    lhs.denominator() * rhs.denominator());
}

int main() {
    Rational oneHalf(1, 2);
    Rational oneEighth(1, 8);
    Rational result = oneHalf * oneEighth;  // 正确
    result = result * oneHalf;              // 正确
    
    result = oneHalf * 2;                   // 正确
    result = 2 * oneHalf;                   // 错误
    /* 
    result = 2.operator*(oneHalf);          // 尝试2(int)*操作符
    result = operator*(2, oneHalf);         // 尝试全局方法
     */
}

/* 
    问：
    是否需要令Rational operator*(const Rational& lhs, const Rational& rhs)成为友元函数。
    思考：
    1.在本节中，operator*借助Rational的public接口完成任务，也推翻了上章的“与
    类相关的函数应该包在一起”的旧有认识。
    2.member函数的反面是non-member函数而非friend函数，不该因为无法成为member而
    直接赋予non-member。
 */