#include <iostream>

using namespace std;

void q1()
{
    string s;
    //    cin >> s;
    s = "08:03:45PM";

    if (0 == s.compare("12:00:00AM"))
        s = "00:00:00";
    else if (0 == s.compare("12:00:00PM"))
        s = "12:00:00";
    else if (s.at(s.length()-2) == 'A')
        s.resize(s.length()-2);
    else {
        int h = (s.at(0)-'0')*10+s.at(1)-'0';
        h += 12;
        s[0] = h/10 + '0';
        s[1] = h%10 + '0';
        s.resize(s.length()-2);
    }
    cout << s << endl;
}

void q2()
{
    int t;
    t = 4;
    //    cin >> t;
    int n;

    n = 0;
    int v = 2;
    while (true) {
        if (v + (v<<1) >= t+3)
            break;
        v <<= 1;
        ++n;
    }

    int sum = 3 * v - 2;

    cout << sum - t << endl;
}

void q3()
{
    int n, k;
    cin >>  n >> k;

    int count = 0, divide = 0;

    for (int i = 0; i < n; ++i)
    {
        int temp;
        cin >> temp;
        int mod = temp % k;
        if (mod == 0)
            divide++;
        else if (mod <= (k - 1) / 2)
            count++;
    }
    if (divide)
        cout << count + 1 << endl;
    else
        cout << count << endl;
}

int main(int argc, char *argv[])
{
    //    q1();
    q2();
    return 0;
}
