访问者模式
=========
可以在不改变元素类的情况下重新定义作用于这些元素的操作
访问者模式通常应用于数据结构相对稳定的系统，它把数据结构和作用于数据结构上的操作解耦，使得操作集合可以相对自由的演化。

**<center>解释器模式结构图</center>**
![avar](访问者模式结构图.png)

```cpp
// 抽象访问者
class Visitor{
public:
    Visitor() {}
    virtual ~Visitor() {}
    virtual void VisitConcreteElementA(ConcreteElementA* concreteElementA){}
    virtual void VisitConcreteElementB(ConcreteElementB* concreteElementB){}
}

class ConcreteVisitor1: public Visitor{
public:
    ConcreteVisitor1() {}
    ~ConcreteVisitor1() {}
    void VisitConcreteElementA(ConcreteElementA* concreteElementA){//my code}
    void VisitConcreteElementB(ConcreteElementB* concreteElementB){//my code}
}

class ConcreteVisitor2: public Visitor{
public:
    ConcreteVisitor2() {}
    ~ConcreteVisitor2() {}
    void VisitConcreteElementA(ConcreteElementA* concreteElementA){//my code}
    void VisitConcreteElementB(ConcreteElementB* concreteElementB){//my code}
}

// 抽象元素对象
class Element{
public:
    Element() {}
    virtual ~Element() {}
    virtual void Accept(Visitor* visitor){}
}

class ConcreteElementA: public Element{
public:
    ConcreteElementA(){}
    ~ConcreteElementA(){}
    void Accept(Visitor* visitor){
        visitor->VisitConcreteElementA(this);
    }
}

class ConcreteElementB: public Element{
public:
    ConcreteElementB(){}
    ~ConcreteElementB(){}
    void Accept(Visitor* visitor){
        visitor->VisitConcreteElementB(this);
    }
}

// 将对象以一种数据结构组织起来
class ObjectStructure{
private:
    list<Element*> _elemnts;
public:
    ObjectStructure(){}
    ~ObjectStructure(){}

    void Attach(Element* element){
        _elements.push_back(element);
    }
    void Detach(Element* element){
        _elements.remove(element);
    }
    void Accept(Visitor* visitor){
        // 遍历访问元素
    }
}

void main(){
    ObjectStructure* o = new ObjectStructure;
    o->Attach(new ConcreteElementA);
    o->Attach(new ConcreteElementB);

    ConcreteVisitor1* v1 = new ConcreteVisitor1;
    ConcreteVisitor2* v2 = new ConcreteVisitor2;

    o->Accept(v1);
    o->Accept(v2);
    delete o;
    delete v1;
    delete v2;
}
```
