#include "stdafx.h"
#include "TFMapStart.h"
#include <process.h>
#include <commctrl.h>
#include "math.h"

unsigned __stdcall StartDrawRun(void*lp)//绘制
{
	TFMapStart*pMeas = (TFMapStart*)lp;
	HDC hdc = GetDC(pMeas->m_hWnd);
	Sleep(100);
	while (false)
	{
		pMeas->m_tfmm.OutDraw(pMeas->GetHDC(), 0, 0);//在缓冲区中绘制背景

		//以下是绘制元素
		pMeas->m_Turret.DrawAll(pMeas->GetHDC());//绘制炮塔
		pMeas->m_Meastar.DrawAll(pMeas->GetHDC());//绘制敌人
		pMeas->m_Bullet.DrawAll(pMeas->GetHDC());//绘制子弹
		pMeas->m_Stunt.DrawALL(pMeas->GetHDC());//特技
		pMeas->m_Turret.DrawButton(pMeas->GetHDC());//选中炮塔后的按钮
		pMeas->DrawOther(TFMapStart::DrawOne);//其他效果
		//显示帧率
		TextOutA(pMeas->GetHDC(), 0, 0, pMeas->m_strfps, strlen(pMeas->m_strfps));

		//将缓冲区中的图像绘制到屏幕指定区域
		pMeas->OnPaint(hdc);
		pMeas->m_ifps++;
		if (pMeas->m_nfps>50)Sleep(10);
		//else Sleep(1);
		while (g_bPause)Sleep(100);//暂停
	}
	ReleaseDC(pMeas->m_hWnd, hdc);
	return 0;
}

unsigned __stdcall StartRun(void*lp)
{
	TFMapStart*pM = (TFMapStart*)lp;
	Sleep(100);
	int mmm;
	while (1)
	{
		//pM->m_Meastar.RetrieveAll(mmm,pM->m_gamesLevel);
		Sleep(100);
	}
}

TFMapStart::TFMapStart()
{
	m_tTop = 0;
	m_hdcT = NULL;
	m_hbitmapT = NULL;
	m_hdc = NULL;
	m_hbitmap = NULL;
	m_ifps = 0;
	m_bLDown = false;
	m_bRDown = false;
	m__bMouseTrack = true;
	m_iselecttype = -1;
	_beginthreadex(NULL, 0, &StartDrawRun, (void*)this, 0, &m_uDrawRunThreadID);
	m_strfps[0] = '\0';

	m_bStart = false;
}

