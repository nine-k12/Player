组合模式
=======
将对象组合成树形结构以表示“部分-整体”的层级结构，组合模式使得用户对单个对象和组合对象的使用具有一致性
当需求中具有部分与整体的层次结构，且希望用户可以忽略组合对象与单个对象之间的区别，统一的操作组合结构中的所有对象时，应该使用组合模式
```cpp
class Component{
private:
    string _name;
public:
    Component():_name("") {}
    Component(const string& name):_name(name) {}
    ~Component() {}
    
    virtual void Add(Component* c){}
    virtual void Remove(Component* c){}
    virtual void Display(int depth){}
}

class Leaf: public Component{
public:
    Leaf(const string& name):Component(name){}

    void Add(Component* c){
        // my code
    }
    void Remove(Component* c){
        // my code
    }
    void Display(int depth){
        // my code
    }   
}

class Composite: public Component{
private:
    list<Component*> _children;
public:
    Composite(const string& name):Component(name){
    }
    ~Composite() {}

    void Add(Component* c){
        _children.push_back(c);
    }
    void Remove(Component* c){
        _children.remove(c);
    }
    void Display(int depth){
        // my code
    }   
}

// 
void main(){
    Composite* root = new Composite("root");
    root->Add(new Leaf("Leaf A"));
    root->Add(new Leaf("Leaf B"));

    Composite* comp1 = new Composite("Composite X");
    comp1->Add(new Leaf("Leaf XA"));
    comp1->Add(new Leaf("Leaf XB"));
    root->Add(comp1);

    Composite* comp2 = new Composite("Composite XY");
    comp2->Add(new Leaf("Leaf XYA"));
    comp2->Add(new Leaf("Leaf XYB"));
    root->Add(comp2);

    root->Add(new Leaf("Leaf C"));
    root->Display();

    delete root;
    delete comp1;
    delete comp2;
}
```
透明模式：
代码中，Leaf类中同样实现了Add, Remove方法，尽管对于Leaf来说不能Add和Remove。这种做法称为透明模式，使得Leaf和Composite对于外界来说没有区别，它们具备完全一致的行为接口。
