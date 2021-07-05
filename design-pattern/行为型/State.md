行为型
======
有限状态机, 将与特定状态相关的行为局部化，并且将不同状态的行为分割开来

```cpp
// 本例状态转换 A -> B -> A
// 用于保存状态的类
class Context{
private:
    State* _state;
public:
    Context():_state(nullptr) {}
    Context(Context* context):_context(context) {}
    ~Context() {
        if(_state){
            delete _state;
            _state = nullptr;
        }
    }

    void Transition(State* state) { 
        if(_state != nullptr){
            delete _state;
            _state = nullptr;
        }
        _state = state;
    } 

    void Request(){
        _state->Handle();
    }
}

class State{
protected:
    Context* _context;
public:
    void SetContext(Context* context){
        _context = context;
    }
    virtual ~State() {}

    virtual void Handle(Context* context) = 0;
}

class ConcreteStateA: public State{
public:
    void Handle(){
        cout << "This state A";
        _context->Transition(new ConcreteStateB);
    }
}

class ConcreteStateB: public State{
public:
    void Handle(){
        cout << "This state B";
        _context->Transition(new ConcreteStateA);
    }
}

//
void main(){
    Context* c = new Context(new ConcreteStateA); // A
    c->Request(); // A -> B
    c->Request(); // B -> A
    c->Request(); // A -> B
    delete c;
}
```