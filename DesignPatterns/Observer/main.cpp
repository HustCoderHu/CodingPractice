#include <iostream>
#include <vector>

using namespace std;

class Observer {
public:
    Observer() { }
    virtual ~Observer() { }
    virtual update() = 0;

};

class Subject {

public:
    Subject() { }
    virtual ~Subject() { }

    void attach(Observer * obsr) { obsrVer.push_back(obsr); }
    void detach(Observer * obsr){
//        for(int i = 0; i < 5; ++i)
        fot (auto iter = obsrVer.begin(); iter != obsrVer.end(); ++iter) {

        }
    }

    void notify();
private:
    vector<Observer*> obsrVer;
};


int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    return 0;
}
