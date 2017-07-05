//自定义控件过程
#include "StdAfx.h"
#include "DButton.h"
#include "Resource.h"
//#include <commctrl.h>
#include <ximage.h>
//#include <wingdi.h>
//#include <graphics.h>		// 这样引用 EasyX 图形库
//#include <conio.h>
//#include <winuser.h>

bool bInitem=false;		//是否在控件里面
bool bLbdown=false;		//左键是否为按下
bool _bMouseTrack=true;	//追踪鼠标
bool bInit=false;		//只初始化一次

HINSTANCE odInst = NULL;  //接收程序实例的句柄
HICON hOwnerDrawIcon = NULL;  //用作自绘按钮的图标
LONG prev_proc;                 //储存按钮先前的回调函数
HICON hIcon = NULL;     

CDButtonD*g_pDButton=NULL;
bool CDButtonD::InitDButton(HINSTANCE hInstance)
{
	if (bInit)
	{
		return false;
	}
	g_pDButton=this;
	bInit=true;
	odInst=hInstance;

	HDC hdc=GetDC(NULL);
	HBIT_BUTTON		=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BUTTON));
	HBIT_MOVE1		=CreateCompatibleBitmap(hdc,64,32);//0,0,69,30
	HBIT_DOWN1		=CreateCompatibleBitmap(hdc,64,32);
	HBIT_Default1	=CreateCompatibleBitmap(hdc,64,32);
												   
	HBIT_MOVE2		=CreateCompatibleBitmap(hdc,64,32);//0,0,69,30
	HBIT_DOWN2		=CreateCompatibleBitmap(hdc,64,32);
	HBIT_Default2	=CreateCompatibleBitmap(hdc,64,32);
												   
	HBIT_MOVE3		=CreateCompatibleBitmap(hdc,64,32);//0,0,69,30
	HBIT_DOWN3		=CreateCompatibleBitmap(hdc,64,32);
	HBIT_Default3	=CreateCompatibleBitmap(hdc,64,32);

	HDC hdcBUTTON	=CreateCompatibleDC(hdc);
	HDC hdcMOVE1	=CreateCompatibleDC(hdc);
	HDC hdcDOWN1	=CreateCompatibleDC(hdc);
	HDC hdcDefault1	=CreateCompatibleDC(hdc);
	HDC hdcMOVE2	=CreateCompatibleDC(hdc);
	HDC hdcDOWN2	=CreateCompatibleDC(hdc);
	HDC hdcDefault2	=CreateCompatibleDC(hdc);
	HDC hdcMOVE3	=CreateCompatibleDC(hdc);
	HDC hdcDOWN3	=CreateCompatibleDC(hdc);
	HDC hdcDefault3	=CreateCompatibleDC(hdc);
	SelectObject(hdcBUTTON, HBIT_BUTTON);
	SelectObject(hdcMOVE1, HBIT_MOVE1);
	SelectObject(hdcDOWN1, HBIT_DOWN1);
	SelectObject(hdcDefault1, HBIT_Default1);
	SelectObject(hdcMOVE2, HBIT_MOVE2);
	SelectObject(hdcDOWN2, HBIT_DOWN2);
	SelectObject(hdcDefault2, HBIT_Default2);
	SelectObject(hdcMOVE3, HBIT_MOVE3);
	SelectObject(hdcDOWN3, HBIT_DOWN3);
	SelectObject(hdcDefault3, HBIT_Default3);

	BitBlt(hdcDefault1, 0, 0, 64, 32, hdcBUTTON, 0, 0, SRCCOPY);
	BitBlt(hdcMOVE1, 0, 0, 64, 32, hdcBUTTON, 0, 32, SRCCOPY);
	BitBlt(hdcDOWN1, 0, 0, 64, 32, hdcBUTTON, 0, 64, SRCCOPY);

	BitBlt(hdcDefault2, 0, 0, 64, 32, hdcBUTTON, 64, 0, SRCCOPY);
	BitBlt(hdcMOVE2, 0, 0, 64, 32, hdcBUTTON, 64, 32, SRCCOPY);
	BitBlt(hdcDOWN2, 0, 0, 64, 32, hdcBUTTON, 64, 64, SRCCOPY);

	BitBlt(hdcDefault3, 0, 0, 64, 32, hdcBUTTON, 64, 0, SRCCOPY);
	BitBlt(hdcMOVE3, 0, 0, 64, 32, hdcBUTTON, 64, 32, SRCCOPY);
	BitBlt(hdcDOWN3, 0, 0, 64, 32, hdcBUTTON, 64, 64, SRCCOPY);

	DeleteDC( hdcBUTTON	);
	DeleteDC( hdcMOVE1	);
	DeleteDC( hdcDOWN1	);
	DeleteDC( hdcDefault1);
	DeleteDC( hdcMOVE2	);
	DeleteDC( hdcDOWN2	);
	DeleteDC( hdcDefault2);	
	DeleteDC( hdcMOVE3	);
	DeleteDC( hdcDOWN3	);
	DeleteDC( hdcDefault3);

	ReleaseDC(NULL,hdc);
