适配器模式
=========
将一个类的接口转换成客户希望的另一个接口，使得两个原本不兼容的接口能够兼容
当系统的数据和行为都正确，但是接口不符时，可以利用适配器使控制范围之外的一个原有对象与某个接口匹配，主要由于希望复用一些现存的类
```cpp
// 需要被适配的类
class Adaptee{ 
public:
    void SpecificRequest(){}
}

// 抽象适配器接口
class Target{
public:
    virtual void Request() = 0;
}

class Adapter: public Target{
private:
    Adaptee* _adaptee;
public:
    Adapter(){
        _adapee = new Adaptee;
    }
    ~Adapter() {
        delete _adapee;
    }

    void Request(){
        _adapee->SpecificRequest();
    }
} 

// 客户端代码
void main(){
    Target target = new Adapter;
    target->Request();
    delete target;
}
```