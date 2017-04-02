#include "serviceop.h"

#include <windows.h>
#include <strsafe.h>
//#include "string"

wchar_t* ctow(const char *str);
void ErrorExit(LPTSTR lpszFunction);

DWORD ServiceOp::StartSvc(const char *ServiceName)
{
    DWORD ret = 0;

    SC_HANDLE hSC = NULL;
    SC_HANDLE hSvc = NULL;
    wchar_t* service_name;
    SERVICE_STATUS stat;

    // Establishes a connection to the service control manager
    // on the specified computer
    // and opens the specified service control manager database.
    hSC = OpenSCManager(NULL, NULL, GENERIC_EXECUTE);
    if (NULL == hSC) {
        ret = -1;
        goto error;
    }
    // Opens an existing service.
    service_name = ctow(ServiceName);
    hSvc = OpenService(hSC, service_name,
                       SERVICE_START | SERVICE_QUERY_STATUS
                       | SERVICE_STOP);
    if (NULL == hSvc) {
        ret = -2;;
        goto error;
    }

    // Retrieves the current status of the specified service.
    if (FALSE == QueryServiceStatus(hSvc, &stat)) {
        ret = -3;;
        goto error;
    }
    if (SERVICE_RUNNING != stat.dwCurrentState) {
        if (FALSE == StartService(hSvc, NULL, NULL)) {
            ret = -4;;
            goto error;
        }
    }
error:
    ErrorExit(TEXT("Start"));
finished:
    if(NULL != hSvc)
        CloseServiceHandle(hSvc);
    if(NULL != hSC)
        CloseServiceHandle(hSC);
    return ret;
}

DWORD ServiceOp::StopSvc(const char *ServiceName)
{
    DWORD ret = 0;

    SC_HANDLE hSC = NULL;
    SC_HANDLE hSvc = NULL;
    wchar_t* service_name;
    SERVICE_STATUS stat;

    hSC = OpenSCManager(NULL, NULL, GENERIC_EXECUTE);
    if (NULL == hSC) {
        ret = -1;;
        goto error;
    }

    service_name = ctow(ServiceName);
    hSvc = OpenService(hSC, service_name,
                       SERVICE_START | SERVICE_QUERY_STATUS
                       | SERVICE_STOP);
    if (NULL == hSvc) {
        ret = -2;;
        goto error;
    }

    if (FALSE == QueryServiceStatus(hSvc, &stat)) {
        ret = -3;;
        goto error;
    }
    if (SERVICE_STOPPED != stat.dwCurrentState) {
        if (FALSE == ControlService(hSvc,
                                    SERVICE_CONTROL_STOP, &stat)) {
            ret = -5;;
            goto error;
        }
    }
error:
    ErrorExit(TEXT("Stop"));
finished:
    if (NULL != hSvc)
        CloseServiceHandle(hSvc);
    if (NULL != hSC)
        CloseServiceHandle(hSC);
    return ret;

}

/*
 * convert char* to wchar_t*
 */
wchar_t* ctow(const char *str)
{
    wchar_t* pwstr;
    size_t req_buf_size;

    if(NULL == str)
        return 0;
    req_buf_size = (size_t)MultiByteToWideChar(CP_ACP, 0, (const char *)str,
                                               int(strlen(str)), NULL, 0);
    if(req_buf_size <= 0)
        return 0;
    pwstr = new wchar_t[req_buf_size+1];
    if(0 == pwstr)
        return 0;

    MultiByteToWideChar(CP_ACP, 0, (const char *)str,
                        int(strlen(str)), pwstr, int(req_buf_size));
    return pwstr;
}

/*
 * display description of the LastError
 */
void ErrorExit(LPTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                dw,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR) &lpMsgBuf,
                0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(
                LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf)+ lstrlen((LPCTSTR)lpszFunction) + 40)
                * sizeof(TCHAR) );
    StringCchPrintf((LPTSTR)lpDisplayBuf,
                    LocalSize(lpDisplayBuf) / sizeof(TCHAR),
                    TEXT("%s failed with error %d: %s"),
                    lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
}
