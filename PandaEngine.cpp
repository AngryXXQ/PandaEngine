// PandaEngine.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "PandaEngine.h"
#include "RenderManager.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

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
    LoadStringW(hInstance, IDC_PANDAENGINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    Transform t;
    t.position = Vector3f(0,-10,50);
    t.rotation = Vector3f(-90,90, 0);
    RenderManager::getInstance()->AddModel("res/Death.FBX","res/Death.fbm/DEATHWING2.tga",t);

    /*
    Transform t0;
    t0.position = Vector3f(0, 0, 10);
    t0.rotation = Vector3f(0, 0, 180);
    RenderManager::getInstance()->AddModel("res/Bear_01/Bear_01.fbx", "res/Bear_01/Bear_Body.png", t0);
    */

    /*
    Transform t1;
    t1.position = Vector3f(1, 0, 10);
    RenderManager::getInstance()->AddModel("res/Bat_01/Bat_01.fbx", t1);
    */

    /*
    Transform t2;
    t2.position = Vector3f(0, 5, 1000);
    t2.scale = Vector3f(0.1, 0.1, 0.1);
    t2.rotation = Vector3f(90, 0, 0);
    RenderManager::getInstance()->AddModel("res/Unitychan/Unitychan.fbx", t2);
    */

    /*
    Transform t3;
    t3.position = Vector3f(0, 0, 10);
    t3.rotation = Vector3f(0, 0, 180);
    RenderManager::getInstance()->AddModel("res/Xiukai_skill01/Xiukai_skill01.fbx", "res/Xiukai_skill01/Xiukai_01_Body.png", t3);
    */

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PANDAENGINE));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }        
        RenderManager::getInstance()->Update();
    }

    RenderManager::getInstance()->Destory();
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PANDAENGINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PANDAENGINE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   float win_width = 1000;
   float win_height = 800;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, win_width, win_height, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   RenderManager::getInstance()->Init(hWnd, win_width, win_height);

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
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        {
            float detal = 1;
            Vector3f rotation(0, 0, 0);
            Vector3f offset(0, 0, 0);
            if (wParam == VK_DOWN)
            {
                offset.z -= detal;
            }
            else if (wParam == VK_UP)
            {
                offset.z += detal;
            }
            else if (wParam == VK_LEFT)
            {
                offset.x -= detal;
            }
            else if (wParam == VK_RIGHT)
            {
                offset.x += detal;
            }
            else if (wParam == VK_NUMPAD7)
            {
                offset.y += detal;
            }
            else if (wParam == VK_NUMPAD8)
            {
                offset.y -= detal;
            }
            else if (wParam == VK_NUMPAD1)
            {
                rotation.x += detal;
                RenderManager::getInstance()->RotateModels(rotation);
            }
            else if (wParam == VK_NUMPAD4)
            {
                rotation.x -= detal;
                RenderManager::getInstance()->RotateModels(rotation);
            }
            else if (wParam == VK_NUMPAD2)
            {
                rotation.y += detal;
                RenderManager::getInstance()->RotateModels(rotation);
            }
            else if (wParam == VK_NUMPAD5)
            {
                rotation.y -= detal;
                RenderManager::getInstance()->RotateModels(rotation);
            }
            else if (wParam == VK_NUMPAD3)
            {
                rotation.z += detal;
                RenderManager::getInstance()->RotateModels(rotation);
            }
            else if (wParam == VK_NUMPAD6)
            {
                rotation.z -= detal;
                RenderManager::getInstance()->RotateModels(rotation);
            }
            RenderManager::getInstance()->ChangeCameraPos(offset);
        }
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
