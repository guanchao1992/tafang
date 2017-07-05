#ifndef 	__TOBASIS__
#define		__TOBASIS__
#include <process.h>
#include "API.h"
#include "GamesLevels.h"
typedef unsigned char BLTTYPE;

typedef struct Basis
{
	int x;//当前坐标。 具体坐标需要除以1000，作为中心点
	int y;//当前坐标。 具体坐标需要除以1000，作为中心点
	int type;//类型//除以1000来确定类型.0是Meastar.1是TURRET。2是BULLET
}BASIS;

typedef struct BasisList
{
	struct BasisList *Pre;
	struct BasisList *Next;
	BasisList()
	{
		Next = NULL;
		Pre = NULL;
	}
	~BasisList()
	{

	}
}*PBasisList;
//地图中各个元素的基础类
class TOBasis
{
public:
	TOBasis();
	virtual ~TOBasis();
public:
	BasisList*CreateBasis();
	void DeleteBasisAll(BasisList* head, TOBasis*b);//头部会被保留
	BasisList* DeleteBasis(BasisList*, BasisList* head, TOBasis*b, bool bjianc/*是否检测条件*/, int(*)(TOBasis* b, BasisList *bl), bool(*)(TOBasis* tb, BasisList *bl), int(*)(TOBasis* b, BasisList *bl));
	virtual int DeleteOT(BasisList*bl);//删除成员前执行的额外的操作
	virtual int DeleteOEnd(BasisList*bl);//删除成员后执行的额外的操作
	virtual bool DeleteOpanduan(BasisList*bl);//删除成员需要执行的额外的操作

	virtual int DrawOne(HDC hdc, int x, int y,int type);
	virtual int DrawAll(HDC hdc);
	static int DeleteOtherOEnd(TOBasis* b, BasisList *bl)//用于回掉
	{
		return b->DeleteOEnd(bl);
	}
	static int DeleteOtherT(TOBasis* b, BasisList *bl)//用于回掉
	{
		return b->DeleteOT(bl);
	}
	static bool Deletepanduan(TOBasis* tb, BasisList *bl)
	{
		return tb->DeleteOpanduan(bl);
	}
private:
	BasisList*m_headList;
	int m_nBasisList;//个数
protected:	
	int SetMoveTo();//
	int FindMoveTo(void *ms, int x, int y);//搜索移动路径
	void GetBasisRect(int type, LPRECT lr); 
	bool InBasisHBit(int x, int y, int type);
	int Draw(HDC hdc, int x, int y, int cx, int cy, HDC hdctop, int rx, int ry);
	int Xunlu(int *x, int *y, int endx, int endy, int speed);
	int Baozha(int type);
	bool m_bhdc;//设备的使用状态
	HDC		m_hdcM;	//蒙版
	HDC		m_hdc1;	//用于透明贴图
	HDC		m_hdc2;	//用于透明贴图
	HBITMAP m_hbitM;//蒙版
	HBITMAP m_hbit1;//用于透明贴图
	HBITMAP m_hbit2;//用于透明贴图
	HPEN m_hpen;
	HFONT m_hFont;
	GamesLevels* m_pgameslevels;
};

//void DrawBasis(TOBasis* b,HDC hdc)
//{
//	b->DrawOne(hdc, 0,0,0);
//}

#endif