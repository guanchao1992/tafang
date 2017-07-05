#include "stdafx.h"
#include "GamesStart.h"
#include "TowerDefense.h"
#include "API.h"
#include "TFMapMask.h"
GamesStart* GamesStart::m_pGamethis = NULL;

unsigned __stdcall GamesAboutRun(void*lp)
{
	GamesStart *pgs = (GamesStart*)lp;
	AboutTextList*Temp;// , Next;
	//int rx = (g_sizewindow.cx - 600) / 2;
	while (pgs->GetType()==3)
	{
		Temp = pgs->GetheadAboutTextList()->Next;

		while (pgs->GetType() == 3&&Temp != pgs->GetheadAboutTextList())
		{
			Temp->y--;
			if (Temp->y < -20)
			{
				Temp = pgs->DeleteAboutTextList(Temp);
			}
			else
			{
				Temp = Temp->Next;
			}
		}
		Sleep(50);
	}
	return 0;
}


LRESULT CALLBACK GamesWndProc(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	HDC hdc;
	PAINTSTRUCT ps;
	POINTS point;
	UNREFERENCED_PARAMETER(lParam);
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_LBUTTONDOWN:
		point = MAKEPOINTS(lParam);
		GamesStart::Getthis()->OnLButtonDown(hWnd,wParam,lParam);
		break;
	case WM_LBUTTONUP:
		point = MAKEPOINTS(lParam);
		GamesStart::Getthis()->OnLButtonUp(hWnd, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		point = MAKEPOINTS(lParam);
		GamesStart::Getthis()->OnMouseMove(hWnd, wParam, lParam);
		break;
	case WM_MOUSELEAVE:
		point = MAKEPOINTS(lParam);
		GamesStart::Getthis()->OnMouseLeave(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL || LOWORD(wParam) == IDCLOSE )
		{
			GamesStart::Getthis()->Close();
			GamesStart::Getthis()->ReShowStart();
			DestroyWindow(hWnd);
			//CloseWindow(hWnd);
		//	return (INT_PTR)TRUE;
		}
		DlgMapMask(hWnd, uMsg, wParam, lParam);
		break;
	case WM_PAINT:
		hdc = ::BeginPaint(hWnd, &ps);
		GamesStart::Getthis()->OnPointT(hdc, &ps.rcPaint);
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 0:
			hdc = GetDC(hWnd);
			AboutTextList*Temp = GamesStart::Getthis()->GetheadAboutTextList()->Next;
			if (Temp&&Temp != Temp->Next)
			{
				while (GamesStart::Getthis()->GetType() == 3 && Temp != GamesStart::Getthis()->GetheadAboutTextList())
				{
					Temp->y--;
					if (Temp->y > -20 && Temp->y < 700)
					{
						BitBlt(GamesStart::Getthis()->GetHDCa(), (g_sizewindow.cx - 600) / 2, Temp->y, 600, 40, GamesStart::Getthis()->GetHDCtr(), (g_sizewindow.cx - 600) / 2, Temp->y, SRCCOPY);
						TextOutA(GamesStart::Getthis()->GetHDCa(), (g_sizewindow.cx - 600) / 2, Temp->y, Temp->buffer, strlen(Temp->buffer));
					}
					Temp = Temp->Next;
				}
			}
			else
			{
				HBITMAP hbit = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_Duang));
				HDC hdcbit = CreateCompatibleDC(NULL);
				SelectObject(hdcbit, hbit);
				BitBlt(GamesStart::Getthis()->GetHDCa(), 92, 60, 215, 133, hdcbit, 0, 0, SRCCOPY);
			}
			RECT rect = { 0, 0, 1000, 1000 };
			BitBlt(hdc, 100, 20, 400, 500, GamesStart::Getthis()->GetHDCa(), 100, 20, SRCCOPY);
			//GamesStart::Getthis()->DrawAbout();
			ReleaseDC(hWnd, hdc);
			break;
		}
		break;
	case WM_DESTROY:
		//DestroyWindow(hWnd);
		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


