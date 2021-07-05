解释器模式
=========
给定一个语言，定义它的文法的一种表示，并定义一个解释器，这个解释器使用该表示来解释语言中的句子
**<center>解释器模式结构图</center>**
![avar](解释器模式结构图.png)

```cpp
// 此例：正则表达式
// 包含解释器之外的一些全局信息
class Context{
private:
    string _input;
    string _output;
public:
    Context():_input(""),_output("") {}
    ~Context() {}
    void SetInput(const string& input):_input(input){}
    string GetInput() {return _input;}
    void SetOutput(const string& output):_output_(output){}
    string GetOutput() {return _output;}
}

// 声明一个抽象的解释操作
class AbstractExpression{
public:
    AbstractExpression() {}
    ~AbstractExpression() {}
    virtual void Interpret(Context* context){}
}

// 实现与文法中的终结符相关的解释操作
class TerminalExpression: public AbstractExpression{
public:
    TerminalExpression() {}
    ~TerminalExpression() {}
    void Interpret(Context* context){//my code}
}

// 为文法中的非终结符实现解释操作
class NonTerminalExpression: public AbstractExpression{
public:
    NonTerminalExpression() {}
    ~NonTerminalExpression() {}
    void Interpret(Context* context){//my code}
}

// 客户端代码
void main(){
    Context* context = new Context;
    list<AbstractExpression*> mList;
    mList.push_back(new TerminalExpression);
    mList.push_back(new NonTerminalExpression);
    mList.push_back(new TerminalExpression);
    mList.push_back(new TerminalExpression);

    for(AbstractExpression* exp: mList){
        exp->Interpret(context);
    }
    delete context;
}
```
当有一个语言需要解释执行，并且可以将语言中的句子表示为一个抽象语法树时，可使用解释器模式
