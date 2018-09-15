#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <algorithm>

#include <assert.h>

using namespace std;

void q1()
{
    string s1;
    string s2;
    unordered_set<char> cset;

//    s1 = "abcdefggg";
//    s2 = "aabg";
    cin >> s1;
    cin >> s2;

    for (char c : s2)
        cset.insert(c);

    string s3;
    s3.reserve(s1.length());
    for(char c : s1) {
        if (cset.end() != cset.find(c))
            continue;
        s3.push_back(c);
    }
    cout << s3 << endl;
}

void str_copy(char *dst, const char *src)
{
    assert((dst!=NULL) && (src!=NULL));
    char *ret = dst;
    while (*src != '\0') {
        *dst = *src;
        ++dst;
        ++src;
    }
    *dst = '\0';
}

void q2()
{
    string inp;
    cin >> inp;

    char *dst = new char[inp.size()+1];
    str_copy(dst, inp.c_str());
    cout << dst << endl;
    delete dst;
}

int main(int argc, char *argv[])
{
    q1();
    return 0;
}
