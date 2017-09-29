#include <iostream>
#define SAFE_DELETE(p) if (p) { delete p; p = NULL;}

using namespace std;


class Subject
{
public:
    Subject() {}
    virtual ~Subject() {}

    virtual void Request() = 0;
};

class RealSubject : public Subject
{
public:
    RealSubject() {}
    ~RealSubject() {}

    void Request() {
        cout << "RealSubject Request" << endl;
    }
};

class Proxy : public Subject
{
public:
    Proxy() : m_pRealSubject(nullptr) {}
    ~Proxy() {
        SAFE_DELETE(m_pRealSubject);
    }

    void Request() {
        if (nullptr == m_pRealSubject) {
            m_pRealSubject = new RealSubject();
        }
        cout << "Proxy Request" << endl;
        m_pRealSubject->Request();
    }

private:
    RealSubject *m_pRealSubject;
};

int main(int argc, char *argv[])
{
    Subject *pSubject = new Proxy();
    pSubject->Request();
    SAFE_DELETE(pSubject);

    return 0;
}
