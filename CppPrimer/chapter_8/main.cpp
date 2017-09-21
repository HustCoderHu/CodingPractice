#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    return 0;
}

void testIO(void)
{
    string word;
    while (cin >> word) {
        cout << word;
    }
}

void fileIO(void)
{
//    IO:ifstream
//    fstream fstrm;
    string filePath("asdf.txt");
//    fstream fstrm(filePath);
    // in out 是以内存为目标
    // so in 表示 from file to mem
    fstream fstrm(filePath); // 默认 in | out
//    fstream fstrm(filePath, ios_base::in | ios_base::out);
    if (fstrm) // 检查是否open成功
        ;
    fstrm.close();
    ifstream ifstrm;
    ifstrm.open(filePath); // 默认 in
//    ifstrm.open(filePath, ios_base::in);
    if (ifstrm) // 检查是否open成功
        ;
    else // 如果已经打开了，就会失败
        ; // 而且failbit被set，后续的所有文件流操作都会fail
    // 所以不要重复open，or记得close
    ifstrm.close();

    ofstream ofstrm;
    ofstrm.open(filePath, ios_base::app); // 即使没有指定out，
//    ofstrm.open(filePath, ofstream::app);
    // 也总是以输出打开
    ofstrm.close();
}

void fstreamDeconstruct(void)
{
    vector<string> fileVec{"a.txt", "b.txt", "c.txt"};
    for (const auto &fName : fileVec) {
        ifstream input(fName);
        // process(input);
    } // 每步循环input都会离开作用域，因此被销毁
    // 析构的时候会close
}

struct PersonInfo {
    string name;
    vector<string> phones;
};

bool valid(const string &phone)
{
    return true;
}

string& format(const string &phone); // 返回引用
string format(const string &phone) // 返回值，返回副本
{
    return phone;
}

void sstreamTest(void)
{
    string line, word;
    vector<PersonInfo> people;
    while (getline(cin, line)) {
        PersonInfo info;
        istringstream record(line);
        record >> info.name;
        while (record >> word)
            info.phones.push_back(word);
        people.push_back(info);
    }
//    using sstream = stringstream;
//    sstream strm;
    for (const auto &entry : people) {
        ostringstream formatted, badNums;
        for (const auto &nums : entry.phones) {
            if (!valid(nums)) {
                badNums << " " << nums;
            } else {
                formatted << " " << format(nums);
            }
        }
        if (badNums.str().empty()) {
            os << entry.name << " "
               << formatted.str() << endl;
        } else {
            cerr << "input error: " << entry.name
                 << "invalid number(s) " << badNums.str() << endl;
        }
    }
}


