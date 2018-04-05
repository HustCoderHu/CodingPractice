#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>

using namespace std;


typedef unsigned long long ll;

void q1();
void q2();
void q3();

int main()
{
    q1();
    q2();
    q3();
    //    cout << "END!" << endl;
    return 0;
}

// 翻转数列
void q1()
{
    return;
    long n;
    long m;

    cin >> n >> m;
    cout << n/m/2*m*m;
    return;

    unordered_map<string, int> amap;
    amap.find("name");
    amap.insert({"name", 0xff});
    amap.begin()->first;

    cout << amap.begin()->first << endl;
    cout << amap.begin()->second << endl;
}

int maxFactor(int a, int b)
{
    int _min = a;
    int _max = b;
    if (a > b) {
        _min = b;
        _max = a;
    }

    //    cout << _min << _max << endl;
    int tmp;
    while ((_max%_min) != 0) {
        tmp = _max%_min;
        _max = _min;
        _min = tmp;
    }

    //    cout << tmp << endl;
    return tmp;
}

unsigned long long Czuhe(int n, int m)
{
    unsigned long long res = 1;

    for (int i = 0; i < m; ++i) {
        res *= n--;
    }
    while (m != 1) {
        res /= m--;
    }
    cout << res <<endl;

    return res;
}


ll plus_mod(ll a, ll b, const ll p)
{
    ll res = 0;
    while (b != 0) {
        res += a;
        b--;
        res %= p;
    }
    return res;
}

void q2()
{
    //    return;
    int K;
    int A, X, B, Y;
    const ll MOD = 1000000007;

    K = 5;
    A = 2, X = 3;
    B = 3, Y = 3;

    //    cin >> K;
    //    cin >> A >> X >> B >> Y;

    ll C[101][101];
    int Cmax = X > Y? X:Y;
    for (int n = 1; n <= Cmax; ++n) {
        C[n][0] = 1;
        C[n][1] = n;
    }

    for (int n = 2; n <= Cmax; ++n) {
        for (int r = 1; r < n; ++r) {
            C[n][r] = C[n-1][r-1] + C[n-1][r];
            C[n][r] %= MOD;
        }
    }

    int cnt = 0;
    for (int x = 0; x <= X; ++x) {
        if (A * x > K)
            break;
        int remain = K - A * x;
        int y = remain / B;
        if (remain != B*y)
            continue;
        cnt += plus_mod(C[X][x], C[Y][y], MOD);
    }

    cout << cnt << endl;

//    Cx[1] = X;
//    Cy[1] = Y;
//    for (int i = 2; i <= X+1; ++i) {
//        Cx[i] = Cx[i-1] * (X-i+1)/i;
//        Cx[i] %= MOD;
//    }
//    for (int i = 2; i <= Y+1; ++i) {
//        Cy[i] = Cy[i-1] * (Y-i+1)/i;
//        Cy[i] %= MOD;
//    }

//    int y;
//    while (true) {
//        y = (K - A*x) / B;
//        int left = (K - A*x) % B;
//        if (left == 0)
//            break;
//        x++;
//    }

    //    cout << x << endl;
    //    cout << y << endl;

//    int minBeishu = A*B/maxFactor(A, B);
//    int step_x = minBeishu / A;
//    int step_y = minBeishu / B;

    //    cout << minBeishu << endl;
    //    cout << step_x << endl;
    //    cout << step_y << endl;

//    while (A*x < K) {
//        cnt += plus_mod(C[X][x], C[Y][y], MOD);
//        x += step_x;
//        y -= step_y;
//    }


}

void q3()
{
    return;
}

int ccc(long long a,long long b)
{
    int res = 0;
    while(b > 0)
    {
        res +=a;
        b--;
        res = res%1000000007;
    }
    return res;
}

void yishuai()
{
    long long aa[105][105];

    for(int i = 0;i <= 101;++i)
    {
        aa[i][1] = (long long)i;
        aa[i][0] = 1;
        aa[i][i] = 1;
    }
    aa[0][0] = 1;
    int k,a,ax,b,by;
    cin>>k>>a>>ax>>b>>by;
    int max = ax > by ? ax : by;
    for(int i = 2;i <= max;++i)
    {
        for(int j = 1;j < i;++j)
        {
            aa[i][j] = (aa[i - 1][j]%1000000007 + aa[i - 1][j - 1]%1000000007)%1000000007;
        }
    }

    long long res = 0;
    for(int i = 0;i <= ax;++i)
    {
        int j = (k - i*a)/b;
        if(k - i*a < 0)continue;
        //System.out.println("" + i + j);
        if((j <= by) && (j*b + i*a == k))
        {
            //System.out.println("yes");
            res += ccc(aa[ax][i],aa[by][j]);
            res = res%1000000007;
        }
    }
    cout<<res<<endl;
}
