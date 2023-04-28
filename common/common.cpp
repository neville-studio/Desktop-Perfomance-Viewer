#include "../DPV.h"
#include "../framework.h"
#include "common.h"
#include <windows.h>
using namespace std;

//
//
//BOOL judgeOSVersion(WORD wMajorVersion, WORD wMinorVersion, WORD wServicePackMajor,WORD wBuildNumber = 0)
//{
//    OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0, {0}, 0, 0 };
//    DWORDLONG        const dwlConditionMask = VerSetConditionMask(VerSetConditionMask(
//        VerSetConditionMask(
//            VerSetConditionMask(
//                0, VER_MAJORVERSION, VER_GREATER_EQUAL),
//            VER_MINORVERSION, VER_GREATER_EQUAL),
//        VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL),VER_BUILDNUMBER,VER_GREATER_EQUAL);
//
//    osvi.dwMajorVersion = wMajorVersion;
//    osvi.dwMinorVersion = wMinorVersion;
//    osvi.wServicePackMajor = wServicePackMajor;
//    osvi.dwBuildNumber = wBuildNumber;
//    return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask) != FALSE;
//}
//string getTEBVersion()
//{
//    HMODULE hModNtdll;
//    //CString strVal;
//    //DWORD dwVersion = 0;
//    string result;
//    if (hModNtdll = LoadLibrary(_T("ntdll.dll")))
//    {
//        //DWORD dwMajorVersion = 0, dwMinorVersion = 0, dwBuildNumber = 0;
//        //TEB *lpTeb = NtCurrentTeb();//������
//        //NtCurrentTeb();//������
//
//        typedef struct _TEB* (WINAPI* getver)();
//        getver pfNtCurrentTeb;
//        pfNtCurrentTeb = (getver)GetProcAddress(hModNtdll, "NtCurrentTeb");
//        if (pfNtCurrentTeb)
//        {
//            TEB* lpTeb = pfNtCurrentTeb();
//            if (lpTeb != NULL)
//            {
//                PEB* lpPeb = lpTeb->ProcessEnvironmentBlock;
//                if (lpPeb != NULL)
//                {
//                    DWORD dwMajVer = lpPeb->OSMajorVersion;
//                    DWORD dwMinVer = lpPeb->OSMinorVersion;
//                    DWORD dwBuildNum = lpPeb->OSBuildNumber;
//                    DWORD dwChangeNum = lpPeb->OSCSDVersion;
//                    //dwVersion = (DWORD)MAKELONG(dwMinVer, dwMajVer);
//                    result = to_string(dwMajVer) + "." + to_string(dwMinVer) + "." + to_string(dwBuildNum) + "." + to_string(dwChangeNum);
//                    //MessageBox(strVal);
//                }
//            }
//        }
//        else {
//            int nError = GetLastError();//��ȡ��ϸ�������
//            string error = "�����˴���" + nError;
//            //strError.Format(_T("��ȡϵͳ�汾����������룺 %d��\n"), nError);
//            //MessageBox(strError);
//            return error;
//        }
//        FreeLibrary(hModNtdll);
//    }
//    else {
//        int nError = GetLastError();//��ȡ��ϸ�������
//        string error = "dllװ�س���" + nError;
//        //strError.Format(_T("װ��dll����������룺 %d��\n"), nError);
//       // MessageBox(strError);
//    }
//    return result;
//}
//string getKernel32Version()
//{
//
//    /*_asm
//    {
//        pushad
//        mov ebx, fs: [0x18] ; get self pointer from TEB
//        mov eax, fs: [0x30] ; get pointer to PEB / database
//        mov ebx, [eax + 0A8h]; get OSMinorVersion
//        mov eax, [eax + 0A4h]; get OSMajorVersion
//        mov j, ebx
//        mov i, eax
//        popad
//    }
//    DWORD dwVersion = 0, dwMiniVersion = 0;
//    WCHAR szDLLName[MAX_PATH] = { 0 };
//    HRESULT hr = SHGetFolderPathW(NULL, CSIDL_SYSTEM, NULL, SHGFP_TYPE_CURRENT, szDLLName);
//    if ((hr == S_OK) && PathAppendW(szDLLName, L"ntoskrnl.exe"))
//    {
//        DWORD dwVerInfoSize = GetFileVersionInfoSizeW(szDLLName, NULL);
//        if (dwVerInfoSize > 0)
//        {
//            HANDLE hHeap = GetProcessHeap();
//            LPVOID pvVerInfoData = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, dwVerInfoSize);
//            if (pvVerInfoData != NULL)
//            {
//                if (GetFileVersionInfoW(szDLLName, 0, dwVerInfoSize, pvVerInfoData))
//                {
//                    UINT ulLength = 0;
//                    VS_FIXEDFILEINFO* pvffi = NULL;
//                    if (VerQueryValueW(pvVerInfoData, L"\\", (LPVOID*)&pvffi, &ulLength))
//                    {
//                        dwVersion = pvffi->dwFileVersionMS;
//                        dwMiniVersion = pvffi->dwFileVersionLS;
//                    }
//                }
//                HeapFree(hHeap, 0, pvVerInfoData);
//            }
//        }
//    }
//    return ""+to_string(HIWORD(dwVersion))+"."+ to_string(LOWORD(dwVersion))+"."+ to_string(HIWORD(dwMiniVersion))+"."+ to_string(LOWORD(dwMiniVersion));*/
//    return "";
//}
////string getNTVersion()
////{
////    DWORD dwVersion = 0;
////    DWORD dwMajorVersion = 0;
////    DWORD dwMinorVersion = 0;
////    DWORD dwBuild = 0;
////    DWORD dwChange= 0;
////
////    dwVersion = GetVersion();
////
////    // Get the Windows version.
////
////    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
////    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
////
////    // Get the build number.
////
////    if (dwVersion < 0x80000000)
////    {
////        dwBuild = (DWORD)(HIWORD(dwVersion));
////    }
////    return "NT " + to_string(dwMajorVersion) + "." + to_string(dwMinorVersion) + "." + to_string(dwBuild);
////
////}
//
//string GetFullOSVersion()
//{
//    string result="δƥ�䵽��ӦWindows����ϵͳ";
//    if (judgeOSVersion(5, 0, 0))
//        result = "Windows 2000";
//    if (judgeOSVersion(5, 0, 1))
//        result = "Windows 2000 Service Pack 1";
//    if (judgeOSVersion(5, 0, 2))
//        result = "Windows 2000 Service Pack 2";
//    if (judgeOSVersion(5, 0, 3))
//        result = "Windows 2000 Service Pack 3";
//    if (judgeOSVersion(5, 0, 4))
//        result = "Windows 2000 Service Pack 4";
//    if (judgeOSVersion(5, 1, 0))
//        result = "Windows XP";
//    if (judgeOSVersion(5, 1, 1))
//        result = "Windows XP Service Pack 1";
//    if (judgeOSVersion(5, 1, 2))
//        result = "Windows XP Service Pack 2";
//    if (judgeOSVersion(5, 1, 3))
//        result = "Windows XP Service Pack 3";
//    if (judgeOSVersion(6, 0, 0))
//        result = "Windows Vista";
//    if (judgeOSVersion(6, 0, 0) && IsWindowsServer())
//        result = "Windows Server 2008";
//    if (judgeOSVersion(6, 0, 1))
//        result = "Windows Vista Service Pack 1";
//    if (judgeOSVersion(6, 0, 2))
//        result = "Windows Vista Service Pack 2";
//    if (judgeOSVersion(6, 0, 1) && IsWindowsServer())
//        result = "Windows Server 2008 Service Pack 1";
//    if (judgeOSVersion(6, 0, 2) && IsWindowsServer())
//        result = "Windows Server 2008 Service Pack 2";
//    if (judgeOSVersion(6, 1, 0))
//        result = "Windows 7";
//    if (judgeOSVersion(6, 1, 1))
//        result = "Windows 7 Service Pack 1";
//    if (judgeOSVersion(6, 1, 1) && IsWindowsServer())
//        result = "Windows Server 2008 R2 Service Pack 1";
//    if (judgeOSVersion(6, 1, 2) && IsWindowsServer())
//        result = "Windows Server 2008 R2 Service Pack 2";
//    if (judgeOSVersion(6, 2, 0))
//        result = "Windows 8";
//    if (judgeOSVersion(6, 3, 0))
//        result = "Windows 8.1";
//    if (judgeOSVersion(6, 2, 0) && IsWindowsServer())
//        result = "Windows Server 2012";
//    if (judgeOSVersion(6, 3, 0) && IsWindowsServer())
//        result = "Windows Server 2012 R2";
//    if (judgeOSVersion(10, 0, 0, 10240))
//        result = "Windows 10 �汾 1507";
//    if (judgeOSVersion(10, 0, 0, 10586))
//        result = "Windows 10 �汾 1511";
//    if (judgeOSVersion(10, 0, 0, 14393))
//        result = "Windows 10 �汾 1607";
//    if (judgeOSVersion(10, 0, 0, 14393) && IsWindowsServer())
//        result = "Windows Server 2016";
//
//    if (judgeOSVersion(10, 0, 0, 15063))
//        result = "Windows 10 �汾 1703";
//    if (judgeOSVersion(10, 0, 0, 16299))
//        result = "Windows 10 �汾 1709";
//    if (judgeOSVersion(10, 0, 0, 17134))
//        result = "Windows 10 �汾 1803";
//    if (judgeOSVersion(10, 0, 0, 17744) && IsWindowsServer())
//        result = "Windows Server 2019";
//
//    if (judgeOSVersion(10, 0, 0, 17763))
//        result = "Windows 10 �汾 1809";
//    if (judgeOSVersion(10, 0, 0, 18362))
//        result = "Windows 10 �汾 1903";
//    if (judgeOSVersion(10, 0, 0, 18363))
//        result = "Windows 10 �汾 1909";
//    if (judgeOSVersion(10, 0, 0, 19041))
//        result = "Windows 10 �汾 2004";
//    if (judgeOSVersion(10, 0, 0, 19042))
//        result = "Windows 10 �汾 20H2";
//    if (judgeOSVersion(10, 0, 0, 19043))
//        result = "Windows 10 �汾 21H1";
//    if (judgeOSVersion(10, 0, 0, 19044))
//        result = "Windows 10 �汾 21H2";
//    if (judgeOSVersion(10, 0, 0, 19045))
//        result = "Windows 10 �汾 22H2";
//    if (judgeOSVersion(10, 0, 0, 22000))
//        result = "Windows 11 �汾 21H2";
//    if (judgeOSVersion(10, 0, 0, 22621))
//        result = "Windows 11 �汾 22H2";
//    if (judgeOSVersion(10, 0, 0, 20348) && IsWindowsServer())
//        result = "Windows Server 2022";
//    string s = getTEBVersion();
//    if (IsWindowsXPOrGreater())
//        return result + " (�ں˰汾��"+s+ + ")"; //getNTVersion() + ")";
//    else 
//        return result;
//}



string wide_Char_To_Multi_Byte(wchar_t* pWCStrKey)
{
    //��һ�ε���ȷ��ת�����ֽ��ַ����ĳ��ȣ����ڿ��ٿռ�
    int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
    char* pCStrKey = new char[pSize + 1];
    //�ڶ��ε��ý�˫�ֽ��ַ���ת���ɵ��ֽ��ַ���
    WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
    pCStrKey[pSize] = '\0';
    //return pCStrKey;

    /*�����Ҫת����string��ֱ�Ӹ�ֵ����*/
    string pKey = pCStrKey;
    return pKey;
}

wchar_t* multi_Byte_To_Wide_Char(const string& pKey)
{
    //string ת char*
    const char* pCStrKey = pKey.c_str();
    //��һ�ε��÷���ת������ַ������ȣ�����ȷ��Ϊwchar_t*���ٶ����ڴ�ռ�
    int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
    wchar_t* pWCStrKey = new wchar_t[pSize];
    //�ڶ��ε��ý����ֽ��ַ���ת����˫�ֽ��ַ���
    MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
    return pWCStrKey;
}