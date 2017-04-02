#include <stdio.h>
#include <string.h>
#include <time.h>
#include <immintrin.h>

#include <cal_p.h>

void allign_cost(size_t cycleTimes);
void direct_test();
void xor_avx2(void *dst, void *op1, void *op2);

inline void cal_p(unsigned char **ppbuf, size_t nDisk, size_t diskLen);
inline void avx2_cal_p(unsigned char **ppbuf, size_t nDisk, size_t bufLen);




inline void cal_p(unsigned char **ppbuf,
           size_t nDisk, size_t diskLen)
{
    unsigned char cdst;
    size_t disk_i;
    size_t addr = 0; // offset in a disk

    for (addr = 0 ; addr < diskLen; addr++) {
        cdst = ppbuf[1][addr];
        for (disk_i = 2; disk_i < nDisk; disk_i++) {
            cdst = cdst ^ ppbuf[disk_i][addr];
        }
        ppbuf[0][addr] = cdst;
    }
}

inline void avx2_cal_p(unsigned char **ppbuf,
                       size_t nDisk, size_t bufLen)
{
    __m256d vdst;
//    __m256d vop;
    unsigned char cdst;

    size_t disk_i;
    size_t addr = 0; // offset in a disk buffer
    size_t nBlk = bufLen/32; // hom many 32B in a col
    size_t blk_i;

    for (blk_i = 0; blk_i < nBlk; blk_i++) {
        vdst = _mm256_loadu_pd((const double*)&ppbuf[1][addr]);
        for (disk_i = 2; disk_i < nDisk; disk_i++) {
//            vop = _mm256_loadu_pd((const double*)&ppbuf[disk_i][addr]);
//            vdst = _mm256_xor_pd(vdst, vop);
            vdst = _mm256_xor_pd(vdst,
                                 _mm256_loadu_pd((const double*)&ppbuf[disk_i][addr]) );
        }
        _mm256_storeu_pd((double*)&ppbuf[0][addr], vdst);
        addr += sizeof(__m256d); // next 32B
    }

    // remaining Bytes, less than 32B
    for ( ; addr < bufLen; addr++) {
        cdst = ppbuf[1][addr];
        for (disk_i = 2; disk_i < nDisk; disk_i++) {
            cdst = cdst ^ ppbuf[disk_i][addr];
        }
        ppbuf[0][addr] = cdst;
    }
}

void allign_cost(size_t cycleTimes)
{
    void *dst;
    void *op1;
    void *op2;
    __m256d vdst;
    __m256d vop1;
    __m256d vop2;

    clock_t start;
    clock_t end;
    double timeCost;
    size_t i;
    cycleTimes = 1024*1024*1024;

    // aligned
    dst = _mm_malloc(32, 32);
    op1 = _mm_malloc(32, 32);
    op2 = _mm_malloc(32, 32);
    start = clock();
    for (i = 0; i < cycleTimes; i++) {
        vop1 = _mm256_load_pd(op1);
        vop2 = _mm256_load_pd(op2);
        vdst = _mm256_xor_pd(vop1, vop2);
        _mm256_store_pd(dst, vdst);
    }
    end = clock();
    timeCost = (end - start) / CLOCKS_PER_SEC;
    _mm_free(dst);
    _mm_free(op1);
    _mm_free(op2);
    printf("aligned: %e \n", timeCost);

    // not aligned
    dst = malloc(32);
    op1 = malloc(32);
    op2 = malloc(32);
    start = clock();
    for (i = 0; i < cycleTimes; i++) {
        vop1 = _mm256_loadu_pd(op1);
        vop2 = _mm256_loadu_pd(op2);
        vdst = _mm256_xor_pd(vop1, vop2);
        _mm256_storeu_pd(dst, vdst);
    }
    end = clock();
    timeCost = (end - start) / CLOCKS_PER_SEC;
    free(dst);
    free(op1);
    free(op2);
    printf("not aligned: %e \n", timeCost);

    // aligned: 4.600000e+001
    // not aligned: 4.700000e+001
}

void direct_test()
{
//    void *dst = _mm_malloc(32, 32);
//    void *op1 = _mm_malloc(32, 32);
//    void *op2 = _mm_malloc(32, 32);

    void *dst = malloc(32);
    void *op1 = malloc(32);
    void *op2 = malloc(32);

    xor_avx2(dst, op1, op2);

//    __m256d v_res;
//    __m256d v_op1;
//    __m256d v_op2;

//    v_op1 = _mm256_loadu_pd(buf_1);
//    v_op2 = _mm256_loadu_pd(buf_2);
//    v_res = _mm256_xor_pd(v_op1, v_op2);
//    _mm256_storeu_pd(buf_res, v_res);

//    v_op1 = _mm256_load_pd(buf_1);
//    v_op2 = _mm256_load_pd(buf_2);
//    v_res = _mm256_xor_pd(v_op1, v_op2);
//    _mm256_store_pd(buf_res, v_res);

//    __m256i v_res;
//    __m256i v_op1;
//    __m256i v_op2;

//    v_op1 = _mm256_load_si256(buf_1);
//    v_op2 = _mm256_load_si256(buf_2);
//    v_res = _mm256_xor_si256(v_op1, v_op2);
//    _mm256_store_si256(buf_res, v_res);

    free(dst);
    free(op1);
    free(op2);
//    _mm_free(dst);
//    _mm_free(op1);
//    _mm_free(op2);

    return ;
}

inline void xor_avx2(void *dst, void *op1, void *op2)
{
    __m256d vdst;
    __m256d vop1;
    __m256d vop2;

    if (0 == ((unsigned long long)op1)%32) {
        putchar('a');
        vop1 = _mm256_load_pd(op1);
    }
    else {
        putchar('b');
        vop1 = _mm256_loadu_pd(op1);
    }

    if (0 == ((unsigned long long)op2)%32)
        vop2 = _mm256_load_pd(op2);
    else
        vop2 = _mm256_loadu_pd(op2);

    vdst = _mm256_xor_pd(vop1, vop2);

    if (0 == ((unsigned long long)dst)%32)
        _mm256_store_pd(dst, vdst);
    else
        _mm256_storeu_pd(dst, vdst);

    return ;
}
