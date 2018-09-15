#ifndef MLST_H
#define MLST_H

#include <vector>
using std::vector;

class Mlst {
public:
    Mlst() {next = nullptr; tail = this;}
    Mlst(int _v) : v(_v) {next = nullptr; tail = this;}

    Mlst *reverse(int n, Mlst* &nextHead) {
        int len = 1;
        Mlst *tnxt = next;
        while (tnxt) {
            ++len;
            tnxt = tnxt->next;
        }
        if (len < n)
            return this;

        Mlst *newh = this;
        Mlst *origh = next;
        newh->next = nullptr;
        for (int i = 2; i <= n; ++i) {
            tnxt = origh;
            origh = origh->next;
            tnxt->next = newh;
            newh = tnxt;
        }
        nextHead = origh;
        return newh;
    }

    void append(int _v) {
        tail->next = new Mlst(_v);
        tail = tail->next;
    }

    void tovec() {
        vec.clear();
        vec.push_back(v);
        Mlst *nxt = next;
        while (nxt) {
            vec.push_back(nxt->v);
            nxt = nxt->next;
        }
    }

    vector<int> vec;

    int v;
    Mlst *next;
    Mlst *tail;
};

#endif // MLST_H
