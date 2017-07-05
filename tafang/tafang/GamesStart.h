#ifndef __GAMESSTART__
#define __GAMESSTART__
#include "TFMapMask.h"
LRESULT CALLBACK GamesWndProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);

struct AboutTextList
{
	char buffer[51];
	int y;//y轴坐标
	struct AboutTextList *Next;
	struct AboutTextList *Pre;
};
class GamesStart
{
public :
	static GamesStart *Getthis()
	{
		return m_pGamethis;
	}
public:
	GamesStart();
	~GamesStart();
	int InitGameStart();
	int ReleaseGameStart();
	int DrawStart();
	int DrawAbout(HDC hdc);
	int ShowStart(HWND hWnd);
	int ReShowStart()
	{
		if (m_hWnd)
			return ShowStart(m_hWnd);
		else
			return 0;
	}
	int CloseStart();
	int ReDarwBk();
	int OnPoint(HDC hdc);
	int OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseLeave(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnCommand(int nID);
	int Open();//打开基础按钮
	int OpenMake();//打开设置画面
	int OpenComplile();//打开地图编辑模式
	int OpenAbout();//打开关于
	int Close();
	int CloseMake();//关闭设置画面
	int CloseComplile();//关闭地图编辑模式
	int CloseAbout();//关闭关于
	int OnPointT(HDC hdc, LPRECT rect);
	int ShowStartButton(int nS);
	HDC GetHDCbk()
	{
		return m_hdc;
	}
	int GetType()
	{
		return m_ntype;
	}
	int AddAboutText(char*buffer,int len);
	AboutTextList*CreateAboutTextList(char*buffer,int len);
	AboutTextList*DeleteAboutTextList(AboutTextList*);
	AboutTextList*DeleteAboutTextListAll();
	AboutTextList*GetheadAboutTextList()
	{
		return m_headAboutTextList;
	}
public:
	HWND m_hWnd;
	HDC GetHDCtr()
	{
		return m_hdctr;
	}
	HDC GetHDCt()
	{
		return m_hdct;
	}
	HDC GetHDCa()
	{
		return m_hdca;
	}
	HWND m_hWndChild;

private:
	HFONT m_hFont;
	HDC		m_hdc;
	HBITMAP m_hbitmap;
	HDC m_hdca;//显示关于
	HBITMAP m_hbitmapa;
	HDC		m_hdct;//窗口显示缓冲
	HBITMAP m_hbitmapt;
	HDC		m_hdctr;//背景。不能随便修改
	HBITMAP m_hbitmaptr;
	int m_ntype;//打开那个界面
	TFMapMask* m_ptfm;
	static GamesStart* m_pGamethis;
	AboutTextList*m_headAboutTextList;
	int m_itAboutTextList;
	unsigned int m_uGamesAboutRunThreadID;
	unsigned int m_uGamesStartDrawRunThreadID;
};
#endif