#ifndef  __TFMAPMASK__
#define	 __TFMAPMASK__
#include "TFMap.h"
#include "GamesLevels.h"


#define ID_BUT_KONG		WM_USER+1
#define ID_BUT_ZHEBI	WM_USER+2
#define ID_BUT_TU		WM_USER+3

static char tfcode[] = "这里是密钥";//密钥
BOOL CALLBACK DlgMapMask(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


//地图编辑类
class TFMapMask
{
public:
	TFMapMask();
	~TFMapMask();
	int InDakai(void* data, int len);//字符串指针中允许包含'\n'
	int EnCode(char* str, int len);//加密字符串
	int DeCode(char* str, int len);//解密字符串
	int InMapStr(char*str, int len);
	int LoadTFMap(char*path, int ng);
	int SaveTFMap(char* name, char*guanqia, char*juqing, int jlen, char*path);
	int SaveTFMap(void* str, TCHAR*name, int len);//保存地图到文件
	int OnDlgCreateMap(HWND hPrentWnd);//打开编辑工具
	int OnCreateMap(HWND hWnd);
	int OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseLeave(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnButton(UINT nID);
	int OnPaint(HDC hdc, LPRECT rect);
	int ReDraw();
	int ReDrawCE();//清零
	int DrawOne(int x, int y, TFtype type);//定点绘制
	int OnDraw();
	int SetnBrush(int nbrush);//设置画刷大小。
	int ReadtfMap(char *name, char *guanqia, TFMap *ptfMap, char *szcmd);//读取当前保存的内容
	int OutDraw(HDC hdc, int x, int y);
	int GetButtonX()
	{
		return m_tfmap.m_nw * 4;
	}
	int PanduanMap();
private:
	HBITMAP m_hbitmap;//画布
	HDC		m_hdc;
	bool m_bLdown;
	bool m_bMouseTrack;
	//bool m_bInitem;
	int m_tfbrush;//标记的画刷
	TFMap m_tfmap;
	int m_nxuan;
	TFtype m_tftype;
	int m_nbrush;//画刷大小
	char m_name[64];
	char m_guanqia[8];
	char m_szcmd[1024];
public:
	int m_nduqu;
	HWND m_hWnd;

};

#endif