TFMapStart::~TFMapStart()
{
	_endthreadex(m_uDrawRunThreadID);

}
//初始化
int TFMapStart::InviStart(HWND hWnd)
{
	m_tTop = TFMS_SHOW_NULL;
	m_hWnd = hWnd;
	m_hdcTurretType = CreateCompatibleDC(NULL);
	m_hbitmapTurretType = CreateBitmap(32, 32, 1, 32, NULL);
	SelectObject(m_hdcTurretType, m_hbitmapTurretType);
	m_hdcT = CreateCompatibleDC(NULL);
	m_hbitmapT = CreateBitmap(200, 60, 1, 32, NULL);
	SelectObject(m_hdcT, m_hbitmapT);
	m_gamesLevel.InitGamesLevels(&m_Map);
	m_Stunt.InitStunt();
	m_Meastar.InitMeastar(&m_gamesLevel,&m_Stunt);	
	m_Bullet.InitBullet(&m_gamesLevel, m_Meastar.m_headListMeastar, &m_Stunt);
	m_Turret.InitTurret(hWnd, &m_gamesLevel, &m_Bullet, &m_Meastar, &m_Map);
	//int x = m_lefttop.x//(g_sizewindow.cx -m_Map.m_nw*4) / 2;

	m_bStart = true;
	return 0;
}
int TFMapStart::ReleaseMapStart()
{
	m_bStart = false;
	g_dbutton->Delete(m_hWnd);
	//g_dbutton->Delete(m_hWnd, IDC_BUT_MapMask);
	//g_dbutton->Delete(m_hWnd, IDC_BUT_Start);
	//g_dbutton->Delete(m_hWnd, IDC_BUT_Pause);
	//g_dbutton->Delete(m_hWnd, IDC_BUT_Stop);
	//g_dbutton->Delete(m_hWnd, IDC_BUT_AddMeastar);
	m_Turret.ReleaseTurret();
	m_Bullet.ReleaseBullet();
	m_Meastar.ReleaseMeastar();
	m_Stunt.ReleaseStunt();
	m_gamesLevel.ReleaseGamesLevels();
	DeleteDC(m_hdcT);
	DeleteObject(m_hbitmapT);
	DeleteDC(m_hdcTurretType);
	DeleteObject(m_hbitmapTurretType);
	return 0;
}
int TFMapStart::ReadnGMap(int nG)
{
	m_tfmm.LoadTFMap("save.txt", nG);
	m_tfmm.ReadtfMap(m_name, m_guanqia, &m_Map, m_szcmd);
	m_gamesLevel.SetGameLevel(nG,1000,10,m_szcmd,strlen(m_szcmd));
	m_Meastar.SetLujing(m_gamesLevel.GetPointListHead(), m_gamesLevel.GetnPoint());
	//m_gamesLevel.DrawGames();
	m_hdc = CreateCompatibleDC(NULL);
	m_hbitmap = CreateBitmap(4 * m_Map.m_nw +1, 4 * m_Map.m_nh +1, 1, 32, NULL);
	SelectObject(m_hdc, m_hbitmap);
	//m_hdc2 = CreateCompatibleDC(NULL);
	//m_hbitmap2 = CreateBitmap(2000, 1500, 1, 32, NULL);
	//SelectObject(m_hdc2, m_hbitmap2);
	SetBkMode(m_hdc, TRANSPARENT);
	SetBkColor(m_hdc, RGB(255, 255, 255));
	m_tfmm.OutDraw(m_hdc, 0, 0);

//	g_dbutton->Create();


	return 0;
}

int TFMapStart::OnPaint(HDC hdc)
{
	if (m_bStart == false)return 0;

	BitBlt(hdc, m_lefttop.x, m_lefttop.y, m_Map.m_nw * 4 + 1, m_Map.m_nh * 4 + 1, m_hdc, 0, 0, SRCCOPY);
	//Rectangle(hdc, x + m_Map.m_nw * 4, y + m_iselecttype%1000 * 40, x + m_Map.m_nw * 4 + 40, y + m_iselecttype * 40+40);
	
	return 0;
}

int TFMapStart::OnDraw(HDC hdc)
{
	if (m_bStart == false)return 0;
	//static SIZE s = { 300, 100 };
//	BitmapToRect(m_hbitmap,m_hbitmap2,g_sizewindow);

	BitBlt(hdc, m_lefttop.x, m_lefttop.y, m_Map.m_nw * 4 + 1, m_Map.m_nh * 4 + 1, m_hdc, 0, 0, SRCCOPY);
	m_gamesLevel.ShowGames(hdc, m_lefttop.x, m_lefttop.y-80);
	return 0;
}

int TFMapStart::OnLButtonDown(POINTS point)
{
	if (m_bStart == false)return 0;
	m_bLDown = true;
	if (m_Turret.OnButton(point.x - m_lefttop.x, point.y - m_lefttop.y))
	{
		return 1;
	}
	m_Turret.m_PitchOnTurret = NULL;
	if (m_iselecttype >= 0 && m_iselecttype<7&&m_bTurretType)
	{
		m_Turret.PlaceTurret(m_iselecttype, point.x - m_lefttop.x, point.y - m_lefttop.y);
		return 2;
	}
	m_Turret.PitchOnTurret((point.x - m_lefttop.x)*1000, (point.y - m_lefttop.y)*1000);
	
	
	return 0;
}

int TFMapStart::OnLButtonUp(POINTS point)
{
	if (m_bStart == false)return 0;
	m_bLDown = false;
	//m_Turret.m_PitchOnTurret = NULL;
	return 0;
}

