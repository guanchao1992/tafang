//自定义控件过程
#include "StdAfx.h"
#include "TowerDefense.h"
#include "TFButton.h"
#include "Resource.h"
#include <commctrl.h>
bool bInitem = false;		//是否在控件里面
bool bLbdown = false;		//左键是否为按下

LONG prev_proc;                 //储存按钮先前的回调函数
CDButtonD*g_pDButton = NULL;

bool CDButtonD::InitDButton()
{
	static bool bInit = false;		//只初始化一次
	if (bInit)
	{
		return false;
	}
	g_pDButton = this;
	bInit = true;

	m_hbitmapM = CreateBitmap(200, 200, 1, 1, NULL);
	m_hbitmap1 = CreateBitmap(200, 200, 1, 32, NULL);
	m_hbitmap2 = CreateBitmap(200, 200, 1, 32, NULL);
	m_hdcM = CreateCompatibleDC(NULL);
	m_hdc1 = CreateCompatibleDC(NULL);
	m_hdc2 = CreateCompatibleDC(NULL);
	SelectObject(m_hdcM, m_hbitmapM);
	SelectObject(m_hdc1, m_hbitmap1);
	SelectObject(m_hdc2, m_hbitmap2);
//	HDC hdc = GetDC(NULL);
//	HBIT_BUTTON = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BUTTON));
	HBIT_MOVE1 = CreateBitmap(64, 64, 1, 32, NULL);// CreateCompatibleBitmap(NULL, 64, 32);//0,0,69,30
	HBIT_DOWN1 = CreateBitmap(64, 64, 1, 32, NULL);//CreateCompatibleBitmap(NULL, 64, 32);
	HBIT_Default1 = CreateBitmap(64, 64, 1, 32, NULL);//CreateCompatibleBitmap(NULL, 64, 32);
	

	HBIT_MOVE2 = CreateBitmap(64, 64, 1, 32, NULL);//CreateCompatibleBitmap(NULL, 64, 32);//0,0,69,30
	HBIT_DOWN2 = CreateBitmap(64, 64, 1, 32, NULL);//CreateCompatibleBitmap(NULL, 64, 32);
	HBIT_Default2 = CreateBitmap(64, 64, 1, 32, NULL);//CreateCompatibleBitmap(NULL, 64, 32);

	HBIT_MOVE3 = CreateBitmap(64, 64, 1, 32, NULL);//CreateCompatibleBitmap(NULL, 64, 32);//0,0,69,30
	HBIT_DOWN3 = CreateBitmap(64, 64, 1, 32, NULL);//CreateCompatibleBitmap(NULL, 64, 32);
	HBIT_Default3 = CreateBitmap(64, 64, 1, 32, NULL);//CreateCompatibleBitmap(NULL, 64, 32);

	HDC hdcMOVE1 = CreateCompatibleDC(NULL);
	HDC hdcDOWN1 = CreateCompatibleDC(NULL);
	HDC hdcDefault1 = CreateCompatibleDC(NULL);
	HDC hdcMOVE2 = CreateCompatibleDC(NULL);
	HDC hdcDOWN2 = CreateCompatibleDC(NULL);
	HDC hdcDefault2 = CreateCompatibleDC(NULL);
	HDC hdcMOVE3 = CreateCompatibleDC(NULL);
	HDC hdcDOWN3 = CreateCompatibleDC(NULL);
	HDC hdcDefault3 = CreateCompatibleDC(NULL);

	SelectObject(hdcMOVE1, HBIT_MOVE1);
	SelectObject(hdcDOWN1, HBIT_DOWN1);
	SelectObject(hdcDefault1, HBIT_Default1);
	SelectObject(hdcMOVE2, HBIT_MOVE2);
	SelectObject(hdcDOWN2, HBIT_DOWN2);
	SelectObject(hdcDefault2, HBIT_Default2);
	SelectObject(hdcMOVE3, HBIT_MOVE3);
	SelectObject(hdcDOWN3, HBIT_DOWN3);
	SelectObject(hdcDefault3, HBIT_Default3);

	BitBlt(hdcDefault1, 0, 0, 64, 32, HDC_BUTTON, 0, 0, SRCCOPY);
	BitBlt(hdcMOVE1, 0, 0, 64, 32, HDC_BUTTON, 0, 32, SRCCOPY);
	BitBlt(hdcDOWN1, 0, 0, 64, 32, HDC_BUTTON, 0, 64, SRCCOPY);

	BitBlt(hdcDefault2, 0, 0, 64, 32, HDC_BUTTON, 64, 0, SRCCOPY);
	BitBlt(hdcMOVE2, 0, 0, 64, 32, HDC_BUTTON, 64, 32, SRCCOPY);
	BitBlt(hdcDOWN2, 0, 0, 64, 32, HDC_BUTTON, 64, 64, SRCCOPY);

	BitBlt(hdcDefault3, 0, 0, 40, 40, HDC_BUTTON, 128, 0, SRCCOPY);
	BitBlt(hdcMOVE3, 0, 0, 40, 40, HDC_BUTTON, 168, 0, SRCCOPY);
	BitBlt(hdcDOWN3, 0, 0, 40, 40, HDC_BUTTON, 208, 0, SRCCOPY);


	DeleteDC(hdcMOVE1);
	DeleteDC(hdcDOWN1);
	DeleteDC(hdcDefault1);
	DeleteDC(hdcMOVE2);
	DeleteDC(hdcDOWN2);
	DeleteDC(hdcDefault2);
	DeleteDC(hdcMOVE3);
	DeleteDC(hdcDOWN3);
	DeleteDC(hdcDefault3);

	// 	g_ctlp=new CTooltip();
	// 	g_ctlp->InitTooltip(hInstance);
	return true;
}
void CDButtonD::Delete(HWND hprent, int nID)
{
	while (m_bbuttond)
	{
		Sleep(100);
	}
	m_bbuttond = true;
	list<DBUTTOND>::iterator pbut;
	for (pbut = m_Dbutond.begin(); pbut != m_Dbutond.end(); pbut++)
	{
		if (pbut->hprent == hprent&&pbut->nID==nID)
		{
			if (pbut->hbitmap != NULL)
			{
				DeleteObject(pbut->hbitmap);
			}
			if (pbut->hbitmap1 != NULL)
			{
				DeleteObject(pbut->hbitmap1);
			}
			if (pbut->hbitmap2 != NULL)
			{
				DeleteObject(pbut->hbitmap2);
			}
			pbut->hbitmap = NULL;
			pbut->hbitmap1 = NULL;
			pbut->hbitmap2 = NULL;
			DestroyWindow(pbut->hdbut);
			if (pbut == m_Dbutond.begin())
			{
				m_Dbutond.erase(pbut);
				pbut = m_Dbutond.begin();
			}
			else
			{
				m_Dbutond.erase(pbut--);
			}
			break;
		}
	}
	m_bbuttond = false;

}
void CDButtonD::Delete(HWND hprent)
{
	while (m_bbuttond)
	{
		Sleep(100);
	}
	m_bbuttond = true;
	list<DBUTTOND>::iterator pbut= m_Dbutond.begin();

	while (pbut != m_Dbutond.end())
	{
		if (pbut->hprent == hprent)
		{
			if (pbut->hbitmap != NULL)
			{
				DeleteObject(pbut->hbitmap);
			}
			if (pbut->hbitmap1 != NULL)
			{
				DeleteObject(pbut->hbitmap1);
			}
			if (pbut->hbitmap2 != NULL)
			{
				DeleteObject(pbut->hbitmap2);
			}
			pbut->hbitmap = NULL;
			pbut->hbitmap1 = NULL;
			pbut->hbitmap2 = NULL;
			DestroyWindow(pbut->hdbut);
			m_Dbutond.erase(pbut);
			pbut = m_Dbutond.begin();
		}
		else
		{
			pbut++;
		}
	}
	m_bbuttond = false;

}
HWND CDButtonD::Create(HWND hprent, HINSTANCE hInstance, int x, int y, int cx, int cy, INT nID, HDC hdcButton, int rx, int ry, int rcx, int rcy, TCHAR*text, int nBackType, HDC backdc)
{
	//在这里判断，是否已经存在了该项。
	bLbdown = false;
	bInitem = false;
	bool bcunzai = false;
	HWND hw = NULL;
	RECT rect = { 0, 0, cx, cy };
	DBUTTOND bufbut;
	while (m_bbuttond)
	{
		Sleep(100);
	}
	m_bbuttond = true;
	list<DBUTTOND>::iterator pbut;
	for (pbut = m_Dbutond.begin(); pbut != m_Dbutond.end(); pbut++)
	{
		if (pbut->hprent == hprent&&pbut->nID == nID)
		{
			bufbut = *pbut;
			hw = pbut->hdbut;
			bcunzai = true;
			//如果该项已存在，则替换掉原来的
			if (pbut->hbitmap != NULL)
			{
				DeleteObject(pbut->hbitmap);
			}
			if (pbut->hbitmap1 != NULL)
			{
				DeleteObject(pbut->hbitmap1);
			}
			if (pbut->hbitmap2 != NULL)
			{
				DeleteObject(pbut->hbitmap2);
			}
			pbut->hbitmap = NULL;
			pbut->hbitmap1 = NULL;
			pbut->hbitmap2 = NULL;
			m_Dbutond.erase(pbut);
			break;
		}
	}
	m_bbuttond = false;
	if (bcunzai == false)
	{
		hw = CreateWindowEx(WS_EX_NOACTIVATE, _T("DButton"), text,
			WS_CHILD | WS_VISIBLE,
			x, y, cx, cy, hprent, (HMENU)nID, g_hinst, NULL);

	}
	else
	{
		SetWindowText(hw, text);
		MoveWindow(hw, x, y, cx, cy, false);
	}
	bufbut.hdbut = hw;
	bufbut.hprent = hprent;
	bufbut.nID = nID;
	bufbut.nBackType = nBackType;
	bufbut.nWidth = cx;
	bufbut.nHeight = cy;
	bufbut.nw = rcx;
	bufbut.nh = rcy;
	if (bufbut.hbitmap1 != NULL)
	{
		DeleteObject(bufbut.hbitmap1);
	}
	if (bufbut.hbitmap2 != NULL)
	{
		DeleteObject(bufbut.hbitmap2);
	}
	if (bufbut.hbitmap != NULL)
	{
		DeleteObject(bufbut.hbitmap);
	}
	if (!(nBackType&BR_TYFMin)&&!(nBackType&BR_TYFMax))
	{
		HRGN hrgn = CreateRectRgn(0, 0, cx, cy);
		SetWindowRgn(hw, hrgn, true);
		DeleteObject(hrgn);
	}
	else if ((nBackType&BR_TYFMin) && !(nBackType&BR_TYFMax))
	{
		HRGN hrgn = CreateRoundRectRgn(0, 0, cx, cy, 2, 2);
		SetWindowRgn(hw, hrgn, true);
		DeleteObject(hrgn);
	}
	else if (!(nBackType&BR_TYFMin) && (nBackType&BR_TYFMax))
	{
		HRGN hrgn = CreateRoundRectRgn(0, 0, cx, cy, 4, 4);
		SetWindowRgn(hw, hrgn, true);
		DeleteObject(hrgn);
	}
	else if ((nBackType&BR_TYFMin) && (nBackType&BR_TYFMax))
	{
		HRGN hrgn = CreateRoundRectRgn(0, 0, cx, cy, 8, 8);
		SetWindowRgn(hw, hrgn, true);
		DeleteObject(hrgn);
	}
	//每次都会创建一个位图，并保存下来
	//DBUTTOND dbd;

	//bufbut.hbitmap保存hdcButton传过来的图像
	//BitBlt(m_hdcM, 0, 0, 40, 40, backdc, 0, 0, SRCCOPY);
	//BitBlt(m_hdc1, 0, 0, 40, 40, m_hdcM, 0, 0, NOTSRCCOPY);
	//BitBlt(m_hdc1, 0, 0, 40, 40, backdc, 0, 0, SRCAND);//dc1是前景
	//
	//BitBlt(m_hdc2, 0, 0, 40, 40, m_hdcM, 0, 0, SRCCOPY);
	//BitBlt(m_hdc2, 0, 0, 40, 40, backdc, x / 1000, y / 1000, SRCAND);//dc2是背景
	//
	//BitBlt(hdcButton, 0, 0, 40, 40, m_hdc1, 0, 0, SRCCOPY);
	//BitBlt(hdcButton, 0, 0, 40, 40, m_hdc2, 0, 0, SRCPAINT);

	bufbut.hbitmap = CreateBitmap(cx, cy, 1, 32, NULL);
	DrawD(bufbut.hdbut, bufbut.hbitmap, 0, 0, cx, cy, hdcButton, rx, ry, rcx, rcy, backdc, x, y, cx, cy, nBackType, 0);

	bufbut.hbitmap1 = CreateBitmap(cx, cy, 1, 32, NULL);
	DrawD(bufbut.hdbut, bufbut.hbitmap1, 0, 0, cx, cy, hdcButton, rx, ry, rcx, rcy, backdc, x, y, cx, cy, nBackType, 1);

	bufbut.hbitmap2 = CreateBitmap(cx, cy, 1, 32, NULL);
	DrawD(bufbut.hdbut, bufbut.hbitmap2, 0, 0, cx, cy, hdcButton, rx, ry, rcx, rcy, backdc, x, y, cx, cy, nBackType, 2);

	m_Dbutond.push_back(bufbut);
	InvalidateRect(hw, &rect, true);
	return hw;
}
//对话框图标句柄

