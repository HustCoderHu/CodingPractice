/**
 * used for calculating raid check p
 * remember cflags += -max2
 * my test env
 * CPU: fx8300 3.3GHz
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

    unsigned char **Lut;

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

    nCycle = 1024*512;

    // use avx2
    start = clock();
    for (cycle_i = 0; cycle_i < nCycle; cycle_i++) {
        avx2_cal_p(ppbuf, nDisk, bufLen);
    }
    end = clock();
    timeCost = (end - start) / CLOCKS_PER_SEC;
    // 11.000000  on release mode
    for (addr = 0; addr < 16; addr++)
        printf("%x ", ppbuf[0][addr]); // p should be  1 | 2 | 4
    printf("\n use avx2: %lf \n", timeCost);

    putchar('\n');

    // lookup table
    Lut = create_lut();
    start = clock();
    for (cycle_i = 0; cycle_i < nCycle; cycle_i++) {
        lookup_p(ppbuf, nDisk, bufLen, Lut);
    }
    end = clock();
    timeCost = (end - start) / CLOCKS_PER_SEC;
    // 104.000000  on release mode
    for (addr = 0; addr < 16; addr++)
        printf("%x ", ppbuf[0][addr]); // p should be  1 | 2 | 4
    printf("\n lookup table: %lf \n", timeCost);
    destroy_lut(Lut);

    putchar('\n');

    // simply xor with nothing
    start = clock();
    for (cycle_i = 0; cycle_i < nCycle; cycle_i++) {
        cal_p(ppbuf, nDisk, bufLen);
    }
    end = clock();
    timeCost = (end - start) / CLOCKS_PER_SEC;
    // 63.000000  on release mode
    for (addr = 0; addr < 16; addr++)
        printf("%x ", ppbuf[0][addr]);
    printf("\n simply xor with nothing: %lf \n", timeCost);

    // release mem
    for (disk_i = 0; disk_i < nDisk; disk_i++) {
        free(ppbuf[disk_i]);
    }
    free(ppbuf);
}
