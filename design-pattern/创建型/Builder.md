建造者模式
=========
    为某种产品的生产提供一种流程化的装配指导
```cpp
// 本例画一个小人
class PersonBuilder{
protected:
    Graph _graph; //  一个画纸 class Pen;
    Pen _pen; // 一个画笔 class Pen
public:
    PersonBuilder(Graph graph, Pen pen){
        _graph = graph;
        _pen = pen;
    }
    ~PersonBuilder() {}

    virtual void BuildHead();
    virtual void BuildBody();
    virtual void BuildLeftArm();
    virtual void BuildRightArm();
    virtual void BuildLeftLeg();
    virtual void BuildRightLeg();
}

class ThinPersonBuilder: public PersonBuilder{
public:
    ThinPersonBuilder(Graph graph, Pen pen):PersonBuilder(graph, pen){}
    ~ThinPersonBuilder() {}

    void BuildHead() {//my code}
    void BuildBody() {//my code}
    void BuildLeftArm() {//my code}
    void BuildRightArm() {//my code}
    void BuildLeftLeg() {//my code}
    void BuildRightLeg() {//my code}
}

// 指导构建过程
class PersonDirector{
private:
    PersonBuilder _personBuilder;
public:
    PersonDirector(PersonBuilder personBuilder):_personBuilder(personBuilder) {}
    ~PersonDirector() {}

    void CreatePerson(){
        _personBuilder.BuildHead();
        _personBuilder.BuildBody();
        _personBuilder.BuildLeftArm();
        _personBuilder.BuildRightArm();
        _personBuilder.BuildLeftLeg();
        _personBuilder.BuildRightLeg();
    }
}

// 客户端代码
void main(){
    Pen pen = Pen();
    Graph graph = Graph();
    ThinPersonBuilder* builder = new ThinPersonBuilder(graph, pen);
    PersonDirector director = new PersonDirector(*builder);
    director.CreatePerson();
}
```