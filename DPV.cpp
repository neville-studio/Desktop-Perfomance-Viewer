// DPV.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "DPV.h"


#define MAX_LOADSTRING 100
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HFONT hFont;
// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DPV, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DPV));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DPV));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    //wcex.style          = NULL;
    //wcex.lpfnWndProc    = WndProc;
    //wcex.cbClsExtra     = 0;
    //wcex.cbWndExtra     = 0;
    //wcex.hInstance      = hInstance;

    //wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DPV));
    //wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    //wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    //wcex.lpszMenuName   = NULL;
    //wcex.lpszClassName  = szWindowClass;
    //wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    //wcex.hbrBackground = CreateSolidBrush(RGB(251, 255, 242));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, NULL,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_CAPTION);
   SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW |WS_EX_NOACTIVATE);
   SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 0, 1);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        //LONG Style = GetWindowLong(hWnd, GWL_EXSTYLE); //hWnd是主窗口句柄
        //SetWindowLong(hWnd, GWL_EXSTYLE, Style | WS_EX_LAYERED);
        //SetLayeredWindowAttributes(hWnd, 0, 0, LWA_ALPHA);
       /* LONG ret = GetWindowLong(hWnd, GWL_EXSTYLE);
        ret = ret | WS_EX_LAYERED;
        SetWindowLong(hWnd, GWL_EXSTYLE, ret);*/
        SetProcessDPIAware();
        RECT workSpace;
        SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&workSpace, 0);
        hFont = CreateFont(-16/*高*/, -8/*宽*/, 0, 0, 400 /*400表示正常字体*/,
            FALSE/*斜体?*/, FALSE/*下划线?*/, FALSE/*删除线?*/, DEFAULT_CHARSET,
            OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
            FF_DONTCARE, TEXT("微软雅黑")
        );
        MoveWindow(hWnd, workSpace.right / 2 - workSpace.left / 2, 50, workSpace.right / 2 - workSpace.left / 2, workSpace.bottom - workSpace.top-50,TRUE);
        HWND OSStatic = CreateWindow(
            L"static",			//静态文本框的类名
            L"操作系统版本",		//控件的文本
            WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ | SS_LEFT /*水平居中*/  /*垂直居中*/,
            0 /*X坐标*/, 0 /*Y坐标*/, workSpace.right/2-workSpace.left/2 /*宽度*/, 20 /*高度*/,
            hWnd,		 //父窗口句柄
            (HMENU)1,	 //为控件指定一个唯一标识符
            hInst,		 //当前程序实例句柄
            NULL
        );
        std::string osVersion;
        osVersion = "操作系统版本：" + getOSFullName();
        SetWindowText(OSStatic, multi_Byte_To_Wide_Char(osVersion));
        SendMessage(OSStatic, WM_SETFONT, (WPARAM)hFont, NULL);
        std::string CPUInfo;
        CPUInfo = "CPU：" + getCPUInformation();
        
        HWND CPUStatic = CreateWindow(
            L"static",			//静态文本框的类名
            L"CPU：",		//控件的文本
            WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ | SS_LEFT /*水平居中*/  /*垂直居中*/,
            0 /*X坐标*/, 20 /*Y坐标*/, workSpace.right / 2 - workSpace.left / 2 /*宽度*/, 44*getCPUCount() /*高度*/,
            hWnd,		 //父窗口句柄
            (HMENU)1,	 //为控件指定一个唯一标识符
            hInst,		 //当前程序实例句柄
            NULL
        );
        
        SetWindowText(CPUStatic, multi_Byte_To_Wide_Char(CPUInfo));
        SendMessage(CPUStatic, WM_SETFONT, (WPARAM)hFont, NULL);

    }

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            //SetLayeredWindowAttributes(hWnd, RGB(251, 255, 242), 0, LWA_COLORKEY);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
            
        }
        break;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdc = (HDC)wParam;
        SetTextColor(hdc, RGB(255,255,254));
        SetBkMode(hdc, TRANSPARENT);
        return (LRESULT)GetStockObject(NULL_BRUSH);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        closeWMI();
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