LRESULT CALLBACK ButtWindProc(
	HWND hWnd,                            //window handle                   
	UINT message,                         // type of message                 
	WPARAM wParam,                        // additional information          
	LPARAM lParam)                        //additional information          
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_LBUTTONDBLCLK:
		PostMessage(hWnd, WM_LBUTTONDOWN, wParam, lParam);
		break;
	case WM_DESTROY:
		bLbdown = false;
		bInitem = false;
		break;
	}
	//将不做处理的消息路由给原默认函数
	return CallWindowProc((WNDPROC)prev_proc, hWnd, message, wParam, lParam);
}

static bool _bMouseTrack = true;
LRESULT CALLBACK CustomButtonWndProc(HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	int wmId, wmEvent;
	//	TCHAR szText[40];
	//	HBRUSH hBrush;
	HDC hdc;
	PAINTSTRUCT ps;
	//	RECT rect;

	switch (uMsg)
	{
	case WM_CREATE:
		bLbdown = false;
		bInitem = false;
		prev_proc = SetWindowLongPtr(GetDlgItem(hwndDlg, MAKEWORD(::GetWindowLong(hwndDlg, GWL_ID), 0)), GWLP_WNDPROC, (LONG)ButtWindProc);
		return 0;
	case WM_PAINT:
		// 		::GetClientRect(hwndDlg,&rect);
		// 		::GetWindowText(hwndDlg,szText,sizeof(szText));
		hdc = ::BeginPaint(hwndDlg, &ps);
		g_pDButton->OnDrawDButton(hwndDlg, hdc, bInitem, bLbdown);
		EndPaint(hwndDlg, &ps);
		// 		hBrush = ::CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
		// 		hBrush = (HBRUSH)::SelectObject(hdc,hBrush);
		// 		::SetBkColor(hdc,GetSysColor(COLOR_BTNFACE));//设置背景颜色
		// 		::SetTextColor(hdc,GetSysColor(COLOR_WINDOWTEXT));//设置文本颜色
		// 
		// 		::Rectangle(hdc,rect.left,rect.top,rect.right,rect.bottom);//着色
		// 		::DrawText(hdc,szText,-1,&rect,
		// 			DT_SINGLELINE|DT_CENTER|DT_VCENTER);//又收获一个财富

		//		::DeleteObject(::SelectObject(hdc,hBrush));
		return 0;
	case WM_RBUTTONDOWN:
		SetFocus(hwndDlg);
		//SendMessage(hwndDlg,WM_SETFOCUS,0,0);
		// GetDlgItem(控件的ID（如IDC_BUTTON1）)->EnableWindow
		//EnableWindow(hwndDlg,false);
		return 0;
	case WM_RBUTTONUP:
		return 0;
	case WM_LBUTTONDOWN:
		SetFocus(GetParent(hwndDlg));
		//SendMessage(GetParent(hwndDlg),WM_SETFOCUS,0,0);
		g_pDButton->m_hLDown = hwndDlg;
		if (bLbdown == false)
		{
			bLbdown = true;
			hdc = GetDC(hwndDlg);
			g_pDButton->OnDrawDButton(hwndDlg, hdc, bInitem, bLbdown);
			ReleaseDC(hwndDlg, hdc);
		}
		return 0;
	case WM_LBUTTONUP:
		//Click
		lParam;
		wParam;
		if (bLbdown == true)
		{
			bLbdown = false;
			//bInitem = false;
			::SendMessage(GetParent(hwndDlg), WM_COMMAND, GetWindowLong(hwndDlg, GWL_ID), (LPARAM)hwndDlg);
		}
		hdc = GetDC(hwndDlg);
		g_pDButton->OnDrawDButton(hwndDlg, hdc, bInitem, bLbdown);
		ReleaseDC(hwndDlg, hdc);
		return 0;
	case WM_MOUSEMOVE:
		if (_bMouseTrack)     // 若允许 追踪，则。 
		{
			TRACKMOUSEEVENT csTME;
			csTME.cbSize = sizeof (csTME);
			csTME.dwFlags = TME_LEAVE;
			csTME.hwndTrack = hwndDlg;// 指定要 追踪 的窗口
			::_TrackMouseEvent(&csTME); // 开启 Windows 的 WM_MOUSELEAVE ， WM_MOUSEHOVER 事件支持

			_bMouseTrack = FALSE;   // 若已经 追踪 ，则停止 追踪 
		}
		g_pDButton->m_hInitem = hwndDlg;
		if (bInitem == false)
		{
			bInitem = true;
			hdc = GetDC(hwndDlg);
			g_pDButton->OnDrawDButton(hwndDlg, hdc, bInitem, bLbdown);
			ReleaseDC(hwndDlg, hdc);
		}
		::SetClassLong(hwndDlg, GCL_HCURSOR, 0);
		//SetCursor(::LoadCursor(odInst,MAKEINTRESOURCE(IDC_CURSOR)));
		SetCursor(LoadCursor(NULL, IDC_HAND));

		return 0;
	case WM_MOUSELEAVE:
		bLbdown = false;
		if (bInitem == true)
		{
			bInitem = false;
			hdc = GetDC(hwndDlg);
			g_pDButton->OnDrawDButton(hwndDlg, hdc, bInitem, bLbdown);
			ReleaseDC(hwndDlg, hdc);
		}
		_bMouseTrack = true;
		SetCursor(LoadCursor(NULL, IDC_ARROW));

		return 0;
	case WM_SHOWText:

		if (wParam == WM_SHOWText)
		{
			TCHAR *pbuf = (TCHAR*)lParam;
			//_bMouseTrack=true;
			POINT point;
			GetCursorPos(&point);
			delete pbuf;
		}

		break;
	case WM_SETFOCUS:
		SetFocus(GetParent(hwndDlg));
		//SendMessage(GetParent(hwndDlg),WM_SETFOCUS,0,0);
		break;
	case WM_DESTROY:
		//删除该项
		_bMouseTrack = true;
		bLbdown = false;
		bInitem = false;
		break;
		while (g_pDButton->m_bbuttond)
		{
			Sleep(100);
		}
		g_pDButton->m_bbuttond = true;
		list<DBUTTOND>::iterator pdbut;
		for (pdbut = g_pDButton->m_Dbutond.begin(); pdbut != g_pDButton->m_Dbutond.end(); pdbut++)
		{
			if (pdbut->hdbut == hwndDlg)
			{
				if (pdbut->hbitmap != NULL)
				{
					DeleteObject(pdbut->hbitmap);
				}
				if (pdbut->hbitmap1 != NULL)
				{
					DeleteObject(pdbut->hbitmap1);
				}
				if (pdbut->hbitmap2 != NULL)
				{
					DeleteObject(pdbut->hbitmap2);
				}
				g_pDButton->m_Dbutond.erase(pdbut--);

			}
		}
		g_pDButton->m_bbuttond = false;

		return 0;
	}
	return ::DefWindowProc(hwndDlg, uMsg, wParam, lParam);
}

