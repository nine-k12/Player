备忘录模式
=========
在不破坏封装性的前提下，捕获一个对象得到内部状态，并在该对象之外保存这个状态，这样以后就可以将该对象恢复到原先保存的状态
备忘录的发起人创建一个备忘录，用以记录当前时刻它的内部状态，并可以在将来利用该备忘录恢复此刻的状态
备忘录的管理者只负责保存好备忘录，不能怼备忘录内容进行检查

```cpp
class Memento{
private:
    string _state;
public:
    Memento(string state):_state(state) {}
    ~Memento() {}

    string GetState() {return _state;}
}

// 备忘录发起者
class Originator{
private:
    string _state;
public:
    Memento* CreateMemento(){
        return new Memento(_state);
    }

    void SetMemento(Memento* memento){
        _state = memento->GetState();
    }

    void show() {cout << _state << endl;}

    string GetState() {return _state;}
    void SetState(string state) {_state = state;}
}

// 备忘录管理者
class CareTaker{
private:
    Memento* _memento;
public:
    CareTaker():_memento(nullptr){}
    ~CareTaker() {}

    Memento* GetMemento() {return _memento}
    Memento* SetMemento(Memento* memento) {_memento = memento;}
}

//
void main(){
    Originatoro* = new Originator;
    o->SetState("On");
    o->show();

    CareTaker* c = new CareTaker;
    c->SetMemento(o->CreateMemento);
    o->SetState("Off");
    o->show();

    o->SetMemento(c->GetMemento());
    o->show();

    delete o;
    delete c;
}
```