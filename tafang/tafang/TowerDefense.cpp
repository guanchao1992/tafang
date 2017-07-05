// TowerDefense.cpp : ����Ӧ�ó������ڵ㡣
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
#include "����������.h"

using namespace std;
#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
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

// �˴���ģ���а����ĺ�����ǰ������:
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

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TOWERDEFENSE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TOWERDEFENSE));

	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	bool bt = false;
	WNDCLASSEX wcex3;
	wcex3.cbSize = sizeof(WNDCLASSEX);
	wcex3.style = CS_HREDRAW | CS_VREDRAW;
	wcex3.lpfnWndProc = GamesWndProc;//�����б�
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
	wcex2.lpfnWndProc = CustomButtonWndProc;//�����б�
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	g_pgs = new GamesStart();
    HWND hWnd;
    g_hinst = hInstance;// ��ʵ������洢��ȫ�ֱ�����

	//��ȡ��Դ
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

	//��ʼ����ť����
	g_dbutton = new CDButtonD();
	g_dbutton->InitDButton();
	g_ptfMapst = new TFMapStart();
	//������Ϸ����
	hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUP,
      100	, 10, 800, 600, NULL, NULL, hInstance, NULL);
	g_hWnd = hWnd;
   if (!hWnd)
   {
      return FALSE;
   }

   //��ʼ����,��������
	g_sizewindow.cx = 800;
	g_sizewindow.cy = 600;
	g_pgs->InitGameStart();
	g_pgs->ReDarwBk();
	g_pgs->ShowStart(hWnd);
    ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//��ʱ������

	InityanshiFree();

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��:
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
			case IDC_BUT_Stop://���ؿ�ʼ����
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
				//��Ϸ��ͼ��ʼ��
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
		// TODO: �ڴ���������ͼ����...
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
			g_ptfMapst->m_tfmm.OutDraw(g_ptfMapst->GetHDC(), 0, 0);//�ڻ������л��Ʊ���

			//�����ǻ���Ԫ��
			g_ptfMapst->m_Turret.DrawAll(g_ptfMapst->GetHDC());//��������
			g_ptfMapst->m_Meastar.DrawAll(g_ptfMapst->GetHDC());//���Ƶ���
			g_ptfMapst->m_Bullet.DrawAll(g_ptfMapst->GetHDC());//�����ӵ�
			g_ptfMapst->m_Stunt.DrawALL(g_ptfMapst->GetHDC());//�ؼ�
			g_ptfMapst->m_Turret.DrawButton(g_ptfMapst->GetHDC());//ѡ��������İ�ť
			g_ptfMapst->DrawOther(TFMapStart::DrawOne);//����Ч��
			//��ʾ֡��
			TextOutA(g_ptfMapst->GetHDC(), 0, 0, g_ptfMapst->m_strfps, strlen(g_ptfMapst->m_strfps));

			//���������е�ͼ����Ƶ���Ļָ������
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

// �����ڡ������Ϣ�������
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
