#ifndef   __TFMAP__
#define	  __TFMAP__
#include "TFmapBasis.h"

#define PM_W_MAX	200	//最大宽度
#define PM_H_MAX	200	//最大高度

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
	unsigned int m_nw;//此次表示的是横向的方格数
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
	int SetSize(UINT w, UINT h)//设置地图大小
	{
		if (w  > PM_W_MAX)m_nw = PM_W_MAX; else m_nw = w;
		if (h  > PM_H_MAX)m_nh = PM_H_MAX; else m_nh = h;
		return 0;
	}
	int ReTf(TFmapShelter*ptfs);//刷新地图区域
	int ReDraw(HWND hWnd, HDC hdc,int x=0,int y=0);//重新绘制
};

#endif