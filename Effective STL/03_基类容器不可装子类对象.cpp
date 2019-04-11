#include <iostream>
#include <vector>
using namespace std;

class BaseClass {
 public:
  BaseClass() { n = 3; }
  virtual ~BaseClass() {}

  int n;
};

class DerivedClass : public BaseClass {
 public:
  DerivedClass() { m = 5; }
  virtual ~DerivedClass() {}

  int m;
};

namespace ErrorDemo {
/*
    感性来讲：我子类就不是BaseClass了吗，凭什么丢东西！
    理性来讲：然而vector申请的连续空间，每个隔间只能容纳一个BaseClass对象，DerivedClass多余的东西也将被割离
 */
void run() {
  vector<BaseClass> bcv;
  DerivedClass dc;
  bcv.push_back(dc);
  DerivedClass *dcp = static_cast<DerivedClass *>(&bcv[0]);
  cout << dcp->n << endl;
  cout << dcp->m << endl;
}
}  // namespace ErrorDemo

namespace CommonDemo {
void run() {
  vector<BaseClass *> bcv;
  DerivedClass *dc = new DerivedClass;
  bcv.push_back(dc);
  DerivedClass *dcp = static_cast<DerivedClass *>(bcv[0]);
  cout << dcp->n << endl;
  cout << dcp->m << endl;
}
}  // namespace CommonDemo

namespace AwesomeDemo {
/*
    这方法可以建立长度10的BaseClass Vector，而且跳过初始化过程。
 */
void run() {
  int maxNumWidgets = 10;

  BaseClass wl[10];  //长度10，初始化
  vector<BaseClass> vw;
  vw.reserve(maxNumWidgets);  //长度10，不带初始化
}
}  // namespace AwesomeDemo

int main() {
  //   using namespace ErrorDemo;
  //   using namespace CommonDemo;
  using namespace AwesomeDemo;
  run();

  return 0;
}