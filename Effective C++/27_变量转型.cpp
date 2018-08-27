#include "iostream"

/* 
    要点：
    1.转型操作：
    const_cast<T>(expression)：通常用来将对象的常量性转除（cast away the constness）。
    dynamic_cast<T>(expression)：主要用来执行“安全向下转型”（safe downcasting）。
    reinterpret_cast<T>(expression)：意图执行低级转型。
    static_cast<T>(expression)：强迫隐式转换。
 */