// 	g_ctlp=new CTooltip();
// 	g_ctlp->InitTooltip(hInstance);
	return true;
}
/*
HWND CDButtonD::Create(HWND hprent,int x,int y,INT nID,TCHAR*text,CTooltip*pctlp)
{
	HWND hw =NULL;
	hw= CreateWindowA("DButton",text,
		WS_CHILD | WS_VISIBLE ,
		x, y, 32, 32, hprent,(HMENU)nID,odInst,NULL);
	g_ctlp=pctlp;

	return hw;
}


HWND CDButtonD::Create(HWND hprent,HINSTANCE hInstance,int x,int y,int cx,int cy,INT nID,LPCSTR lpname,TCHAR*text,int nBackType,CTooltip*pctlp)
{
	HWND hw =NULL;
	hw= CreateWindowA("DButton",text,
		WS_CHILD | WS_VISIBLE ,
		x, y, cx, cy, hprent,(HMENU)nID,odInst,NULL);
	g_ctlp=pctlp;
	//每次都会创建一个位图，并保存下来
	DBUTTOND dbd;
	dbd.hdc=CreateCompatibleDC(NULL);
	dbd.hbitmapM=CreateBitmap(cx,cy,1,1,NULL);
	SelectObject(dbd.hdc ,dbd.hbitmapM);

	dbd.hbitmap=LoadBitmap(hInstance,lpname);
	HDC dc=CreateCompatibleDC(NULL);
	SelectObject(dc,dbd.hbitmap);
	BitBlt(dbd.hdc,0,0,cx,cy,dc,0,0,NOTSRCERASE);
	dbd.nID=nID;
	dbd.nWidth=cx;
	dbd.nHeight=cy;
	dbd.nBackType=nBackType;
	dbd.hprent=hprent;
	m_Dbutond.push_back(dbd);
	DeleteDC(dc);
	return hw;
}*/
void CDButtonD::Delete(HWND hprent)
{
	while(m_bbuttond)
	{
		Sleep(100);
	}
	m_bbuttond=true;
	list<DBUTTOND>::iterator pbut;
	for(pbut=m_Dbutond.begin();pbut!=m_Dbutond.end();pbut++)
	{
		if (pbut->hprent==hprent)
		{
			if (pbut->hbitmap!=NULL)
			{
				DeleteObject(pbut->hbitmap);
			}
			if (pbut->hbitmap1!=NULL)
			{
				DeleteObject(pbut->hbitmap1);
			}
			if (pbut->hbitmap2!=NULL)
			{
				DeleteObject(pbut->hbitmap2);
			}
			pbut->hbitmap=NULL;
			pbut->hbitmap1=NULL;
			pbut->hbitmap2=NULL;
			if (pbut==m_Dbutond.begin())
			{
				m_Dbutond.erase(pbut);
				pbut=m_Dbutond.begin();
			}
			else
			{
				m_Dbutond.erase(pbut--);
			}
		}
	}
	m_bbuttond=false;

}
HWND CDButtonD::Create(HWND hprent,HINSTANCE hInstance,int x,int y,int cx,int cy,INT nID,HDC hdcButton,int rx,int ry,int rcx,int rcy,TCHAR*text,int nBackType,HDC backdc)
{
	//在这里判断，是否已经存在了该项。
	bLbdown=false;
	bInitem=false;
	bool bcunzai=false;
	HWND hw =NULL;
	RECT rect={0,0,cx,cy};
	DBUTTOND bufbut;
	while(m_bbuttond)
	{
		Sleep(100);
	}
	m_bbuttond=true;
	list<DBUTTOND>::iterator pbut;
	for(pbut=m_Dbutond.begin();pbut!=m_Dbutond.end();pbut++)
	{
		if (pbut->hprent==hprent&&pbut->nID==nID)
		{
			bufbut=*pbut;
			hw=pbut->hdbut;
			bcunzai=true;
			//如果该项已存在，则替换掉原来的
			if (pbut->hbitmap!=NULL)
			{
				DeleteObject(pbut->hbitmap);
			}
			if (pbut->hbitmap1!=NULL)
			{
				DeleteObject(pbut->hbitmap1);
			}
			if (pbut->hbitmap2!=NULL)
			{
				DeleteObject(pbut->hbitmap2);
			}
			pbut->hbitmap=NULL;
			pbut->hbitmap1=NULL;
			pbut->hbitmap2=NULL;
			m_Dbutond.erase(pbut);
			break;
		}
	}
	m_bbuttond=false;
	if (bcunzai==false)
	{
		hw= CreateWindowEx(WS_EX_NOACTIVATE,_T("DButton"),text,
			WS_CHILD | WS_VISIBLE ,
			x, y, cx, cy, hprent,(HMENU)nID,odInst,NULL);
		
	}
	else
	{
		SetWindowText(hw,text);
		MoveWindow(hw,x,y,cx,cy,false);
	}	
	bufbut.hdbut=hw;
	bufbut.hprent=hprent;
	bufbut.nID=nID;
	bufbut.nBackType=nBackType;
	bufbut.nWidth=cx;
	bufbut.nHeight=cy;
	bufbut.nw=rcx;
	bufbut.nh=rcy;
	if (bufbut.hbitmap1!=NULL)
	{
		DeleteObject(bufbut.hbitmap1);
	}
	if (bufbut.hbitmap2!=NULL)
	{
		DeleteObject(bufbut.hbitmap2);
	}
	if (bufbut.hbitmap!=NULL)
	{
		DeleteObject(bufbut.hbitmap);
	}
	if (nBackType==BR_W1P0F1B1||nBackType==BR_W1P0F0B0)
	{
		HDC hdc=GetDC(hw);
		SIZE sss;
		int tlen;
		SelectObject(hdc,m_hFont1);
		TCHAR strbuffer[256];
		GetWindowText(hw,strbuffer,30);
		GetTextExtentExPoint(hdc, strbuffer, lstrlen(strbuffer), 100, &tlen, NULL, &sss);
		SetWindowPos(hw,NULL,0,0,sss.cx+10,cy,SWP_NOMOVE);
		ReleaseDC(hw,hdc);
		cx=sss.cx+10;
		bufbut.nWidth=cx;
	}
	
	if (nBackType==BR_W0P1F1B1||nBackType==BR_W1P0F1B1)
	{
		HRGN hrgn=CreateRoundRectRgn(0,0,cx,cy,6,6);
		SetWindowRgn(hw,hrgn,true);
		DeleteObject(hrgn);
	}
	else if(nBackType==BR_W0P1F0B0||nBackType==BR_W1P0F0B0)
	{
		//无
		HRGN hrgn=CreateRectRgn(0,0,cx,cy);
		SetWindowRgn(hw,hrgn,true);
		DeleteObject(hrgn);
	}
	else
	{
		HRGN hrgn=CreateRoundRectRgn(0,0,cx,cy,2,2);
		SetWindowRgn(hw,hrgn,true);
		DeleteObject(hrgn);
	}
	
//每次都会创建一个位图，并保存下来
	//DBUTTOND dbd;


	//bufbut.hbitmap保存hdcButton传过来的图像
	bufbut.hbitmap=CreateBitmap(cx,cy,1,32,NULL);
	DrawD(bufbut.hdbut,bufbut.hbitmap,0,0,cx,cy,hdcButton,rx,ry,rcx,rcy,backdc,x,y,cx,cy,nBackType,0);

	bufbut.hbitmap1=CreateBitmap(cx,cy,1,32,NULL);
	DrawD(bufbut.hdbut,bufbut.hbitmap1,0,0,cx,cy,hdcButton,rx,ry,rcx,rcy,backdc,x,y,cx,cy,nBackType,1);

	bufbut.hbitmap2=CreateBitmap(cx,cy,1,32,NULL);
	DrawD(bufbut.hdbut,bufbut.hbitmap2,0,0,cx,cy,hdcButton,rx,ry,rcx,rcy,backdc,x,y,cx,cy,nBackType,2);

	m_Dbutond.push_back(bufbut);
	InvalidateRect(hw,&rect,true);
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
		bLbdown=false;
		bInitem=false;
		break;
	}
	//将不做处理的消息路由给原默认函数
	return CallWindowProc((WNDPROC)prev_proc, hWnd, message, wParam, lParam);
}

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

	switch(uMsg)
	{
	case WM_CREATE:
		{
			bLbdown=false;
			bInitem=false;

			if(hOwnerDrawIcon == NULL)
				hOwnerDrawIcon = (HICON)LoadImage(odInst, 
				MAKEINTRESOURCE(IDI_SMALL), 
				IMAGE_ICON, 
				38,
				38,
				0);
			prev_proc = SetWindowLongPtr(GetDlgItem(hwndDlg, MAKEWORD(::GetWindowLong(hwndDlg,GWL_ID),0)), GWLP_WNDPROC, (LONG)ButtWindProc);

			SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
			//SetFocus(GetDlgItem(hwndDlg, MAKEWORD(::GetWindowLong(hwndDlg,GWL_ID),0)));
			//SendMessage(GetDlgItem(hwndDlg, MAKEWORD(::GetWindowLong(hwndDlg,GWL_ID),0)),WM_SETFOCUS,0,0);
		}
		return 0;
	case WM_PAINT:
// 		::GetClientRect(hwndDlg,&rect);
// 		::GetWindowText(hwndDlg,szText,sizeof(szText));

		hdc = ::BeginPaint(hwndDlg,&ps);
		g_pDButton->OnDrawDButton(hwndDlg,hdc,bInitem,bLbdown);

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
		{
			SetFocus(hwndDlg);
			//SendMessage(hwndDlg,WM_SETFOCUS,0,0);

			// GetDlgItem(控件的ID（如IDC_BUTTON1）)->EnableWindow
			//EnableWindow(hwndDlg,false);
		}
		return 0;
	case WM_RBUTTONUP:
		{

		}
		return 0;
	case WM_LBUTTONDOWN:
		{
			SetFocus(GetParent(hwndDlg));
			//SendMessage(GetParent(hwndDlg),WM_SETFOCUS,0,0);
			g_pDButton->m_hLDown=hwndDlg;
			if (bLbdown==false)
			{
				bLbdown=true;
				hdc=GetDC(hwndDlg);
				g_pDButton->OnDrawDButton(hwndDlg,hdc,bInitem,bLbdown);
				ReleaseDC(hwndDlg,hdc);
			}
		}
		return 0;
	case WM_LBUTTONUP:
		{
			//Click
			lParam;
			wParam;
			if (bLbdown==true)
			{
				bLbdown=false;
				_bMouseTrack=true;
				bInitem=false;
				::SendMessage(GetParent(hwndDlg),WM_COMMAND,GetWindowLong(hwndDlg,GWL_ID),(LPARAM)hwndDlg);
			}
			hdc=GetDC(hwndDlg);
			g_pDButton->OnDrawDButton(hwndDlg,hdc,bInitem,bLbdown);
			ReleaseDC(hwndDlg,hdc);
		}
		return 0;
	case WM_MOUSEMOVE:
		{
			g_pDButton->m_hInitem=hwndDlg;
			if (bInitem==false)
			{
				bInitem=true;
				hdc=GetDC(hwndDlg);
				g_pDButton->OnDrawDButton(hwndDlg,hdc,bInitem,bLbdown);
				ReleaseDC(hwndDlg,hdc);
			}
		}
		return 0;
	case WM_MOUSELEAVE:
		{
			bLbdown=false;
			if (bInitem==true)
			{
				bInitem=false;
				hdc=GetDC(hwndDlg);
				g_pDButton->OnDrawDButton(hwndDlg,hdc,bInitem,bLbdown);
				ReleaseDC(hwndDlg,hdc);
			}
		}
		return 0;
	case WM_SHOWText:
		{
			if (wParam==WM_SHOWText)
			{
				TCHAR *pbuf=(TCHAR*)lParam;
				//_bMouseTrack=true;
				POINT point;
				GetCursorPos(&point);
				delete pbuf;
			}
		}
		break;
	case WM_SETFOCUS:
		{
			SetFocus(GetParent(hwndDlg));
			//SendMessage(GetParent(hwndDlg),WM_SETFOCUS,0,0);
		}
		break;
	case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT) lParam;
			//声明一个指向DRAWITEMSTRUCT结构体的指针并将其指向存储着按钮构造信息的lParam

			if(lpDIS->CtlID != MAKEWORD(::GetWindowLong(hwndDlg,GWL_ID),0)	)
				return (0);
			
			HDC dc = lpDIS->hDC; //用于按钮绘制的DC
			BOOL bIsPressed  = (lpDIS->itemState & ODS_SELECTED);
			BOOL bIsFocused  = (lpDIS->itemState & ODS_FOCUS);
			BOOL bIsDisabled = (lpDIS->itemState & ODS_DISABLED);
			BOOL bDrawFocusRect = !(lpDIS->itemState & ODS_NOFOCUSRECT);
			//判断按钮各种状态的BOOL值
			RECT itemRect = lpDIS->rcItem; //按钮的矩形区域

			SetBkMode(dc, TRANSPARENT); //设置绘制按钮时的背景状态
			if (bIsFocused)  //判断按钮是否获得了焦点并对其边框进行处理
			{
				HBRUSH br = CreateSolidBrush(RGB(0,0,0));  
				FrameRect(dc, &itemRect, br);
				InflateRect(&itemRect, -1, -1);
				DeleteObject(br);
			} // if        

			COLORREF crColor = GetSysColor(COLOR_BTNFACE);//得到系统按钮颜色

			HBRUSH    brBackground = CreateSolidBrush(crColor);//创建画刷

			FillRect(dc, &itemRect, brBackground);//绘制按钮

			DeleteObject(brBackground);

			// 这里画被按下去的按钮
			if (bIsPressed)
			{
				HBRUSH brBtnShadow = CreateSolidBrush(GetSysColor(COLOR_BTNSHADOW));
				FrameRect(dc, &itemRect, brBtnShadow);
				DeleteObject(brBtnShadow);
			}

			else //如果没有被按下就这样画
			{
				UINT uState = DFCS_BUTTONPUSH |
					((bIsPressed) ? DFCS_PUSHED : 0);

				DrawFrameControl(dc, &itemRect, DFC_BUTTON, uState);
			}

			TCHAR sTitle[100];
			GetWindowText(GetDlgItem(hwndDlg, MAKEWORD(::GetWindowLong(hwndDlg,GWL_ID),0)), sTitle, 100);//得到按钮的文本

			RECT captionRect = lpDIS->rcItem;//把文本的区域设置为按钮区域


			BOOL bHasTitle = (sTitle[0] !='/0');//按钮上是否有文本存在

			//这里画按钮上的图标,具体实现见下面
			(GetDlgItem(hwndDlg, MAKEWORD(::GetWindowLong(hwndDlg,GWL_ID),0)), &dc, bHasTitle, 
				&lpDIS->rcItem, &captionRect, bIsPressed, bIsDisabled);

			if (bHasTitle)//如果按钮有文本标题
			{
				// 按钮被按下的处理
				if (bIsPressed)
					OffsetRect(&captionRect, 1, 1);

				// 将文本居中
				RECT centerRect = captionRect;
				DrawText(dc, sTitle, -1, &captionRect, DT_WORDBREAK | DT_CALCRECT|DT_CENTER);
				LONG captionRectWidth = captionRect.right - captionRect.left;
				LONG captionRectHeight = captionRect.bottom - captionRect.top;
				LONG centerRectWidth = centerRect.right - centerRect.left;
				LONG centerRectHeight = centerRect.bottom - centerRect.top;
				OffsetRect(&captionRect, (centerRectWidth - captionRectWidth)/2, (centerRectHeight - captionRectHeight)/2);

				SetBkMode(dc, TRANSPARENT);

				if (bIsDisabled)//如果按钮被禁用
				{
					OffsetRect(&captionRect, 1, 1);
					SetTextColor(dc, ::GetSysColor(COLOR_3DHILIGHT));
					DrawText(dc, sTitle, -1, &captionRect, DT_WORDBREAK | DT_CENTER);
					OffsetRect(&captionRect, -1, -1);
					SetTextColor(dc, ::GetSysColor(COLOR_3DSHADOW));
					DrawText(dc, sTitle, -1, &captionRect, DT_WORDBREAK | DT_CENTER);
				} 
				else //如果没被禁用正常画
				{
					SetTextColor(dc, ::GetSysColor(COLOR_BTNTEXT));
					SetBkColor(dc, ::GetSysColor(COLOR_BTNFACE));
					DrawText(dc, sTitle, -1, &captionRect, DT_WORDBREAK | DT_CENTER);
				} 

			}
			// 画按钮得到焦点时的虚线方框
			if (bIsFocused && bDrawFocusRect)
			{
				RECT focusRect = itemRect;
				InflateRect(&focusRect, -3, -3);
				DrawFocusRect(dc, &focusRect);
			} // if
			return (TRUE);
		}
		return 0;	
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			//删除该项
			while(g_pDButton->m_bbuttond)
			{
				Sleep(100);
			}
			g_pDButton->m_bbuttond=true;
			list<DBUTTOND>::iterator pdbut;
			for(pdbut=g_pDButton->m_Dbutond.begin();pdbut!=g_pDButton->m_Dbutond.end();pdbut++)
			{
				if (pdbut->hdbut==hwndDlg)
				{
					g_pDButton->m_Dbutond.erase(pdbut);
					break;
				}
			}
			g_pDButton->m_bbuttond=false;
		}
		return 0;
	}
	return ::DefWindowProc(hwndDlg,uMsg,wParam,lParam);
}

