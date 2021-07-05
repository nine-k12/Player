观察者模式
=========
即发布-订阅模式，一种一对多的依赖关系，让多个观察者对象同时监听一个主题对象，这个主题对象在状态发生变化时会通知所有观察者对象，使它们能够更新自己
```cpp
// 抽象被观察者，当其状态发生变化时，将通知其他观察者
class Subject{
public:
    Subject(){}
    ~Subject(){}
    virtual void Attach(const Oberver* observer);
    virtual void Detach(const Oberver* observer);
    virtual void Notify();
}

// 一个具体的被观察者 Boss 
class Boss: public Subject{
private:
    list<Oberver*> _observers; // 对它进行观察的观察者
    string _action; // 被观察者当前的状态

public:
    Boss(){
        _action = "";
    }
    ~Boss(){}

    void Attach(const Oberver* observer){
        _obervers.push_back(oberver);
    }
    void Detach(const Oberver* observer){
        _obervers.remove(observer);
    }
    void Notify(){
        for(const Observer: _observers)
            Observer->Update();
    }

    void SetState(const string& state){
        _action = state;
    }
    string GetState() {return _action;}
}

// 抽象观察者
class Oberver{
protected:
    string _name;
    Subject _sub;
public:
    Observer(const string& name, const Subject& sub){
        _name = name;
        _sub = sub;
    }
    virtual void Update() {}
}

class StockObserver: public Observer{
public:
    StockObserver(const string& name, const Subject& sub):Observer(name, sub){}
    ~StockObserver() {}

    void Update(){// my code}
}

// 客户端代码
void main(){
    Boss* boss = new Boss;
    StockObserver* oberver1 = new StockObserver("Jone", *boss);
    StockObserver* oberver2 = new StockObserver("Hellen", *boss);
    // 被观察的对象 boss, 观察者 observer1, observer2
    boss->Attach(oberver1);
    boss->Attach(oberver2);
    boss->SetState("i'm back."); // 被观察对象状态改变
    boss->Notify(); // 通知所有的观察者

    delete boss;
    delete observer1;
    delete observer2;
}
```

上述代码中，所有观察者被通知主题对象发生变化后，都调用Update方法，但是现实中，不一定 所有的观察者都能够调用Update方法，它们在主题对象发生变化时，可能会有各自不同的处理过程，不一定都会命名为Update
为了解决这个问题，可以使用委托
--------------------------------------------------------
委托对象所搭载的所有方法都必须有相同的参数列表和返回值类型
```cpp
class Subject{
private:
    string _action;
public:
    Subject():_action(""){}
    ~Subject(){}

    virtual void Notify(){}
    void SetState(const string& state){_action = state;}
    string GetState() {return _action;}
}

class Boss: public Subject{
public:
    CMultiDelegate<void, string> update; 
    // 创建一个返回值为void，参数值为string的委托
    void Notify() {update(_action);}
}
```
C++实现委托CMultiDelegate代码见 https://blog.csdn.net/y1196645376/article/details/51408114
```cpp
// 抽象观察者
class Oberver{
protected:
    string _name;
    Subject _sub;
public:
    Observer(string name, Subject sub){
        _name = name;
        _sub = sub;
    }
}

class StockObserver: public Observer{
public:
    StockObserver(const string& name, Subject sub):Observer(name, sub){}
    ~StockObserver() {}

    void Close(){// my code}
}

class SpeakObserver: public Observer{
public:
    SpeakObserver(const string& name, Subject sub):Observer(name, sub){}
    ~SpeakObserver() {}

    void StopSpeak(){// my code}
}
// 客户端代码
void main(){
    Boss* boss = new Boss;
    StockObserver* oberver1 = new StockObserver("Jone", *boss);
    SpeakObserver* oberver2 = new SpeakObserver("Hellen", *boss);

    boss->update +=  //new EventHandle(oberver1->close());
    boss->update +=  // new EventHandle(oberver2->StopSpeak());
    
    boss->SetState(“i'm back.");
    boss.Notify();
}
```