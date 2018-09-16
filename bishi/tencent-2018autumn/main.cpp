#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

// 分解质因数
void LCM1_n(int n, unordered_map<int, int> bAnde)
{
}

// LCM(n+1, n+2, ... m) = LCM(1, 2, ..., m) 最小的m
void q1()
{
    int n;
    cin >> n;
    cout << n*2 << endl;
    unordered_map<int, int> bAnde;
    LCM1_n(n, bAnde);

    unordered_map<int, int> bAndradio;
}

// 求入度 > 出度的点数
void q2()
{

}

void q3()
{
    int t;
    int a,b,c;

    cin >> t;
    for (int i = 0; i < t; ++i) {
        cin >> a >> b >> c;
        int j = 1;
        for (; j <= b; ++j) {
            if ((a*j)%b == c) {
                cout << "YES" << endl;
                break;
            }
        }
        if (j == b+1)
            cout << "NO" << endl;
    }
}

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    return 0;
}