int TFMapStart::OnMouseMove(POINTS point)
{
	if (m_bStart == false)return 0;
	m_pointCursor = point;
	if (m__bMouseTrack)     // 若允许 追踪，则。 
	{
//		POINT point;
		//GetClipCursor;
		CURSORINFO po;
		po.flags = 1;
		TRACKMOUSEEVENT csTME;
		csTME.cbSize = sizeof (csTME);
		csTME.dwFlags = TME_LEAVE;
		csTME.hwndTrack = m_hWnd;// 指定要 追踪 的窗口
		::_TrackMouseEvent(&csTME); // 开启 Windows 的 WM_MOUSELEAVE ， WM_MOUSEHOVER 事件支持

		m__bMouseTrack = FALSE;   // 若已经 追踪 ，则停止 追踪
#ifndef _DEBUG
		RECT rect;
		GetWindowRect(m_hWnd, &rect);
		ClipCursor(&rect);
#endif
	}
	::SetClassLong(m_hWnd, GCL_HCURSOR, 0);
	
	//if (m_bLDown)
	//{
	//	if (m_Turret.m_PitchOnTurret)
	//	{
	//		m_Turret.m_PitchOnTurret->pt.x = (point.x - m_lefttop.x)/4*4*1000;
	//		m_Turret.m_PitchOnTurret->pt.y = (point.y - m_lefttop.y)/4*4*1000;
	//	}
	//
	//}
	
	RECT rect = { (point.x - m_lefttop.x - 16) / 4 * 4, (point.y - m_lefttop.y - 16) / 4 * 4,( point.x - m_lefttop.x + 16) / 4 * 4,( point.y - m_lefttop.y + 16) / 4 * 4 };
	//m_b1 = IsTrueRect(&rect);
	//m_b2 = m_Turret.JudgeTurretRect(&rect);
	m_Turret.OnMove(point.x - m_lefttop.x, point.y - m_lefttop.y);
	if (IsTrueRect(&rect) && m_Turret.JudgeTurretRect(&rect))
	{
		m_bTurretType = true;
	}
	else
	{
		m_bTurretType = false;
	}
		
	return 0;
}
int TFMapStart::OnMouseLever()
{
	if (m_bStart == false)return 0;
	m__bMouseTrack = true;
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	return 0;
}
int TFMapStart::OnRButtonDown(POINTS point)
{
	if (m_bStart == false)return 0;
	m_Turret.m_PitchOnTurret = NULL;
	//sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)(y1 - y2));
//	Turret pt;
//	pt.ADO = 20;
////	pt.size = 0x00100010;//16*16.需要乘以4
//	pt.type = rand() % 6;
//	pt.x = (point.x  - m_lefttop.x) / 4 * 4*1000;
//	pt.y = (point.y  - m_lefttop.y) / 4 * 4*1000;
//	for (int i = 0; i < 5; i++)
//	{
//		pt.AttackType[i] = 0;
//	}
//	//memchr(pt.AttackType, 0, 5);
//	pt.AttackType[0] = 11;
//	pt.AttackType[1] = 40;
//	m_Turret.CreateTurretList(&pt);
//	m_Turret.PlaceTurret(m_iselecttype, point.x - m_lefttop.x, point.y - m_lefttop.y);
	m_iselecttype = -1;
	return 0;
}

int TFMapStart::OnRButtonUp(POINTS point)
{
	if (m_bStart == false)return 0;
	return 0;
}

