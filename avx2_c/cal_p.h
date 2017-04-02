#ifndef CAL_P_H
#define CAL_P_H

#include <immintrin.h>


unsigned char** create_lut(void);
void destroy_lut(unsigned char **Lut);

inline void lookup_p(unsigned char **ppbuf,
           size_t nDisk, size_t diskLen, unsigned char **Lut) {
    unsigned char cdst;
    size_t disk_i;
    size_t addr = 0; // offset in a disk

    for (addr = 0 ; addr < diskLen; addr++) {
        cdst = ppbuf[1][addr];
        for (disk_i = 2; disk_i < nDisk; disk_i++) {
//            cdst = cdst ^ ppbuf[disk_i][addr];
            cdst = Lut[cdst][ppbuf[disk_i][addr]];
        }
        ppbuf[0][addr] = cdst;
    }

}

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


#endif // CAL_P_H
