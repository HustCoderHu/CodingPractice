#include <iostream>

class Target {
public:
    Target(){}
    virtual ~Target(){}
    virtual void request() {
        std::cout << "Target::Request()" << std::endl;
    } //定义标准接口
};

class Adaptee { // 被适配的类
public:
    Adaptee(){}
    virtual ~Adaptee(){}

    void specificRequest() {
        std::cout << "Adaptee::SpecificRequest()" << std::endl;
    }

};

// 对象模式
class Adapter : public Target {
public:
    Adapter() : m_pAdaptee(new Adaptee) {}
    Adapter(Adaptee *adaptee) : m_pAdaptee(adaptee) {}
    virtual ~Adapter(){}

    virtual void request() {
        m_pAdaptee->specificRequest();
    }

private:
    Adaptee* m_pAdaptee;

};

// 类模式
class Adapter2 : public Target, private Adaptee {
public:
    Adapter2(){}
    ~Adapter2();
    virtual void request() { //实现Target定义的Request接口
        specificRequest();
    }
};

using namespace std;

int main(int argc, char *argv[])
{
//    Adaptee * adaptee  = new Adaptee();
    Target* tar = new Adapter();
    tar->request();
    return 0;
}
