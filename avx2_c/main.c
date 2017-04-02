/**
 * used for calculating raid check p
 * remember cflags += -max2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <limits.h>
#include <cal_p.h>

void comp_avx2();

int main(void)
{
    comp_avx2();
    return 0;
}

void comp_avx2()
{
    unsigned char **ppbuf;
    size_t nDisk;
    size_t disk_i;
    size_t bufLen;
    size_t addr;
    char j;

    clock_t start;
    clock_t end;
    double timeCost;
    size_t nCycle;
    size_t cycle_i;

    nDisk = 4;
    bufLen = 1024*64; // 64 KB per disk buffer

    // prepare for data
    ppbuf = malloc(nDisk * sizeof(*ppbuf));
    ppbuf[0] = malloc(bufLen);
    memset(ppbuf[0], 0, bufLen);
    for (disk_i = 1, j=1; disk_i < nDisk; disk_i++, j=j<<1) {
        ppbuf[disk_i] = malloc(bufLen);
        memset(ppbuf[disk_i], j, bufLen); // j = 1 2 4
    }
    // have a look
    for (disk_i = 1; disk_i < nDisk; disk_i++) {
        printf("%x ", ppbuf[disk_i][0]);
    }
    putchar('\n');

    nCycle = 1024*256;
//    nCycle = 1024*256;

    // use avx2
    start = clock();
    for (cycle_i = 0; cycle_i < nCycle; cycle_i++) {
        avx2_cal_p(ppbuf, nDisk, bufLen);
    }
    end = clock();
    timeCost = (end - start) / CLOCKS_PER_SEC;
    // 6.0 s on my fx8300 3.3GHz
    for (addr = 0; addr < 16; addr++)
        printf("%x ", ppbuf[0][addr]); // p should be  1 | 2 | 4
    printf("\n use avx2: %lf \n", timeCost);

    putchar('\n');

    // not use avx2
    start = clock();
    for (cycle_i = 0; cycle_i < nCycle; cycle_i++) {
        cal_p(ppbuf, nDisk, bufLen);
    }
    end = clock();
    timeCost = (end - start) / CLOCKS_PER_SEC;
    // 49.0 s on my fx8300 3.3GHz
    for (addr = 0; addr < 16; addr++)
        printf("%x ", ppbuf[0][addr]);
    printf("\n not use avx2: %lf \n", timeCost);

    // release mem
    for (disk_i = 0; disk_i < nDisk; disk_i++) {
        free(ppbuf[disk_i]);
    }
    free(ppbuf);
}
