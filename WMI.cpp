#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#include "WMI.h"
#include <tchar.h>
#pragma comment(lib, "wbemuuid.lib")
Locales localesPack = Locales();
//string getUBRVersion()
//{
//    if (IsWindows7SP1OrGreater())
//    {
//
//        
//        LPCWSTR sw = _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\");//_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\Bandizip.exe");
//        wprintf(L"SW is %s\n", sw);
//        if (ERROR_SUCCESS == RegOpenKey(HKEY_LOCAL_MACHINE, sw, &hRetKey))
//        {
//            return true;
//        }
//        printf("OpenRegKey return is false!\n");
//        return false;
//        
//
//    }else return ""
//}

//void wcharTochar(const wchar_t* wchar, char* chr, int length)
//{
//    WideCharToMultiByte(CP_UTF8, 0, wchar, -1,
//        chr, length, NULL, NULL);
//}

bool OpenRegKey(HKEY& hRetKey)
{
    LPCWSTR sw = _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");//_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\Bandizip.exe");
    wprintf(L"SW is %s\n", sw);
    if (ERROR_SUCCESS == RegOpenKey(HKEY_LOCAL_MACHINE, sw, &hRetKey))
    {
        
        return true;
    }
    printf("OpenRegKey return is false!\n");
    return false;
}

string QueryRegKey(LPCWSTR strSubKey, LPCWSTR strValueName)//这里是传3个参数
{
    DWORD dwType = REG_DWORD;//定义数据类型
    DWORD dwLen = MAX_PATH;

    DWORD data = 0;
    HKEY hKey;
    HKEY hSubKey;
    if (OpenRegKey(hKey))
    {
        if (ERROR_SUCCESS == RegOpenKey(HKEY_LOCAL_MACHINE, strSubKey, &hSubKey))
        {
            TCHAR buf[256] = { 0 };

            if (ERROR_SUCCESS == RegQueryValueEx(hSubKey, L"UBR", 0, &dwType, (LPBYTE)&data, &dwLen))
            {
                RegCloseKey(hSubKey);
                
            }
            else {
                //RegCloseKey(hSubKey);
                return "";
            }
        }

        RegCloseKey(hKey); //关闭注册表
        return to_string(data);
    }

    return "";
}



HRESULT hres;
IWbemServices* pSvc = NULL;
IWbemLocator* pLoc = NULL;
BOOL isWMIOpened = false;
BOOL isSecurityInited = false;

