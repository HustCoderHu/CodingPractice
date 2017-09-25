#include <iostream>

using namespace std;

class Product {
public:

    virtual const char* getName() = 0;
    virtual ~Product() = default;
private:
    int productID;
};

class Product_A : public Product {
public:
    string productName;
    Product_A(const string &name) : productName(name) {}
    const char* getName() override {
        return productName.c_str();
    }

    ~Product_A(){}
};

class Product_B : public Product {
public:
    string productName;
    Product_B(const string &name) : productName(name) {}
    const char* getName() override {
        return productName.c_str();
    }

    ~Product_B(){}
};

class Factory {
public:
//    Factory(const string &name) : pName(name) {}
    virtual Product* createProduct() = 0;
};

class Factory_A : public Factory {
public:
    string pName;
    Factory_A(const string &name) : pName(name) {}
    Product* createProduct() override {
        return new Product_A(pName);
    }

    ~Factory_A(){}
};

class Factory_B : public Factory {
public:
    string pName;
    Factory_B(const string &name) : pName(name) {}
    Product* createProduct() override {
        return new Product_B(pName);
    }

    ~Factory_B(){}
};

int main(int argc, char *argv[])
{
    Factory* fac = new Factory_B(string("bbb"));
    Product* prob = fac->createProduct();

    Factory* fac2 = new Factory_A(string("aaa"));
    Product* proa = fac2->createProduct();

////    Product* proa = Factory_A("aaa").createProduct();

    cout << proa->getName() << endl;
    cout << prob->getName() << endl;

    delete proa;
    delete fac2;
    delete prob;
    delete fac;
    return 0;
}
