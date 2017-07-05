#ifndef  __TFMAPMASK__
#define	 __TFMAPMASK__
#include "TFMap.h"
#include "GamesLevels.h"


#define ID_BUT_KONG		WM_USER+1
#define ID_BUT_ZHEBI	WM_USER+2
#define ID_BUT_TU		WM_USER+3

static char tfcode[] = "��������Կ";//��Կ
BOOL CALLBACK DlgMapMask(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


//��ͼ�༭��
class TFMapMask
{
public:
	TFMapMask();
	~TFMapMask();
	int InDakai(void* data, int len);//�ַ���ָ�����������'\n'
	int EnCode(char* str, int len);//�����ַ���
	int DeCode(char* str, int len);//�����ַ���
	int InMapStr(char*str, int len);
	int LoadTFMap(char*path, int ng);
	int SaveTFMap(char* name, char*guanqia, char*juqing, int jlen, char*path);
	int SaveTFMap(void* str, TCHAR*name, int len);//�����ͼ���ļ�
	int OnDlgCreateMap(HWND hPrentWnd);//�򿪱༭����
	int OnCreateMap(HWND hWnd);
	int OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnMouseLeave(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int OnButton(UINT nID);
	int OnPaint(HDC hdc, LPRECT rect);
	int ReDraw();
	int ReDrawCE();//����
	int DrawOne(int x, int y, TFtype type);//�������
	int OnDraw();
	int SetnBrush(int nbrush);//���û�ˢ��С��
	int ReadtfMap(char *name, char *guanqia, TFMap *ptfMap, char *szcmd);//��ȡ��ǰ���������
	int OutDraw(HDC hdc, int x, int y);
	int GetButtonX()
	{
		return m_tfmap.m_nw * 4;
	}
	int PanduanMap();
private:
	HBITMAP m_hbitmap;//����
	HDC		m_hdc;
	bool m_bLdown;
	bool m_bMouseTrack;
	//bool m_bInitem;
	int m_tfbrush;//��ǵĻ�ˢ
	TFMap m_tfmap;
	int m_nxuan;
	TFtype m_tftype;
	int m_nbrush;//��ˢ��С
	char m_name[64];
	char m_guanqia[8];
	char m_szcmd[1024];
public:
	int m_nduqu;
	HWND m_hWnd;

};

#endif