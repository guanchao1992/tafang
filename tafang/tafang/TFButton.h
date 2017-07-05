#ifndef   __TFBUTTON__
#define	  __TFBUTTON__
#define IDB_CESHI 1231
#include <list>
using namespace std;

//��ť��ͼ����,W��ʾ����P��ʾͼƬ��F��ʾԲ��,B��ʾ����

#define BR_TYBack		0x0001	//͸������
#define BR_TYFMin		0x0002	//С��Բ��
#define BR_TYFMax		0x0004	//����Բ��.����Բ�ǿ���ͬʱ�򿪣����Ǵ���Բ��
#define BR_TY_W			0x0008	//������
#define BR_TY_P			0x0010	//��ǰ��

#define BR_TY_TY_1		0x0100	//����Ϊ�������͡���BR_TYBackδ����ʱ��Ч
#define BR_TY_TY_2		0x0200	//
#define BR_TY_TY_3		0x0400	//
#define BR_TY_TY_4		0x0800	//

//#define BR_W0P1F0B0		0		//ʵ��͸����
//#define BR_W1P0F1B1		1		//9,10//���ڴ�С������ַ��ĳ��ȵ���
//#define BR_W0P1F1B1		2		//-1���б�������ͼ�������֣�С��Բ�ǣ�2��-1��ͬ
//#define BR_W0P1F2B2		3		//-3���б�������ͼ�������֣��к�Բ�ǣ�
//#define BR_W0P1F2B3		4		//3
//#define BR_W1P0F2B3		5		//-2
//#define BR_W0P2F2B0		6		//-5  IDC_BUT_HeadPortrait
//#define BR_W2P0F2B0		7		//-6  IDPS_BITIMAGE
//#define BR_W1P0F0B0		8		//ʵ��͸��
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
	DBUTTOND& operator =(DBUTTOND &temp)//��ֵ��������غ���  
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
	void Delete(HWND hprent);//ɾ���ô����µ����а�ť��Դ
	void Delete(HWND hprent, int nID);
	int DrawD(HWND hwnd, HBITMAP hbitmap, int x, int y, int cx, int cy, HDC hdctop, int x1, int y1, int cx1, int cy1, HDC hdcbom, int x2, int y2, int cx2, int cy2, int type, int ng);
	int SetDraw(HWND hdu, bool bdraw);

	list <DBUTTOND> m_Dbutond;
	bool m_bbuttond;
	HWND m_hInitem;
	HWND m_hLDown;
private:	
	RECT m_rect;

	//���Զ�Ӽ��װ�ť������ͼ

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