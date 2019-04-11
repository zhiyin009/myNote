#include <iostream>

namespace CommonDemo {

class Lock {
 public:
  explicit Lock(std::mutex *pm)
      : mutexPtr(pm, [](std::mutex *p) { p->unlock(); }) {
    mutexPtr.get()->lock();
  }

 private:
  // 采用shared_ptr而不用std::metux metuxPtr，考虑到Lock被拷贝。
  std::shared_ptr<std::mutex> mutexPtr;
};

struct Image {
  Image(std::istream &imgSrc) { /* Read from istream */
  }
};
}  // namespace CommonDemo

namespace ProblemDemo {
using Lock = CommonDemo::Lock;
using Image = CommonDemo::Image;

class Menu {
 public:
  Menu() {
    bgImage = NULL;
    imageChanges = 0;
  }

  void changeBackground(std::istream &imgSrc) {
    Lock ml(&mutex);
    delete bgImage;
    ++imageChanges;
    bgImage = new Image(imgSrc);
  }

 private:
  std::mutex mutex;  // 互斥器
  Image *bgImage;
  int imageChanges;
};
}  // namespace ProblemDemo

namespace BetterDemo {
using Lock = CommonDemo::Lock;
using Image = CommonDemo::Image;

/*
   这种做法几乎足够提供 changeBackground 强烈的异常安全保证。
   美中不足是参数imgSrc，如果Image构造函数抛出异常，有可能输入流的读取
   记号已被移走，而这样的搬移对程序其余部分是一种可见的状态改变。
 */
class Menu {
 public:
  Menu() { imageChanges = 0; }

  void changeBackground(std::istream &imgSrc) {
    Lock ml(&mutex);
    pImpl.reset(new Image(imgSrc));
    ++imageChanges;
  }

 private:
  std::mutex mutex;  // 互斥器
  std::shared_ptr<Image> pImpl;
  int imageChanges;
};

/* PrettyMenu Impl
   封装性已经由 pImpl 是 private 保证了。
   也可以将 PMImpl
   嵌套于PrettyMenu中，但打包问题（packaging，如“独立撰写异常安全码”），
   是我们这里所挂虑的事。
 */
struct PMImpl {
  std::shared_ptr<Image> bgImage;
  int imageChanges;
};

/*
   copy and swap 是典型的提供强烈保证的做法
 */
class PrettyMenu {
 public:
  void changeBackground(std::istream &imgSrc) {
    using std::swap;
    Lock ml(&mutex);
    std::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));

    pNew->bgImage.reset(new Image(imgSrc));  // 修改副本
    ++pNew->imageChanges;

    swap(pNew, pImpl);
  }

 private:
  std::mutex mutex;  // 互斥器
  std::shared_ptr<PMImpl> pImpl;
};
}  // namespace BetterDemo

int main() {
  using PMenu = ProblemDemo::Menu;
  PMenu *pm = new PMenu();
  pm->changeBackground(std::cin);

  return 0;
}

/*
   要点：
   异常安全性的函数满足条件：
    不泄漏任何资源：如资源锁在new失败后未解锁。
    不允许数据败坏：如资源指针在new失败后被改变。
   异常安全性的函数会提供以下保证：
    基本承诺：如果异常被抛出，程序内的任何事物仍然保持在有效状态下。
    强烈保证：如果异常被抛出，程序状态不改变。
    不抛掷保证：承诺绝不抛出异常，因为它们总是能够完成它们原先承诺的功能。
 */