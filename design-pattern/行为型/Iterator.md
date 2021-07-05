迭代器模型
=========
提供一种方法顺序访问一个聚合对象中的各个元素，而又不暴露该对象的内部表示

```cpp
// 抽象聚合体类，将要被迭代器遍历
template<typename T>
class Aggregate{
public:
    virtual Iterator<T>* CreateIterator()
}

template<typename T>
class ConcreteAggregate: public Aggregate{
private:
    list<T> _items;
public:
    ConcreteAggregate(){}
    ~ConcreteAggregate(){}

    int Count(){
        return _items.size();
    }

    T GetItem(int index){
        if(index >= Count() || index < 0)
            return NULL;

        auto it=_items.begin()
        for(; it != _items.end() && index >= 0; it++){
            index--;
        }
        return *it;
    }

    void SetItem(int index, T value){
        if(index < Count()){
            _items->insert();
        }
        auto it = _items.begin();
        std::advance(it, index);
        _items.insert(it, value);
    }

    Iterator<T>* CreateIterator(){
        return new ConcreteIterator(this);
    }
}

// 迭代器抽象类
template<typename T>
class Iterator{ 
// 可以基于该抽象类生成多种遍历方式的迭代器
public:
    Iterator() {}
    virtual ~Iterator() {}
    
    virtual T First();
    virtual T Next();
    virtual bool IsDone();
    virtual T CurrentItem();
}

template<typename T>
class ConcreteIterator: public Iterator{
private:
    ConcreteAggregate* _aggregate;
    int _current;
public:
    ConcreteIterator(ConcreteAggregate* aggregate){
        _aggregate = aggregate;
    }
    ~ConcreteIterator(){}

    T First(){
        return _aggregate->GetItem(0);
    }

    T Next(){
        T res = NULL;
        _current++;
        if(_current < _aggregate->Count()){
            res = _aggregate->GetItem(_current);
        }
        return res;
    }

    bool IsDone(){
        return _current >= _aggregate->Count();
    }
    T CurrentItem(){
        return _aggregate->GetItem(_current);
    }
}

//
void main(){
    ConcreteAggregate<string>* con = new ConcreteAggregate<string>;
    con->SetItem("a");
    con->SetItem("b");
    con->SetItem("c");

    Iterator<string>* it = new ConcreteIterator<string>(con);
    string item = it->First();
    while(!it->IsDone()){
        cout  << it->CurrentItem();
        it->Next();
    }
    delete con;
    delete it;
}
```