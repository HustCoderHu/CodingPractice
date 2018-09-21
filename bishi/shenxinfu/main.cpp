#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <string.h>

using namespace std;

int water[10000];

void q1()
{
    int T;
    int n;
    vector<int> hight;
    vector<int> res;
    cin >> T;
    res.reserve(T);

    for(int ti = 0; ti < T; ++ti) {
        cin >> n;
        hight.resize(n);
        for (int i = 0; i < n; ++i) {
            int h;
            cin >> h;
            hight[i]= h;
        }
        memset(water, 0, sizeof(int)*10000);

        int maxIdx = 0;
        int leftMax = hight.at(0);

        for (int i = 1; i < n; ++i) {
            int pre = hight.at(i - 1);
            int right = hight.at(i);
            if (right <= pre) {
                water[i-1] = right;
            } else {
                // 左侧板
                // 左高右低
                if (leftMax >= right) { // 高 低 中
                    // 比右板矮的全部更新
                    for (int j = leftMax; j <= i-1; ++j) {
                        if (hight.at(j) < right) {
                            water[j] = right;
                        }
                    }
                } else if (leftMax > pre) { // 中 低 高
                    for (int j = maxIdx; j <= i-1; ++j)
                        water[j] = leftMax;
                } else { // 低 中 高
                    water[i-1] = pre;
                }

                maxIdx = i;
                leftMax = right;
            }
        }
        int sum = 0;
        for (int i = 0; i <= n-2; ++i)
            sum += water[i];
        res.push_back(sum);
    }

    for (int v : res) {
        cout << v << endl;
    }
}


void q2()
{
    int a1, b1, v1;
    int a2, b2, v2;

    int T;
    vector<pair<int, int>> res;

    cin >> T;
    res.reserve(T);
    for (int ti = 0; ti < T; ++ti) {
        cin >> a1 >> b1 >> v1 >> a2 >> b2 >> v2;
        int dz = v1 * b2 - v2 * b1;
        int dx = a1 * b2 - a2 * b1;
        if (0 == dx || 0 == dz
                || (dx < 0 && dz > 0)
                || (dx > 0 && dz < 0)
                || (dz % dx != 0)) {
            res.push_back({-1, -1});
            continue;
        }
        int x = dz / dx;
        int y = (v1 - a1 * x) / b1;
        if (y <= 0 || (a1*x+b1*y != v1)) {
            res.push_back({-1, -1});
            continue;
        }
        res.push_back({x, y});
    }

    for (pair<int, int> &pr : res) {
        int x = pr.first;
        int y = pr.second;
        if (-1 == x) {
            cout << "UNKNOWN"<< endl;
            continue;
        }
        cout << x << " " << y << endl;
    }
}

int main(int argc, char *argv[])
{
    q1();
    return 0;
}
