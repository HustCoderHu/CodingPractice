#ifndef CAL_P_H
#define CAL_P_H

void cal_p(unsigned char **ppbuf, size_t nDisk, size_t diskLen);
void avx2_cal_p(unsigned char **ppbuf, size_t nDisk, size_t diskLen);

#endif // CAL_P_H
