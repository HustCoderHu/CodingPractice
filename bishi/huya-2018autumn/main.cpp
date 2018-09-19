#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

void q1()
{
    vector<pair<int, int>> p_classScore;

    int classNo;
    int score;

    while (cin >> classNo) {
        cin >> score;
        p_classScore.push_back({classNo, score});
    }

    auto cmp = [](const pair<int,int> &a, const pair<int,int> &b)
    {
        return (a.first < b.first)
                || (a.first == b.first && a.second >= b.second);
    };

    sort(p_classScore.begin(), p_classScore.end(), cmp);

    for (const pair<int,int> &p : p_classScore)
        cout << p.first << " " << p.second << endl;
}

// 最长回文字串
int calcH(const string& s)
{
    size_t maxl = 0;
    for (int i = 0; i < s.length(); ++i) {
        // 剩下的长度不可能更长
        if (2*(s.length()-i)-1  <= maxl)
            break;

        // 奇数
        size_t len = 1;
        int left = i-1;
        int right = i+1;
        while (0 <= left && right < s.length()
               && s.at(left) == s.at(right)) {
            len += 2;
            --left;
            ++right;
        }
        maxl = max(maxl, len);

        // 偶数
        len = 0;
        left = i;
        right = i+1;
        while (0 <= left && right < s.length()
               && s.at(left) == s.at(right)) {
            len += 2;
            --left;
            ++right;
        }
        maxl = max(maxl, len);
    }
    return maxl;
}

void q2()
{
    vector<string> inp;
    vector<int> hlen;

    string s;
    while (getline(cin, s)) // 空格也是有效输入
        inp.push_back(s);

    inp.push_back("123abcba231");
    inp.push_back("adc121112111");

    hlen.reserve(inp.size());

    for (const string& str : inp)
        hlen.push_back(calcH(str));

    for (int l : hlen)
        cout << l << endl;
}

void q3()
{
    string s;

    //    s = "BeAutiful";
    cin >> s;

    unordered_set<char> yuanSet{'A', 'E', 'I', 'O', 'U',
                                'a', 'e', 'i', 'o', 'u'};

    int i = 0;
    int j = s.length()-1;
    while (i<j) {
        while (i < j &&
               yuanSet.end() == yuanSet.find(s.at(i)))
            ++i;

        while (i < j &&
               yuanSet.end() == yuanSet.find(s.at(j)))
            --j;
        swap(s[i], s[j]);
        ++i;
        --j;
    }
    cout << s << endl;
}

int main(int argc, char *argv[])
{
    //    q3();
    //    q1();

    const char a[] = "aaa";
    const char b[] = "aaa";
    cout << a == b << endl;
//    q2();
    return 0;
}
