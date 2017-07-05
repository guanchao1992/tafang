// TowerDefense.cpp : 定义应用程序的入口点。
//
//Tower defense
//TowerDefense
//TOWERDEFENSE
#include "stdafx.h"
#include "TowerDefense.h"
#include "TFmapBasis.h"
#include "TFMapMask.h"
#include "API.h"
#include "TFMapStart.h"
#include "GamesStart.h"
#include "名字真难起.h"

using namespace std;
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HINSTANCE g_hinst;
CDButtonD *g_dbutton;
bool g_bPause = false;
HBITMAP HBIT_Membit;
HDC		HDC_Membit;
HBITMAP HBITMAP_Meastar;
HDC		HDC_Meastar;
HBITMAP HBITMAP_TURRET;
HDC		HDC_TURRET;
HBITMAP HBITMAP_BULLET;
HDC		HDC_BULLET;
HBITMAP HBITMAP_STUNT;
HDC		HDC_STUNT;
HBITMAP HBITMAP_BUTTON;
HDC		HDC_BUTTON;
HWND g_hWnd=NULL;
TFMapStart *g_ptfMapst;
GamesStart *g_pgs;
SIZE	g_sizewindow;
int g_beilv = 1;

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int SetBeilv(int b)
{
	g_beilv = b;
	return b;
}
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TOWERDEFENSE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TOWERDEFENSE));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
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
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	bool bt = false;
	WNDCLASSEX wcex3;
	wcex3.cbSize = sizeof(WNDCLASSEX);
	wcex3.style = CS_HREDRAW | CS_VREDRAW;
	wcex3.lpfnWndProc = GamesWndProc;//好友列表
	wcex3.cbClsExtra = 0;
	wcex3.cbWndExtra = 0;
	wcex3.hInstance = hInstance;
	wcex3.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TOWERDEFENSE));
	wcex3.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wcex2.lpszMenuName	= MAKEINTRESOURCE(IDC_CHATC);
	wcex3.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex3.lpszClassName = _T("GamesWndProc");
	wcex3.lpszMenuName = MAKEINTRESOURCE(IDC_TOWERDEFENSE);
	wcex3.hIconSm = LoadIcon(wcex3.hInstance, MAKEINTRESOURCE(IDI_TOWERDEFENSE));
	bt=RegisterClassEx(&wcex3);

	WNDCLASSEX wcex2;
	wcex2.cbSize = sizeof(WNDCLASSEX);
	wcex2.style = CS_HREDRAW | CS_VREDRAW;
	wcex2.lpfnWndProc = CustomButtonWndProc;//好友列表
	wcex2.cbClsExtra = 0;
	wcex2.cbWndExtra = 0;
	wcex2.hInstance = hInstance;
	wcex2.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TOWERDEFENSE));
	wcex2.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wcex2.lpszMenuName	= MAKEINTRESOURCE(IDC_CHATC);
	wcex2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex2.lpszClassName = _T("DButton");
	wcex2.lpszMenuName = MAKEINTRESOURCE(IDC_TOWERDEFENSE);
	wcex2.hIconSm = LoadIcon(wcex2.hInstance, MAKEINTRESOURCE(IDI_TOWERDEFENSE));
	bt=RegisterClassEx(&wcex2);


	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TOWERDEFENSE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName =  MAKEINTRESOURCE(IDC_TOWERDEFENSE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	g_pgs = new GamesStart();
    HWND hWnd;
    g_hinst = hInstance;// 将实例句柄存储在全局变量中

	//读取资源
	HBIT_Membit = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_ZHEBI));
	HDC_Membit = CreateCompatibleDC(NULL);
	SelectObject(HDC_Membit, HBIT_Membit);
	HBITMAP_Meastar = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_Meastar));
	HDC_Meastar = CreateCompatibleDC(NULL);
	SelectObject(HDC_Meastar, HBITMAP_Meastar);
	HBITMAP_TURRET = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_TURRET));
	HDC_TURRET = CreateCompatibleDC(NULL);
	SelectObject(HDC_TURRET,HBITMAP_TURRET);
	HBITMAP_BULLET = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BULLET));
	HDC_BULLET = CreateCompatibleDC(NULL);
	SelectObject(HDC_BULLET,HBITMAP_BULLET);
	HBITMAP_STUNT = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_STUNT));
	HDC_STUNT = CreateCompatibleDC(NULL);
	SelectObject(HDC_STUNT, HBITMAP_STUNT);
	HBITMAP_BUTTON = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BUTTON));
	HDC_BUTTON = CreateCompatibleDC(NULL);
	SelectObject(HDC_BUTTON, HBITMAP_BUTTON);

	SetBkColor(HDC_Meastar, RGB(255, 255, 255));

	//初始化按钮对象
	g_dbutton = new CDButtonD();
	g_dbutton->InitDButton();
	g_ptfMapst = new TFMapStart();
	//创建游戏窗口
	hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUP,
      100	, 10, 800, 600, NULL, NULL, hInstance, NULL);
	g_hWnd = hWnd;
   if (!hWnd)
   {
      return FALSE;
   }

   //开始界面,背景设置
	g_sizewindow.cx = 800;
	g_sizewindow.cy = 600;
	g_pgs->InitGameStart();
	g_pgs->ReDarwBk();
	g_pgs->ShowStart(hWnd);
    ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//计时器设置

	InityanshiFree();

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//



