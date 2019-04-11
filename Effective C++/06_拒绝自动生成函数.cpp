#include <iostream>
using namespace std;

/*
C++ iostream程序库中用于防止copy行为
member函数或friend函数之内拷贝操作，链接器报错。除此之外是编译器报错
*/
class Uncopyable {
 private:
  Uncopyable(const Uncopyable&);
  Uncopyable& operator=(const Uncopyable&);
};

/*
将上述链接器报错移至编译器发出（更早察觉）
*/
class UncopyableBase {
 protected:
  UncopyableBase() {}
  ~UncopyableBase() {}

 private:
  UncopyableBase(const UncopyableBase&);
  UncopyableBase& operator=(const UncopyableBase&);
};

class Test : private UncopyableBase {
 public:
  Test() {}
  ~Test() {}
};

int main() {
  Test* a = new Test();
  Test b = Test(*a);

  system("pause");
}