GamesStart::GamesStart()
{
	m_hdc = NULL;
	m_hbitmap = NULL;
	m_ntype = 0;
	m_hdct = NULL;
	m_hbitmapt = NULL;
	m_hWnd=NULL;
	m_hWndChild=NULL;
	GamesStart::m_pGamethis = this;
	m_headAboutTextList = NULL;
	m_itAboutTextList = 0;
}

GamesStart::~GamesStart()
{
	if (GamesStart::m_pGamethis ==this)
		GamesStart::m_pGamethis = NULL;
}

//int GamesStart::DrawAbout()
//{
//	AboutTextList*Temp = m_headAboutTextList->Next;
//	while (Temp != m_headAboutTextList)
//	{
//		if (Temp->y >-20 && Temp->y < 600)
//		{
//			BitBlt(m_hdca, 40, Temp->y, 400, 40, m_hdctr, 40, Temp->y, SRCCOPY);
//			TextOutA(m_hdca, 40, Temp->y, Temp->buffer, strlen(Temp->buffer));
//
//		}
//		Temp = Temp->Next;
//	}
//	return 0;
//}
int GamesStart::OnPointT(HDC hdc,LPRECT rect)
{
	BitBlt(hdc, rect->left, rect->top, rect->right - rect->left, rect->bottom - rect->top, m_hdct, rect->left, rect->top, SRCCOPY);
	//BitBlt(hdc, 50, 60, 500, 700, m_hdct2, 50, 60, SRCAND);
	if (m_ntype == 2)
	{
		m_ptfm->OnPaint(hdc,rect);
	}
	//else if (m_ntype == 3)
	//{
	//	BitBlt(hdc, 100, 20,400, 500, m_hdca, 100, 20, SRCCOPY);
	//}
	return 0;
}
int GamesStart::InitGameStart()
{
	m_hFont = CreateFont(24, // nHeight 
		0, 0, 0, 2, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		_T("楷体"));
	m_hdc = CreateCompatibleDC(NULL);
	m_hbitmap = CreateBitmap(2000, 2000, 1, 32, NULL);
	SelectObject(m_hdc, m_hbitmap);
	m_hdctr = CreateCompatibleDC(NULL);
	m_hbitmaptr = CreateBitmap(2000, 2000, 1, 32, NULL);
	SelectObject(m_hdctr, m_hbitmaptr);

	//ReDarwBk();

	m_headAboutTextList = (AboutTextList*)malloc(sizeof(AboutTextList));
	m_headAboutTextList->Next = m_headAboutTextList;
	m_headAboutTextList->Pre = m_headAboutTextList;
	
//	_beginthreadex(NULL, 0, &GamesStartDrawRun, (void*)this, 0, &m_uGamesStartDrawRunThreadID);


	return 0;
}

