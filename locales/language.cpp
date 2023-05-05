#include "language.hpp"



Locales::Locales()
{
	switch (GetUserDefaultUILanguage())
	{
	case 2052:
		OSVersionLabel = "\xE6\x93\x8D\xE4\xBD\x9C\xE7\xB3\xBB\xE7\xBB\x9F\xE7\x89\x88\xE6\x9C\xAC\xEF\xBC\x9A";
		CPULabel = "CPU\xEF\xBC\x9A";
		memoryLabel = "\xE5\x86\x85\xE5\xAD\x98\xEF\xBC\x9A";
		GPULabel = "\xE6\x98\xBE\xE5\x8D\xA1\xE4\xBF\xA1\xE6\x81\xAF\xEF\xBC\x9A";
		DiskLabel = "\xE7\xA1\xAC\xE7\x9B\x98\xEF\xBC\x9A";
		ConnectedNetworkCardLabel = "\xE5\xB7\xB2\xE8\xBF\x9E\xE6\x8E\xA5\xE7\x9A\x84\xE7\xBD\x91\xE5\x8D\xA1\xE4\xBF\xA1\xE6\x81\xAF\xEF\xBC\x9A\n";
		fmtWin8 = L"资源使用率：\tCPU：%.2lf%%（%.2lf GHz）\t内存：%d MB 空闲\t网络活动：%.1f %cB/s";
		fmtWin7 = L"资源使用率：\tCPU：%.2lf%%\t内存：%d MB 空闲\t网络活动：%.1f %cB/s";
		fmtVista = L"资源使用率：\tCPU：%.2lf%%\t内存：%d MB 空闲";
		IPAddressLabel = "\n\t\t IP\xE5\x9C\xB0\xE5\x9D\x80\xEF\xBC\x9A";
		defaultGatewayLabel = "\n\t\t \xE9\xBB\x98\xE8\xAE\xA4\xE7\xBD\x91\xE5\x85\xB3\xEF\xBC\x9A";
		CPUCoreLabel = " \xE6\xA0\xB8\xE5\xBF\x83";
		CPULogicProcessorLabel = " \xE9\x80\xBB\xE8\xBE\x91\xE5\xA4\x84\xE7\x90\x86\xE5\x99\xA8";
		MACLabel = "\n\t\t MAC\xE5\x9C\xB0\xE5\x9D\x80\xEF\xBC\x9A";
		mh = "\xEF\xBC\x9A";
		kernalVersionlabel = "\xEF\xBC\x88\xE5\x86\x85\xE6\xA0\xB8\xE7\x89\x88\xE6\x9C\xAC\xEF\xBC\x9A";
		khbh = "\xEF\xBC\x89";
		displaymodeLabel = " \xE6\x98\xBE\xE7\xA4\xBA\xE6\xA8\xA1\xE5\xBC\x8F\xEF\xBC\x9A";
		capacityLabel = " \xE5\xAE\xB9\xE9\x87\x8F\xEF\xBC\x9A";
		diskstatusLabel = " \xE7\x8A\xB6\xE6\x80\x81\xEF\xBC\x9A";
		wcscpy_s(tip1,L"关于");
		wcscpy_s(tip2, L"白色");
		wcscpy_s(tip3, L"黑色");
		wcscpy_s(tip4, L"退出");
		break;

	case 1033:
	default:
		OSVersionLabel = "OS Version:";
		CPULabel = "CPU:";
		memoryLabel = "RAM:";
		GPULabel = "GPU:";
		DiskLabel = "Disk:";
		ConnectedNetworkCardLabel = "Connected Network Card:\n";
		fmtWin8 = L"Usage:\tCPU：%.2lf%%（%.2lf GHz）\tRAM: %d MB free\tNetwork: %.1f %cB/s";
		fmtWin7 = L"Usage: \tCPU：%.2lf%%\tRAM：%d MB free\tNetwork: %.1f %cB/s";
		fmtVista = L"Usage: \tCPU：%.2lf%%\tRAM: %d MB free";
		IPAddressLabel = "\n\t\t IP address: ";
		CPUCoreLabel = " Cores";
		CPULogicProcessorLabel = " Logic Processors";
		defaultGatewayLabel = "\n\t\t Default Gateway: ";
		MACLabel = "\n\t\t MAC Address: ";
		kernalVersionlabel = " (Windows NT ";
		displaymodeLabel = " Display: ";
		capacityLabel = " size:";
		diskstatusLabel = " Status:";
		mh = ": ";
		khbh = ")";
		wcscpy_s(tip1, L"About");
		wcscpy_s(tip2, L"White");
		wcscpy_s(tip3, L"Black");
		wcscpy_s(tip4, L"Exit");
		break;
	}
	OutputDebugString(to_wstring(GetUserDefaultLCID()).c_str());
}
