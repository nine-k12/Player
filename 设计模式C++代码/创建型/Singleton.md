单例模式
=======
主要解决一个全局使用类频繁的创建和销毁的问题

使类仅有一个实例，并且提供一个访问它的全局访问点 ，该实例被所有程序模块共享。通过让类自身负责保存它唯一的实例，这个类可以保证没有其他实例可以被创建，并且它可以提供一个访问该实例的方法
```cpp
// 懒汉模式
class Singleton{
private:
    static Singleton* _singleton;
    Singleton() {}
    ~Singleton() {
        if(_singleton)
            delete _singleton;
    }
    Singleton(const Singleton&) {}
    Singleton& operator=(const Singleton&) {}

public:
    Singleton& operator=(const Singleton&) = delete;
    Singleton (const Singleton&) = delete;
    static Singleton* GetInstance(){
        if(_singleton == nullptr){
            Lock lock; // 基于作用域的加锁，超出作用域，自动调用析构函数解锁
            if(_singleton == nullptr){
                _singleton = new Singleton;
            }
        }

        return _singleton;
    }
}
Singleton::_singleton = nullptr;

// 客户端代码
void main(){
    Singleton* s1 = Singleton->GetInstance();
    Singleton* s2 = Singleton->GetInstance();
    if(s1 == s2)
        cout << "s1 = s2";
    delete s1;
    delete s2;
}

// 饿汉模式
class Singleton{
private:
    static Singleton* _singleton = new Singleton();
    Singleton() {}
    ~Singleton() {
        delete _singleton;
    }
    Singleton(const Singleton&) {}
    Singleton& operator=(const Singleton&) {}

public:
    static Singleton* GetInstance(){
        return _singleton;
    }
}
```
单例模式与实用类的静态方法：
实用类知识一些方法属性的集合，它不保存状态，仅提供静态方法或静态属性供人使用，且不能用于集成多态，而单例模式虽然实例唯一，但是可以有子类集成。

简单代码方便理解，可能存在内存泄露的问题，且多线程时，若多个线程同时调用GetInstance则可能实例化多个对象

