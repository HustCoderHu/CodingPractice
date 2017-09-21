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


}
