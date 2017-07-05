#include "StdAfx.h"
#include "TFmapBasis.h"
#include "TowerDefense.h"

TFmapBasis::TFmapBasis(void)
{
	m_tfattribute=NULL;
	m_height=0;
	m_width=0;
	m_tfipos=0;
	m_hBKbitmap=NULL;	
	m_hbitmap=NULL;		
	m_hBKdc=NULL;		
	m_hdc=NULL;	

}

TFmapBasis::~TFmapBasis(void)
{
}

int TFmapBasis::InitInstance()//初始化地图类
{
	m_hbitmap = CreateBitmap(m_width, m_height, 1, 32, NULL);
	m_hdc = CreateCompatibleDC(NULL);
	SelectObject(m_hdc, m_hbitmap);
	return 0;
}

int TFmapBasis::setBkbitmap(HBITMAP hbitmap)
{
	if (m_hBKbitmap!=NULL)
	{
		DeleteObject(m_hBKbitmap);
		DeleteDC(m_hBKdc);
	}
	m_hBKbitmap=CreateBitmap(m_width,m_height,1,32,NULL);
	HDC dc = CreateCompatibleDC(NULL);
	m_hBKdc=CreateCompatibleDC(NULL);
	SelectObject(m_hBKdc, m_hBKbitmap);
	SelectObject(dc, hbitmap);
	BitBlt(m_hBKdc, 0, 0, m_width, m_height, dc, 0, 0, SRCCOPY);
	DeleteDC(dc);
	return 0;
}

int TFmapBasis::addShelter(TFmapShelter* type,int iPors)
{
	if (m_tfipos==0)
	{
		m_tfattribute->Next=type;
		type->Pre=m_tfattribute;
	}
	else
	{
		TFmapShelter *TempShelter=m_tfattribute;
		TFmapShelter *NextShelter;
		int io=0;
		while(io<m_tfipos&&io!=iPors&&TempShelter!=NULL)
		{
			NextShelter=TempShelter->Next;
			TempShelter=NextShelter;
			io++;
		}
		TempShelter->Next=type;
		type->Pre=TempShelter;
	}
	m_tfipos++;
	return 0;
}

int TFmapBasis::deleteShelter(int iPors)
{
	TFmapShelter *TempShelter=m_tfattribute;
	TFmapShelter *NextShelter;
	TFmapShelter *PreShelter;
	int io=0;
	while(io<m_tfipos&&io!=iPors&&TempShelter->Next!=NULL)
	{
		NextShelter=TempShelter->Next;
		TempShelter=NextShelter;
		io++;
	}
	PreShelter=TempShelter->Pre;
	delete TempShelter;
	PreShelter->Next=NULL;
	m_tfipos--;
	return 0;
}

int TFmapBasis::setTFAttribute(TFAttribute* type,int iPors)
{
	TFmapShelter *TempShelter=m_tfattribute;
	TFmapShelter *NextShelter;
	int io=0;
	while(io<m_tfipos&&io!=iPors&&TempShelter->Next!=NULL)
	{
		NextShelter=TempShelter->Next;
		TempShelter=NextShelter;
		io++;
	}
	TempShelter->type=*type;
	return 0;
}

int TFmapBasis::getTFAttribute(TFAttribute* type,int iPors)
{
	TFmapShelter *TempShelter=m_tfattribute;
	TFmapShelter *NextShelter;
	int io=0;
	while(io<m_tfipos&&io!=iPors&&TempShelter->Next!=NULL)
	{
		NextShelter=TempShelter->Next;
		TempShelter=NextShelter;
		io++;
	}
	*type=TempShelter->type;
	return 0;
}

int TFmapBasis::paint(HDC hdc)
{
	//此处绘制背景
	HDC memdc=CreateCompatibleDC(NULL);
	HBITMAP hbitmem=CreateBitmap(m_width,m_height,1,32,NULL);
	SelectObject(memdc,hbitmem);

	HDC hdcBKmap=CreateCompatibleDC(NULL);
	SelectObject(hdcBKmap,m_hBKbitmap);
	BitBlt(memdc,0,0,m_width,m_height,hdcBKmap,0,0,SRCCOPY);
	DeleteDC(hdcBKmap);

	for (int i=10;i<=0;i++)//按照层次先后绘制
	{
		TFmapShelter *TempShelter=m_tfattribute;
		TFmapShelter *NextShelter;
		int io=0;
		while(io<m_tfipos&&TempShelter->Next!=NULL)
		{
			NextShelter=TempShelter->Next;
			TempShelter=NextShelter;
			io++;
			//在此处绘制地图元素
			if (i==TempShelter->type.icheng)
			{
				switch (TempShelter->type.type)
				{
				case TYPE_KONG:break;//这个可以不绘制

				case TYPE_ZHEBI:
					BitBlt(m_hdc, TempShelter->type.x, TempShelter->type.y, 32, 32, HDC_Membit, 32 * 1, 0, SRCCOPY);
					break;
				case TYPE_TU:
					BitBlt(m_hdc, TempShelter->type.x, TempShelter->type.y, 32, 32, HDC_Membit, 32 * 2, 0, SRCCOPY);
					break;
				}
			}
		}
	}
	DeleteDC(memdc);
	return 0;
}
