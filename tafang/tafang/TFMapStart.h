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
	int ADC(HDC hdc, TurretList*, MeastarList*);//攻击一次，调用绘图
	int SelectTurretType(int type);//选中的炮塔类型
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
	unsigned int m_uDrawRunThreadID;//进程ID
	int m_nG;//当前关卡
	char m_name[64];//关卡名
	char m_guanqia[8];
	TFMap m_Map;
	char m_szcmd[1024];
	HBITMAP m_hbitmap;
	HDC m_hdc;
	HDC m_hdcT;//会在屏幕的最前端显示
	HBITMAP m_hbitmapT;
	unsigned int m_tTop;//显示前景的样式。高位表示类型，低位表示贴图次数
	POINTS m_lefttop;//显示图像左上角的位置
	POINTS m_pointCursor;
	bool m_bLDown;
	bool m_bRDown;
	bool m__bMouseTrack;
	int m_iselecttype;
	HDC		m_hdcTurretType;//选中的模板
	HBITMAP m_hbitmapTurretType;
	bool m_bTurretType;
	bool m_bStart;
public:	
	char m_strfps[50];//用于显示
	int m_ifps;//用于计数
	int m_nfps;//保存帧数
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