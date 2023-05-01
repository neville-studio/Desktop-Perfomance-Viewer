#pragma once
#include <Pdh.h>
#include <PdhMsg.h>
#pragma comment(lib,"pdh.lib")
#include <string>
#include "DPV.h"
using namespace std;
class DPHViewer {
public:
	DPHViewer(WCHAR CounterPathBuffer[PDH_MAX_COUNTER_PATH]);
	double getData();
protected:
	void init();
	void config(WCHAR CounterPathBuffer[PDH_MAX_COUNTER_PATH]);
    void destroy();
private:
    PDH_STATUS Status;
    HQUERY Query;
    HCOUNTER Counter;
    PDH_FMT_COUNTERVALUE DisplayValue;
    DWORD CounterType;
    SYSTEMTIME SampleTime;
    PDH_BROWSE_DLG_CONFIG BrowseDlgData;
    int inited ;
    WCHAR CounterPathBuffer[PDH_MAX_COUNTER_PATH];
};