bool bLDOWN = false;
POINTS oldPoint;
int ntime = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	switch (message)
	{
	case WM_CREATE:


		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		if (wmId >= IDC_BUT_TURRET)
		{
			g_ptfMapst->OnCommand(wmId);
		}
		else
		{
			switch (wmId)
			{
			case  IDC_BUT_Start:
				if (g_bPause==false)
				{
					g_ptfMapst->m_Meastar.Chuguai();
				}
				else
				{
					SendMessage(hWnd, WM_COMMAND, IDC_BUT_Pause, 0);
				}
				break;
			case IDC_BUT_Pause:
				if (g_bPause)
				{
					g_ptfMapst->DrawTop(TFMS_SHOW_NULL);
					g_bPause = false;
				}
				else
				{
					g_ptfMapst->DrawTop(TFMS_SHOW_PAUSE);
					g_bPause = true;
				}
				break;
			case IDC_BUT_Stop://返回开始界面
				g_bPause = false;
				ntime = 0;
				g_beilv = 1;
				KillTimer(hWnd, 0);
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				g_ptfMapst->ReleaseMapStart();
				g_pgs->ReShowStart();
				break;
			case IDC_BUT_WIN:
				g_bPause = true;
				g_ptfMapst->DrawTop(TFMS_SHOW_WIN);
				break;
			case IDC_BUT_DIED:
				g_bPause = true;
				g_ptfMapst->DrawTop(TFMS_SHOW_DIED);
				break;
			case IDC_BUT_BEILV1:
				SetBeilv(1);
				break;
			case IDC_BUT_BEILV2:
				SetBeilv(2);
				break;
			case IDC_BUT_BEILV3:
				SetBeilv(3);
				break;
			case IDC_BUT_BEILV4:
				SetBeilv(4);
				break;
			case IDC_BUT_GameStart:
				//游戏地图初始化
				g_ptfMapst->InviStart(hWnd);
				g_ptfMapst->ReadnGMap(1);
				g_ptfMapst->SetLeftTop(g_pgs->GetHDCbk(), g_sizewindow.cx, g_sizewindow.cy);
				SetTimer(hWnd, 0, 1000, NULL);
				SetTimer(hWnd, 1, 1000, NULL);
				SetTimer(hWnd, 2, 1, NULL);
				g_pgs->CloseStart();
				break;
			case IDC_BUT_GameMake:
				g_pgs->OpenMake();
				break;
			case IDC_BUT_GameComplile:
				g_pgs->OpenComplile();
				break;
			case IDC_BUT_GameAbout:
				g_pgs->OpenAbout();
				break;
			case IDC_BUT_GameEdit:
				PostQuitMessage(0);
				break;
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
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		g_pgs->OnPoint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		bLDOWN = true;
		g_ptfMapst->OnLButtonDown(MAKEPOINTS(lParam));
		break;
	case WM_LBUTTONUP:
		bLDOWN = false;
		g_ptfMapst->OnLButtonUp(MAKEPOINTS(lParam));
		break;
	case WM_RBUTTONDOWN:
		g_ptfMapst->OnRButtonDown(MAKEPOINTS(lParam));
		break;
	case WM_RBUTTONUP:
		g_ptfMapst->OnRButtonUp(MAKEPOINTS(lParam));
		break;
	case WM_MOUSEMOVE:
		oldPoint = MAKEPOINTS(lParam);
		g_ptfMapst->OnMouseMove(MAKEPOINTS(lParam));
		break;
	case WM_MOUSELEAVE:
		g_ptfMapst->OnMouseLever();
		return 0;
	case WM_KEYDOWN:
	{
					   //Key State Masks for Mouse Messages
					   //SHORT sh=GetKeyState(MK_SHIFT);
					   //	//MK_SHIFT
					   //BYTE a[]="a";
					   //bool b=GetKeyboardState(a);
					   //int aaa = 0;

	}
		break;
	case WM_SIZE:
		
		GetWindowRect(hWnd, &rect);
		g_sizewindow= { rect.right - rect.left, rect.bottom - rect.top };
		g_pgs->ReDarwBk();
		g_pgs->ShowStart(hWnd);
		g_ptfMapst->SetLeftTop(g_pgs->GetHDCbk(), 10, 120);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 0:
			if (ntime > 0 && g_bPause==false)
			{
				Meastar ms;
				ms.type = rand() % 6;
				ms.speed = 60;//(rand() % 3+2) * 100;
				ms.life = 20000;
				ms.lifeUp = ms.life;
				MeastarList *ps=g_ptfMapst->m_Meastar.CreateMeastar(&ms);
				//g_ptfMapst->m_Meastar.FindMoveTo(&ps->ms, 0, 50*4);
				ntime--;
			}
			break;
		case 1:
			g_ptfMapst->GetnFPS();
			break;
		case 2:

			hdc = GetDC(hWnd);
			g_ptfMapst->m_tfmm.OutDraw(g_ptfMapst->GetHDC(), 0, 0);//在缓冲区中绘制背景

			//以下是绘制元素
			g_ptfMapst->m_Turret.DrawAll(g_ptfMapst->GetHDC());//绘制炮塔
			g_ptfMapst->m_Meastar.DrawAll(g_ptfMapst->GetHDC());//绘制敌人
			g_ptfMapst->m_Bullet.DrawAll(g_ptfMapst->GetHDC());//绘制子弹
			g_ptfMapst->m_Stunt.DrawALL(g_ptfMapst->GetHDC());//特技
			g_ptfMapst->m_Turret.DrawButton(g_ptfMapst->GetHDC());//选中炮塔后的按钮
			g_ptfMapst->DrawOther(TFMapStart::DrawOne);//其他效果
			//显示帧率
			TextOutA(g_ptfMapst->GetHDC(), 0, 0, g_ptfMapst->m_strfps, strlen(g_ptfMapst->m_strfps));

			//将缓冲区中的图像绘制到屏幕指定区域
			//g_ptfMapst->OnPaint(hdc, 100, 100);
			g_ptfMapst->OnDraw(hdc);
			g_ptfMapst->m_ifps++;
			//if (g_ptfMapst->m_nfps>50)Sleep(10);
			ReleaseDC(hWnd, hdc);

			break;
		}
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
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
