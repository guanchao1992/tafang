#ifndef   __TOWERDEFENSE__
#define	  __TOWERDEFENSE__
#define _CRT_SECURE_NO_WARNINGS
#include "resource.h"
#include "TFButton.h"

#define ID_BUT_OK		10000+0
#define ID_BUT_COLSE	10000+1
#define ID_BUT_SAVE		10000+2
#define ID_BUT_LOAD		10000+3
#define ID_BUT_REDRWN	10000+4
#define ID_BUT_CE		10000+5

#define IDC_BUT_MapMask			WM_USER+1
#define IDC_BUT_AddMeastar		WM_USER+2
#define IDC_BUT_Start			WM_USER+3
#define IDC_BUT_Pause			WM_USER+4
#define IDC_BUT_Stop			WM_USER+5
#define IDC_BUT_BEILV1			WM_USER+6
#define IDC_BUT_BEILV2			WM_USER+7
#define IDC_BUT_BEILV3			WM_USER+8
#define IDC_BUT_BEILV4			WM_USER+9
#define IDC_BUT_BEILV5			WM_USER+10
#define IDC_BUT_WIN				WM_USER+11
#define IDC_BUT_DIED			WM_USER+12

#define IDC_BUT_GameStart		WM_USER+101
#define IDC_BUT_GameMake		WM_USER+102					 
#define	IDC_BUT_GameComplile	WM_USER+103							   
#define IDC_BUT_GameAbout		WM_USER+104									  
#define IDC_BUT_GameEdit		WM_USER+105									
											 
#define IDC_BUT_TURRET	(WM_USER+1000)


extern HINSTANCE g_hinst;
extern CDButtonD *g_dbutton;
extern bool g_bPause;
extern HBITMAP HBIT_Membit;
extern HDC		HDC_Membit;
extern HBITMAP HBITMAP_Meastar;
extern HDC		HDC_Meastar;
extern HBITMAP HBITMAP_TURRET;
extern HDC		HDC_TURRET;
extern HBITMAP HBITMAP_BULLET;
extern HDC		HDC_BULLET;
extern HBITMAP HBITMAP_STUNT;
extern HDC		HDC_STUNT;
extern HBITMAP HBITMAP_BUTTON;
extern HDC		HDC_BUTTON;
extern SIZE	g_sizewindow;
extern int g_beilv;
extern HWND g_hWnd;

int SetBeilv(int b);

#endif