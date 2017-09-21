#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>

using namespace std;

void findCount(void);
void readOnlyAlgorithm(void);
void writeAlgorithm(void);
void rearrangeAlgorithm(void);
void customOp(void);
void iterReexplore(void);

int main(int argc, char *argv[])
{
    findCount();
    readOnlyAlgorithm();
    writeAlgorithm();
    rearrangeAlgorithm();
	customOp();
	iterReexplore();

    return 0;
}

void findCount(void)
{
    return ;
    int val = 23;
    vector<int> ivec{12, 32, 23, 34, 45, 56, 67, 78, 89, 910};
//    string val("what the fvck design pattern");
    auto result = find(ivec.cbegin(), ivec.cend(), val); // 返回迭代器
    // 没找到就返回， 第二个参数 cend
    if (result == ivec.cend())
        cout << "not found " << endl;
    else
        cout << "found it" << endl;

    int ia[] = {27, 210, 83, 12, 47, 83, 109, 83};
    val = 83;
    int *res = find(begin(ia), end(ia), val);
    *res = 38;
    cout << *res << endl;
    auto res2 = count(begin(ia), end(ia), val);
    cout << res2 << endl;
}

void readOnlyAlgorithm(void)
{
    return ;

    vector<int> ivec{27, 210, 83, 12, 47, 83, 109, 83};
    int sum_0 = accumulate(ivec.cbegin(), ivec.cend(), 0); // 初始值 0
    vector<string> svec{"what", "the", "fvck", "design", "pattern"};
    // 连接所有str
    string strNum = accumulate(svec.cbegin(), svec.cend(), string(""));

    // ivec 至少得 len >= svec
//    equal(svec.cbegin(), svec.cend(), ivec.cbegin());
}

void writeAlgorithm(void)
{
    return ;

    vector<int> ivec{27, 210, 83, 12, 47, 83, 109, 83};
    // 置0
    fill(ivec.begin(), ivec.end(), 0);
    fill_n(ivec.begin(), ivec.size(), 0);
    fill(ivec.begin(), ivec.begin() + ivec.size()/2, 10);

    vector<int> vec1;
    auto it = back_inserter(vec1);
    *it = 42; // equal to push_back
    fill_n(it, 10, 0); // 添加了10个0

    int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a2[sizeof(a1)/sizeof(*a1)];
    // ret 指向a2尾元素之后的位置
    auto ret = copy(begin(a1), end(a1), a2);

    int sum_0 = accumulate(ivec.cbegin(), ivec.cend(), 0); // 初始值 0
    vector<string> svec{"what", "the", "fvck", "design", "pattern"};
    // 连接所有str
    string strNum = accumulate(svec.cbegin(), svec.cend(), string(""));

    // ivec 至少得 len >= svec
//    equal(svec.cbegin(), svec.cend(), ivec.cbegin());
    // 将所有 83 替换成 0
    replace(ivec.begin(), ivec.end(), 83, 0);

    vector<int> vec2;
    vec2.reserve(ivec.size());
    // 替换 83 为 0 并保存在 vec2，ivec保持不变
    replace_copy(ivec.begin(), ivec.end(),
                 back_inserter(vec2), 83, 0);
}

bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size() || s1 < s2;

    if (s1.size() != s2.size())
        return s1.size() < s2.size();
    else
        return s1 < s2;
}

void rearrangeAlgorithm(void)
{
    return;

    vector<string> words{"aaa", "bb", "bb", "cc", "dd", "dd", "ee"};
    // 按字典序排序， 以便查找重复单词
    sort(words.begin(), words.end());
    // unique重排输入范围， 使得每个单词只出现一次
    // 排列在范围的前部，返回指向不重复区域之后一个位置的迭代器
    auto end_unique = unique(words.begin(), words.end());
    // words = {"aa", "bb", "cc", "dd", "ee", "bb", "dd"} ;
    // *end_unique == string("bb")
    // 使用向量操作erase 删除重复单词
    words.erase(end_unique, words.end());

    // sort 第三个参数 谓词 predicate
    // 稳定排序，相等元素相对顺序不变
    stable_sort(words.begin(), words.end(), isShorter);
}

