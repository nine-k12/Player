工厂方法 Factory Method
=======================
主要解决接口选择的问题，该模式下定义一个创建对象得到接口，让其子类自己决定实例化哪一个工厂类，使其创建爱你过程延迟到子类进行

工厂方法定义一个用于创建对象的抽象方法, 其子类重载该方法返回一个实例

##一、简单工厂
从简单工厂中直接获得具有相应功能的产品
```cpp
// 本例：一个计算器
class OperationFactory{
pubilc:
    Operation* createOperate(string operate){
        Operation oper = nullptr;
        switch(operate){
            case "+": oper = new OperationAdd; break;
            case "-": oper = new OperationSub; break;
        }
        return oper;
    }
}
// 执行不同计算工能的产品
class Operation{
private:
    double _numA;
    double _numB;
    
public:
    Operation():_numA(0),_numB(0){}
    Operation(double numA, double numB):_numA(numA),_numB(numB){}
    ~Operation() {}

    virtual void setNumberA(double val){_numA = val;}
    virtual void setNumberB(double val){_numB = val;}

    virtual double setNumberA(){return _numA;}
    virtual double setNumberB(){return_numB;}

    virtual double getResult(){}
}

class OperationAdd: public Operation{
    double getResult(){
        return _numA + _numB;
    }
}

class OperationSub: public Operation{
    double getResult(){
        return _numA - _numB;
    }
}
// 客户端代码
void main(){
    // 直接从工厂中获得想要的产品
    Operation* oper = OperationFactory.createOperate("+");
    oper->setNumberA(1);
    oper->setNumberB(3);
    double res = oper->getResult();
    delete oper;
}
```
可以看到，当希望向简单工厂中添加新功能时，由于工厂中包含判断逻辑，因此需要在OperationFactory中增加case分支，并添加由Operation派生得到的产品。应用方式不会发生变化。因此简单工厂对拓展与修改同时开放，违反了开放-封闭原则。

----------------------------------------------------------------
##二、工厂方法
获取所需的工厂, 然后从工厂中取得所需的产品
eg: 先获取加法工厂AddFactory, 再从加法工厂中获取执行加法操作的产品OperationAdd
```cpp
class BaseOperationFactory{
    Operation* CreateOperation();
}

class AddFactory: public BaseOperationFactory{
public:
    Operation* createOperation(){
        return new OperationAdd;
    }
}

class SubFactory: public BaseOperationFactory{
public:
    Operation* createOperation(){
        return new OperationSub;
    }  
}

// 客户端代码
void main(){
    // 先获得能生产所需产品的工厂（这些工厂都生产同一类产品），再从这个工厂中获取#单个#产品
    OperationFactory* operFactory = new AddFactory;  // (1)
    Operation* oper =  operFactory->CreateOperation();
    oper->setNumberA(1);
    oper->setNumberB(3);
    double res = oper->getResult();
    delete operFactory;
    delete  oper;
}
```
可以看到当我们需要增加新功能时，需要添加由BaseOperationFactory派生得到的子工厂和由由Operation派生得到的相应的产品，并且还需要修改客户端代码 (1)。仅进行了拓展没有对原代码进行修改，不违反开发-封闭原则。

----------------------------------------------------------------
##三、抽象工厂
抽象工厂管理 不同的工厂，每个工厂都可以提供特定的产品。在运行时，需要什么产品就实例化其对应的具体工厂，从工厂中获得产品
提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类
```cpp
// 本例: 对 sql 和 Access 数据库进行操作
// 两种具体的产品
class User{
private:
    int _id;
    string name;
public:
    int getId() {return _id;}
    void setId(int val):_id(val){}

    string getName() {return _name;}
    void setName(const String& name):_name(name){}
}

class Department{
private:
    int _id;
    string name;
public:
    int getId() {return _id;}
    void setId(int val):_id(val){}

    string getName() {return _name;}
    void setName(const String& name):_name(name){}
}

// 抽象工厂，其中包含所有产品创建所需的抽象方法，此例中即为创建User和Department
在运行时会创建一个具体工厂的实例如 SqlServerFactory
class BaseFactory{
public:
    virtual BaseUser* CreateUser();
    virtual BaseDepartment* CreateDepartment();
}

class SqlServerFactory: public BaseFactory{
public:
    BaseUser* CreateUser(){
        return new SqlServerUser;
    }

    BaseDepartment* createDepartment(){
        return new SqlServerDepartment;
    }
}

class AccessServerFactory{
public:
    BaseUser* CreateUser{
        return new AccessServerUser;
    }

    BaseDepartment* createDepartment(){
        return new AccessServerDepartment;
    }
}

// 第一种产品工厂 User
class BaseUser{
public:
    virtual void Insert(const User& user);
    virtual User GetUser(int Id) const;
}

class SqlServerUser: BaseUser{
public:
    void Insert(const User& user){// my code}
    User GetUser(int Id) const{// my code}
}

class AccessServerUser: BaseUser{
public:
    void Insert(const User& user){// my code}
    void GetUser(int Id) const{// my code}
}

// 第二种产品工厂 Department
class BaseDepartment{
public:
    virtual void Insert(const Department& department);
    virtual Department GetDepartment(int Id) const;
}

class SqlServerDepartment: BaseDepartment{
public:
    void Insert(const Department& Department){ // my code }
    Department GetUser(int Id) const{ // my code }
}

class AccessServerDepartment: BaseDepartment{
public:
    void Insert(const Department& Department){// my code}
    Department GetDepartment(int Id) const{// my code}
}

// 客户端代码
void main(){
    // 不同的工厂有一个共同的父类，可以获得生产不同产品的工厂，生产一组产品，如 user, department
    User* user = new User;
    BaseFactory* factory = new SqlServerFactory; // 需要一个sql数据库的工厂
    BaseUser* iu = factory->CreateUser();
    iu->Insert(user);
    iu->GetUser(1);
    delete user;
    delete factory;
    delete iu;
}
```
如果要在抽象工厂中增加新的功能，则需要修改 BaseFactory, SqlServerFactory, AccessServerFactory,以及增加相应的产品的类, 此外还需要修改每处客户端代码

----------------------------------------------------------------
##四、反射机制
只根据类的名字(String)创建类的实例
用一个字典保存 key=类的名字，value=创建类对象函数的入口
```cpp
class MyClass{
private:
    string _name;
public:
    MyClass(string& name):_name(name){}
    ~MyClass(){}
    void show(){
        cout << _name << endl;
    }
};

int main(){
    #define CREATE(cls_name) \
        MyClass* ins_##cls_name = new MyClass(cls_name); \
        ins_##cls_name->show();
    string hello = "Hello";
    string world = "World";
    CREATE(hello);
    CREATE(world);
    return 0;
}
/* 输出
hello 
world
*/
```
