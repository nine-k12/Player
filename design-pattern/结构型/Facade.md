外观模式
=======

为复杂系统提供一个简单接口，使得耦合大大降低，子系统更容易使用
   |  系统结构  |
   -------------
   | 数据访问层 |
   |   外观层   |
   | 业务逻辑层 |
   |   外观层   |
   |   表示层   |

```cpp
class Facade{
private:
    SubSystem1* _one;
    SubSystem2* _two;
public:
    Facade(){
        _one = new SubSystem1;
        _two = new SubSystem2;
    }

    void methodA(){
        _one->method1();
        _two->method2();
    }

    void methodB(){
        _one->method1();
    }
}

class SubSystem1{
public:
    SubSystem1() {}
    ~SubSystem1() {}
    void method1(){}
}

class SubSystem2{
public:
    SubSystem2() {}
    ~SubSystem2() {}
    void method2(){}
}

// 客户端代码
void main(){
    Facade* facade = new Facade;
    facade->methodA();
    delete facade;
}
```