int TFMapStart::OnCommand(int nId)
{
	if (m_bStart == false)return 0;
	m_iselecttype=nId - IDC_BUT_TURRET;
	SelectTurretType(m_iselecttype);
	return 0;
}
//攻击一次，调用绘图
int TFMapStart::ADC(HDC hdc,TurretList* tc, MeastarList*ms)
{
	if (m_bStart == false)return 0;
	int cx1 = 64;//((tc->pt.size & 0xffff0000) >> 16) * 4;
	int cy1 = 64;//(tc->pt.size & 0x0000ffff) * 4;
	int x1=tc->pt.x+cx1/2;
	int y1=tc->pt.y+cy1/2;
	int x2=ms->ms.x + 20;
	int y2=ms->ms.y + 20;
	int l = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
	int ll=(int)sqrt((float)l);

	if (ll<=tc->pt.l)//将子弹添加到子弹链表中
	{
//	int n = 0;
//	while (true)
//	{
//		ms->x += ms->fangxiang.x / ll/ 100 * 1000;
//		ms->y += ms->fangxiang.y / ll/ 100 * 1000;
//	
//	if (ms->x < 0 && ms->fangxiang.x < -20)ms->fangxiang.x = -ms->fangxiang.x;
//	else if (ms->x > 380 * 1000 && ms->fangxiang.x > 0)ms->fangxiang.x = -ms->fangxiang.x;
//	if (ms->y < 0 && ms->fangxiang.y < -20)ms->fangxiang.y = -ms->fangxiang.y;
//	else if (ms->y > 380 * 1000 && ms->fangxiang.y > 0)ms->fangxiang.y = -ms->fangxiang.y;
//	if (ms->fangxiang.x == 0)ms->fangxiang.x = rand();
//	if (ms->fangxiang.y == 0)ms->fangxiang.y = rand();
//
//		Sleep(100);
//	}
	}
	return 0;
}

int TFMapStart::SelectTurretType(int type)
{
	if (m_bStart == false)return 0;
	BitBlt(m_hdcTurretType, 0, 0, 32, 32, HDC_TURRET, type % 10 * 32, type / 10 * 32, SRCCOPY);
	RECT rect = { 0, 0, 32, 32 };
	UCHAR *pby = new UCHAR[32*32 * 4 + 1];
	DWORD dwsize = GetBitmapBits(m_hbitmapTurretType, 32*32 * 4, pby);
	if (dwsize)
	{
		for (int i = 0; i<dwsize/4; i++)
		{
			//if (pby[i] != 0)//被忽略的颜色是RGB(0,0,0)
			{
				pby[4 * i] = pby[4 * i]/2;//蓝
				pby[4 * i + 1] = pby[4 * i + 1]/2;//禄
				if (pby[4 * i + 2]!=0)
					pby[4 * i + 2] = 255 - (255 - pby[4 * i + 2])*0.2;
					//pby[4 * i + 2] = 255;//红
				//pby[4 * i + 3] =255;
			}
		}
		SetBitmapBits(m_hbitmapTurretType, dwsize, pby);
	}
	m_Turret.SelectTurretType(type,m_SelectTurret);
	return 0;
}

int TFMapStart::DrawOther(int DrawOne(TOBasis*, HDC, int, int, int))
{
	if (m_bStart == false)return 0;
	char buffer[256];
	if (m_iselecttype >= 0 && m_iselecttype < 7)
	{
		
		//BitBlt()
		if (m_bTurretType)
			DrawOne(&m_Turret,m_hdc, (m_pointCursor.x - m_lefttop.x - 16) / 4 * 4 * 1000, (m_pointCursor.y - m_lefttop.y - 16) / 4 * 4 * 1000, m_iselecttype + 1000);
		else
			BitBlt(m_hdc, (m_pointCursor.x - m_lefttop.x - 16) / 4 * 4, (m_pointCursor.y - m_lefttop.y - 16) / 4 * 4 , 32, 32, m_hdcTurretType, 0, 0, SRCAND);
			//DrawOne(m_hdc, (m_pointCursor.x - m_lefttop.x - 16) / 4 * 4 * 1000, (m_pointCursor.y - m_lefttop.y - 16) / 4 * 4 * 1000, 32, 32, m_iselecttype + 1000);
	//	m_iselecttype
		RECT rect = { (m_pointCursor.x - m_lefttop.x) / 4 * 4 - m_SelectTurret.l, (m_pointCursor.y - m_lefttop.y) / 4 * 4 - m_SelectTurret.l,
			(m_pointCursor.x - m_lefttop.x) / 4 * 4 + m_SelectTurret.l,( m_pointCursor.y - m_lefttop.y ) / 4 * 4 + m_SelectTurret.l };
		Arc(m_hdc, rect.left, rect.top, rect.right, rect.bottom, 0, 0, 0, 0);

	}

	ShowTop(m_hdc);
	//sprintf(buffer, "%d,%d", m_b1, m_b2);
	//TextOutA(m_hdc, 200, 0, buffer,strlen(buffer));
	return 0;
}

