#pragma once
#include <string>
#include <Windows.h>
using namespace std;

class Locales {
public:
	string OSVersionLabel;
	string kernalVersionlabel;
	string CPULabel;
	string CPUCoreLabel;
	string CPULogicProcessorLabel;
	string memoryLabel;
	string DiskLabel;
	string capacityLabel;
	string displaymodeLabel;
	string diskstatusLabel;
	string ConnectedNetworkCardLabel;
	string IPAddressLabel;
	string defaultGatewayLabel;
	string MACLabel;
	wstring fmtWin8;
	wstring fmtWin7;
	wstring fmtVista;
	string mh;
	string khbh;
	string GPULabel;
	WCHAR tip1[32];
	WCHAR tip2[32];
	WCHAR tip3[32];
	WCHAR tip4[32];
	Locales();
};
