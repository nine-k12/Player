代理模式
=======
两个互不认识的对象提供一种代理以控制对象的访问

```cpp
// 本例中sender通过代理送给Receiver礼物

// 收送礼物双方都是人
class People{
private:
    string _name;
public:
    People(const string& name):_name(name){}
    ~People(){}
}

// 代理和赠送方的公共接口
class GiveGift{
public:
    GiveGift(){}
    virtual ~GiveGift(){}
    void GiveFlowers();
}

// 代理
class Proxy: public GiveGift{
private:
    Sender _sender;
public:
    Proxy(const People& people){
        _sender = new Sender(people);
    }
    ~Proxy() {delete _sender;}
    void GiveFlowers() {_sender.GiveFlowers();}
}

// 被代理的赠送方
class Sender: public GiveGift{
private:
    People _recv;
public:
    Sender(const People& people):_recv(people){}
    void GiveFlowers(){cout << "give flowers.";}
}

// 客户端程序
void main(){
    // 知道接收放，代理随便找一个人将东西送给接收者
    People receiver = new People("Jone");
    Proxy senderProxy = new Proxy(receiver);
    senderProxy->GiveFlowers();
    delete receiver;
    delete senderProxy;
}
```

代理种类：
1、远程代理：
    为一个对象在不同的地址空间提供局部代理，可以隐藏一个对象存在于不同地址空间的事实
2、虚拟代理：
    根据需要创建开销很大的对象，通过它来存放 需要很长时间的真实对象
3、安全代理：
    用于控制真实对象访问时的权限
4、智能指引：
    当调用真实的对象时，代理处理另外一些事。通过代理在访问一个对象时附加一些内务处理
    