void CDButtonD::OnReDraw(HWND hprent,HWND hwnd)
{
	HDC hdc=GetDC(hwnd);
	OnDrawDButton(hwnd,hdc,bInitem,bLbdown);
	ReleaseDC(hwnd,hdc);
}
void CDButtonD::OnDrawDButton(HWND hwnd,HDC hdc,bool bInitem,bool bLbdown)
{	
	HDC dc1=CreateCompatibleDC(hdc);
	while(m_bbuttond)
	{
		Sleep(100);
	}
	m_bbuttond=true;
	list<DBUTTOND>::iterator pdbut;
	for(pdbut=m_Dbutond.begin();pdbut!=m_Dbutond.end();pdbut++)
	{
		if (pdbut->hdbut==hwnd)
		{
			if (pdbut->bSel==true)
			{
				SelectObject(dc1,pdbut->hbitmap1);
			}
			else
			{
				if (m_hInitem==hwnd&&bInitem==true)
				{
					if (m_hLDown==hwnd&&bLbdown==true)
						SelectObject(dc1,pdbut->hbitmap1);
					else
						SelectObject(dc1,pdbut->hbitmap2);
				}
				else
				{
					SelectObject(dc1,pdbut->hbitmap);
				}
			}	
			BitBlt(hdc,0,0,pdbut->nWidth,pdbut->nHeight,dc1,0,0,SRCCOPY);
			//以下都是需要显示字的
		}
	}
	DeleteDC(dc1);
	m_bbuttond=false;
}

