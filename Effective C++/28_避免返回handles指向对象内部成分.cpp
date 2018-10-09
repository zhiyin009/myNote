#include "iostream"
#include "memory"

// 设计一个正方形类，其中需要一对对角坐标来确定正方形。
class Point {
  public:
    Point(int a, int b): x(a), y(b) {}
    void setX(int val) { x = val; }
    void setY(int val) { y = val; }

  private:
    int x;
    int y;    
};

struct RectData {
    RectData(Point &ulp, Point &drp): ulhc(ulp), drhc(drp) {}

    Point ulhc;     // ulhc = "upper left-hand corner"
    Point drhc;
};

namespace ProblemDemo {
  class Rectangle
  {
  public:
    Rectangle(RectData data)
    {
      pData.reset(new RectData(data));
    }

    Point& upperLeft() const { return pData->ulhc; }
    Point& lowwerRight() const { return pData->drhc; }

  private:
    std::shared_ptr<RectData> pData;
  };
}

namespace BetterDemo {
  class Rectangle
  {
  public:
    Rectangle(RectData data)
    {
      pData.reset(new RectData(data));
    }

    const Point& upperLeft() const { return pData->ulhc; }
    const Point& lowwerRight() const { return pData->drhc; }

  private:
    std::shared_ptr<RectData> pData;
  };

  const Point *danglingPoint()
  {
    Point coord1(1, 2);
    Point coord2(2, 4);
    Rectangle rec(RectData(coord1, coord2));
    return &(rec.upperLeft());
  }
}

// 如上写法，当一个函数返回指向成员的指针，仅仅是函数本身为const，而忽略了指针本身的修改操作
int main() {
  Point coord1(1, 2);
  Point coord2(2, 4);
  {
    using Rectangle = ProblemDemo::Rectangle;
    Rectangle rec(RectData(coord1, coord2));
    rec.upperLeft().setX(3);
  }

  {
    using Rectangle = BetterDemo::Rectangle;
    Rectangle rec(RectData(coord1, coord2));
    rec.upperLeft().setX(3);
  }

  // 尽管如此，仍有存在dangling handles的风险。
  {
    using BetterDemo::danglingPoint;
    const Point *pp = danglingPoint(); // 虚吊（dangling）句柄
  }
}
/* 
  要点：
  1.避免返回指针指向“访问级别较低”的成员。
  2.返回指针，留意虚吊。

  反思：
  1.注意
  A: rec.upperLeft().setX(3);
  B: Point p = rec.upperLeft(); p.setX(3)
  C: Point &p = rec.upperLeft(); p.setX(3)
  A和B为不同情况，A和C才是相同的。
 */