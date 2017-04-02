#ifndef MYWLAN_H
#define MYWLAN_H

//#include <iostream>
#include "windows.h"

#include <string>

//using namespace std;

class Mywlan
{
public:
    Mywlan();
    ~Mywlan();

private:
    HANDLE hClient;

public:
    int WlanInit(void);
    int WlanExit(void);

    int SetSSID(std::string ssid);
    int SetKEY(std::string key);
    int GetPeerNum(void);

    int StartWlan(void);

private:
    static int DisplayWlanError(DWORD dwReasonCode);
};

#endif // MYWLAN_H
