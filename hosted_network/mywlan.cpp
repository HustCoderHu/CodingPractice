#include "mywlan.h"

#include <serviceop.h>
//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#include <winnt.h>

//#include "winsock2.h"
//#include "windows.h"
//#include "wlanapi.h"
//#include "iphlpapi.h"

//#pragma comment(lib, "ws2_32.lib")
//#pragma comment(lib, "IPHLPAPI.lib"
//#pragma comment(lib, "wlanapi.lib")
#include "winsock2.h"
#include "wlanapi.h"

#pragma comment(lib, "wlanapi.lib")

std::wstring s2ws(const std::string str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

std::string ws2s(const std::wstring wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.to_bytes(wstr);
}

Mywlan::Mywlan()
{
//    Init();
//    StartWlanSvc();
}

int Mywlan::WlanInit()
{
    DWORD dwServiceVersion = 0;
    //    HANDLE hWlanClient = NULL;
    DWORD dwError = 0;

    ServiceOp::StartSvc("wlansvc");

    dwError = WlanOpenHandle(WLAN_API_VERSION, NULL,               // reserved
                             &dwServiceVersion, &hClient);

    if (ERROR_SUCCESS != dwError) {
        DisplayWlanError(dwError);
        return -1;
    }
    // check service version
    if (WLAN_API_VERSION_MAJOR(dwServiceVersion) <
            WLAN_API_VERSION_MAJOR(WLAN_API_VERSION_2_0)) {
        return -2;
        WlanCloseHandle(hClient, NULL);
    }

    BOOL bIsAllow = TRUE;
    WLAN_HOSTED_NETWORK_REASON dwFailedReason;
    dwError = WlanHostedNetworkSetProperty(hClient,
                                           wlan_hosted_network_opcode_enable,
                                           sizeof(bIsAllow),
                                           &bIsAllow,
                                           &dwFailedReason,
                                           NULL);
    if (ERROR_SUCCESS != dwError) {
        DisplayWlanError(dwError);
        return -3;
    }

    return 0;
}

int Mywlan::WlanExit()
{
    if (NULL != hClient)
        WlanCloseHandle(hClient, NULL);

    return 0;
}

int Mywlan::SetSSID(std::string ssid)
{
    WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS cfg;
    WLAN_HOSTED_NETWORK_REASON dwFailedReason;

    DWORD dwError = 0;

    memset(&cfg, 0, sizeof(WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS));

    cfg.dwMaxNumberOfPeers = 20;
    memcpy(cfg.hostedNetworkSSID.ucSSID, ssid.c_str(), ssid.length()) ;
    cfg.hostedNetworkSSID.uSSIDLength = ssid.length();
    dwError = WlanHostedNetworkSetProperty(hClient,
                                           wlan_hosted_network_opcode_enable,
                                           sizeof(cfg),
                                           &cfg,
                                           &dwFailedReason,
                                           NULL);
    if (ERROR_SUCCESS != dwError) {
        DisplayWlanError(dwError);
        return -3;
    }

    return 0;
}

int Mywlan::SetKEY(std::string key)
{
    //    WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS cfg;
    WLAN_HOSTED_NETWORK_REASON dwFailedReason;

    DWORD dwError = 0;

    dwError = WlanHostedNetworkSetSecondaryKey(hClient,
                                               strlen((const char*)chkey) + 1,
                                               (PUCHAR)key.c_str(),
                                               TRUE,
                                               FALSE,
                                               &dwFailedReason,
                                               NULL);
    if(ERROR_SUCCESS != dwError) {
        DisplayWlanError(dwError);
        return -4;
    }
}

int Mywlan::GetPeerNum()
{
    PWLAN_HOSTED_NETWORK_STATUS ppWlanHostedNetworkStatus = NULL;

    DWORD dwError = 0;

    dwError = WlanHostedNetworkQueryStatus(hClient
                                           &ppWlanHostedNetworkStatus,
                                           NULL);
    if(ERROR_SUCCESS != dwError) {
        DisplayWlanError(dwError);
        return -5;
    }
    return ppWlanHostedNetworkStatus->dwNumberOfPeers;
}

int Mywlan::StartWlan()
{

}

int Mywlan::DisplayWlanError(DWORD dwReasonCode)
{
    DWORD  dwBufferSize;
    PWCHAR pStringBuffer;

    dwBufferSize = 4096;
    pStringBuffer = new WCHAR[dwBufferSize];

    // retrieves a string that describes a specified reason code
    WlanReasonCodeToString(dwReasonCode, dwBufferSize,
                           pStringBuffer, NULL);
    MessageBox(NULL, (LPCTSTR)pStringBuffer, TEXT("Error"), MB_OK);

    delete pStringBuffer;
    return 0;
}
