int GamesStart::ReleaseGameStart()
{	
//	_endthreadex(m_uGamesStartDrawRunThreadID);
	DeleteAboutTextListAll();
	yanshiFree(m_headAboutTextList);
	m_headAboutTextList = NULL;
	DeleteDC(m_hdct);
	DeleteObject(m_hbitmapt);
	m_hdct = NULL;
	m_hbitmapt = NULL;
	DeleteDC(m_hdc);
	DeleteObject(m_hbitmap);
	m_hdc = NULL;
	m_hbitmap = NULL;
	DeleteObject(m_hFont);
	return 0;
}
int GamesStart::ReDarwBk()
{

	//显示开始画面
	HBITMAP hbitmap = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_GAMESTART));
	BitmapToRect(hbitmap, m_hbitmap, g_sizewindow);
	SIZE s = { g_sizewindow.cx - 80, g_sizewindow.cy - 70 };
	HBITMAP hbitmap1 = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_GAMESTART_MAKE));
	BitmapToRect(hbitmap1, m_hbitmaptr, s);
	if (m_hdct)
	{
		DeleteDC(m_hdct);
		DeleteObject(m_hbitmapt);
	}
	m_hdct=CreateCompatibleDC(NULL);
	m_hbitmapt = CreateBitmap(s.cx, s.cy, 1, 32, NULL);
	SelectObject(m_hdct,m_hbitmapt);
	SetBkMode(m_hdct, TRANSPARENT);
	SelectObject(m_hdct, m_hFont);
	SetTextColor(m_hdct,RGB(254,254,254) );
	return 0;
}
//显示开始界面
int GamesStart::ShowStart(HWND hWnd)
{
	m_hWnd = hWnd;
	int x = g_sizewindow.cx / 2 - 70;
	int y = g_sizewindow.cy - 300;
	if (m_ntype == 0)//无
	{
		g_dbutton->Create(hWnd, g_hinst, x, y, 140, 32, IDC_BUT_GameStart, HDC_BUTTON, 0, 116, 140, 40, _T("开始游戏"), BR_TYBack | BR_TY_W, m_hdc);
		g_dbutton->Create(hWnd, g_hinst, x, y + 40, 140, 32, IDC_BUT_GameMake, HDC_BUTTON, 0, 116, 140, 40, _T("设置"), BR_TYBack | BR_TY_W, m_hdc);
		g_dbutton->Create(hWnd, g_hinst, x, y + 80, 140, 32, IDC_BUT_GameComplile, HDC_BUTTON, 0, 116, 140, 40, _T("编辑"), BR_TYBack | BR_TY_W, m_hdc);
		g_dbutton->Create(hWnd, g_hinst, x, y + 120, 140, 32, IDC_BUT_GameAbout, HDC_BUTTON, 0, 116, 140, 40, _T("关于TowerDefense"), BR_TYBack | BR_TY_W, m_hdc);
		g_dbutton->Create(hWnd, g_hinst, x, y + 160, 140, 32, IDC_BUT_GameEdit, HDC_BUTTON, 0, 116, 140, 40, _T("退出游戏"), BR_TYBack | BR_TY_W, m_hdc);
	}
	RECT rect = { 0, 0, g_sizewindow.cx, g_sizewindow.cy };
	InvalidateRect(hWnd,&rect,true);
	return 0;
}

//关闭开始界面
int GamesStart::CloseStart()
{
	g_dbutton->Delete(m_hWnd, IDC_BUT_GameStart);
	g_dbutton->Delete(m_hWnd, IDC_BUT_GameMake);
	g_dbutton->Delete(m_hWnd, IDC_BUT_GameComplile);
	g_dbutton->Delete(m_hWnd, IDC_BUT_GameAbout);
	g_dbutton->Delete(m_hWnd, IDC_BUT_GameEdit);
	return 0;
}
//绘制
int GamesStart::DrawStart()
{
	
	return 0;
}