int TFMapStart::IsTrueRect(const LPRECT rect)
{
	//TFtype_KONG
	int tw = rect->left / 4;
	int th = rect->top / 4;
	int w=(rect->right - rect->left)/4;
	int h=(rect->bottom - rect->top) / 4;
	if (rect->left<0 || rect->top<0 || tw + w>m_Map.m_nw || th + h>m_Map.m_nh)
		return false;
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (m_Map.tf[tw + i][th + j] & 0x01)//为真表示遮蔽，不允许放置
			{
				return false;
			}
		}
	}
	return true;
}

//传入显示区大小
int TFMapStart::SetLeftTop(HDC hdcbk,int cx, int cy)
{
	m_lefttop.x = (cx-m_Map.m_nw*4)/2;
	m_lefttop.y = 120;

	//g_dbutton->Create(m_hWnd, g_hinst, x, 0, 64, 32, IDC_BUT_MapMask, NULL, 0, 0, 0, 0, _T("test"), BR_TY_W | BR_TY_TY_1);
	g_dbutton->Create(m_hWnd, g_hinst, m_lefttop.x + 70*0, 0, 64, 32, IDC_BUT_Start, HDC_BUTTON, 0, 96, 20, 20, _T("开始"), BR_TY_TY_1, NULL);
	g_dbutton->Create(m_hWnd, g_hinst, m_lefttop.x + 70 * 1, 0, 64, 32, IDC_BUT_Pause, HDC_BUTTON, 20, 96, 20, 20, _T("暂停"), BR_TY_TY_1, NULL);
	g_dbutton->Create(m_hWnd, g_hinst, m_lefttop.x + 70 * 2, 0, 64, 32, IDC_BUT_Stop, HDC_BUTTON, 40, 96, 20, 20, _T("返回"), BR_TY_TY_1, NULL);
	//g_dbutton->Create(m_hWnd, g_hinst, x + 70*4, 0, 64, 32, IDC_BUT_AddMeastar, HDC_BUTTON, 60, 96, 20, 20, _T("test"), BR_TY_W | BR_TY_TY_1, NULL);
	g_dbutton->Create(m_hWnd, g_hinst, m_lefttop.x + 210 + 38, 0, 32, 32, IDC_BUT_BEILV1, HDC_BUTTON, 40, 96, 20, 20, _T("1"), BR_TY_TY_1, NULL);
	g_dbutton->Create(m_hWnd, g_hinst, m_lefttop.x + 210 + 38 * 2, 0, 32, 32, IDC_BUT_BEILV2, HDC_BUTTON, 40, 96, 20, 20, _T("2"), BR_TY_TY_1, NULL);
	g_dbutton->Create(m_hWnd, g_hinst, m_lefttop.x + 210 + 38 * 3, 0, 32, 32, IDC_BUT_BEILV3, HDC_BUTTON, 40, 96, 20, 20, _T("3"), BR_TY_TY_1, NULL);
	g_dbutton->Create(m_hWnd, g_hinst, m_lefttop.x + 210 + 38 * 4, 0, 32, 32, IDC_BUT_BEILV4, HDC_BUTTON, 40, 96, 20, 20, _T("4"), BR_TY_TY_1, NULL);


	g_dbutton->Create(m_hWnd, g_hinst, 4 * m_Map.m_nw + m_lefttop.x + 1, m_lefttop.y + 40 * 0, 40, 40, IDC_BUT_TURRET + 0, HDC_TURRET, 32 * 0, 0, 32, 32, _T("0"), BR_TYBack, hdcbk);
	g_dbutton->Create(m_hWnd, g_hinst, 4 * m_Map.m_nw + m_lefttop.x + 1, m_lefttop.y + 40 * 1, 40, 40, IDC_BUT_TURRET + 1, HDC_TURRET, 32 * 1, 0, 32, 32, _T("0"), BR_TYBack, hdcbk);
	g_dbutton->Create(m_hWnd, g_hinst, 4 * m_Map.m_nw + m_lefttop.x + 1, m_lefttop.y + 40 * 2, 40, 40, IDC_BUT_TURRET + 2, HDC_TURRET, 32 * 2, 0, 32, 32, _T("0"), BR_TYBack, hdcbk);
	g_dbutton->Create(m_hWnd, g_hinst, 4 * m_Map.m_nw + m_lefttop.x + 1, m_lefttop.y + 40 * 3, 40, 40, IDC_BUT_TURRET + 3, HDC_TURRET, 32 * 3, 0, 32, 32, _T("0"), BR_TYBack, hdcbk);
	g_dbutton->Create(m_hWnd, g_hinst, 4 * m_Map.m_nw + m_lefttop.x + 1, m_lefttop.y + 40 * 4, 40, 40, IDC_BUT_TURRET + 4, HDC_TURRET, 32 * 4, 0, 32, 32, _T("0"), BR_TYBack, hdcbk);
	g_dbutton->Create(m_hWnd, g_hinst, 4 * m_Map.m_nw + m_lefttop.x + 1, m_lefttop.y + 40 * 5, 40, 40, IDC_BUT_TURRET + 5, HDC_TURRET, 32 * 5, 0, 32, 32, _T("0"), BR_TYBack, hdcbk);
	g_dbutton->Create(m_hWnd, g_hinst, 4 * m_Map.m_nw + m_lefttop.x + 1, m_lefttop.y + 40 * 6, 40, 40, IDC_BUT_TURRET + 6, HDC_TURRET, 32 * 6, 0, 32, 32, _T("0"), BR_TYBack, hdcbk);

	return 0;
}

