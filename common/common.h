#pragma once
#define _WIN32_DCOM
#include <iostream>
//#pragma warning(disable: 4996)
#include <shlwapi.h>
#include<ShlObj.h>
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "version.lib")
using namespace std;
#include <wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
#include<string>
#include<comutil.h>
#include <VersionHelpers.h>


using namespace std;
string wide_Char_To_Multi_Byte(wchar_t* pWCStrKey);
wchar_t* multi_Byte_To_Wide_Char(const string& pKey);
__int64 diffFileTime(FILETIME time1, FILETIME time2);