int GamesStart::OnPoint(HDC hdc)
{
	BitBlt(hdc, 0, 0, g_sizewindow.cx, g_sizewindow.cy, m_hdc, 0, 0, SRCCOPY);
	return 0;
}
//打开基础按钮
int GamesStart::Open()
{	
	//Rectangle(m_hdct, 0, 0, g_sizewindow.cx - 80, g_sizewindow.cy - 70);
	SIZE s = { g_sizewindow.cx - 80, g_sizewindow.cy - 70 };

	BitBlt(m_hdct, 0, 0, s.cx,s.cy,m_hdctr,0,0,SRCCOPY);

	ShowStartButton(SW_HIDE);

	m_hWndChild = CreateWindowEx(WS_EX_NOACTIVATE, _T("GamesWndProc"), _T(""),
		WS_CHILD | WS_VISIBLE, 40, 30, g_sizewindow.cx - 80, g_sizewindow.cy - 70, m_hWnd, (HMENU)100, g_hinst, NULL);
	if (m_hWndChild)
	{
		ShowWindow(m_hWndChild, SW_SHOW);
		g_dbutton->Create(m_hWndChild, g_hinst, g_sizewindow.cx - 80 - 100, g_sizewindow.cy - 70 - 50, 40, 40, IDOK, HDC_BUTTON, 140, 96, 20, 20,
			_T("确定"), BR_TYBack| BR_TY_P | BR_TY_TY_1 | BR_TY_TY_2, m_hdct);
		g_dbutton->Create(m_hWndChild, g_hinst, g_sizewindow.cx - 80 - 50, g_sizewindow.cy - 70 - 50, 40, 40, IDCLOSE, HDC_BUTTON, 160, 96, 20, 20,
			_T("返回"), BR_TYBack | BR_TY_P | BR_TY_TY_1 | BR_TY_TY_2, m_hdct);
	}
	SetTimer(m_hWndChild,0,10, NULL);
	return 0;
}
//打开设置画面
int GamesStart::OpenMake()
{
	//创建另一个画布覆盖背景
	m_ntype = 1;
	Open();

	TextOut(m_hdct, 40, 40, _T("1：分辨率AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"), 50);
	TextOut(m_hdct, 40, 70, _T("2：分辨率2AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"), 50);
	TextOut(m_hdct, 40, 100, _T("3：难度：精打细算  高难度  一般的  简单   上帝模式AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"), 50);
	TextOut(m_hdct, 40, 130, _T("4：难度高级选项AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"), 50);
	TextOut(m_hdct, 40, 160, _T("5：是否开启特效AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"), 50);
	TextOut(m_hdct, 40, 190, _T("6：游戏速度AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"), 50);
//	TextOut(m_hdct, 40, 220, _T("7：游戏速度AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"), 50);

	return 0;
}
//打开地图编辑模式
int  GamesStart::OpenComplile()
{
	m_ntype = 2;
	Open();
	m_ptfm = new TFMapMask();
	m_ptfm->OnCreateMap(m_hWndChild);
	return 0;
}
//打开关于
int GamesStart::OpenAbout()
{	
	m_ntype = 3;
	Open();
	m_itAboutTextList = 0;
	m_hdca = CreateCompatibleDC(NULL);
	m_hbitmapa = CreateBitmap(600, 700, 1, 32, NULL);
	SelectObject(m_hdca, m_hbitmapa);
	SetBkMode(m_hdca, TRANSPARENT);
	SelectObject(m_hdca, m_hFont);
	BitBlt(m_hdca, 0, 0, 600, 700, m_hdctr, 100, 40, SRCAND);

	
	char buffer[256]="0想在这里显示什么呢？";
	for (int i = 0; i < 9; i++)
	{
		AddAboutText("", 0);
	}
	sprintf(buffer,"一大拨CE接近中");
	AddAboutText(buffer, strlen(buffer));
	for (int i = 0; i < 4; i++)
	{
		AddAboutText("", 0);
	}
	sprintf(buffer, "导演  CE");
	AddAboutText(buffer, strlen(buffer));
	sprintf(buffer, "编剧  CE");
	AddAboutText(buffer, strlen(buffer));
	sprintf(buffer, "特效  CE");
	AddAboutText(buffer, strlen(buffer));
	sprintf(buffer, "音乐  CE");
	AddAboutText(buffer, strlen(buffer));
	sprintf(buffer, "演员表");
	AddAboutText(buffer, strlen(buffer));
	sprintf(buffer, "CE1号   CE2号   CE3号   CE4号");
	AddAboutText(buffer, strlen(buffer));
	sprintf(buffer, "CE5号   CE6号   CE7号   CE8号");
	AddAboutText(buffer, strlen(buffer));
	sprintf(buffer, "CE9号   CE10号  CE11号  CE12号");
	AddAboutText(buffer, strlen(buffer));
	sprintf(buffer, "CE13号  CE14号  CE15号  CE16号");
	AddAboutText(buffer, strlen(buffer));
	sprintf(buffer, "CE17号   CE18号  CE19号  CE20号");
	AddAboutText(buffer, strlen(buffer));
	sprintf(buffer, "CE21号   CE22号  CE23号  CE24号");
	AddAboutText(buffer, strlen(buffer));
	sprintf(buffer, "CE25号   CE26号  CE27号  CE28号");
	AddAboutText(buffer, strlen(buffer));
	sprintf(buffer, "CE29号   CE30号  CE31号  CE32号");
	AddAboutText(buffer, strlen(buffer));


	_beginthreadex(NULL, 0, &GamesAboutRun, (void*)this, 0, &m_uGamesAboutRunThreadID);

	return 0;
}

