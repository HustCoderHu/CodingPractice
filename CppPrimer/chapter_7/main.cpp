#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    return 0;
}

// const 成员函数
class Sales_data {
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

    string isbn() const { return bookNo; }
    // 定义在类内部的函数是隐式的inline
    // 定义在外部也必须要const
    Sales_data(string s) = default; // 要求编译器生成构造函数
    // 类内部 外部定义均可
    Sales_data(const string &s):bookNo(s) {}
    // 非委托构造函数使用对应的实参初始化成员
    Sales_data(const string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(istream &);

    // 其余构造函数全都委托给另一个构造函数
//    Sales_data():Sales_data("", 0, 0) {}
//    Sales_data(std::string s):Sales_data(s, 0, 0) {}
//    Sales_data(std::istream &is):Sales_data()
//    {
//        read(is, *this);
//    }
};


// 编译器自动生成 合成的默认构造函数
class Screen;

class Window_mgr {
public:
    // 窗口中每个屏幕的编号
    using ScreenIndex = std::vector<Screen>::size_type;
    // 按照编号将指定的Screen重置为空白
    void clear(ScreenIndex i);
    ScreenIndex addScreen(const Screen&);
private:
    std::vector<Screen> screens;
//    std::vector<Screen> screens{Screen(24, 80, ' ')};
};
// 返回类习惯出现在类名之前，所以事实上它是位于类的作用域之外，
// 必须要制定哪个类定义了它
Window_mgr::ScreenIndex
Window_mgr::addScreen(const Screen &)
{
//    screens.push_back(s);
//    return screens.size() - 1;
}

class Screen {
    // Windows_mgr的成员可以访问Screen类的私有部分
    // 不存在传递性，即Windows_mgr的友元对Screen无效
    friend class Window_mgr;
    // 只为函数提供访问权限，函数必须先声明
    friend void Window_mgr::clear(ScreenIndex i);

public:
    using pos = std::string::size_type;
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    // 可变数据成员
    mutable size_t access_ctr;
    // 保存一个数值，用于记录成员函数被调用的次数
    // 即使在一个const对象内也能被修改
    // _dispaly()
    void do_display(std::ostream &os) const {
        os << contents;
    }

public:
    Screen() = default; // 因为Screen有另一个构造函数
    // 所以本函数是必需的
    // cursor 被其类内初始值初始化为0
    Screen(pos ht, pos wd, char c): height(ht), width(wd),
        contents(ht*wd, c) { }
    char get() const {
        return contents[cursor];
    }
    inline char get(pos ht, pos wd) const;
    Screen& move(pos r, pos c); // 返回引用
    // myScreen.move(4, 0).set('#');
    // 不返回引用的话，则改变的是副本的内容

    void some_member() const;
    // 根据对象是否是const 重载了display函数
    Screen& display(std::ostream &os) {
        do_display(os); return *this;
    }
    const Screen& display(std::ostream &os) const {
        do_display(os); return *this;
    }
};
void Screen::some_member() const
{
    ++access_ctr;
}


void Window_mgr::clear(ScreenIndex i)
{
    // s 是一个Screen的引用，指向我们想清空的那个屏幕
    Screen &s = screens[i];
    // 将那个选定的Screen重置为空白
    s.contents = string(s.height * s.width, ' ');
}

// 友元声明和作用域
// 友元声明的作用是影响访问权限，它并非普通意义上的声明
struct X {
    friend void f() { /* 友元函数可以定义在类的内部*/ }
//    X() { f(); } // 错误：f还没有被声明
    void g();
    void h();
};
//void X::g() { return f(); } // 错误：f还没有被声明
// 必须在类的外部提供相应的声明从而使得函数可见
void f();                   // 声明那个定义在X中的函数
void X::h() { return f(); } // 正确：现在f的声明在作用域中了

// 类成员初始化
class Y {
    // 按出现顺序初始化
    int i;
    int j;
public:
    // 未定义的：i在j之前被初始化
    Y(int val):j(val), i(j) {}
};

// 常见错误
void common_err(void)
{
//    Sales_data obj(); //定义了一个函数而非对象
//    obj.isbn(); //    // obj是一个函数
//    Sales_data obj;   // obj 是默认初始化的对象
}

// 隐式的类类型转换
// 构造函数只有一个实参时
void forExample(void)
{
    string nullBook = "9-999-99999-9";
//    item.combine(nullBook);
    // combine(const Sales_data&)

    // 只允许一步类类型转换
    // 错误，需要2步
    // (1) const string -> string
    // (2) string -> Sales_data
//    item.combine("9-999-99999-9");

    // 从标准输入创建一个临时的Sales_dataSales_data对象
//    item.combine(cin);
}

// explicit 禁止隐式转换
class plicitSalesData {
public:
    plicitSalesData() = default;
    explicit plicitSalesData(const std::string &s);
    explicit plicitSalesData(std::istream&);
};
// item.combine(nullBook); // 错误：构造函数是 explicit的

// 聚合类
struct Data {
    int ival;
    string s;
};

// 静态成员
//double Accound::interestRate = initRate();
class Bar {
public:
    // ...
private:
    static Bar mem1; // 静态成员可以是不完全类型
    Bar *mem2;  // 正确，指针从成员可以是不完全类型
//    Bar mem3; // error 数据成员必须是完全类型
};
