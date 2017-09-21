#include <iostream>
#include <string>

#include <stdexcept> // runtime_error
#include <typeinfo>

#include <cctype>
#include <vector>

using namespace std;

void practice_1_6(void);
void zh_process(void);
void reference(void);


int main(int argc, char *argv[])
{
    //    practice_1_6();
//    zh_process();
//    reference();
    defString();

    return 0;
}

void practice_1_6(void)
{
    int v1, v2;
    v1 = 1;
    v2 = 2;
    cout << "===============================" << endl;
    cout << "practice 1.6" << endl;
    cout << "the sum of " << v1;
    cout << " and " << v2;
    cout << " is " << v1 + v2 << endl;
    cout << "===============================" << endl;
}

void zh_process(void)
{
    try {
        locale lc("zh_CN.UTF-8");
        locale::global(lc);
//        wstring wstr = L"狼人杀好难";
        wchar_t *wstr = L"狼人杀好难";
        wcout << wstr << endl;
    } catch (runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        cerr << "Type:" << typeid(e).name() << endl;
    }
}

void reference(void)
{
    int r1 = 1;
    int &r2 = r1;
    int r3 = 3;

    r2 = r3;
    r3++;
    cout << r2 << endl; // 3
}


