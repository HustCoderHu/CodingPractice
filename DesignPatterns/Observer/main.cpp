#include <iostream>
#include <vector>

using namespace std;

class Subject;

class Observer {
public:
//    Observer() { }
    virtual ~Observer() { }
    virtual void update(int) = 0;

};

class Subject {
public:
//    Subject() { }
    virtual ~Subject() { }
    virtual void attach(Observer *) = 0;
    virtual void detach(Observer *) = 0;
    virtual void notify() = 0;
};

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(Subject *sub) : m_pSubject(sub) { }
    ~ConcreteObserver() { cout << "ConcreteObserver deconstruct" << endl; }

    void update(int val) override {
        cout << "get update, new state: " << val << endl;
    }
private:
     Subject *m_pSubject;
};

class ConcreteSubject : public Subject {
public:
//    ConcreteSubject() { }
//    ~ConcreteSubject() { }

    void attach(Observer * obsr) override { obsrVer.push_back(obsr); }
    void detach(Observer * obsr) override {
//        for(int i = 0; i < 5; ++i)
        for (auto iter = obsrVer.begin(); iter != obsrVer.end(); ++iter) {
            if (*iter == obsr) {
                obsrVer.erase(iter);
                break;
            }
        }
    }

    void notify() override {
        for (auto obVar : obsrVer)
            obVar->update(m_iState);
    }
    int getState() { return m_iState; }
    void setState(int i) { m_iState = i; }

private:
    vector<Observer*> obsrVer;
    int m_iState;
};

int main(int argc, char *argv[])
{
    ConcreteSubject *pSub = new ConcreteSubject();
    Observer *pOb0 = new ConcreteObserver(pSub);
    Observer *pOb1 = new ConcreteObserver(pSub);

    pSub->attach(pOb0);
    pSub->attach(pOb1);

    pSub->setState(2);
    pSub->notify();

    pSub->detach(pOb0);

    pSub->setState(3);
    pSub->notify();

    delete pOb0;
    delete pOb1;
    delete pSub;

    return 0;
}

// http://design-patterns.readthedocs.io/zh_CN/latest/behavioral_patterns/observer.html
// www.jellythink.com/archives/359