bool check_size(const string &s, string::size_type sz)
{
    return s.size() >= sz;
}

void customOp(void)
{
    return ;
    //    find_if();

    // lambda 表达式
//    [capture list](params list) -> return type {func body}
    auto f = [](const string &s1, const string &s2) {
        return s1.size() < s2.size() || s1 < s2;
    };
//    stable_sort(words.begin(), words.end(), f);

    // 变量捕获 值and引用
    size_t v1 = 42;
    auto f2 = [v1] { return v1; }; // 创建时拷贝
    // 值拷贝 类型是const ，不能作为左值
    v1 = 0;
    auto j = f2(); // 42

    auto f3 = [&v1] { return v1; };
    auto j2 = f3(); // 0
    // 普通变量 如int string或其他非指针类型，通常值捕获方式

    string::size_type sz = 3;
    // 隐式捕获，编译器推断
    // = 值捕获, & 引用捕获
    auto f4 = [=](const string &s) {
        return s.size() >= sz;
    };
	auto f4_iter = find_if(words.cbegin(), words.cend(), f4);
	if (f_1_iter == words.cend()) {
        cout << "not found" << endl;
    } else {
        cout << *f_1_iter << endl;
    }
	for_each(f_1_iter, words.cend(), [](const string &s){
        cout << s << " ";
    });
    cout << endl;
    // 混合使用，第一个必须是 & or = ，默认捕获方式
    // 后接显式捕获
    auto f5 = [&, sz](const string &s) { }; // 值捕获
    auto f6 = [=, &sz](const string &s) { };
    // 可变lambda
//    https://msdn.microsoft.com/zh-cn/library/dd293608.aspx
// = 在使用 capture 子句时，建议你记住以下几点（尤其是使用采取多线程的 lambda 时）：
//=1= 引用捕获可用于修改外部变量，而值捕获却不能实现此操作。 （mutable允许修改副本，而不能修改原始项。）
//=2= 引用捕获会反映外部变量的更新，而值捕获却不会反映。
//=3= 引用捕获引入生存期依赖项，而值捕获却没有生存期依赖项。 当 lambda 以异步方式运行时，这一点尤其重要。
//=4= 如果在异步 lambda 中通过引用捕获本地变量，该本地变量将很可能在 lambda 运行时消失，从而导致运行时访问冲突。
    v1 = 42;
    auto f7 = [v1]() mutable {
        cout << v1 << endl;
        ++v1; // 不加mutable v1就是read-only variable
        cout << v1 << endl;
        cout << &v1 << endl;
        return v1;
    };
    cout << "v1: " << v1 << endl;
    v1 = 0;
    cout << &v1 << endl;
    auto j3 = f7(); // 43
    cout << "j3: " << j3 << endl;
    cout << "v1: " << v1 << endl;


    // 返回类型
    // primer 中文版 P353 不只有return 语句，则自动推断为void
    // 但是我的mingw并没有报错，至少在返回类型都是int的情况下
    // 如果返回类型不止一种，才会报错
    auto f8 = [](int i) {
        if (i < 0)
            return -i;
        else
            return i;
    };
    int aa = f8(-3);
    cout << aa << endl; // 3

    // 参数绑定 auto newCallable = bind(callable, argList);
    using namespace std::placeholders;
    // _n 在placeholders中，表示func的第n个参数
    auto check6 = bind(check_size, _1, 6);
}

void iterReexplore(void)
{
//    return ;
    // 插入迭代器 back_inserter front_inserter inserter
    vector<int> vec;
    istream_iterator<int> inIter(cin); // #include <iterator>
    istream_iterator<int> eof; // eof 被定义为空
    while (inIter != eof) { // 遇到文件尾or IO 错误就跳出
        vec.push_back(*inIter);
        ++inIter;
    }
    // 或者
    vector<int> vec2(inIter, eof); // 从迭代器范围构造vec

    ostream_iterator<int> outIter(cout, " "); // 第二个参数可选，必须是C风格字符串
    // const char* or char[]
    // 每个元素后接 第二个参数
    for (auto e : vec) {
        *outIter = e; // 从cout输出
        ++outIter;
    }
    copy(vec.cbegin(), vec.cend(), outIter);
}
