#include <iostream>
#include <algorithm>
#include <time.h>
#include <omp.h>

using namespace std;

void comp_if();

int main(int argc, char *argv[])
{
    comp_if();
    return 0;
}

void comp_if()
{
    clock_t start;
    clock_t end;
    double timeCost;

    int channels = 64; // 2048;
    channels *= 256;
    int w = 112; // 7;
    int size = w * w;

    float *data = new float[channels * size];

    start = clock();
//    #pragma omp parallel for
    for (int q = 0; q < channels; ++q) {
        float* ptr = data + size * q;
        for (int i = 0; i < size; ++i) {
            if (ptr[i] < 0)
                ptr[i] = 0;
        }
    }
    end = clock();
    timeCost = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "if: " << timeCost << endl;
//    printf("\n if: %lf \n", timeCost);

    start = clock();
//    #pragma omp parallel for
    for (int q = 0; q < channels; ++q) {
        float* ptr = data + size * q;
        for (int i = 0; i < size; ++i) {
//                ptr[i] = max(ptr[i], 0);
        }
    }
    end = clock();
    timeCost = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "max: " << timeCost << endl;

    start = clock();
//    #pragma omp parallel for
    for (int q = 0; q < channels; ++q) {
        float* ptr = data + size * q;
        for (int i = 0; i < size; ++i) {
            ptr[i] = ptr[i] > 0 ? ptr[i] : 0;
        }
    }
    end = clock();
    timeCost = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "? a:b : " << timeCost << endl;
//    printf("\n ? a:b : %lf \n", timeCost);

    delete[] data;
}
