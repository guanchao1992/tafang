#ifndef   __TFMAP__
#define	  __TFMAP__
#include "TFmapBasis.h"

#define PM_W_MAX	200	//�����
#define PM_H_MAX	200	//���߶�

class TFMap
{
public:
	TFMap()
	{
		m_nw = 100;
		m_nh = 100;
		ReMap();
	}
	~TFMap()
	{}
	TFMap&operator=(TFMap &p)
	{
		this->m_nh = p.m_nh;
		this->m_nw = p.m_nw;
		for (unsigned int i = 0; i < p.m_nw; i++)
		{
			for (unsigned int j = 0; j < p.m_nh; j++)
			{
				this->tf[i][j] = p.tf[i][j];
			}
		}
		return *this;
	}
	unsigned int m_nw;//�˴α�ʾ���Ǻ���ķ�����
	unsigned int m_nh;
	TFtype tf[PM_H_MAX][PM_W_MAX];
	int ReMap()
	{
		for (int i = 0; i < PM_W_MAX; i++)
		{
			for (int j = 0; j < PM_H_MAX; j++)
			{
				tf[i][j] = TFtype_KONG;
			}
		}
		return 0;
	}
	int SetSize(UINT w, UINT h)//���õ�ͼ��С
	{
		if (w  > PM_W_MAX)m_nw = PM_W_MAX; else m_nw = w;
		if (h  > PM_H_MAX)m_nh = PM_H_MAX; else m_nh = h;
		return 0;
	}
	int ReTf(TFmapShelter*ptfs);//ˢ�µ�ͼ����
	int ReDraw(HWND hWnd, HDC hdc,int x=0,int y=0);//���»���
};

#endif