BOOL openWMI()
{
    // Step 1: --------------------------------------------------
    // Initialize COM. ------------------------------------------

    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {
        cout << "Failed to initialize COM library. Error code = 0x"
            << hex << hres << endl;
        return FALSE;                  // Program has failed.
    }

    // Step 2: --------------------------------------------------
    // Set general COM security levels --------------------------
    if(!isSecurityInited)
    hres = CoInitializeSecurity(
        NULL,
        -1,                          // COM authentication
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities 
        NULL                         // Reserved
    );


    if (FAILED(hres))
    {
        cout << "Failed to initialize security. Error code = 0x"
            << hex << hres << endl;
        CoUninitialize();
        return FALSE;                    // Program has failed.
        
    }
    isSecurityInited = TRUE;
    // Step 3: ---------------------------------------------------
    // Obtain the initial locator to WMI -------------------------

    

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);

    if (FAILED(hres))
    {
        cout << "Failed to create IWbemLocator object."
            << " Err code = 0x"
            << hex << hres << endl;
        CoUninitialize();
        return FALSE;                 // Program has failed.
    }

    // Step 4: -----------------------------------------------------
    // Connect to WMI through the IWbemLocator::ConnectServer method

    

    // Connect to the root\cimv2 namespace with
    // the current user and obtain pointer pSvc
    // to make IWbemServices calls.
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
        NULL,                    // User name. NULL = current user
        NULL,                    // User password. NULL = current
        0,                       // Locale. NULL indicates current
        NULL,                    // Security flags.
        0,                       // Authority (for example, Kerberos)
        0,                       // Context object 
        &pSvc                    // pointer to IWbemServices proxy
    );

    if (FAILED(hres))
    {
        cout << "Could not connect. Error code = 0x"
            << hex << hres << endl;
        pLoc->Release();
        CoUninitialize();
        return FALSE;                // Program has failed.
    }

    cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;
    // Step 5: --------------------------------------------------
    // Set security levels on the proxy -------------------------

    hres = CoSetProxyBlanket(
        pSvc,                        // Indicates the proxy to set
        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
        NULL,                        // Server principal name 
        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
        NULL,                        // client identity
        EOAC_NONE                    // proxy capabilities 
    );

    if (FAILED(hres))
    {
        cout << "Could not set proxy blanket. Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return FALSE;               // Program has failed.
    }
    return TRUE;
}
BOOL closeWMI()
{
    if (isWMIOpened == 1) {
        if (pSvc != NULL)
            pSvc->Release();
        if (pLoc != NULL)
            pLoc->Release();
        CoUninitialize();
        isWMIOpened = 0;
    }
    return TRUE;
}
int CPUCount = 0;
int getCPUCount() {
    return CPUCount;
};
string getCPUInformation()
{
    IEnumWbemClassObject* pEnumerator = NULL;
    if (!isWMIOpened)isWMIOpened = openWMI();
    if (!isWMIOpened)return "Some Error occored.";
    // Step 6: --------------------------------------------------
    // Use the IWbemServices pointer to make requests of WMI ----

    // For example, get the name of the operating system

    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_Processor"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres))
    {
        cout << "Query for operating system name failed."
            << " Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "发生错误，代码：0x" + hres;               // Program has failed.
    }

    // Step 7: -------------------------------------------------
    // Get the data from the query in step 6 -------------------

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    string result = "";
    CPUCount = 0;
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
            &pclsObj, &uReturn);

        if (0 == uReturn)
        {
            break;
        }

        VARIANT vtProp;

        VariantInit(&vtProp);
        // Get the value of the Name property
        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        result += "\t"+to_string(CPUCount) + localesPack.mh + wide_Char_To_Multi_Byte(vtProp.bstrVal);
        VariantClear(&vtProp);
        hr = pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, 0, 0);
        result += " @"+to_string((int)vtProp.lVal/1000)+"."+ to_string((int)vtProp.lVal / 10 % 100)+"GHz";
        VariantClear(&vtProp);
        hr = pclsObj->Get(L"NumberOfCores", 0, &vtProp, 0, 0);
        result += " " + to_string(vtProp.lVal) + localesPack.CPUCoreLabel;
        VariantClear(&vtProp);
        hr = pclsObj->Get(L"NumberOfLogicalProcessors", 0, &vtProp, 0, 0);
        result += " " + to_string(vtProp.lVal) + localesPack.CPULogicProcessorLabel;
        VariantClear(&vtProp);
        hr = pclsObj->Get(L"Description", 0, &vtProp, 0, 0);
        result += "\n\t\t"+wide_Char_To_Multi_Byte(vtProp.bstrVal) + "";
        VariantClear(&vtProp);
        CPUCount++;
        pclsObj->Release();
    }

    // Cleanup
    // ========
    pEnumerator->Release();
    return result;   // Program successfully completed.

}
int MemoryCount = 0;
int getMemoryCount()
{
    return MemoryCount;
}
string sizeToStr(unsigned long long size)
{
    if (size < 0x400)
        return to_string(size) + "B";
    else if (size < 0x100000L)
        return to_string(size / 1024) + "KB";
    else if (size < 0x40000000L)
        return to_string(size / 1024 / 1024) + "MB";
    else
        return to_string(size / 1024 / 1024 / 1024) + "GB";
    

}

int DiskCount = 0;
int getDiskCount() {
    return DiskCount;
}

string getDiskInfo()
{
    IEnumWbemClassObject* pEnumerator = NULL;
    if (!isWMIOpened)isWMIOpened = openWMI();
    if (!isWMIOpened)return "Some Error occored.";



    // Step 6: --------------------------------------------------
    // Use the IWbemServices pointer to make requests of WMI ----

    // For example, get the name of the operating system

    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_DiskDrive"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres))
    {
        cout << "Query for operating system name failed."
            << " Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "发生错误，代码：0x" + hres;               // Program has failed.
    }

    // Step 7: -------------------------------------------------
    // Get the data from the query in step 6 -------------------

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    string result = "";
    DiskCount = 0;
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
            &pclsObj, &uReturn);

        if (0 == uReturn)
        {
            break;
        }

        VARIANT vtProp;

        VariantInit(&vtProp);
        // Get the value of the Name property
        hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
        result += "\t" + to_string(DiskCount) + localesPack.mh + wide_Char_To_Multi_Byte(vtProp.bstrVal);
        hr = pclsObj->Get(L"Size", 0, &vtProp, 0, 0);
        string capicaty = wide_Char_To_Multi_Byte(vtProp.bstrVal);
        result += localesPack.capacityLabel + sizeToStr(atoll(capicaty.c_str()));
        hr = pclsObj->Get(L"Status", 0, &vtProp, 0, 0);
        result +=  localesPack.diskstatusLabel +wide_Char_To_Multi_Byte(vtProp.bstrVal);
        result += "\n";
        VariantClear(&vtProp);
        DiskCount++;
        pclsObj->Release();
    }
    // Cleanup
    // ========
    pEnumerator->Release();
    return result;   // Program successfully completed.
}


