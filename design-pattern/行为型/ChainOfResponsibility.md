职责链模式
=========
使多个对象都有机会处理请求，从而避免请求的发送者和接受者之间的耦合关系，将这个对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。请求者不必知道哪个对象会来处理其请求，总之该请求最终会被处理

![avar](职责链结构模式图.png)

```cpp
class Handler{
private:
    Handler* _successor;
public:
    Handler() {}
    ~Handler() {}

    void SetSuccessor(Handler* successor){
        _successor = successor;
    }
    virtual void HandleRequest(int request) {}
}

class ConcreteHandler1: public Handler{
public:
    ConcreteHandler1(){}
    ~ConcreteHandler1(){}

    void HandleRequest(int request) {
        if(request >= 0 && request < 10){
            // 有权处理
        }
        else if(_successor != nullptr){
            _successor->HandleRequest(request);  // 转交给 下一个
        }
    }

}

class ConcreteHandler2: public Handler{
public:
    ConcreteHandler2(){}
    ~ConcreteHandler2(){}

    void HandleRequest(int request) {
        if(request >= 10 && request < 20){
            // 有权处理
        }
        else if(_successor != nullptr){
            _successor->HandleRequest(request);  // 转交给 下一个
        }
    }

}

// 客户端代码
void main(){
    Handler* h1 = new ConcreteHandler1;
    Handler* h2 = new ConcreteHandler2;
    h1->SetSuccessor(h2);
    int[] request = {2,3,14,19};
    for(int r: request)
        h1->HandleRequest(r);
    delete h1;
    delete h2;
}
```