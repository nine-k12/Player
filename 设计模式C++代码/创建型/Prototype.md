原型模式
=======
用原型实例来指定创建对象的种类，通过拷贝原型来创建新的对象
```cpp
class Prototype{
private:
    string _id;
public:
    Prototype(const string& id):_id(id){}
    ~Prototype(){}

    void GetId() {return _id;}
    virtual Prototype* Clone() = 0;
}

class ConcretePrototype: public Prototype{
public:
    ConcretePrototype(const string& id):Prototype(id){}

    Prototype* Clone() {
        // 注意深复制和浅复制
        return new ConcretePrototype(this->GetId());
    }
}

// 
void main(){
    ConcretePrototype* p1 = new ConcretePrototype("me");
    ConcretePrototype* c1 = p1->clone();
    delete p1;
    delete c1;
}
```