int videoDriverCount = 0;
int getVideoDriverCount()
{
    return videoDriverCount;
}

string getVideoDriverInfo()
{
    IEnumWbemClassObject* pEnumerator = NULL;
    if (!isWMIOpened)isWMIOpened = openWMI();
    if (!isWMIOpened)return "Some Error occored.";



    // Step 6: --------------------------------------------------
    // Use the IWbemServices pointer to make requests of WMI ----

    // For example, get the name of the operating system

    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_VideoController"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres))
    {
        cout << "Query for operating system name failed."
            << " Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "发生错误，代码\xEF\xBC\x9A 0x" + hres;               // Program has failed.
    }

    // Step 7: -------------------------------------------------
    // Get the data from the query in step 6 -------------------

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    string result = "";
    videoDriverCount = 0;
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
            &pclsObj, &uReturn);

        if (0 == uReturn)
        {
            break;
        }

        VARIANT vtProp;

        VariantInit(&vtProp);
        // Get the value of the Name property
        hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
        result += "\t" + to_string(videoDriverCount) + localesPack.mh + wide_Char_To_Multi_Byte(vtProp.bstrVal);
        VariantClear(&vtProp);
        hr = pclsObj->Get(L"VideoModeDescription", 0, &vtProp, 0, 0);
        //string capicaty = wide_Char_To_Multi_Byte(vtProp.bstrVal);
        if(vtProp.bstrVal!=NULL)
        result += localesPack.displaymodeLabel + wide_Char_To_Multi_Byte( vtProp.bstrVal);
        result += "\n\t";
        VariantClear(&vtProp);
        videoDriverCount++;
        pclsObj->Release();
    }
    // Cleanup
    // ========
    pEnumerator->Release();
    return result;   // Program successfully completed.
}

int ConnectedNetworkDriverCount = 0;
int getConnectedNetworkDriverCount()
{
    return ConnectedNetworkDriverCount;
}

string getConnectedNetworkDriverInfo()
{
    IEnumWbemClassObject* pEnumerator = NULL;
    if (!isWMIOpened)isWMIOpened = openWMI();
    if (!isWMIOpened)return "Some Error occored.";
    // Step 6: --------------------------------------------------
    // Use the IWbemServices pointer to make requests of WMI ----

    // For example, get the name of the operating system

    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_NetworkAdapterConfiguration"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres))
    {
        cout << "Query for operating system name failed."
            << " Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "发生错误，代码：0x" + hres;               // Program has failed.
    }

    // Step 7: -------------------------------------------------
    // Get the data from the query in step 6 -------------------

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    string result = "";
    ConnectedNetworkDriverCount = 0;
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
            &pclsObj, &uReturn);

        if (0 == uReturn)
        {
            break;
        }

        VARIANT vtProp;

        VariantInit(&vtProp);
        // Get the value of the Name property
        hr = pclsObj->Get(L"IPEnabled", 0, &vtProp, 0, 0);
        //result += "\t" + to_string(videoDriverCount) + "：" + wide_Char_To_Multi_Byte(vtProp.bstrVal);
        BOOL flag = vtProp.boolVal;
        if (flag) {
            VariantClear(&vtProp);
            hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
            if (vtProp.bstrVal != NULL)
                result += "\t" + to_string(ConnectedNetworkDriverCount) + localesPack.mh + wide_Char_To_Multi_Byte(vtProp.bstrVal);
            VariantClear(&vtProp);
            hr = pclsObj->Get(L"IPAddress", 0, &vtProp, 0, 0);
            result += localesPack.IPAddressLabel;
            //string capicaty = wide_Char_To_Multi_Byte(vtProp.bstrVal);
            if (vtProp.vt & (VT_ARRAY | VT_BSTR))
            {
                SAFEARRAY* pIPs = vtProp.parray;
                LONG lBound, uBound, i;
                SafeArrayGetLBound(pIPs, 1, &lBound);
                SafeArrayGetUBound(pIPs, 1, &uBound);
                for (i = lBound; i <= uBound; i++)
                {
                    BSTR bstrIP;
                    hr = SafeArrayGetElement(pIPs, &i, &bstrIP);
                    if (SUCCEEDED(hr))
                    {
                        result += ""+ wide_Char_To_Multi_Byte(bstrIP) +"\t";
                        SysFreeString(bstrIP);
                    }
                }
            }
            /*if (vtProp.bstrVal != NULL)
                result += "\n\t\t IP地址：" + wide_Char_To_Multi_Byte(vtProp.vt);*/
            VariantClear(&vtProp);
            hr = pclsObj->Get(L"DefaultIPGateWay", 0, &vtProp, 0, 0);
            result += localesPack.defaultGatewayLabel;

            //string capicaty = wide_Char_To_Multi_Byte(vtProp.bstrVal);
            if (vtProp.vt & (VT_ARRAY | VT_BSTR))
            {
                SAFEARRAY* pIPs = vtProp.parray;
                LONG lBound, uBound, i;
                SafeArrayGetLBound(pIPs, 1, &lBound);
                SafeArrayGetUBound(pIPs, 1, &uBound);
                for (i = lBound; i <= uBound; i++)
                {
                    BSTR bstrIP;
                    hr = SafeArrayGetElement(pIPs, &i, &bstrIP);
                    if (SUCCEEDED(hr))
                    {
                        result += " " + wide_Char_To_Multi_Byte(bstrIP);
                        SysFreeString(bstrIP);
                    }
                }
            }
            VariantClear(&vtProp);
            /*if (vtProp.bstrVal != NULL)
            result += " 默认网关：" + wide_Char_To_Multi_Byte(vtProp.bstrVal);*/
            hr = pclsObj->Get(L"MACAddress", 0, &vtProp, 0, 0);
            if(vtProp.bstrVal!=NULL)
            result += localesPack.MACLabel + wide_Char_To_Multi_Byte(vtProp.bstrVal);
            result += "\n";
            ConnectedNetworkDriverCount++;

        }
        VariantClear(&vtProp);
         
        pclsObj->Release();
    }
    // Cleanup
    // ========
    pEnumerator->Release();
    return result;   // Program successfully completed.
}


