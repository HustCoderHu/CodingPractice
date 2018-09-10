#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void q1();

int main(int argc, char *argv[])
{
    q1();
    return 0;
}

typedef pair<int, int> item;

// 求第k大
void q1()
{
    int topk = 5;
    vector<int> input{1024, 3, 64, 4, 64, 41, 238};

    vector<item> pairV2idx;
    pairV2idx.reserve(topk);
    // 小顶堆
    auto comp = [](const item& x, const item& y) {
        return x.first > y.first;
    };
    int i = 0;
    for (; i < topk; ++i) {
        pairV2idx.push_back({input.at(i), i});
    }
    make_heap(pairV2idx.begin(), pairV2idx.end(), comp);

    for(; i < input.size(); ++i) {
        pop_heap(pairV2idx.begin(), pairV2idx.end(), comp);
        pairV2idx[topk-1] = {input.at(i), i};
        push_heap(pairV2idx.begin(), pairV2idx.end(), comp);
    }

    pop_heap(pairV2idx.begin(), pairV2idx.end(), comp);
    cout << pairV2idx.back().second+1 << endl;
}
// STL中的堆（heap）操作
// https://www.cnblogs.com/xkfz007/archive/2012/08/25/2655620.html
