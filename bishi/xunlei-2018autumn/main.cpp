#include <iostream>

using namespace std;

void q1();

int main(int argc, char *argv[])
{
    q1();
    return 0;
}

void q1()
{
    int a, b;
//    scanf("%d %d", &a, &b);
    a = 10;
    b = -61;

//    int dp[17];

    // ax < (-b) * (7-x)
    int x = (-b)*7/(a-b);
    int y = 7-x;

    if (a*x + b*y == 0)
        ++y;
    int v = a*(17-y*2) + b*y*2;
    if (y > 4)
        v -= (a-b)*(y-4);

    cout << v;
}


#include <math.h>
//const int N = 1000005;
//long long n;
//int visit[N];

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

void q2()
{
    long long n;
    if (scanf("%lld", &n) == EOF)
        return ;

    int ret = 0;
//    memset(visit, 0, sizeof(visit));
    long long m = sqrt(n + 0.5);
    long long a, b, c;
    for (long long i = 1; i <= m; ++i) {
        for (long long j = i + 1; j <= m; j += 2) {
            if (gcd(j, i) != 1)
                continue;
            a = j * j - i * i;
            b = 2 * i * j;
            c = i * i + j * j;
            if (c <= n) {
                ++ret;
//                visit[a] = visit[b] = visit[c] = 1;
            }
//            for (int k = 2; c * k <= n; ++k)
//                visit[k * a] = visit[k * b] = visit[k * c] = 1;
        }
    }
    cout << ret;
}
