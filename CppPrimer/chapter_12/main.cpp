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
}
