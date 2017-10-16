#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

// unordered hash函数组织的

using namespace std;

void useSet(void);

int main(int argc, char *argv[])
{
    useSet();
    return 0;
}

void countWord(void)
{
    return ;
    map<string, size_t> wordCount;
    string word;
    while (cin >> word)
        ++wordCount[word];

    for (const auto &w : wordCount)
        cout << w.first << "occurs " << w.second
             << ((w.second > 1)? " times" : " time") << endl;
}

// 关联容器概述
void useSet(void)
{
//    return ;
    set<string> exclude{"the", "but", "and", "or", "an", "a",
                       "The", "But", "And", "Or", "An", "A"};
    string word("but");
    if (exclude.find(word) == exclude.cend())
        cout << "not found" << endl;
    else
        cout << "found" << endl;
}

class Sales_data {
public:
    Sales_data() = default;
    ~Sales_data() = default;
    int isbn() const { return Isbn; }
private:
    int Isbn;
};
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}
void multi(void)
{
    vector<int> ivec;
    ivec.reserve(10);
    for (int i = 0; i != 10; ++i) {
        ivec.push_back(i);
        ivec.push_back(i);
    }
    set<int> iset(ivec.cbegin(), ivec.cend()); // 包含10个不重复的elem
    multiset<int> miset(ivec.cbegin(), ivec.cend()); // 包含全部20个

    // 定义mul set时必须提供两个类型
    // 关键字类型，以及比较操作
    multiset<Sales_data, decltype(compareIsbn)*> bookStore(compareIsbn);
}

// pair
void pairOp()
{
    pair<string, string> anon;
    pair<string, size_t> wordCount;
    pair<string, vector<int>> line;
    // 默认值初始化
    pair<string, string> author{"James", "Joycc"};
    cout << author.first << endl;
    cout << author.second << endl;
}
pair<string, int> process(vector<string> &v)
{
    if (!v.empty()) {
        return {v.back(), v.back().size()}; //  列表初始化
        return make_pair(v.back(), v.back().size());
    } else
        return pair<string, int>(); //  隐式构造返回值
}

// 关联容器操作
void op1()
{
    set<string>::value_type v1; //  string
    set<string>::key_type v2;   //  同 value_type
    map<string, int>::value_type v3;    //  pair<const string, int>
    map<string, int>::key_type v4;      //  string
    map<string, int>::mapped_type v5;   //  int

    // 迭代器
    map<string, size_t> wordCount;
    auto mapIt = wordCount.begin();
    cout << mapIt->first;
    cout << " " << mapIt->second << endl;
//    mapIt->first = "new key";   //  error: key is const
    ++mapIt->second;

    // set :: iter is const

    // add element
    vector<int> ivec = {2, 4, 6, 8, 2, 4, 6, 8};
    set<int> iset;
    // set 2 种插入
    iset.insert(ivec.cbegin(), ivec.cend());    //  4
    iset.insert({1, 3, 1, 3});                  //  +2
    // map 4种
    string word;
    wordCount.insert({word, 1});
    wordCount.insert(make_pair(word, 1));
    wordCount.insert(pair<string, size_t>(word, 1));
    wordCount.insert(map<string, size_t>::value_type(word, 1));

    // insert 返回值 pair<iter, bool>
    // iter 执行具有给定关键字的elem(value_type)， bool 元素是否插入成功
    auto ret = wordCount.insert({word, 1});
    if (!ret.second)    //  word 已在 wordCound 中
        ++ret.first->second;    //  ++((ret.first)->second

    // delete element
    // 返回 删除元素的数量
    map<string, size_t>::iterator pos;
    map<string, size_t>::const_iterator first, last;
    map<string, int>::key_type vv4;
    wordCount.erase(pos);
    wordCount.erase(first, last);
    wordCount.erase(vv4);
    // multi ret > 1 possibly
}
