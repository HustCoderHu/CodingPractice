#include <iostream>

class Singleton {
private:
    static Singleton *inst; // 1
    Singleton() {} // 2

public:
    static Singleton* getInst() { // 3
        if (nullptr == inst)
            inst = new Singleton();
        return inst;
    }
    void show() {
        std::cout << "singletonOperation" << std::endl;
    }

    ~Singleton() {
        delete inst;
    }
};

Singleton* Singleton::inst = nullptr;

using namespace std;

int main(int argc, char *argv[])
{
    Singleton* inst = Singleton::getInst();
    inst->show();
    return 0;
}