void CDButtonD::OnReDraw(HWND hprent, HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	OnDrawDButton(hwnd, hdc, bInitem, bLbdown);
	ReleaseDC(hwnd, hdc);
}
void CDButtonD::OnDrawDButton(HWND hwnd, HDC hdc, bool bInitem, bool bLbdown)
{
	HDC dc1 = CreateCompatibleDC(hdc);
	while (m_bbuttond)
	{
		Sleep(100);
	}
	m_bbuttond = true;
	list<DBUTTOND>::iterator pdbut;
	for (pdbut = m_Dbutond.begin(); pdbut != m_Dbutond.end(); pdbut++)
	{
		if (pdbut->hdbut == hwnd)
		{
			if (pdbut->bSel == true)
			{
				SelectObject(dc1, pdbut->hbitmap1);
			}
			else
			{
				if (m_hInitem == hwnd&&bInitem == true)
				{
					if (m_hLDown == hwnd&&bLbdown == true)
						SelectObject(dc1, pdbut->hbitmap1);
					else
						SelectObject(dc1, pdbut->hbitmap2);
				}
				else
				{
					SelectObject(dc1, pdbut->hbitmap);
				}
			}
			BitBlt(hdc, 0, 0, pdbut->nWidth, pdbut->nHeight, dc1, 0, 0, SRCCOPY);
			//以下都是需要显示字的
		}
	}
	DeleteDC(dc1);
	m_bbuttond = false;
}

