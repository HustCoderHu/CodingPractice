#include <iostream>
#include <string>

class Pet {
public:
//    char* brand;
    virtual void sounds() = 0;
    virtual ~Pet() = default;
};

class Cat : public Pet {
public:
    void sounds() override {
        std::cout << "meow" << std::endl;
    }

    ~Cat(){}
};

class Dog : public Pet {
public:
    void sounds() override {
        std::cout << "bark" << std::endl;
    }

    ~Dog(){}
};

class PetShop_base {
public:
//    Factory(const string &name) : pName(name) {}
    virtual Pet* getPet() = 0;
    virtual ~PetShop_base() = default;
};

class CatZone : public PetShop_base {
public:
//    Factory_A(const string &name) : pName(name) {}
    Pet* getPet() override {
        return new Cat();
    }

    ~CatZone(){}
};

class DogZone : public PetShop_base {
public:
//    Factory_B(const string &name) : pName(name) {}
    Pet* getPet() override {
        return new Dog();
    }

    ~DogZone(){}
};

using namespace std;

int main(int argc, char *argv[])
{
    PetShop_base* dogzone = new DogZone();
    Pet* dog = dogzone->getPet();

    PetShop_base* catzone = new CatZone();
    Pet* cat = catzone->getPet();

////    Product* proa = Factory_A("aaa").createProduct();

    cat->sounds();
    dog->sounds();

    delete cat;
    delete catzone;
    delete dog;
    delete dogzone;

    return 0;
}
