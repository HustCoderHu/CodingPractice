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
    double netPrice(std::size_t) const override; // override 显示注明
};

double printTotal(ostream &os, const Quote &item, size_t n)
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
