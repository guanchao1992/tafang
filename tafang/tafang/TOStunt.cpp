#include "stdafx.h"
#include "TOStunt.h"
#include "API.h"

unsigned __stdcall StuntRun(void*lp)//特技
{
	TOStunt*pStunt = (TOStunt*)lp;
	while (pStunt->GetInitStunt())
	{
		StuntList *Temp = (StuntList *)pStunt->m_headListStunt->Next;
		while (Temp != pStunt->m_headListStunt)
		{
			if (Temp->tj.nn >= Temp->tj.nm)
			{
				Temp=pStunt->DeleteStuntList(Temp);
			}
			else
			{
				Temp->tj.nn++;
				Temp = (StuntList *)Temp->Next;
			}
		}
		Sleep(80);
		while (g_bPause)Sleep(100);//暂停
	}
	return 0;
}

TOStunt::TOStunt()
{
	m_bInitStunt = false;
}


TOStunt::~TOStunt()
{
}


int TOStunt::InitStunt()
{
	m_bInitStunt = true;
	m_headListStunt = (StuntList*)malloc(sizeof(StuntList));
	m_headListStunt->Next = m_headListStunt;
	m_headListStunt->Pre = m_headListStunt;
	_beginthreadex(NULL, 0, &StuntRun, (void*)this, 0, &m_uStuntRunThreadID);
	return 0;
}
int TOStunt::ReleaseStunt()
{
	m_bInitStunt = false;
	//_endthreadex(m_uStuntRunThreadID);
	DeleteBasisAll(m_headListStunt, this);
	free(m_headListStunt);
	m_headListStunt = NULL;
	return 0;
}
StuntList*TOStunt::CreateStuntList(STUNT *tj)
{
	StuntList* tjl=(StuntList*)malloc(sizeof(StuntList));
	tjl->tj = *tj;
	tjl->Next = m_headListStunt;
	tjl->Pre = m_headListStunt->Pre;
	m_headListStunt->Pre->Next = tjl;
	m_headListStunt->Pre = tjl;

	return tjl;
}
int TOStunt::DeleteOT(BasisList*bl)//删除成员前执行的额外的操作
{
	return 0;
}
int TOStunt::DeleteOEnd(BasisList*bl)
{
	StuntList*pbl = ((StuntList*)bl);
	
	return 0;
}
bool TOStunt::DeleteOpanduan(BasisList*bl)//删除成员需要执行的额外的操作
{
	return true;
}
StuntList* TOStunt::DeleteStuntList(StuntList*bl)
{
	return (StuntList*)DeleteBasis(bl, m_headListStunt, this,true, TOBasis::DeleteOtherT, TOBasis::Deletepanduan, TOBasis::DeleteOtherOEnd);
}
/*
StuntList*TOStunt::DeleteStuntList(StuntList*tjl)
{
	StuntList*Temp = tjl->Next;
	tjl->Pre->Next = tjl->Next;
	tjl->Next->Pre = tjl->Pre;
	//yanshiFree(tjl);
	free(tjl);
	return Temp;
}*/
int TOStunt::DrawOne(HDC hdc, int x, int y, int type)
{

	type = type % 1000;
	int rx = type % 10 * 48;
	int ry = type / 10 * 48;
	//以下为透明贴图代码.底色为白色
	if (m_bhdc)//此处的作用是防止贴图错位
	{
		BitBlt(m_hdcM, 0, 0, 48, 48, HDC_STUNT, rx, ry, SRCCOPY);
		BitBlt(m_hdc1, 0, 0, 48, 48, m_hdcM, 0, 0, NOTSRCCOPY);
		BitBlt(m_hdc1, 0, 0, 48, 48, HDC_STUNT, rx, ry, SRCAND);//dc1是前景

		BitBlt(m_hdc2, 0, 0, 48, 48, m_hdcM, 0, 0, SRCCOPY);
		BitBlt(m_hdc2, 0, 0, 48, 48, hdc, x / 1000, y / 1000, SRCAND);//dc2是背景

		BitBlt(hdc, x / 1000, y / 1000, 48, 48, m_hdc1, 0, 0, SRCCOPY);
		BitBlt(hdc, x / 1000, y / 1000, 48, 48, m_hdc2, 0, 0, SRCPAINT);
		m_bhdc = false;
	}
	else
	{
		BitBlt(m_hdcM, 200, 0, 48, 48, HDC_STUNT, rx, ry, SRCCOPY);
		BitBlt(m_hdc1, 200, 0, 48, 48, m_hdcM, 200, 0, NOTSRCCOPY);
		BitBlt(m_hdc1, 200, 0, 48, 48, HDC_STUNT, rx, ry, SRCAND);//dc1是前景

		BitBlt(m_hdc2, 200, 0, 48, 48, m_hdcM, 200, 0, SRCCOPY);
		BitBlt(m_hdc2, 200, 0, 48, 48, hdc, x / 1000, y / 1000, SRCAND);//dc2是背景

		BitBlt(hdc, x / 1000, y / 1000, 48, 48, m_hdc1, 200, 0, SRCCOPY);
		BitBlt(hdc, x / 1000, y / 1000, 48, 48, m_hdc2, 200, 0, SRCPAINT);
		m_bhdc = true;
	}
	return 0;
}
int TOStunt::DrawALL(HDC hdc)
{
	StuntList *Temp = (StuntList *)m_headListStunt->Next;
	while (Temp != m_headListStunt)
	{
		if (Temp->tj.nn < Temp->tj.nm)
			DrawOne(hdc, Temp->tj.x - 24000, Temp->tj.y - 24000, Temp->tj.type * 10 + Temp->tj.nn + 3000);
		Temp = (StuntList *)Temp->Next;
	}
	return 0;
}

int TOStunt::Baozha(int x, int y, int type)
{	
	
	STUNT tj;
	tj.x = x;
	tj.y = y;
	tj.cx = 48;
	tj.cy = 48;
	tj.nm = 10;//贴图个数
	tj.nn = 0;
	tj.type = type;

	 switch (type)
	 {
	 case STUNT_BAOZHA:
		 tj.nm = 10;
	 case STUNT_JIZHONG:
		 tj.nm = 3;
	 }
	CreateStuntList(&tj);
	return 0;
}