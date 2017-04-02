#include <iostream>
#include "serviceop.h"

#include <strsafe.h>
using namespace std;

int main(int argc, char *argv[])
{
    DWORD err;
//    err = ServiceOp::StartSvc("wlansvc");
    err = ServiceOp::StopSvc("wlansvc");
    cout << err << endl;
//    ErrorExit(TEXT(""));
    return 0;
}
