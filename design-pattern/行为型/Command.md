命令模式
=======
将请求封装为一个对象，从而可以利用不同的请求对客户进行参数化，从而支持对请求排队、记录请求日志、撤销操作

```cpp
// 本例描述在餐厅顾客向服务员点餐，服务员通知厨师做菜的过程
class Cook{ // 厨师
public:
    Cook() {}
    ~Cook() {}
    
    void BakeMutton() {//my code}
    void BakeChickenWing(){//my code}
}

// 给厨师发出的订单命令
class Command{
private:
    Cook* _cook; // 命令接受者
public:
    Command(Cook* cook){_cook = cook;}
    ~Command() {}

    virtual void ExecteCommand(){}
}

class BakeMuttonCommand: public Command{
public:
    BakeMuttonCommand(Cook* cook):Command(cook){}
    ~BakeMuttonCommand() {}

    void ExecteCommand(){
        _cook->BakeMutton();
    }
}

class BakeChickenWingCommand: public Command{
public:
    BakeChickenWingCommand(Cook* cook):Command(cook){}
    ~BakeChickenWingCommand() {}

    void ExecteCommand(){
        _cook->BakeChickenWing();
    }
}

// 服务员
class Waiter{
private:
    list<Command*> _orders;
public:
    Waiter(){
    }
    ~Waiter() {}

    void SetOrder(Command* command){
        if(command == ){ // 若没有菜了，该订单不能满足
            // mycode
        }
        else {
            _orders.push_back(command);
        }
    }

    void CancelOrder(Command* command){ // 提交当前所有订单
        _orders.remove(command);
    }

    void Notify(){ // my code}
}

//客户端代码
void main(){
    Cook* cook = new Cook;
    Command* c1 = new BakeMuttonCommand(cook);
    Command* c2 = new BakeChickenWingCommand(cook);
    Waiter* waiter = new Waiter;
    waiter->SetOrder(c1);
    waiter->SetOrder(c2);
    waiter->Notify();

    delete cook;
    delete c1;
    delete c2;
    delete waiter;
}
```