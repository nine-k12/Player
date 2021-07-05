模板方法
=======
当需要在某一细节层次一致的一个过程或一系列步骤，但其个别步骤在更详细的层次上的实现可能不同时，通常考虑模板方法
将不变的行为移到超类中，去除子类中重复的代码
```cpp
class TestPaper{
public:
    TestPaper() {}
    virtual ~TestPaper() {}

    virtual string answer1() {return "";}
    virtual string answer2() {return "";}

    void TestQusetion1() {
        cout << "Q1:";
        cout << "answer: " << answer1();
    }
    void TestQusetion2() {
        cout << "Q2:";
        cout << "answer: " << answer2();
    }
}

class TestPaperA: public TestPaper{
public:
    string answer1() {return "a";}
    string answer2() {return "b";}
}

// 客户端代码
void main(){
    TestPaper* stuA = new TestPaperA;
    stuA->TestQusetion1();
    stuA->TestQusetion2();
    delete stuA;
}
```