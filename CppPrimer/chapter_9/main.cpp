#include <iostream>
#include <typeinfo>
#include <vector>
#include <list>
#include <array>
#include <deque>

using namespace std;

void elementType(void);
void containerInit(void);
void containerOp(void);

int main(int argc, char *argv[])
{
//    cout << argc << endl; // 1
//    cout << argv[0] << endl; // xxx.exe
    elementType();
    containerInit();
    containerOp();
    return 0;
}

void elementType(void)
{
    return ;
    list<string> strList;
    strList.push_back(string("aaa"));
    strList.push_back(string("bbb"));
    strList.push_back(string("ccc"));
    auto firstWord = *strList.begin();
    cout << typeid(firstWord).name() << endl;

    list<int> intList{0, 1, 2, 3, 4, 5};
    auto firstInt = *(intList.begin());
    cout << typeid(firstInt).name() << endl;

    auto iter = intList.begin();
    list<int>::reference second = *(++iter);
//    list<int>::value_type val;
    cout << typeid(second).name() << endl;

    vector<int> ivec(1);
//    cout << ivec.max_size() << endl;
    cout << ivec.capacity() << endl;
    deque<int> ideq{0, 1, 2, 3, 4};
//    cout << ideq.size() << endl;
//    cout << ideq.max_size() << endl;
}

void containerInit(void)
{
    return ;
    vector<int> ivec(10, -1); // 没有-1 就初始化为0

    array<int, 8> iarr = {0, 1, 2, 3, 4, 5, 6}; // [7] = 0
    array<string, 10> sarr;

    array<int, 10>::size_type i;

    array<int, 8> iarr2 = iarr; // 类型相同就可以拷贝

    // 假定noDefault 是一个没有默认构造函数的class
//    vector<noDefault> v1(10, init); // right 提供了元素初始化器
//    vector<noDefault> v1(10); // wrong
}

void containerOp(void)
{
//    return ;
//    c1 = c2; // 拷贝
    list<string> names;
    vector<const char*> oldstyle;
    // right 可以将 const char* 转换为string
//    names.assign(oldstyle.cbegin(), oldstyle.cend());
    vector<string> svec1(10);
    vector<string> svec2(24);
    // 除array外 交换都快，没有交换元素，只是交换了内部的数据结构
    swap(svec1, svec2);


    vector<int> v1 = {1, 3, 5, 7, 9};
    vector<int> v2 = {1, 3, 5, 7};
    cout << (v1 < v2) << endl; // falses

    vector<string> v = {"a1", "b2", "c3", "d4"};
    // 返回 "e5" 的迭代器
    v.insert(v.begin(), {"e5", "f6"});
    // runtime error 拷贝范围不能指向目标位置
//    v.insert(v.begin(), v.begin(), v.end());

    try {
        v2.at(4);
    } catch (runtime_error err) {
        cout << err.what() << endl;
    }
}

void emplaceOp(void)
{
//    vector<Sales_data> c;
//    c.emplace_back("978-12341241", 25, 15.99);
//    c.push_back(Sales_data("978-12341241", 25, 15.99));
}
