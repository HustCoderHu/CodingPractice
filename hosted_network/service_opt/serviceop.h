#ifndef SERVICEOP_H
#define SERVICEOP_H
#include <windows.h>

class ServiceOp
{
public:
    ServiceOp();

    static DWORD StartSvc(const char *ServiceName);
    static DWORD StopSvc(const char *ServiceName);
};

#endif // SERVICEOP_H