string getMemoryInfo()
{
    IEnumWbemClassObject* pEnumerator = NULL;
    if (!isWMIOpened)isWMIOpened = openWMI();
    if (!isWMIOpened)return "Some Error occored.";

    

    // Step 6: --------------------------------------------------
    // Use the IWbemServices pointer to make requests of WMI ----

    // For example, get the name of the operating system

    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_PhysicalMemory"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres))
    {
        cout << "Query for operating system name failed."
            << " Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "some error occured code: 0x" + hres;               // Program has failed.
    }

    // Step 7: -------------------------------------------------
    // Get the data from the query in step 6 -------------------

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    string result="";
    MemoryCount = 0;
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
            &pclsObj, &uReturn);

        if (0 == uReturn)
        {
            break;
        }

        VARIANT vtProp;

        VariantInit(&vtProp);
        // Get the value of the Name property
        hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
        result += "\t"+to_string(MemoryCount) + localesPack.mh + wide_Char_To_Multi_Byte(vtProp.bstrVal);
        if (IsWindows10OrGreater()) {
            VariantClear(&vtProp);
            hr = pclsObj->Get(L"ConfiguredClockSpeed", 0, &vtProp, 0, 0);
            result += " @" + to_string((int)vtProp.llVal) + "MHz";
        }
        VariantClear(&vtProp);
        hr = pclsObj->Get(L"Capacity", 0, &vtProp, 0, 0);
        string capicaty = wide_Char_To_Multi_Byte(vtProp.bstrVal);
        result += " " + sizeToStr(atoll(capicaty.c_str()));
        result += "\n";
        VariantClear(&vtProp);
        MemoryCount++;
        pclsObj->Release();
    }

    // Cleanup
    // ========
    pEnumerator->Release();
    return result;   // Program successfully completed.
}


string getOSFullName()
{
    IEnumWbemClassObject* pEnumerator = NULL;
    if (!isWMIOpened)isWMIOpened = openWMI();
    if (!isWMIOpened)return "Some Error occored.";
    
   

    // Step 6: --------------------------------------------------
    // Use the IWbemServices pointer to make requests of WMI ----

    // For example, get the name of the operating system
    
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_OperatingSystem"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres))
    {
        cout << "Query for operating system name failed."
            << " Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "发生错误，代码：0x" + hres;               // Program has failed.
    }

    // Step 7: -------------------------------------------------
    // Get the data from the query in step 6 -------------------

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    string result;
    
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
            &pclsObj, &uReturn);

        if (0 == uReturn)
        {
            break;
        }

        VARIANT vtProp;

        VariantInit(&vtProp);
        // Get the value of the Name property
        hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
        //wcout << " OS Name : " << vtProp.bstrVal << endl;
        result = wide_Char_To_Multi_Byte(vtProp.bstrVal);
        VariantClear(&vtProp);
        hr = pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
        result += localesPack.kernalVersionlabel + wide_Char_To_Multi_Byte(vtProp.bstrVal);
        string ubr = QueryRegKey(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"UBR");
        if (ubr.length()!=0)
            result += "."+QueryRegKey(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"UBR");
        result+= localesPack.khbh;
        VariantClear(&vtProp);

        pclsObj->Release();
    }

    // Cleanup
    // ========
    pEnumerator->Release();
    return result;   // Program successfully completed.

}
