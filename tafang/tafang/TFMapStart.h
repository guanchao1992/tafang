#ifndef __TFMAPSTART__
#define	__TFMAPSTART__

#include "stdio.h"
#include "TFMapMask.h"
#include "TOMeastar.h"
#include "TOTurret.h"
#include "TOStunt.h"
#include "GamesLevels.h"




class TFMapStart
{
public:
	TFMapStart();
	~TFMapStart();
	int InviStart(HWND hWnd);
	int ReleaseMapStart();
	int ReadnGMap(int nG);
	int OnPaint(HDC hdc);
	int OnDraw(HDC hdc);
	inline HDC GetHDC()
	{
		return m_hdc;
	}
	int GetnFPS()
	{
		m_nfps = m_ifps;
		m_ifps = 0;
		sprintf(m_strfps, "#FPS:%d#", m_nfps);
		return m_nfps;
	}
	int OnLButtonDown(POINTS point);
	int OnLButtonUp(POINTS point);
	int OnMouseMove(POINTS point);
	int OnRButtonDown(POINTS point);
	int OnRButtonUp(POINTS point);
	int OnMouseLever();
	int OnCommand(int ID);
	int ADC(HDC hdc, TurretList*, MeastarList*);//����һ�Σ����û�ͼ
	int SelectTurretType(int type);//ѡ�е���������
	int DrawOther(int DrawOne(TOBasis*tb, HDC, int, int, int));
	int DrawTop(int t);
	int ShowTop(HDC hdc);
	//int DrawOne(HDC hdc, int x, int y, int type);
	int IsTrueRect(const LPRECT rect);
	int SetLeftTop(HDC hdcbk, int x, int y);
	static int DrawOne(TOBasis*tb, HDC hdc, int x, int y, int type)
	{
		tb->DrawOne(hdc, x, y, type);
		return 0;
	}
	
private:
	unsigned int m_uDrawRunThreadID;//����ID
	int m_nG;//��ǰ�ؿ�
	char m_name[64];//�ؿ���
	char m_guanqia[8];
	TFMap m_Map;
	char m_szcmd[1024];
	HBITMAP m_hbitmap;
	HDC m_hdc;
	HDC m_hdcT;//������Ļ����ǰ����ʾ
	HBITMAP m_hbitmapT;
	unsigned int m_tTop;//��ʾǰ������ʽ����λ��ʾ���ͣ���λ��ʾ��ͼ����
	POINTS m_lefttop;//��ʾͼ�����Ͻǵ�λ��
	POINTS m_pointCursor;
	bool m_bLDown;
	bool m_bRDown;
	bool m__bMouseTrack;
	int m_iselecttype;
	HDC		m_hdcTurretType;//ѡ�е�ģ��
	HBITMAP m_hbitmapTurretType;
	bool m_bTurretType;
	bool m_bStart;
public:	
	char m_strfps[50];//������ʾ
	int m_ifps;//���ڼ���
	int m_nfps;//����֡��
	HWND m_hWnd;
	TOTurret m_Turret;
	TOMeastar m_Meastar;
	TOBullet m_Bullet;
	TFMapMask m_tfmm;
	GamesLevels m_gamesLevel;

	TOStunt m_Stunt;
	Turret m_SelectTurret;
};

#endif