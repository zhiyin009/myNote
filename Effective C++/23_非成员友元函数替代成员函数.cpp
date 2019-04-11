#include "iostream"

/*
    假设将有一个类用来表示网页浏览器，用户需要一个清理资源的函数。
    clearEveryThing包括：清除下载元素缓存区，清除访问过的URL，移除系统中的所有cookies
 */

class WebBrowser {
 public:
  void clearCache();
  void clearHistory();
  void removeCookies();

  // 或许会将clearEveryThing定义于类中
  void clearEveryThing();
};

/*
    可行性讨论
    1.封装性：如果将访问成员变量的函数个数作为封装性的指标，那么将清除函数放在类内将降低封装性。
    2.依赖性：如果将函数以功能划分，如：书签，cookie，那么类外便于将功能函数放置于不用文件中的，
    拆解相关函数编译依赖关系。namespace可以跨越多个源码文件class不能。
 */

// 头文件”webbrowser.h“，WebBrowser自身核心机能
namespace WebBrowserStuff {
class WebBrowser {};
}  // namespace WebBrowserStuff

// 头文件”webbrowserbookmarks.h“
namespace WebBrowserStuff {
// 书签相关便利的函数
}

// 头文件”webbrowsercookies.h“
namespace WebBrowserStuff {
// cookie相关便利的函数
}

/*
    思考
    1.看此章前，对“封装”的理解是一个类紧紧包裹着与之相关的函数操作。而本节以成员变量的暴露程度
    （可访问成员变量的函数个数）帮助理解“封装概念”。
    2.学习运用namespace的可跨源文件特性，构建功能层面的函数接口方法。
 */