#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void q1()
{
    vector<int> inp;
    int n;

    cin >> n;
    inp.resize(n);
    for (int i = 0; i < n ; ++i)
        cin >> inp[i];

    if (n <= 2) {
        cout << -1 << endl;
        return;
    }

    int maxe = -1;

    int cnt = 2;
    maxe = max(inp.at(0), inp.at(1));
    maxe = max(maxe, inp.at(2));


    int sum = inp.at(0) + inp.at(1);
    for (; cnt < n; ++cnt) {
        sum += inp.at(cnt);
        maxe = max(maxe, inp.at(cnt));
        if (2*maxe < sum)
            break;
    }
    if (cnt == n) {
        cnt == -1;
    }
    cout << cnt+1 << endl;
}



void q2()
{
    int q;
    int k, l, r;

    vector<int> kvec;
    vector<long> lvec;
    vector<long> rvec;

    cin >> q;
    kvec.reserve(q);
    lvec.reserve(q);
    rvec.reserve(q);
    for (int i = 0; i < q; ++i) {
        cin >> k >> l >> r;
        kvec.push_back(k);
        lvec.push_back(l);
        rvec.push_back(r);
    }

    vector<long> res;
    res.reserve(q);
    int v;
    for (int i = 0; i < q; ++i) {
        v = 1;
        k = kvec.at(i);
        l = lvec.at(i);
        r = rvec.at(i);
        while (v*k-1 <= r) {
            v *= k;
        }
        while (v < l) {
            v = v +
        }
    }
}

int main(int argc, char *argv[])
{
//    q1();
    q2();
    return 0;
}
