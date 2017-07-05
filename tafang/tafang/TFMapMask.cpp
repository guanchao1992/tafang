#include "stdafx.h"
#include "TFMapMask.h"
#include "TowerDefense.h"
#include <winuser.h>
#include <tchar.h>
#include <commctrl.h>
#include <io.h>
#include "API.h"
TFMapMask*g_tfMapMask = NULL;
TFMapMask::TFMapMask()
{
	g_tfMapMask = this;
	m_bLdown = false;
	m_bMouseTrack = true;
	//m_bInitem = false;
	m_tfbrush = TYPE_KONG;
	m_nxuan=0;
	m_hWnd=NULL;
	m_nbrush = 4;
	m_nduqu = 0;
	if (m_hbitmap != NULL)DeleteObject(m_hbitmap);
	if (m_hdc != NULL) DeleteDC(m_hdc);
	m_hbitmap = CreateBitmap(4 * m_tfmap.m_nw + 1, 4 * m_tfmap.m_nh + 1, 1, 32, NULL);
	m_hdc = CreateCompatibleDC(NULL);
	SelectObject(m_hdc, m_hbitmap);
}

TFMapMask::~TFMapMask()
{
	DeleteObject(m_hbitmap);
	DeleteDC(m_hdc);
}

BOOL CALLBACK DlgMapMask(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	UNREFERENCED_PARAMETER(lParam);
	HDC hdc;
	HBITMAP hbitmap;
	//HDC hdcbut;
	//HBITMAP hbitmapbut;
	RECT rect;
	switch (message)
	{
	case WM_INITDIALOG:
		g_tfMapMask->m_hWnd = hDlg;
		hdc = CreateCompatibleDC(NULL);
		hbitmap = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_ZHEBI));
		SelectObject(hdc, hbitmap);

		g_dbutton->Create(hDlg, g_hinst, g_tfMapMask->GetButtonX() + 80, 0, 64, 32, ID_BUT_SAVE, HDC_BUTTON, 20, 96, 20, 20, _T("保存"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
		g_dbutton->Create(hDlg, g_hinst, g_tfMapMask->GetButtonX() + 80, 40, 64, 32, ID_BUT_LOAD, HDC_BUTTON, 40, 96, 20, 20, _T("读取"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
		g_dbutton->Create(hDlg, g_hinst, g_tfMapMask->GetButtonX() + 80, 80, 64, 32, ID_BUT_REDRWN, HDC_BUTTON, 60, 96, 20, 20, _T("刷新"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
		g_dbutton->Create(hDlg, g_hinst, g_tfMapMask->GetButtonX() + 80, 120, 64, 32, ID_BUT_CE, HDC_BUTTON, 80, 96, 20, 20, _T("清空"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
																
		g_dbutton->Create(hDlg, g_hinst, g_tfMapMask->GetButtonX(), 0, 64, 32, ID_BUT_KONG, hdc, 0, 0, 32, 32, _T("0"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
		g_dbutton->Create(hDlg, g_hinst, g_tfMapMask->GetButtonX(), 32, 64, 32, ID_BUT_ZHEBI, hdc, 32, 0, 32, 32, _T("1"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
		g_dbutton->Create(hDlg, g_hinst, g_tfMapMask->GetButtonX(), 64, 64, 32, ID_BUT_TU, hdc, 64, 0, 32, 32, _T("2"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
		g_tfMapMask->OnButton(ID_BUT_KONG);
		DeleteDC(hdc);
		
		//GetWindowRect(hDlg, &rect);
		//ClipCursor(&rect);
		break;
	case WM_LBUTTONDOWN:
		g_tfMapMask->OnLButtonDown(hDlg, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		g_tfMapMask->OnLButtonUp(hDlg, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		g_tfMapMask->OnMouseMove(hDlg, wParam, lParam);
		break;
	case WM_MOUSELEAVE:
		g_tfMapMask->OnMouseLeave(hDlg, wParam, lParam);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hDlg, &ps);
		g_tfMapMask->OnPaint(hdc,&ps.rcPaint);	
		EndPaint(hDlg, &ps);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (wmId == IDOK || wmId == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (wmId >= ID_BUT_KONG&&wmId <= ID_BUT_KONG+100)
		{
			g_tfMapMask->OnButton(wmId);
		}
		else if (wmId == ID_BUT_SAVE)
		{
			char buffer[] = "(2000,30,2000,50)(1500,40,2500,70)(1000,50,3000,60)(800,60,3500,75)(2000,30,4000,50)(1500,40,4500,70)(1000,50,5000,60)(800,60,5500,75)(2000,30,6000,50)(1500,40,6500,70)(1000,50,7000,60)(800,60,7500,75)(2000,30,8000,50)(1500,40,8500,70)(1000,50,9000,60)(800,60,9500,75)";
			g_tfMapMask->SaveTFMap("这里是名字","1",buffer,strlen(buffer),"save.txt");
		}
		else if (wmId == ID_BUT_LOAD)
		{
			g_tfMapMask->m_nduqu++;
			g_tfMapMask->LoadTFMap("save.txt", g_tfMapMask->m_nduqu);
		}
		else if (wmId == ID_BUT_REDRWN)
		{
			g_tfMapMask->ReDraw();
		}
		else if (wmId == ID_BUT_CE)
		{
			g_tfMapMask->ReDrawCE();
		}
		break;
	}
	return false;
}
int TFMapMask::InMapStr(char*str,int len)//确保传入的指针是正确的
{
	for (int x = 0; x < m_tfmap.m_nw; x++)
	{
		for (int y = 0; y < m_tfmap.m_nh; y++)
		{
			str[m_tfmap.m_nh*x + y] = m_tfmap.tf[x][y];
		}
	}
	return 0;
}

int TFMapMask::LoadTFMap(char*path, int ng)//ng表示关卡。从1开始
{
	char buffer[1024];
	int filesize, nf =0,nm= 0;
	FILE *fl = fopen(path, "rb");
	if (fl)
	{
		filesize = filelength(fileno(fl));
		void* vbuf=malloc(filesize + 1);
		char *str = (char*)vbuf;
		while (nf=fread(buffer, 1, 1024, fl))
		{
			for (int i = 0; i < nf; i++)
				str[nm + i] = buffer[i];
			nm += nf;
		}
		fclose(fl);
		DWORD pos0 = (DWORD)str;
		DWORD pos1 = pos0;
		DWORD pos2 = pos1;
		int ng2 = ng;
		while (ng2-- >0)
		{
			pos1=findstr(&str[pos1-pos0], filesize+pos0-pos1, "#:这里是真正的尾部}");
			if (pos1 == 0 || ng2 == 0)
			{
				if (pos1 == 0)
				{
					free(vbuf);
					m_nduqu = 1;
					return LoadTFMap(path, m_nduqu);
				}
				break;
			}
			pos2 = pos1;
			pos1++;
			int a = 0;
		}
		if (pos1 != 0 && ng2 == 0)
		{
			//char name[64];
			//char guanqia[8];
			char *pmap = NULL;
			short nw = 0;
			short nh = 0;
			//位置是从 pos2到pos1
			if (ng>1)
				pos2 += 30;
			DWORD pos3 = pos2;
			char *ps = (char*)pos2;
			int lenps = pos1 - pos2;
			DeCode(ps,lenps);
			pos3 = findstr(ps, lenps, "{:1");
			if (pos3!=NULL)
				strncpy(m_name, (char*)(pos3 + 3), 64 - 5);
			pos3 = findstr(ps, lenps, "{:2");
			if (pos3 != NULL)
				strncpy(m_guanqia, (char*)(pos3 + 3), 8 - 5);
			pos3 = findstr(ps, lenps, "{:3");
			if (pos3 != NULL)
			{
				nw = *(short*)(pos3 + 3);
				nh = *(short*)(pos3 + 3 + 2);
			}
			pos3 = findstr(ps, lenps, "{:4");
			if (pos3 != NULL)
				pmap = (char*)(pos3 + 3);
			pos3 = findstr(ps, lenps, "{:5");
			if (pos3 != NULL)
				strcpy(m_szcmd, (char*)(pos3 + 3));
			
			if (nw > PM_W_MAX)nw = PM_W_MAX;
			if (nh > PM_H_MAX)nh = PM_H_MAX;
			m_tfmap.SetSize(nw, nh);
			for (int x = 0; x < nw; x++)
			{
				for (int y = 0; y < nh; y++)
				{
					m_tfmap.tf[x][y] = (TFtype)pmap[x*nw + y];
				}
			}
			ReDraw();
			//while (1)
			//{
			//	pos3 = findstr()
			//}
		}
		free(vbuf);
	}
	//  0头部标识8字节。
	//	1名称64字节。
	//	2关卡8个字节
	//	3字符串的头部给出地图的大小。9个字节
	//	4每个字符表示4个方格。在地图外的部分被忽略掉。
	//	5特定的剧情以及其他。
	//	-1尾部标识。	8字节。
	return 0;
}

//剧情{(等待时间，数量，基础生命(显示时除以100)，基础速度(显示时除以100))}
int TFMapMask::SaveTFMap(char* name, char*guanqia, char*juqing, int jlen, char*path)
{
	//m_tfmap.m_nw; m_tfmap.m_nh;//大小
	//m_tfmap.tf;//内存中保存的地图
	int nre = 8 + 64 + 8 + 8 + m_tfmap.m_nw*m_tfmap.m_nh + 2 + 3 + jlen + 2 + 3 + 8;
	void *buffer = malloc(nre+30);
	char *pstr = (char*)buffer;
	nre = 0;
	strcpy(pstr, "{:0头!!}");
	nre += 8;
	strcpy(pstr + nre, "{:1");
	strncpy(pstr + nre + 3, name, 64 - 2 - 3);
	if (strlen(name) < 64 - 2 - 3)*(pstr + nre+3  + strlen(name)) = '\0';//字符串的尾部
	strcpy(pstr + nre + 64 - 2, "!}");
	nre += 64;
	strcpy(pstr + nre, "{:2");
	strncpy(pstr + nre + 3, guanqia, 8 - 2 - 3);
	//if (strlen(name) < 8 - 2 - 3)*(pstr + nre + 3 + strlen(name)) = '\0';
	strcpy(pstr + nre + 8 - 2, "!}");
	nre += 8;
	short nw = m_tfmap.m_nw;
	short nh = m_tfmap.m_nh;
	strcpy(pstr + nre, "{:3");
	strncpy(pstr + nre + 3, (char*)&((short)nw), 2);
	strncpy(pstr + nre + 3+2, (char*)&((short)nh), 2);
	strcpy(pstr + nre + 9 - 2, "!}");
	nre += 9;

	strcpy(pstr + nre, "{:4");
	InMapStr(pstr + nre + 3,NULL);
	strcpy(pstr + nre + 3 + m_tfmap.m_nw*m_tfmap.m_nh, "!}");
	
	nre += 3 + 2 + m_tfmap.m_nw*m_tfmap.m_nh;

	strcpy(pstr + nre, "{:5");
	strncpy(pstr + nre + 3, juqing, jlen);
	*(pstr + nre + 3 + jlen) = '\0';
	strcpy(pstr + nre + 3 + jlen+1, "!}");
	nre += 3 + 2 +1+ jlen;

	strcpy(pstr + nre, "{:-1尾!}");
	nre += 8;
	
	EnCode(pstr,nre);
	
	//在加密之后添加尾部标识。用于确保正确解密。
	strcpy(pstr + nre, "#:这里是真正的尾部}");
	nre += 30;
	FILE *fl=fopen(path, "ab");
	fwrite(buffer, 1, nre, fl);

	fclose(fl);
	free(buffer);
	return 0;
}
int TFMapMask::SaveTFMap(void* str, TCHAR*name, int len)
{
	EnCode((char*)str, len);
	FILE *pf = _tfopen(name, _T("rb"));

	fwprintf_s(pf, (TCHAR*)str, len);
//	fprintf_s(pf, (TCHAR*)str, len);
	return 0;
}

int TFMapMask::InDakai(void* data, int len)//所打开的地图。此处设定规则
{
	//  0头部标识8字节。
	//	1名称64字节。
	//	2关卡8个字节
	//	3字符串的头部给出地图的大小。9个字节
	//	4每个字符表示4个方格。在地图外的部分被忽略掉。
	//	5特定的剧情以及其他。
	//	-1尾部标识。	8字节。
	//	"{:0头部标识!}{:1这里是名称!}{:2这里是关卡!}{:3这里是大小!}{:4此处给出一大串字符串。!}{:5这里给出特定剧情}{:-1尾部标识!}"

	return 0;
}

int TFMapMask::EnCode(char* str, int len)
{
	for (int i = 0, j = 0; i < len; i++, j++)
	{
		if (tfcode[j] == '\0')j = 0;
		str[i] ^= tfcode[j];
		//str[i] =(char)(str- i);
		str[i] -= i;
	}
	return 0;
}

int TFMapMask::DeCode(char* str, int len)
{
	for (int i = 0, j = 0; i < len; i++, j++)
	{
		if (tfcode[j] == '\0')j = 0;
		str[i] += i;
		str[i] ^= tfcode[j];
	}
	return 0;
}

int TFMapMask::OnDlgCreateMap(HWND hPrentWnd)//打开编辑工具
{
	ReDraw();
	DialogBox(g_hinst, MAKEINTRESOURCE(IDD_DIALOG_MASK), hPrentWnd, DlgMapMask);
	return 0;
}
int TFMapMask::OnCreateMap(HWND hWnd)
{
	ReDraw();
	m_hWnd = hWnd;
	HDC hdc = CreateCompatibleDC(NULL);
	HBITMAP hbitmap = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_ZHEBI));
	SelectObject(hdc, hbitmap);

	g_dbutton->Create(hWnd, g_hinst, GetButtonX() + 80, 0, 64, 32, ID_BUT_SAVE, HDC_BUTTON, 20, 96, 20, 20, _T("保存"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
	g_dbutton->Create(hWnd, g_hinst, GetButtonX() + 80, 40, 64, 32, ID_BUT_LOAD, HDC_BUTTON, 40, 96, 20, 20, _T("读取"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
	g_dbutton->Create(hWnd, g_hinst, GetButtonX() + 80, 80, 64, 32, ID_BUT_REDRWN, HDC_BUTTON, 60, 96, 20, 20, _T("刷新"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
	g_dbutton->Create(hWnd, g_hinst, GetButtonX() + 80, 120, 64, 32, ID_BUT_CE, HDC_BUTTON, 80, 96, 20, 20, _T("清空"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
	
	g_dbutton->Create(hWnd, g_hinst, GetButtonX(), 0, 64, 32, ID_BUT_KONG, hdc, 0, 0, 32, 32, _T("0"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
	g_dbutton->Create(hWnd, g_hinst, GetButtonX(), 32, 64, 32, ID_BUT_ZHEBI, hdc, 32, 0, 32, 32, _T("1"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
	g_dbutton->Create(hWnd, g_hinst, GetButtonX(), 64, 64, 32, ID_BUT_TU, hdc, 64, 0, 32, 32, _T("2"), BR_TY_P | BR_TY_W | BR_TY_TY_1);
	g_tfMapMask->OnButton(ID_BUT_KONG);
	DeleteDC(hdc);
	return 0;
}

int TFMapMask::ReDrawCE()
{
	for (int x = 0; x < m_tfmap.m_nw; x++)
	{
		for (int y = 0; y < m_tfmap.m_nh; y++)
		{
			m_tfmap.tf[x][y] = TFtype_KONG;
		}
	}
	ReDraw();
	return 0;
}

int TFMapMask::DrawOne(int x, int y, TFtype type)//定点绘制
{
	int nbrush = m_nbrush * 4;
	RECT rect = { x - 4 - nbrush / 2, y - 4 - nbrush/2, x + 4 + nbrush / 2, y + 4 + nbrush / 2 };
	HDC hdc;
	int nx=0;
	int ny=0;
	if (nbrush > 1)
	{
		for (int i = 0; i < m_nbrush; i++)
		{
			for (int j = 0; j < m_nbrush; j++)
			{
				nx = x / 4 + i - m_nbrush / 2;
				ny = y / 4 + j - m_nbrush / 2;
				if (nx >= 0 && ny >= 0 && nx < m_tfmap.m_nw&&ny < m_tfmap.m_nw)
					m_tfmap.tf[nx][ny] = type;
			}
		}
	}
	else
	{
		m_tfmap.tf[x / 4][y / 4] = type;
	}		
	BitBlt(m_hdc, x / 4 * 4 - nbrush / 2, y / 4 * 4 - nbrush / 2, nbrush, nbrush, HDC_Membit, type % 8 * 32, type / 8 * 32, SRCCOPY);

	InvalidateRect(m_hWnd, &rect, true);
	return 0;
}
int TFMapMask::OnDraw()
{

	return 0;
}

int TFMapMask::OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	m_bLdown = true;
	OnMouseMove(hWnd, wParam, lParam);
	return 0;
}
int TFMapMask::OnLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	m_bLdown = false;

	return 0;
}

int TFMapMask::OnMouseLeave(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	m_bMouseTrack = true;
	if (m_bLdown)
	{
		POINT point;
		RECT rect;
		GetCursorPos(&point);
		GetWindowRect(hWnd, &rect);
		if (point.x > rect.right)SetCursorPos(rect.right-1,point.y);
		if (point.x < rect.left)SetCursorPos( rect.left + 1,point.y);
		if (point.y < rect.top)SetCursorPos(point.x, rect.top + 1);
		if (point.y > rect.bottom)SetCursorPos(point.x, rect.bottom - 1);
		/*
		if (m_bMouseTrack)     // 若允许 追踪，则。 
		{
			TRACKMOUSEEVENT csTME;
			csTME.cbSize = sizeof (csTME);
			csTME.dwFlags = TME_LEAVE;
			csTME.hwndTrack = hWnd;// 指定要 追踪 的窗口
			::_TrackMouseEvent(&csTME); // 开启 Windows 的 WM_MOUSELEAVE ， WM_MOUSEHOVER 事件支持

			m_bMouseTrack = FALSE;   // 若已经 追踪 ，则停止 追踪 
		}*/
		
	}	
	
	return 0;
}
int TFMapMask::OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	POINTS point=MAKEPOINTS(lParam);
	if (m_bLdown)
	{
		DrawOne(point.x, point.y, m_tftype);
	}
	if (m_bMouseTrack)     // 若允许 追踪，则。 
	{
		TRACKMOUSEEVENT csTME;
		csTME.cbSize = sizeof (csTME);
		csTME.dwFlags = TME_LEAVE;
		csTME.hwndTrack = hWnd;// 指定要 追踪 的窗口
		::_TrackMouseEvent(&csTME); // 开启 Windows 的 WM_MOUSELEAVE ， WM_MOUSEHOVER 事件支持

		m_bMouseTrack = FALSE;   // 若已经 追踪 ，则停止 追踪 
	}
	return 0;
}
int TFMapMask::OnPaint(HDC hdc,LPRECT rect)
{

//	BitBlt(hdc, 0, 0, m_tfmap.m_nw * 4 + 1, m_tfmap.m_nh * 4 + 1, m_hdc, 0, 0, SRCCOPY);
	BitBlt(hdc, rect->left, rect->top, rect->right - rect->left, rect->bottom - rect->top, m_hdc, rect->left, rect->top, SRCCOPY);

	return 0;
}
int TFMapMask::OnButton(UINT nID)
{
	if (nID != m_nxuan)
	{
		g_dbutton->SetDraw(GetDlgItem(m_hWnd, m_nxuan), false);
		g_dbutton->SetDraw(GetDlgItem(m_hWnd, nID), true);
	}
	m_nxuan = nID;
	switch (m_nxuan)
	{
	case ID_BUT_KONG:
		m_tftype = TFtype_KONG;
		break;
	case	ID_BUT_ZHEBI:
		m_tftype = TFtype_ZHEBI;
		break;
	case	ID_BUT_TU:
		m_tftype = TFtype_TU;
		break;
	}
	return 0;
}
int TFMapMask::SetnBrush(int nbrush)//设置画刷大小。
{
	m_nbrush = nbrush;
	return 0;
}

int TFMapMask::ReadtfMap(char *name, char *guanqia, TFMap *ptfMap, char *szcmd)
{
	strcpy(name,m_name);
	strcpy(guanqia, m_guanqia);
	strcpy( szcmd,m_szcmd);
	ptfMap->m_nw = m_tfmap.m_nw;
	ptfMap->m_nh = m_tfmap.m_nh;
	for (int x = 0; x < m_tfmap.m_nw;x++)
		for (int y = 0; y < m_tfmap.m_nh; y++)
		{
			ptfMap->tf[x][y] = m_tfmap.tf[x][y];
		}
	return 0;
}

int TFMapMask::ReDraw()
{
	m_tfmap.ReDraw(m_hWnd,m_hdc);
	return 0;
}

int TFMapMask::OutDraw(HDC hdc,int x,int y)
{
	BitBlt(hdc, x, y, m_tfmap.m_nw * 4+1, m_tfmap.m_nh * 4+1, m_hdc, x, y, SRCCOPY);
	
	return 0;
}


int TFMapMask::PanduanMap()
{
	m_tfmap.m_nw;
	m_tfmap.m_nh;
	//m_tfmap.tf[][];
	//需要寻路算法。

	//左手定则.//速度方向的左边可以走则转向。到顶后反向
	//左转向规则.x1=y;y1=-x;
	return 0;
}

POINTS xun(POINTS&p ,POINTS topoint)
{
	


	return p;
}
