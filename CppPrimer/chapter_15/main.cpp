#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    return 0;
}

class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double salesPrice):
        bookNo(book), price(salesPrice) { }
    std::string isbn() const { return bookNo; }
    // 返回给定数量的书籍的销售总额
//    virtual double netPrice(std::size_t n) const = 0;
    virtual double netPrice(std::size_t n) const {
        return n * price;
    }
    virtual ~Quote() = default; // 构造
private:
    std::string bookNo;
protected:
    double price = 0.0; // 普通状态下不打折的价格
};

class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;
//    Bulk_quote(const std::string&, double, std::size_t, double);
    Bulk_quote(const std::string& book, double p,
               std::size_t qty, double disc) :
        Quote(book, p), min_qty(qty), discount(disc) { }
    double netPrice(std::size_t) const override; // override 显示注明
private:
    std::size_t min_qty = 0;  // 适用折扣政策的最低购买量
    double discount = 0.0;    // 以小数表示的折扣额
};

// 如果达到了购买书籍的某个最低限量值， 就可以享受折扣价格了
double Bulk_quote::netPrice(size_t cnt) const
{
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

void printTotal(ostream &os, const Quote &item, size_t n)
{
    // 根据 item 的对象类型调用 netPrice
    double ret = item.netPrice(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << endl;
}

// 动态绑定
void testRunTimeBinding(void)
{
    return ;
    Quote basic;
    Bulk_quote bulk;
    printTotal(cout, basic, 20); // Quote 的 netPrice
    printTotal(cout, bulk, 20); // Bulk_quote 的 netPrice
}

// 派生类声明
//class Bulk_quote : public Quote;  // 错误 派生列表不能出现在这里
//class Bulk_quote;                 // 正确

// class Quote;         // 声明但未定义
// 错误 Quote 必须被定义
//class Bulk_quote : public Quote { };
// 禁止继承
class NoDerived final { };  // 不能作为基类

// override 好处，使得程序员的意图更加清晰的同时让编译器可以为我们发现一些错误
// 派生类如果定义了一个函数与基类中虚函数的名字相同但是形参列表不同，编译器将认为
// 新定义的这个函数和基类的虚函数是相互独立的，也就是覆盖失败
struct B {
    virtual void f1(int) const;
    virtual void f2();
    void f3();
};

struct D1 : B {
    void f1(int) const override;    // 正确
//    void f2(int) override;          // 错误 B没有形如f2(int)的函数
//    void f3() override;             // 错误 f3不是虚函数
//    void f4() override;             // 错误 B没有名为f4的函数
};

struct D2 : B {
    void f1(int) const final;       // 不允许后续的其他类覆盖f1(int)
};
struct D3 : D2 {
    void f2();                      // 正确 覆盖从间接基类B继承而来的f2
//    void f1(int) const;             // 错误 final不能覆盖
};

// 虚函数默认实参 基类派生类的默认实参最好一致
// 回避虚函数
void avoidVfunc(void)
{
    // 强行调用基类中定义的函数版本 而不管baseP的动态类型
    // 编译时完成解析
//    double undiscounted = baseP->Quote::netPrice(42);
}
