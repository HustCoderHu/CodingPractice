#include <iostream>
#include <memory>
#include <vector>
#include <string.h>

using namespace std;

static inline size_t alignSize(size_t sz, int n)
{
    return (sz + n-1) & -n;
}

class Mat {
public:
    Mat(int _w, int _h, int _c) : w(_w), h(_h), c(_c) {
        cstep = alignSize(_w * _h * sizeof(float), 16) >> 2;
        data = (float*)malloc(sizeof(float) * cstep * _c);
    }
    ~Mat() {
        free(data);
    }


    void setChannelInitVal() {
        int feature_sz = w * h;
        for (int q = 0; q != c; ++q) {
            for (int i = 0; i != feature_sz; ++i)
                data[cstep * q + i] = q;
        }
    }
    void disp() {
        int feature_sz = w * h;
        for (int q = 0; q != c; ++q) {
            for (int i = 0; i != feature_sz; ++i) {
                cout << data[cstep * q + i] << " ";
            }
        }
    }

    int w;
    int h;
    int c;
    size_t cstep;

    float *data;
};

static inline swapChannel(float *cha, float *chb, int feature_size)
{
    float *tmp = new float[feature_size];
//    memcpy(tmp, cha, sizeof(float) * feature_size);
//    memcpy(cha, chb, sizeof(float) * feature_size);
//    memcpy(chb, tmp, sizeof(float) * feature_size);

    delete[] tmp;
}

static int forward(const Mat &bottom_blob, Mat &top_blob);

int main(int argc, char *argv[])
{
    Mat bot(1, 1, 16);
    bot.setChannelInitVal();
//    bot.disp();
    Mat top(1, 1, 16);

    forward(bot, top);
    top.disp();
}

static int forward(const Mat &bottom_blob, Mat &top_blob)
{
    int group_ = 4;

    int w = bottom_blob.w;
    int h = bottom_blob.h;
    int c = bottom_blob.c;
    int cstep = bottom_blob.cstep;
    int chs_per_group = c / group_;

    float *top_dat = top_blob.data;
    float *bot_dat = bottom_blob.data;
    int q;
    for (int i = 0; i != group_; ++i) {
        for (int j = 0; j != chs_per_group; ++j) {
            q = chs_per_group * i + j;
            float *dst_ch = top_dat + cstep * q;
            q = chs_per_group * j + i;
            float *src_ch = bot_dat + cstep * q;
            memcpy(dst_ch, src_ch, cstep); // or w * h
        }
    }
}
