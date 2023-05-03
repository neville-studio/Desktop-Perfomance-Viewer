#include "../DPV.h"
#include "../framework.h"
#include "common.h"
#include <windows.h>
using namespace std;



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
    delete[] pCStrKey;
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
    //delete[] pCStrKey;
    return pWCStrKey;
}
__int64 diffFileTime(FILETIME time1, FILETIME time2)
{
    __int64 a = time1.dwHighDateTime * pow(2,32) + time1.dwLowDateTime;
    __int64 b = time2.dwHighDateTime * pow(2, 32) + time2.dwLowDateTime;
    return (b - a);
    
}