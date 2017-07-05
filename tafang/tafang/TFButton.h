#ifndef   __TFBUTTON__
#define	  __TFBUTTON__
#define IDB_CESHI 1231
#include <list>
using namespace std;

//按钮绘图规则,W表示文字P表示图片，F表示圆角,B表示背景

#define BR_TYBack		0x0001	//透明背景
#define BR_TYFMin		0x0002	//小型圆角
#define BR_TYFMax		0x0004	//中型圆角.两个圆角开关同时打开，就是大型圆角
#define BR_TY_W			0x0008	//有文字
#define BR_TY_P			0x0010	//有前景

#define BR_TY_TY_1		0x0100	//以下为背景类型。当BR_TYBack未开启时生效
#define BR_TY_TY_2		0x0200	//
#define BR_TY_TY_3		0x0400	//
#define BR_TY_TY_4		0x0800	//

//#define BR_W0P1F0B0		0		//实现透明的
//#define BR_W1P0F1B1		1		//9,10//窗口大小会根据字符的长度调整
//#define BR_W0P1F1B1		2		//-1是有背景，有图，无文字，小号圆角，2和-1相同
//#define BR_W0P1F2B2		3		//-3是有背景，无图，有文字，中号圆角，
//#define BR_W0P1F2B3		4		//3
//#define BR_W1P0F2B3		5		//-2
//#define BR_W0P2F2B0		6		//-5  IDC_BUT_HeadPortrait
//#define BR_W2P0F2B0		7		//-6  IDPS_BITIMAGE
//#define BR_W1P0F0B0		8		//实现透明
//#define BR_W0P2F0B0		9

#define WM_SHOWText		WM_USER+1231
LRESULT CALLBACK CustomButtonWndProc(HWND, UINT, WPARAM, LPARAM);

struct DBUTTOND
{
	HBITMAP hbitmap;
	HBITMAP hbitmap1;
	HBITMAP hbitmap2;
	bool	bSel;
	int		nID;
	int		nWidth;
	int		nHeight;
	int		nw;
	int		nh;
	int		nBackType;
	HWND	hprent;
	HWND	hdbut;
	bool bLbdown;
	bool bInitem;
	DBUTTOND()
	{
		bLbdown = false;
		bInitem = false;
		bSel = false;
		hbitmap2 = NULL;
		hbitmap1 = NULL;
		hbitmap = NULL;
		nID = 0;
		nWidth = 32;
		nHeight = 32;
		nw = 30;
		nh = 30;
		nBackType = 0;
		hprent = NULL;
		hdbut = NULL;
	}
	DBUTTOND& operator =(DBUTTOND &temp)//赋值运算符重载函数  
	{
		this->bSel = temp.bSel;
		this->hbitmap = temp.hbitmap;
		this->hbitmap1 = temp.hbitmap1;
		this->hbitmap2 = temp.hbitmap2;
		//		this->hdc=temp.hdc;
		//		this->hbitmapM=temp.hbitmapM;
		this->nID = temp.nID;
		this->nWidth = temp.nWidth;
		this->nHeight = temp.nHeight;
		this->nw = temp.nw;
		this->nh = temp.nh;
		this->nBackType = temp.nBackType;
		this->hprent = temp.hprent;
		this->hdbut = temp.hdbut;
		return *this;
	}
};

class CDButtonD
{
public:
	CDButtonD();
	~CDButtonD();
	void OnPaint();
	void OnLButtonDown();
	void OnLButtonUp();
	void OnMouseMove();
	bool InitDButton();
	void OnDrawDButton(HWND hwnd, HDC hdc, bool bInitem, bool bLbdown);
	void OnReDraw(HWND hprent, HWND hwnd);
	HWND Create(HWND hprent, int x, int y, INT nID, TCHAR*text);
	HWND Create(HWND hprent, HINSTANCE hInstance, int x, int y, int cx, int cy, INT nID, LPCSTR lpname, TCHAR*text, int nBackType);
	HWND Create(HWND hprent, HINSTANCE hInstance, int x, int y, int cx, int cy, INT nID, HDC hdcButton, int rx, int ry, int rcx, int rcy, TCHAR*text, int nBackType, HDC backdc = NULL);
	void Delete(HWND hprent);//删除该窗口下的所有按钮资源
	void Delete(HWND hprent, int nID);
	int DrawD(HWND hwnd, HBITMAP hbitmap, int x, int y, int cx, int cy, HDC hdctop, int x1, int y1, int cx1, int cy1, HDC hdcbom, int x2, int y2, int cx2, int cy2, int type, int ng);
	int SetDraw(HWND hdu, bool bdraw);

	list <DBUTTOND> m_Dbutond;
	bool m_bbuttond;
	HWND m_hInitem;
	HWND m_hLDown;
private:	
	RECT m_rect;

	//可以多加几套按钮背景贴图

	HBITMAP HBIT_MOVE1;
	HBITMAP HBIT_DOWN1;
	HBITMAP HBIT_Default1;
	HBITMAP HBIT_MOVE2;
	HBITMAP HBIT_DOWN2;
	HBITMAP HBIT_Default2;
	HBITMAP HBIT_MOVE3;
	HBITMAP HBIT_DOWN3;
	HBITMAP HBIT_Default3;

	HBITMAP HBIT_BUTTON;
	HFONT m_hFont;
	HFONT m_hFont1;

	HBITMAP m_hbitmapM;
	HBITMAP m_hbitmap1;
	HBITMAP m_hbitmap2;
	HDC		m_hdcM; 
	HDC		m_hdc1;
	HDC		m_hdc2;
};

#endif