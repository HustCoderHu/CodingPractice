#include <iostream>

class Singleton {
private:
    static Singleton *inst; // 1
    Singleton() = default; // 2

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
        std::cout << "deconstruct" << std::endl;
        inst = nullptr;
    }
};

Singleton* Singleton::inst = nullptr;

using namespace std;

int main(int argc, char *argv[])
{
    Singleton *inst = Singleton::getInst();
    inst->show();
    delete inst;
    return 0;
}
