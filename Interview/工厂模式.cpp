#include <iostream>
using namespace std;

/*
    运用template，写一个与生产类型无关的工厂模式
 */

class GunBase {
 public:
  GunBase(string name) { this->name = name; }
  void printName() { cout << "It's " << this->name << endl; }
  virtual void shoot() = 0;
  virtual ~GunBase() {}

 private:
  string name;
};

class AK : public GunBase {
 public:
  AK() : GunBase("AK") {}
  void shoot() {
    this->printName();
    cout << "dadada" << endl;
  }
};

class UMP : public GunBase {
 public:
  UMP() : GunBase("UMP") {}
  void shoot() {
    this->printName();
    cout << "piupiupiu" << endl;
  }
};

class GunFactory {
 public:
  template <class T>
  static T* create() {
    return new T();
  }
};

int main() {
  GunBase* gun = NULL;
  gun = GunFactory::create<AK>();
  gun->shoot();
  delete gun;

  gun = GunFactory::create<UMP>();
  gun->shoot();
  delete gun;

  gun = NULL;
  return 0;
}