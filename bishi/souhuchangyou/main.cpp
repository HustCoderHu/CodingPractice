#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

int dist(int x1, int y1, int x2, int y2)
{
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

void q1()
{
    char dot;
    int x, y;
    int n;
    vector<pair<int, int>> npcVec;

    cin >> x >> dot >> y >> dot;
    cin >> n;
    npcVec.reserve(n);

    int npx, npy;
    for (int i = 0; i < n; ++i) {
        cin >> dot >> npx >> dot >> npy;
        npcVec.push_back({npx, npy});
    }
    int maxDist = INT_MAX;
    for (pair<int, int> &pr : npcVec) {
        int d = dist(x, y, pr.first, pr.second);
        if (d < maxDist) {
            maxDist = d;
            npx = pr.first;
            npy = pr.second;
        }
    }
    printf("(%d,%d)", npx, npy);
}

int mypow(int x, int e) {
    int v = 1;
    for (int i = 0; i < e; ++i)
        v *= x;
    return v;
}

void q2()
{
    int n, k;
    n = 3;
    k = 100;
//    cin >> n >> k;

    int i = 0;
    vector<int> lv;
    while (k) {
        if (k & 0x1)
            lv.push_back(i);
        ++i;
        k >>= 1;
    }
    int v = 0;
    int lastPow = 1;
    int laste = 0;
    for (int i = 0; i < lv.size(); ++i) {
        int curpow = lastPow * mypow(n, lv.at(i)-laste);
        v += curpow;
        lastPow = curpow;
        laste = lv.at(i);
    }

    cout << v;
}

int main(int argc, char *argv[])
{
//    q1();
    q2();
    return 0;
}