CDButtonD::CDButtonD()
{ 
	HBITMAP HBIT_MOVE1 = NULL;
	HBITMAP HBIT_DOWN1 = NULL;
	HBITMAP HBIT_Default1 = NULL;
	HBITMAP HBIT_BUTTON = NULL;
	m_bbuttond = false;
	m_hInitem = NULL;
	m_hLDown = NULL;
	m_hFont = CreateFont(14, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		1, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("宋体")); // lpszFac
	m_hFont1 = CreateFont(14, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		2, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("宋体")); // lpszFac
}

CDButtonD::~CDButtonD()
{
	DeleteObject(m_hbitmapM);
	DeleteObject(m_hbitmap1);
	DeleteObject(m_hbitmap2);
	DeleteDC(m_hdcM);
	DeleteDC(m_hdc1);
	DeleteDC(m_hdc2);
}
void CDButtonD::OnPaint()
{

}
void CDButtonD::OnLButtonDown()
{

}
void CDButtonD::OnLButtonUp()
{

}
void CDButtonD::OnMouseMove()
{

}

int CDButtonD::DrawD(HWND hwnd, HBITMAP hbitmap, int x, int y, int cx, int cy, HDC hdctop, int x1, int y1, int cx1, int cy1, HDC hdcbom, int x2, int y2, int cx2, int cy2, int type, int ng)
{	
	HDC hdcout = CreateCompatibleDC(NULL);
	SelectObject(hdcout, hbitmap);
	HDC hdcbit = CreateCompatibleDC(NULL);
	HDC hdc = CreateCompatibleDC(NULL);
	HDC dc1 = CreateCompatibleDC(hdcout);
	HDC dc2 = CreateCompatibleDC(hdcout);
	HDC dc3 = CreateCompatibleDC(hdcout);
	HDC dcM = CreateCompatibleDC(hdcout);
	HBITMAP hbitbutton = CreateBitmap(cx, cy, 1, 32, NULL);
	HBITMAP bit2 = CreateCompatibleBitmap(hdcout, cx, cy);
	HBITMAP bit3 = CreateCompatibleBitmap(hdcout, cx, cy);
	HBITMAP bit1 = CreateCompatibleBitmap(hdcout, cx, cy);
	HBITMAP bitM = CreateBitmap(cx, cy, 1, 1, NULL);

	SelectObject(hdc, hbitbutton);
	SelectObject(dcM, bitM);
	SelectObject(dc1, bit1);
	SelectObject(dc2, bit2);
	SelectObject(dc3, bit3);
	RECT rect = { 0, 0, cx, cy };
	if (hdctop != NULL)
	{
		//SetBkColor(hdctop, RGB(255, 255, 255));
		BitBlt(dcM, (cx - cx1) / 2, (cy - cy1) / 2, cx1, cy1, hdctop, x1, y1, NOTSRCERASE);
	}
	if (BR_TYBack&type)//透明背景
	{
		SetBkMode(dc1, TRANSPARENT);
		Rectangle(dc1, -1, -1, cx+2, cy+2);

		//FillRect(dc1,&rect,g_hbackbrush);
		if (hdcbom != NULL)
			BitBlt(dc1, 0, 0, cx, cy, hdcbom, x2, y2, SRCCOPY);
	}
	//else
	//{
		if ((BR_TY_TY_1&type) && !(BR_TY_TY_2&type) && !(BR_TY_TY_3&type))
		{
			if (ng == 1)
				SelectObject(hdcbit, HBIT_DOWN1);
			else if (ng == 2)
				SelectObject(hdcbit, HBIT_MOVE1);
			else if (ng == 0)
				SelectObject(hdcbit, HBIT_Default1);
		}
		else if (!(BR_TY_TY_1&type) && (BR_TY_TY_2&type) && !(BR_TY_TY_3&type))
		{
			if (ng == 1)
				SelectObject(hdcbit, HBIT_DOWN2);
			else if (ng == 2)
				SelectObject(hdcbit, HBIT_MOVE2);
			else if (ng == 0)
				SelectObject(hdcbit, HBIT_Default2);
		}
		else if ((BR_TY_TY_1&type) && (BR_TY_TY_2&type) && !(BR_TY_TY_3&type))
		{
			if (ng == 1)
				SelectObject(hdcbit, HBIT_DOWN3);
			else if (ng == 2)
				SelectObject(hdcbit, HBIT_MOVE3);
			else if (ng == 0)
				SelectObject(hdcbit, HBIT_Default3);
		}
		//	cxim.Resample(cx, cy);
		//	cxim.Draw(dc1, 0, 0, cx, cy);
		BitBlt(dc1, 0, 0, cx, cy, hdcbit, 0, 0, SRCCOPY);
		

//	}
	{
		BitBlt(dc2, 0, 0, cx, cy, dcM, 0, 0, SRCCOPY);
		SetBkColor(dcM, RGB(255, 255, 255));

		//消除底色贴图
		BitBlt(dc3, 0, 0, cx, cy, dcM, 0, 0, NOTSRCERASE);
		if (hdctop != NULL)
		{
			BitBlt(dc2, (cx - cx1) / 2, (cy - cy1) / 2, cx1, cy1, hdctop, x1, y1, SRCAND);
		}
		BitBlt(dc3, 0, 0, cx, cy, dc1, 0, 0, SRCAND);

		//去除背景的中的白色
		if (hdcbom != NULL)
		{ 
			BitBlt(m_hdcM, 0, 0, cx, cx, dc3, 0, 0, SRCCOPY);
			BitBlt(m_hdc1, 0, 0, cx, cx, m_hdcM, 0, 0, NOTSRCCOPY);
			BitBlt(m_hdc1, 0, 0, cx, cx, dc3, 0, 0, SRCAND);//dc1是前景
		
			BitBlt(m_hdc2, 0, 0, cx, cx, m_hdcM, 0, 0, SRCCOPY);
			BitBlt(m_hdc2, 0, 0, cx, cx, hdcbom,x2,y2, SRCAND);//dc2是背景
		
			BitBlt(hdcout, 0, 0, cx, cx, m_hdc1, 0, 0, SRCCOPY);
			BitBlt(hdcout, 0, 0, cx, cx, m_hdc2, 0, 0, SRCPAINT);
		}
		else 
			BitBlt(hdcout, 0, 0, cx, cy, dc3, 0, 0, SRCCOPY);

		
		//if ((BR_TYBack&type) && hdctop)
		//{
		//
		//}
		//else 
		if (BR_TYBack&type)
		{
			//实现透明背景贴图的颜色深浅变化

			RECT rect = { 0, 0, cx, cy };
			UCHAR *pby = new UCHAR[cx*cy * 4 + 1];
			DWORD dwsize = 0;
			if (ng == 1)
			{
				dwsize = GetBitmapBits(hbitmap, cx*cy * 4, pby);
				if (dwsize)
				{
					for (int i = 0; i<dwsize; i++)
					{
						if (pby[i] != 0)//被忽略的颜色是RGB(0,0,0)
						{
							pby[i] = 255 - (255 - pby[i])*0.6;
						}
					}
					SetBitmapBits(hbitmap, dwsize, pby);
				}
			}
			else if (ng == 2)
			{
				dwsize = GetBitmapBits(hbitmap, cx*cy * 4, pby);
				if (dwsize)
				{
					for (int i = 0; i<dwsize; i++)
					{
						if (pby[i] != 0)//被忽略的颜色是RGB(0,0,0)
						{
							pby[i] = 255 - (255 - pby[i])*0.8;
						}
					}
					SetBitmapBits(hbitmap, dwsize, pby);
				}
			}
			delete pby;
		}
		BitBlt(hdcout, 0, 0, cx, cy, dc2, 0, 0, SRCPAINT);
		SetBkMode(hdcout, TRANSPARENT);

		if (type&BR_TY_W)
		{
			TCHAR strbuffer[256];
			GetWindowText(hwnd, strbuffer, 256);
			SIZE sss;
			int ncpy = 1;
			int tlen = 0;
			int ni = 0;
			int tempi = 0;
			int height = 0;
			int len = lstrlen(strbuffer);

			TCHAR szshow[50];
			for (int i = 0; i <= len; i++)
			{
				if (strbuffer[i] == '\n' || strbuffer[i] == NULL)
				{
					SelectObject(hdcout, m_hFont1);
					SetTextColor(hdcout, RGB(50, 145, 150));
					SetBkMode(hdcout, TRANSPARENT);
					tempi = 0;
					strbuffer[i] = NULL;
					GetTextExtentExPoint(hdcout, &strbuffer[ni], i - ni, cx, &tlen, NULL, &sss);
					tempi += tlen;
					ncpy++;
					while (tempi<i - ni)
					{
						GetTextExtentExPoint(hdcout, &strbuffer[ni + tempi], i - ni, cx, &tlen, NULL, NULL);
						tempi += tlen;
						ncpy++;
					}
					ni = i + 1;
				}
			}
			if (1)
			{
				if (ncpy == 1)
				{
					GetTextExtentExPoint(hdcout, strbuffer, len, 300, NULL, NULL, &sss);
					tlen = sss.cx;
				}
				else
				{
					GetTextExtentExPoint(hdcout, &strbuffer[ni], lstrlen(&strbuffer[ni]), 300, NULL, NULL, &sss);
					if (tlen<sss.cx)
					{
						tlen = sss.cx;
					}
				}
				SelectObject(hdcout, m_hFont);
				SetTextColor(hdcout, RGB(250, 245, 250));
				GetTextExtentExPoint(hdcout, strbuffer, lstrlen(strbuffer), 300, NULL, NULL, &sss);
				TextOut(hdcout, (cx - sss.cx) / 2, (cy - sss.cy) / 2, strbuffer, lstrlen(strbuffer));
			}
		}
	}
	DeleteObject(hbitbutton);
	DeleteObject(bit2);
	DeleteObject(bit3);
	DeleteObject(bit1);
	DeleteObject(bitM);
	DeleteDC(hdcbit);
	DeleteDC(hdc);
	DeleteDC(hdcout);
	DeleteDC(dc1);
	DeleteDC(dc2);
	DeleteDC(dc3);
	DeleteDC(dcM);
	return 0;
}

int CDButtonD::SetDraw(HWND hdu, bool bdraw)
{
	HWND hbut = NULL;
	HDC hdc=NULL;
	bool bInitem = false;
	bool bLbdown = false;
	while (m_bbuttond)
	{
		Sleep(100);
	}
	m_bbuttond = true;
	list<DBUTTOND>::iterator pdbut;
	for (pdbut = m_Dbutond.begin(); pdbut != m_Dbutond.end(); pdbut++)
	{
		if (pdbut->hdbut == hdu)
		{
			pdbut->bSel = bdraw;
			hbut = pdbut->hdbut;
			bInitem = pdbut->bInitem;
			bLbdown = pdbut->bLbdown;
			break;
		}
	}
	m_bbuttond = false;	
	hdc = GetDC(hbut);
	OnDrawDButton(hbut, hdc, bInitem, bLbdown);
	ReleaseDC(hbut, hdc);
	return 0;
}
