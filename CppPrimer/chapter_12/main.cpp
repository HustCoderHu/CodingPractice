#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    return 0;
}

// shared_ptr
void testSharedPtr(void)
{
    auto p3 = make_shared<int>(42);
    auto p4 = make_shared<string>(10, '9');
    auto p5 = make_shared<int>();
    auto p6 = make_shared<string>("999");
}

// 共享底层 vector
class StrBlob {
public:
    using size_type = std::vector<std::string>::size_type;

    StrBlob() : data(make_shared<std::vector<std::string>>()) { }
    StrBlob(std::initializer_list<std::string> i1)
        :data(make_shared<std::vector<std::string>>(i1)) { }

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加和删除元素
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    // 元素访问
    std::string& front() const;
    std::string& back();

private:
    std::shared_ptr<std::vector<std::string>> data;
    // 如果data[i] 不合法，就抛出一个异常
    void check(size_type i, const std::string &msg) const {
        if (i >= data->size())
            throw out_of_range(msg);
    }
};
void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}
string& StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}
string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

// new 初始化
void testNewInit(void)
{
    StrBlob obj;
    // auto 只能单一初始化器
    auto p1 = new auto(obj);
//    p1 = new auto{a, b, c}; // 错误
}

// new 失败
void newFail(void)
{
    int *p1 = new int;              // 如果分配失败 new 抛出 std::bad_allow
    // 定位 new (placement new)
    int *p2 = new (nothrow) int;    // 失败 返回 空指针
}

// shared_ptr 和 new 混合使用
shared_ptr<int> mixShared(void)
{
//    shared_ptr<int> p1 = new int(1024); // 错误，隐式转换失败
    shared_ptr<int> p2(new int(1024));  // 必须直接初始化

//    return new int(1024); // 错误，原因同 p1
    return shared_ptr<int>(new int(1024));

}

// 不要使用 get 初始化另一个智能指针 or  给智能指针赋值
void getFault(void)
{
    shared_ptr<int> p(new int(42));
    // 正确，但使用 q 时要注意，不要让他管理的指针被释放
    int *q = p.get();
    {
        // 未定义：两个独立的 shared_ptr 指向相同的内存
        shared_ptr<int>(q);
    }   // 程序块结束，q 被销毁，它指向的内存被释放
    int foo = *p;   // p 指向的内存已经被释放了
}

// 其他 shared_ptr 操作
void otherSharedOp(void)
{
    shared_ptr<int> p;
    p.reset(new int(1024));

    shared_ptr<string> p2;
    if(!p2.unique())
        p2.reset(new string(*p2));  // 我们不是唯一
    // 用户，分配新的拷贝
//    *p2 += newVal;
}

// 智能指针和异常
void f()
{
    shared_ptr<int> sp(new int(42));
    // 这段代码抛出一个异常，且在f中未被catch
}   // 函数结束时 shared_ptr 自动释放内存
// 使用自定义释放操作

#ifdef connection
void endConnection(connection *p)
{
    disconnect(*p);
}
auto lambda = [](connection *p) { disconnect(*p); }
void f2(destination &d)
{
    connection c = connect(&d);
    shared_ptr<connection> p(&c, endConnection);
    // 使用连接
    // 当 f2 退出时 (即使是由于异常而退出)，connection
    // 会被正确关闭
}
#endif

// unique_ptr
// 不支持普通的拷贝 or 赋值
void uniqueOp()
{
//    unique_ptr<T, D> u(d);
    // d 替代 delete，类型为 D
//    u.release();  //  放弃控制权，返回指针
    // 并置空 u。
    // ！！！ 资源没有被 delete，需要用户 delete

    // p1 转移给 p2, p1 置空
    unique_ptr<string> p1(new string("abc"));
    unique_ptr<string> p2(p1.release());
//    auto p3(p2.release());
    p1.reset(p2.release());
}
// 禁止拷贝的列外
unique_ptr<int> clone(int p)
{
    // 拷贝 or 赋值一个将要被销毁的 unique_ptr
    return unique_ptr<int>(new int(p));
    // 局部对象类似
    // 这是一种特殊的 "拷贝"
}
// 重写连接程序
#ifdef connection
void f3(destination &d)
{
    connection c = connect(&d);
    unique_ptr<connection, decltype(endConnection)*>
            p(&c, endConnection);
    // 加 * 表示函数指针
    shared_ptr<connection> p(&c, endConnection);
    // 使用连接
    // 当 f3 退出时 (即使是由于异常而退出)，connection
    // 会被正确关闭
}
#endif

// weak_ptr 弱共享
// weak_ptr<T> w(sp)    sp 类型 shared_ptr
// w = p    p 可以是shared_ptr or weak_ptr
// w.expired()  return w.use_count() == 0
// w.lock()
void weakLock()
{
    weak_ptr<int> wp;
    if (shared_ptr<int> np = wp.lock()) {
        // 在 if 中，np 与 p 共享对象
    }
}
