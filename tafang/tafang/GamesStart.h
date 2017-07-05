#ifndef __GAMESSTART__
#define __GAMESSTART__
#include "TFMapMask.h"
LRESULT CALLBACK GamesWndProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);

struct AboutTextList
{
	char buffer[51];
	int y;//y������
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
	int Open();//�򿪻�����ť
	int OpenMake();//�����û���
	int OpenComplile();//�򿪵�ͼ�༭ģʽ
	int OpenAbout();//�򿪹���
	int Close();
	int CloseMake();//�ر����û���
	int CloseComplile();//�رյ�ͼ�༭ģʽ
	int CloseAbout();//�رչ���
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
	HDC m_hdca;//��ʾ����
	HBITMAP m_hbitmapa;
	HDC		m_hdct;//������ʾ����
	HBITMAP m_hbitmapt;
	HDC		m_hdctr;//��������������޸�
	HBITMAP m_hbitmaptr;
	int m_ntype;//���Ǹ�����
	TFMapMask* m_ptfm;
	static GamesStart* m_pGamethis;
	AboutTextList*m_headAboutTextList;
	int m_itAboutTextList;
	unsigned int m_uGamesAboutRunThreadID;
	unsigned int m_uGamesStartDrawRunThreadID;
};
#endif