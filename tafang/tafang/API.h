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
unsigned __stdcall yanshiFreeRun(void*lp);//��ʱfree
unsigned int  yanshiFree(void*lp);
void InityanshiFree();
bool JudgeRectTo(const LPRECT r1, const LPRECT r2);//�ж����������Ƿ��ཻ
int BitmapToRect(HBITMAP hbitmap, HBITMAP hbitout, SIZE &s);


struct PointF
{
	int x;
	int y;
	int G;//G����ʾ�����A�ƶ���������ָ�������һ�� �ķѡ�
	int H;//H����ʾ��ָ���ķ����ƶ����յ�B��Ԥ�ƺķѡ�
	int F;//F=H+G
	bool btrue;//�Ƿ����,true��ʾ����ͨ��
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


//������ʹ��ʱ����Ҫ�ͷ� ����ĵ� ���ڴ�
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
	//�жϵ��Ƿ��ڱ���//�˴����ж��ڴ档�뱣֤ʹ�õĵ�ͼ�ڴ��ַδ�����ı�
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