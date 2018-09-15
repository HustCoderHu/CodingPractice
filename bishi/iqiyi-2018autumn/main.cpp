#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

void q1();
void q2();

int main(int argc, char *argv[])
{
    q1();
    q2();
    return 0;
}

int calc(int ar[], int lsum, int rsum)
{
    int gap;
    gap = rsum - lsum;

    int linc[3] = {9-ar[0], 9-ar[1], 9-ar[2]};
    int rdec[3] = {ar[3], ar[4], ar[5]};
    auto comp = [](int a, int b) {return a>b;};
    auto cmp = [](int a, int b) {return a<b;};

    sort(linc, linc+3, comp);
    sort(rdec, rdec+3, cmp);

    int cnt = 0;

    if (gap <= max(linc[0], rdec[2]))
        cnt = 1;
    else if (gap <= linc[0]+rdec[2])
        cnt = 2;
    else
        cnt = 3;
    return cnt;
}

void q1()
{
    return;
    string num = "103018";
    num = "018103";
//    cin >> num;
//    num = "000018";

    int ar[6];
    for (int i = 0; i < 6; ++i) {
        ar[i] = num.at(i) - '0';
    }

    int lsum = ar[0] + ar[1] + ar[2];
    int rsum = ar[3] + ar[4] + ar[5];

    int res;
    if (lsum == rsum)
        res = 0;
    else if (lsum < rsum) {
        res = calc(ar, lsum, rsum);
    } else {
        swap(ar[0], ar[3]);
        swap(ar[1], ar[4]);
        swap(ar[2], ar[5]);
        res = calc(ar, rsum, lsum);
    }
    cout << res;
    return ;
}

void q2()
{
//    return;
    int n, m, p;
    vector<pair<int, int>> avec;

    cin >> n >> m >> p;
    avec.reserve(n);
    for (int i = 1; i <= n; ++i) {
        int ai;
//        scanf("%d", &ai);
//        cin >> ai;
        avec.push_back({i, ai});
    }
    for (int i = 0; i < m; ++i) {
        char t;
        int di;
//        scanf("%c", &t);
//        scanf("%d", &di);
//        cin >> t;
//        cin >> di;
        if ('A' == t)
            ++(avec[di].second);
        else
            --(avec[di].second);
    }
    auto cmp = [](const pair<int, int> &a ,const pair<int, int> &b) {
        return a.second > b.second;
    };

    sort(avec.begin(), avec.end(), cmp);
    int rank = 0;
    int formerval = -1000;

    for (int i = 0; i < avec.size(); ++i) {
        pair<int, int>& pr = avec[i];
        if (pr.second != formerval) {
            rank = i+1;
            formerval = pr.second;
        }
        if (pr.first == p)
            break;
    }
    cout << rank;
}