CDButtonD::CDButtonD()
{
	HBIT_MOVE=NULL;
	HBIT_DOWN=NULL;
	HBIT_Default=NULL;
	HBITMAP HBIT_MOVE1=NULL;
	HBITMAP HBIT_DOWN1=NULL;
	HBITMAP HBIT_Default1=NULL;
	HBITMAP HBIT_BUTTON=NULL;
	m_bbuttond=false;
	m_hInitem=NULL;
	m_hLDown=NULL;
	m_hFont=CreateFont(14, // nHeight 
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
	m_hFont1=CreateFont(14, // nHeight 
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

int CDButtonD::DrawD(HWND hwnd,HBITMAP hbitmap, int x, int y, int cx, int cy, HDC hdctop,int x1, int y1, int cx1, int cy1, HDC hdcbom,int x2, int y2, int cx2, int cy2, int type,int ng)
{
	CxImage cxim;
	HBRUSH hbrush=NULL;
	RECT rect={0,0,cx,cy};
	HDC hdcout=CreateCompatibleDC(NULL);
	SelectObject(hdcout,hbitmap);
	HDC dc1=CreateCompatibleDC(hdcout);
	HDC dc2=CreateCompatibleDC(hdcout);
	HDC dc3=CreateCompatibleDC(hdcout);
	HDC dcM=CreateCompatibleDC(hdcout);

	HBITMAP bit2=CreateCompatibleBitmap(hdcout,cx,cy);
	HBITMAP bit3=CreateCompatibleBitmap(hdcout,cx,cy);
	HBITMAP bit1=CreateCompatibleBitmap(hdcout,cx,cy);	

	HBITMAP bitM=CreateBitmap(cx,cy,1,1,NULL);
	SelectObject(dcM,bitM);
	
	SelectObject(dc2,bit2);
	SelectObject(dc3,bit3);
	SelectObject(dc1,bit1);
	if (hdctop!=NULL)
	{
		if (type==BR_W0P2F2B0)
			SetBkColor(hdctop,RGB(0,0,0));
		else
			SetBkColor(hdctop,RGB(255,255,255));
		BitBlt(dcM,(cx-cx1)/2,(cy-cy1)/2,cx1,cy1,hdctop,x1,y1,NOTSRCERASE);
		
	}
	if (ng==1)
	{
		switch(type)
		{
		case BR_W0P1F1B1:
		case BR_W1P0F1B1:
			cxim.CreateFromHBITMAP(HBIT_DOWN1);
			break;
		case BR_W0P1F2B3:
		case BR_W1P0F2B3:
			cxim.CreateFromHBITMAP(HBIT_DOWN2);
			break;
		case BR_W0P1F2B2:
			cxim.CreateFromHBITMAP(HBIT_DOWN3);
			break;
		}
	}
	else if(ng==2)
	{
		//鼠标在按钮上
		switch(type)
		{
		case BR_W0P1F1B1:
		case BR_W1P0F1B1:
			cxim.CreateFromHBITMAP(HBIT_MOVE1);
			break;
		case BR_W0P1F2B3:
		case BR_W1P0F2B3:
			cxim.CreateFromHBITMAP(HBIT_MOVE2);
			break;
		case BR_W0P1F2B2:
			cxim.CreateFromHBITMAP(HBIT_MOVE3);
			break;
		}
	}
	else
	{
		//还原
		switch(type)
		{
		case BR_W0P1F1B1:
		case BR_W1P0F1B1:
			cxim.CreateFromHBITMAP(HBIT_Default1);
			break;
		case BR_W0P1F2B3:
		case BR_W1P0F2B3:
			cxim.CreateFromHBITMAP(HBIT_Default2);
			break;
		case BR_W0P1F2B2:
			cxim.CreateFromHBITMAP(HBIT_Default3);
			break;
		}
	}
	{

		if (type==BR_W2P0F2B0)
		{
			SetBkMode(dc1,TRANSPARENT);
			Rectangle(dc1,0,0,cx,cy);
			//FillRect(dc1,&rect,g_hbackbrush);
		}
		else
		{

			cxim.Resample(cx,cy);
			cxim.Draw(dc1,0,0,cx,cy);
		}
		if(hdcbom!=NULL)
			BitBlt(dc1,0,0,cx,cy,hdcbom,x2,y2,SRCCOPY);

		BitBlt(dc2,0,0,cx,cy,dcM,0,0,SRCCOPY);
		SetBkColor(dcM,RGB(255,255,255));

		//消除底色贴图

		BitBlt(dc3,0,0,cx,cy,dcM,0,0,NOTSRCERASE);
		if (hdctop!=NULL)
		{
			BitBlt(dc2,(cx-cx1)/2,(cy-cy1)/2,cx1,cy1,hdctop,x1,y1,SRCAND);
		}

		BitBlt(dc3,0,0,cx,cy,dc1,0,0,SRCAND);

		BitBlt(hdcout,0,0,cx,cy,dc3,0,0,SRCCOPY);
		if(type==BR_W1P0F0B0||type==BR_W0P1F0B0||type==BR_W0P2F0B0)
		{
			RECT rect={0,0,cx,cy};
			UCHAR *pby=new UCHAR[cx*cy*4+1];
			DWORD dwsize=0;
			if (ng==1)
			{
				dwsize=GetBitmapBits(hbitmap,cx*cy*4,pby);
				if(dwsize)
				{
					for (int i=0;i<dwsize;i++)
					{
						if(pby[i]!=0)//被忽略的颜色是RGB(0,0,0)
						{
							pby[i]=255-(255-pby[i])*0.6;
						}
					}
					SetBitmapBits(hbitmap,dwsize,pby);
				}
			}
			else if(ng==2)
			{
				dwsize=GetBitmapBits(hbitmap,cx*cy*4,pby);
				if(dwsize)
				{
					for (int i=0;i<dwsize;i++)
					{
						if(pby[i]!=0)//被忽略的颜色是RGB(0,0,0)
						{
							pby[i]=255-(255-pby[i])*0.8;
						}
					}
					SetBitmapBits(hbitmap,dwsize,pby);
				}
			}
			delete pby;
		}
		BitBlt(hdcout,0,0,cx,cy,dc2,0,0,SRCPAINT);
		SetBkMode(hdcout,TRANSPARENT);
		if (type==BR_W1P0F2B3||type==BR_W0P1F2B2||type==BR_W2P0F2B0)
		{
			TCHAR strbuffer[256];
			GetWindowText(hwnd,strbuffer,256);
			SIZE sss;
			int ncpy=1;
			int tlen=0;
			int ni=0;
			int tempi=0;
			int height=0;
			int len=lstrlen(strbuffer);

			TCHAR szshow[50];
			for (int i=0;i<=len;i++)
			{
				if (strbuffer[i]=='\n'||strbuffer[i]==NULL)
				{

					SelectObject(hdcout,m_hFont1);
					SetTextColor(hdcout,RGB(50,145,150));
					SetBkMode(hdcout,TRANSPARENT);
					tempi=0;
					strbuffer[i]=NULL;
					GetTextExtentExPoint(hdcout,&strbuffer[ni],i-ni,cx,&tlen,NULL,&sss);
					if (type==BR_W2P0F2B0)
					{
						wcsncpy(szshow, &strbuffer[ni], tlen);
						szshow[tlen]=NULL;
						TextOut(hdcout,0,ncpy*17-16,szshow,lstrlen(szshow));
					}
					tempi+=tlen;
					ncpy++;
					while (tempi<i-ni)
					{
						GetTextExtentExPoint(hdcout,&strbuffer[ni+tempi],i-ni,cx,&tlen,NULL,NULL);
						if (type==BR_W2P0F2B0)
						{
							wcsncpy(szshow, &strbuffer[ni + tempi], tlen);
							szshow[tlen]=NULL;
							TextOut(hdcout,0,ncpy*17-16,&strbuffer[ni+tempi],lstrlen(szshow));
						}
						tempi+=tlen;
						ncpy++;
					}
					ni=i+1;
				}
			}
			if (type!=BR_W2P0F2B0)
			{
				if (ncpy==1)
				{
					GetTextExtentExPoint(hdcout,strbuffer,len,300,NULL,NULL,&sss);
					tlen=sss.cx;
				}
				else
				{
					GetTextExtentExPoint(hdcout,&strbuffer[ni],lstrlen(&strbuffer[ni]),300,NULL,NULL,&sss);
					if (tlen<sss.cx)
					{
						tlen=sss.cx;
					}
				}
				//int cx=tlen+4;
				//int cy=sss.cy*ncpy+6;
				SelectObject(hdcout,m_hFont);
				SetTextColor(hdcout,RGB(250,245,250));
				GetTextExtentExPoint(hdcout,strbuffer,lstrlen(strbuffer),300,NULL,NULL,&sss);
				TextOut(hdcout,(cx-sss.cx)/2,(cy-sss.cy)/2,strbuffer,lstrlen(strbuffer));
			}
		}
		else if (type==BR_W1P0F1B1||type==BR_W1P0F0B0)//只允许显示30个字符
		{
			if (type==BR_W1P0F0B0)
			{

				SetTextColor(hdcout,RGB(255,255,255));
			}
			SIZE sss;
			RECT rect;
			int tlen;
			SelectObject(hdcout,m_hFont1);
			GetWindowRect(hwnd,&rect);
			TCHAR strbuffer[256];
			GetWindowText(hwnd,strbuffer,30);
			GetTextExtentExPoint(hdcout,strbuffer,lstrlen(strbuffer),rect.right-rect.left-10,&tlen,NULL,&sss);
			if (sss.cx>rect.right-rect.left)
			{
				strbuffer[tlen]='.';
				strbuffer[tlen+1]='.';
				strbuffer[tlen+2]=NULL;
			}

			GetTextExtentExPoint(hdcout,strbuffer,lstrlen(strbuffer),rect.right-rect.left-10,&tlen,NULL,&sss);
			TextOut(hdcout,(cx-sss.cx)/2,(cy-sss.cy)/2,strbuffer,lstrlen(strbuffer));
		}
	
	}	
	DeleteObject(bit1);
	DeleteObject(bit2);
	DeleteObject(bit3);
	DeleteDC(hdcout);
	DeleteDC(dc1);
	DeleteDC(dc2);
	DeleteDC(dc3);
	DeleteDC(dcM);
	DeleteObject(bitM);
	return 0;
}

int CDButtonD::SetDraw(HWND hdu,bool bdraw)
{
	while(m_bbuttond)
	{
		Sleep(100);
	}
	m_bbuttond=true;
	list<DBUTTOND>::iterator pdbut;
	for(pdbut=m_Dbutond.begin();pdbut!=m_Dbutond.end();pdbut++)
	{
		if (pdbut->hdbut==hdu)
		{
			pdbut->bSel=bdraw;
		}
	}
	m_bbuttond=false;
	return 0;
}
