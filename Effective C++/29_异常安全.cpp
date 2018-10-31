#include <functional>
#include <iostream>

namespace ProblemDemo {

class Lock {
  public:
    explicit Lock(std::mutex *pm) : mutexPtr(pm, [](std::mutex *p){std::cout << "123"; p->unlock();})
    {
        mutexPtr.get()->lock();
    }

  private:
    // 采用shared_ptr而不用std::metux metuxPtr，考虑到Lock被拷贝。
    std::shared_ptr<std::mutex> mutexPtr;
};

struct Image {
    Image(std::istream &imgSrc) {
        id = 0;
    };

    int id;
};

class Menu {
    public: 
        void changeBackground(std:: istream& imgSrc) {
            Lock ml(&mutex);
            delete bgImage;
            ++ imageChanges;
            bgImage = new Image(imgSrc);
        }

    private:
        std::mutex mutex; // 互斥器
        Image* bgImage;
        int imageChanges;
};

}

int main() {
    return 0;
}