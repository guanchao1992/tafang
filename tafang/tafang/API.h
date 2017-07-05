#ifndef   __API__
#define	  __API__

#include "resource.h"
#include "TowerDefense.h"
#include <process.h>
template<typename T>

//T jueduizhi(T a);

T jueduizhi(T a)
{
	return a < 0 ? -a : a;
}
//unsigned int jueduizhi(int a)
//{
//	return a < 0 ? -a : a;
//}

//unsigned int jueduizhi(int a);
unsigned int findstr(const char *buffer, int len, const char*str);
unsigned __stdcall yanshiFreeRun(void*lp);//延时free
unsigned int  yanshiFree(void*lp);
void InityanshiFree();
bool JudgeRectTo(const LPRECT r1, const LPRECT r2);//判断两个矩形是否相交
int BitmapToRect(HBITMAP hbitmap, HBITMAP hbitout, SIZE &s);


struct PointF
{
	int x;
	int y;
	int G;//G：表示从起点A移动到网络上指定方格的一点 耗费。
	int H;//H：表示从指定的方格移动到终点B的预计耗费。
	int F;//F=H+G
	bool btrue;//是否堵塞,true表示可以通行
	PointF*Pre;
	PointF()
	{
		x = 0;
		y = 0;
		G = 0;
		H = 0;
		F = 0;
		btrue = true;
		Pre = NULL;
	}
};

struct PointFP
{
	PointF *pf;
	PointFP *Next;
	PointFP *Pre;
};

//int xunluA(PointF**pmap, int w, int h, POINTS p1, POINTS p2, POINTS*point, int len);
int xunluA(PointF*pmap, int w, int h, POINTS p1, POINTS p2, POINTS*point, int len);


//链表在使用时，不要释放 传入的点 的内存
class PointFPList
{
public:
	PointFPList()
	{
		m_ListHead = (PointFP*)malloc(sizeof(PointFP));
		m_ListHead->Next = m_ListHead;
		m_ListHead->Pre = m_ListHead;
	}
	~PointFPList()
	{
		DeleteAll();
		free(m_ListHead);
	}
	PointFP *AddPointF(PointF *po)
	{
		PointFP *pfp = (PointFP*)malloc(sizeof(PointFP));
		pfp->pf = po;
		pfp->Next = m_ListHead->Next;
		pfp->Pre = m_ListHead;
		m_ListHead->Next->Pre = pfp;
		m_ListHead->Next = pfp;
		return pfp;
	}
	void DeletePointF(PointF*po)
	{
		PointFP *Temp = m_ListHead->Next;
		while (Temp != m_ListHead)
		{
			if (Temp->pf == po)
			{
				Temp->Next->Pre = Temp->Pre;
				Temp->Pre->Next = Temp->Next;
				free(Temp);
				return;
			}
			Temp = Temp->Next;
		}
	}
	void DeleteAll()
	{
		PointFP *Temp = m_ListHead->Next;
		PointFP *Next;
		while (Temp != m_ListHead)
		{
			Next = Temp->Next;
			free(Temp);
			Temp = Next;
		}
	}
	//判断点是否在表中//此处是判断内存。请保证使用的地图内存地址未发生改变
	bool InList(PointF*po)
	{
		PointFP *Temp = m_ListHead->Next;
		while (Temp != m_ListHead)
		{
			if (Temp->pf == po)
			{
				return true;
			}
			Temp = Temp->Next;
		}
		return false;
	}
	PointF* GetminF()
	{
		PointF *ref = NULL;
		PointFP *Temp = m_ListHead->Next;
		int nf = 1000000;
		while (Temp != m_ListHead)
		{
			if (nf>Temp->pf->F)
			{
				nf = Temp->pf->F;
				ref = Temp->pf;
			}
			Temp = Temp->Next;
		}
		return ref;
	}

private:
	PointFP *m_ListHead;
};




#endif