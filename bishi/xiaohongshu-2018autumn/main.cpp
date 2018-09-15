#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include <mlst.h>

using namespace std;

void q1();
void q2();
void q3();

int main(int argc, char *argv[])
{
    q1();
    q2();
    return 0;
}



void q1()
{
//    return;
    int lv = 0;
    Mlst *h = nullptr;
    Mlst *tail = nullptr;

    vector<int> inp;
    while (EOF != scanf("%d", &lv)) {
        inp.push_back(lv);
    }
    int k = inp.back();

    for (int i = 0; i <inp.size()-1; ++i) {
        if (nullptr == h) {
            h = new Mlst(inp.at(i));
        }
        else {
            h->append(inp.at(i));
        }
    }
    tail = h;

    Mlst *newh = nullptr;
    Mlst *curHead = h;
    Mlst *nextHead = nullptr;

    Mlst *toret;
    newh = curHead->reverse(k, nextHead);
    toret = newh;
    while (newh != curHead) {
        curHead->next = nextHead;
        curHead = nextHead;
        newh = curHead->reverse(k, nextHead);
    }
    toret->tovec();
    Mlst *next = toret;
    while (next) {
        cout << next->v << " ";
        next = next->next;
    }
}

int count(int n, int& cnt2)
{
    cnt2 = 0;
    int cnt5 = 0;
    if (n != 0) {
        int tmp = n;
        while ((tmp&0x1) == 0) {
            ++cnt2;
            tmp >>= 1;
        }
        // 5
        tmp = n;
        while ((tmp % 5) == 0) {
            ++cnt5;
            tmp /= 5;
        }
    }
    return cnt5;
}

void q2()
{
    return;
    int n = 11;
//    cin >> n;
    int cnt2 = 0;
    int cnt5 = 0;
    //cnt5 = count(n, cnt2);
//    cout << cnt2 << endl;
//    cout << cnt5 << endl;

    int former2 = 0;
    int former5 = 0;
    for (int i = 1; i <= n; ++i) {
        int get2 = 0;
        former5 += count(i, get2);
        former2 += get2;

        cnt2 += former2;
        cnt5 += former5;
    }
    cout << min(cnt5, cnt2) << endl;
}

void q3()
{
    return;
}