int TFMapStart::ShowTop(HDC hdc)
{
	int x;
	int y;	
	x= (m_Map.m_nw * 4 - 200) / 2;
	y= (m_Map.m_nh * 4 - 60) / 2;
	switch (m_tTop & 0xffff0000)
	{
	case TFMS_SHOW_NULL:
		break;
	case TFMS_SHOW_PAUSE://暂停
	case TFMS_SHOW_WIN:
	case TFMS_SHOW_DIED:
		BitBlt(hdc, x, y, 200, 60, m_hdcT, 0, 0, SRCCOPY);
		m_tTop++;
		break;
	}
	return 0;
}
int TFMapStart::DrawTop(int t)
{
	switch (t&0xffff0000)
	{
	case TFMS_SHOW_NULL:
		m_tTop =NULL;
		break;
	case TFMS_SHOW_PAUSE://暂停
		m_tTop &= 0x00001111;
		m_tTop |= 0x00010000;
		Rectangle(m_hdcT, 0, 0, 200, 60);
		Rectangle(m_hdcT, 10, 5, 180, 50);
		TextOut(m_hdcT, 85, 20, _T("pasue"), 5);
		break;
	case TFMS_SHOW_WIN:
		m_tTop &= 0x00001111;
		m_tTop |= 0x00020000;
		Rectangle(m_hdcT, 0, 0, 200, 60);
		Rectangle(m_hdcT, 10, 5, 180, 50);
		TextOut(m_hdcT, 80, 20, _T("you win"), 7);
		break;
	case TFMS_SHOW_DIED:
		m_tTop &= 0x00001111;
		m_tTop |= 0x00030000;
		Rectangle(m_hdcT, 0, 0, 200, 60);
		Rectangle(m_hdcT, 10, 5, 180, 50);
		TextOut(m_hdcT, 80, 20, _T("you died"), 8);
		break;
	}
	return 0;
}