#include <iostream>

using namespace std;

void paramPassation(void);

int main(int argc, char *argv[])
{
    paramPassation();
    return 0;
}

bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

void paramPassation(void)
{
    string s1("hello");
    string s2("world");
    cout << isShorter(s1, s2) << endl;
}

// 如果不修改变量，那就定义成const
bool isEmpty(const string &s)
{
    return s.empty();
}

//void print(const int*);
//void print(const int[]);
//void print(const int[4]);
//三个函数等价

void print(const int ia[], size_t size)
{
    for (size_t i = 0; i < size; ++i)
        cout << ia[i] << endl;
}

// 返回一个指针，该指针指向含有10个int的数组
auto func(int i) -> int(*)[10];
//int (*func(int i))[10]; // 等价
// 返回函数指针的函数
auto f1(int) -> int (*)(int*, int*);

// 默认实参
typedef string::size_type sz;
string screen(sz ht = 24, sz wid = 80, char backgrnd = ' ');
void defaultParam(void)
{
    string windown;
    windown = screen();
    windown = screen(66);
    windown = screen(66, 256);
    windown = screen(66, 256, '#');
}

// 重载匹配
void manip(long);
void manip(float);
void testManip(void)
{
    manip(3.14); // 3.14 is type double
    // 既能转换成long ，也能float
    // 所有算数类型转换的级别一样，所以this is 二义性调用
}



