#include <iostream>
#include <string>
#include <vector>

using namespace std;

void defString(void);
void vector_3_3(void);
void vectorOp(void);
void binSearch(void);
void arrayOp(void);
void cStyleString(void);
void vectorInit(void);
void undefinedBehavior(void);


int main(int argc, char *argv[])
{
//    vector_3_3();
//    vectorOp();
//    arrayOp();
//    cStyleString();
    undefinedBehavior();
    return 0;
}

void defString(void)
{
    string s4(4, 'c');
//    cout << s4 << endl; // cccc
//    while (getline(cin, s4)) // \n not get
//        cout << s4 << endl;
    string s1 = "abcd";
    string s2 = s1;
    s1[0] = 'e';
//    cout << s1 << endl; // ebcd
//    cout << s2 << endl; // abcd

    string str("hello world !!! ~");
    decltype(str.size()) punct_cnt = 0;
    for (auto c : str) {
        if (ispunct(c))
            punct_cnt++;
    }
//    cout << punct_cnt
//         << " punctuation characters in " << str
//         << endl;
    for (auto &c : str)
        c = toupper(c);
//    cout << str << endl;

    if (!str.empty()) {
//        cout << str[0] << endl;
    }
}

void vector_3_3(void)
{
    vector<string> svec;
    vector<vector<string>> svecVec;
    vector<string> v1{"a", "an", "the"}; // 列表初始化
//    vector<string> v2("a", "an", "the"); // compile error
    vector<int> ivec_0(10, -1); // (n, val)
    vector<int> ivec_1(10); // n
    vector<int> ivec_2{10}; // 1, 10
//    vector<int> vi = 10; // compile error
    vector<string> v2{2};
    vector<string> v3{"3"};
    vector<string> v4{4, "5"};
    vector<string> v5(6); // (n [, val])
//    vector<string> v4{4, 5}; // compile error
//    vector<string> v4{4, 5, "hi"}; // compile error
//    vector<string> v6(6, 7); // compile error
    cout << v2.size() << endl;
    cout << v3.size() << endl;
    cout << v4.size() << endl;
    cout << v5.size() << endl;
}

void vectorOp(void)
{
    vector<string> svec;
    svec.push_back("today");
    svec.push_back(" is");
    svec.push_back(" Sunday");

//    cout << "hello world" << endl;
    cout << svec.size() << endl;
    for(auto iter : svec) {
//        cout << iter;
    }
    cout << endl;

    for (auto iter = svec.begin(); iter != svec.end(); iter++) {
        cout << *iter;
        // 使用了迭代器的循环体.不要添加元素, coz 迭代器会失效
        // svec.push_back(" Sunday");
    }
    cout << endl;

    for (auto const_iter = svec.cbegin();
         const_iter != svec.cend(); const_iter++) {
        cout << *const_iter;
    }
    cout << endl;

    return ;
}

void binSearch(void)
{
    string text("0123456789");
    char sought = '4';
    auto beg = text.begin();
    auto end = text.end();
    auto mid = beg + (end - beg) / 2;
//    auto mid = (beg + end) / 2; // compile error
    // 根据c++ primer 3.4.2 迭代器 表 3.7
    // 迭代器支持 - , 但不支持 + 运算

    while(mid != end && *mid != sought) {
        if (sought < *mid)
            end = mid - 1;
        else
            beg = mid + 1;
        mid = beg + (end - beg) / 2;
    }

}

void arrayOp(void)
{
    int scores[] = {70, 80, 90, 80, 70};
    for (auto i : scores)
        cout << i << endl;

    auto ia2(scores);     // type int*
    decltype(scores) ia3; // type int[5]

    int ia[2][3] = {70, 80, 90, 80, 70, 60};
    for (auto &row : ia) // auto row : ia  compile error
        for (auto col : row)
            cout << col << endl;
    // 除了最内层循环外，其他所有循环的控制变量都应该是引用类型
//    cout <<
}

void cStyleString(void)
{
    string text("hello world !!!");
    auto str = text.c_str();
    text[0] = 'H';
    text[6] = 'W';
    cout << str << endl; // Hello World !!!
    // c_str() 被修改
}

void vectorInit(void)
{
    int int_arr[] = {0, 1, 2, 3, 4, 5};
    vector<int> ivec(begin(int_arr), end(int_arr));
}

void undefinedBehavior(void)
{
    int i = 4;
    i = i++; // warning: operation on 'i' may be undefined

    int intt = 8;
    for (i = 0; (intt = i) || true; i++) {
        if (1 == i)
            break;
        cout << intt << endl;
    }
}

void exceptionTest(void)
{
    string str1, str2;
    while (cin >> str1 >> str2) {
        try {
            // 正常流程
        }
        // #include <stdexcept>
        catch (runtime_error err) {
            cout << err.what() << endl;
            cout << "Try again? enter y or n" << endl;
            char c;
            cin >> c;
            if (!cin || c == 'n')
                break;
        } catch (range_error err) {
            // 运行时错误: 生成的结果超过了有意义的值域范围
        } catch (overflow_error err) {
            // 运行时错误: 计算上溢
        } catch (underflow_error err) {
            // 运行时错误: 计算下溢

        } catch (logic_error err) {
            // 程序逻辑错误
        } catch (domain_error err) {
            // 逻辑错误： 参数对应的结果值不存在
        } catch (invalid_argument err) {
            // 逻辑错误： 无效参数
        } catch (length_error err) {
            // 逻辑错误： 试图创建一个超出该类型最大长度的对象
        } catch (out_of_range err) {
            // 逻辑错误： 使用一个超过有效范围的值
        }

    }
}