int GamesStart::Close()
{
	switch (m_ntype)
	{
	case 0:
		break;
	case 1:
		CloseMake();
		break;
	case 2:
		CloseComplile();
		break;
	case 3:
		CloseAbout();
		break;
	}
	return 0;
}
//关闭设置画面
int GamesStart::CloseMake()
{
	g_dbutton->Delete(m_hWndChild);
	ShowStartButton(SW_SHOW);
	m_ntype = 0;
	return 0;
}
//关闭地图编辑模式
int GamesStart::CloseComplile()
{
	ShowStartButton(SW_SHOW);
	m_ntype = 0;
	return 0;
}
//关闭关于
int GamesStart::CloseAbout()
{
	ShowStartButton(SW_SHOW);
	m_ntype = 0;
	//_endthreadex(m_uGamesAboutRunThreadID);
	DeleteAboutTextListAll();
	DeleteDC(m_hdca);
	DeleteObject(m_hbitmapa);
	return 0;
}

int GamesStart::OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (m_ntype == 2)
	{
		m_ptfm->OnMouseMove(hWnd,wParam,lParam);
	}
	return 0;
}
int GamesStart::OnMouseLeave(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (m_ntype == 2)
	{
		m_ptfm->OnMouseLeave(hWnd, wParam, lParam);
	}
	return 0;
}
int GamesStart::OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (m_ntype == 2)
	{
		m_ptfm->OnLButtonDown(hWnd, wParam, lParam);
	}
	return 0;
}
int GamesStart::OnLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (m_ntype == 2)
	{
		m_ptfm->OnLButtonUp(hWnd, wParam, lParam);
	}
	return 0;
}
int GamesStart::OnCommand(int nID)
{
	return 0;
}
int GamesStart::ShowStartButton(int nS)
{
	ShowWindow(GetDlgItem(m_hWnd, IDC_BUT_GameStart), nS);
	ShowWindow(GetDlgItem(m_hWnd, IDC_BUT_GameMake), nS);
	ShowWindow(GetDlgItem(m_hWnd, IDC_BUT_GameComplile), nS);
	ShowWindow(GetDlgItem(m_hWnd, IDC_BUT_GameAbout), nS);
	ShowWindow(GetDlgItem(m_hWnd, IDC_BUT_GameEdit), nS);
	return 0;
}
int GamesStart::AddAboutText(char*buffer, int len)
{
	CreateAboutTextList(buffer, len);
	CreateAboutTextList("",0);
	return 0;
}
AboutTextList*GamesStart::CreateAboutTextList(char*buffer, int len)
{	
	AboutTextList*al = (AboutTextList*)malloc(sizeof(AboutTextList));
	if (len > 50)
	{
		al->y = m_itAboutTextList + 30;
		strncpy(al->buffer,buffer,50);
		al->buffer[50] = '\0';
		al->Next = m_headAboutTextList;
		al->Pre = m_headAboutTextList->Pre;
		m_headAboutTextList->Pre->Next = al;
		m_headAboutTextList->Pre = al;
		m_itAboutTextList+=30;
		CreateAboutTextList(buffer+50,len-50);
	}
	else
	{
		al->y = m_itAboutTextList + 30;
		strncpy(al->buffer, buffer, len);
		al->buffer[len] = '\0';
		al->Next = m_headAboutTextList;
		al->Pre = m_headAboutTextList->Pre;
		m_headAboutTextList->Pre->Next = al;
		m_headAboutTextList->Pre = al;
		m_itAboutTextList+=30;
	}
	
	return al;
}
AboutTextList*GamesStart::DeleteAboutTextList(AboutTextList* al)
{
	AboutTextList* Temp = al->Next;
	al->Next->Pre = al->Pre;
	al->Pre->Next = al->Next;

	return Temp;
}
AboutTextList*GamesStart::DeleteAboutTextListAll()
{
	AboutTextList* Temp = m_headAboutTextList->Next;
	AboutTextList*Next = Temp->Next;
	m_headAboutTextList->Next = m_headAboutTextList;
	m_headAboutTextList->Pre = m_headAboutTextList;

	while (Temp != m_headAboutTextList)
	{
		Next = Temp->Next;
		free(Temp);
		Temp = Next;
	}
	return NULL;
}