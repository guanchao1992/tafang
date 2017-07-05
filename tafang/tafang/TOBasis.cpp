#include "stdafx.h"
#include "TowerDefense.h"
#include "TOBasis.h"


TOBasis::TOBasis()
{

	m_bhdc = false;
	m_hdcM = CreateCompatibleDC(NULL);
	m_hdc1 = CreateCompatibleDC(NULL);
	m_hdc2 = CreateCompatibleDC(NULL);
	m_hbitM = CreateBitmap(200*2, 100, 1, 1, NULL);
	m_hbit1 = CreateBitmap(200*2, 100, 1, 32, NULL);
	m_hbit2 = CreateBitmap(200*2, 100, 1, 32, NULL);
	SelectObject(m_hdcM, m_hbitM);
	SelectObject(m_hdc1, m_hbit1);
	SelectObject(m_hdc2, m_hbit2);
	SetBkColor(m_hdcM, RGB(255, 255, 255));
}

TOBasis::~TOBasis()
{

	DeleteDC(m_hdcM);
	DeleteDC(m_hdc1);
	DeleteDC(m_hdc2);
	DeleteObject(m_hbitM);
	DeleteObject(m_hbit1);
	DeleteObject(m_hbit2);


}

int TOBasis::DrawAll(HDC hdc)
{
	return 0;
}
int TOBasis::DrawOne(HDC hdc, int x, int y, int type)
{
	HDC hms;
	int rx;
	int ry;
	if (type / 1000 == 1)
	{
		hms = HDC_TURRET;
		type = type % 1000;
		rx = type % 10 * 32;
		ry = type / 10 * 32;

	}
	else if (type / 1000 == 2)
	{ 
		hms = HDC_BULLET; 
		type = type % 1000;
		rx = type % 10 * 24;
		ry = type / 10 * 24;
	}
	else if (type / 1000 == 3)
	{
		hms = HDC_STUNT;
		type = type % 1000;
		rx = type % 10 * 48;
		ry = type / 10 * 48;
	}
	else
	{
		hms = HDC_Meastar;
		type = type % 1000;
		rx = type % 10 * 40;
		ry = type / 10 * 40;
	}
	//以下为透明贴图代码.底色为白色
	if (m_bhdc)//此处的作用是防止贴图错位
	{
		BitBlt(m_hdcM, 0, 0, 101, 101, hms, rx, ry, SRCCOPY);
		BitBlt(m_hdc1, 0, 0, 101, 101, m_hdcM, 0, 0, NOTSRCCOPY);
		BitBlt(m_hdc1, 0, 0, 101, 101, hms, rx, ry, SRCAND);//dc1是前景

		BitBlt(m_hdc2, 0, 0, 101, 101, m_hdcM, 0, 0, SRCCOPY);
		BitBlt(m_hdc2, 0, 0, 101, 101, hdc, x / 1000, y / 1000, SRCAND);//dc2是背景

		BitBlt(hdc, x / 1000 , y / 1000 , 101, 101, m_hdc1, 0, 0, SRCCOPY);
		BitBlt(hdc, x / 1000 , y / 1000 , 101, 101, m_hdc2, 0, 0, SRCPAINT);
		m_bhdc = false;
	}
	else
	{
		BitBlt(m_hdcM, 200, 0, 101, 101, hms, rx, ry, SRCCOPY);
		BitBlt(m_hdc1, 200, 0, 101, 101, m_hdcM, 200, 0, NOTSRCCOPY);
		BitBlt(m_hdc1, 200, 0, 101, 101, hms, rx, ry, SRCAND);//dc1是前景

		BitBlt(m_hdc2, 200, 0, 101, 101, m_hdcM, 200, 0, SRCCOPY);
		BitBlt(m_hdc2, 200, 0, 101, 101, hdc, x / 1000, y / 1000, SRCAND);//dc2是背景

		BitBlt(hdc, x / 1000 , y / 1000, 101, 101, m_hdc1, 200, 0, SRCCOPY);
		BitBlt(hdc, x / 1000 , y / 1000 , 101, 101, m_hdc2, 200, 0, SRCPAINT);
		m_bhdc = true;
	}
	return 0;
}

int TOBasis::Draw(HDC hdc, int x, int y, int cx, int cy, HDC hdctop,int rx,int ry)
{
	BitBlt(m_hdcM, 100, 0, cx, cy, hdctop, rx, ry, SRCCOPY);
	BitBlt(m_hdc1, 100, 0, cx, cy, m_hdcM, 100, 0, NOTSRCCOPY);
	BitBlt(m_hdc1, 100, 0, cx, cy, hdctop, rx, ry, SRCAND);//dc1是前景
	BitBlt(m_hdc2, 100, 0, cx, cy, m_hdcM, 100, 0, SRCCOPY);
	BitBlt(m_hdc2, 100, 0, cx, cy, hdc, x, y, SRCAND);//dc2是背景
	BitBlt(hdc, x, y, cx, cy, m_hdc1, 100, 0, SRCCOPY);
	BitBlt(hdc, x, y, cx, cy, m_hdc2, 100, 0, SRCPAINT);
	//m_bhdc = false;

	return 0;
}

//获取特定类型type在位图中的位置
void TOBasis::GetBasisRect(int type, LPRECT lr)
{
	lr->left = type % 1000 % 10;
	lr->top = type%1000 / 10;
	if (type / 1000==1)
	{
		lr->right = lr->left + 32;
		lr->bottom = lr->top + 32;
	}
	else if (type / 1000 == 1)
	{
		lr->right = lr->left + 24;
		lr->bottom = lr->top + 24;
	}
	else
	{
		lr->right = lr->left + 40;
		lr->bottom = lr->top + 40;
	}

}

//通过贴图，判断点所在位置是否为有效颜色（不为白色）
bool TOBasis::InBasisHBit(int x, int y,int type)
{
	if (x<-32 || x>32 || y<-32 || y>32)return false;
	HBITMAP hb;
	if (type / 1000 == 1)hb = HBITMAP_TURRET;
	else if (type / 1000 == 2)hb = HBITMAP_BULLET;
	else if (type / 1000 == 3)hb = HBITMAP_STUNT;
	else hb = HBITMAP_Meastar;
	UCHAR pby[400*400 * 4 + 1];//此处是图的宽×高
	DWORD dwsize = 0;
	RECT rect;
	GetBasisRect(type, &rect);
	dwsize = GetBitmapBits(HBITMAP_Meastar, 400*400 * 4, pby);
	int n = 400 * (rect.top + y) + rect.left + x;
	if (pby[n] == 255 && pby[n+1] == 255 && pby[n+2] == 255)//此时表示所选位置是白色
	{
		return false;
	}
	else
	{
		return true;
	}

	return false;
}

int TOBasis::Xunlu(int *x,int *y,int endx,int endy,int speed)
{

	float nl = sqrt((float)endx*endx + (float)endy*endy);//两点距离	
	if (nl<speed / 100 * 1000)
	{
		//ms->x = ms->endx;
		//ms->y = ms->endy;
#if _DEBUG
		//SetEndPoint(ms, rand() % 400,rand() % 400,rand()%8+1);
		//SetEndPoint(ms, rand() % 400,rand() % 400,4);
#endif
	}
	else
	{
		*x += (int)(endx / nl*speed / 100 * 1000);
		*y += (int)(endy / nl*speed / 100 * 1000);
	}
	return 0;
}

BasisList*TOBasis::CreateBasis()
{
	BasisList *ps = (BasisList*)malloc(sizeof(BasisList));
	//ps->ms = ms;
	//ps->Next = NULL;
	if (m_headList== NULL)
	{
		m_headList = ps;
	}
	else
	{
		ps->Next = m_headList;
		m_headList = ps;
	}
	return ps;
}
//删除成员前执行的额外的操作
int TOBasis::DeleteOT(BasisList*bl)
{
	return 0;
}
//删除成员后执行的额外的操作
int TOBasis::DeleteOEnd(BasisList*bl)
{
	return 0;
}
//删除成员需要执行的额外的操作
bool TOBasis::DeleteOpanduan(BasisList*bl)
{
	return true;
}

void TOBasis::DeleteBasisAll(BasisList* head, TOBasis*b)
{
	while (head->Next!=head)
	{	
		b->DeleteBasis(head->Next, head, b, false, TOBasis::DeleteOtherT, TOBasis::Deletepanduan, TOBasis::DeleteOtherOEnd);
	}
}

BasisList* TOBasis::DeleteBasis(BasisList*bll, BasisList* head, TOBasis*b,bool bjianc/*是否检测条件*/, int(*DelOT)(TOBasis* b, BasisList *bl), bool(*DelOpanduan)(TOBasis* tb, BasisList *bl), int(*DelOEnd)(TOBasis* b, BasisList *bl))
{
	DelOT(b,bll);
	BasisList* Temp = bll->Next;
	if (bll&&bll != head)//不允许删除链表头
	{
		if (bjianc||DelOpanduan(b, bll))
		m_nBasisList--;
		bll->Next->Pre = bll->Pre;
		bll->Pre->Next = bll->Next;
		//free(Temp);
		//DeleteOther(b, bll);
		DelOEnd(b,bll);
		yanshiFree(bll);
	}
	return Temp;
}
/*
void TOBasis::DeleteBasis(BasisList* dl)
{
	BasisList*Pre = NULL;
	BasisList*Temp = m_headList;
	while (Temp)
	{
		if (Temp==dl)//判断条件
		{
			if (Temp == m_headList)
			{
				m_headList =Temp->Next;
			}
			else
			{
				Pre->Next = Temp->Next;
			}
			//yanshiFree(Temp);
			free(Temp);
			break;
		}
		else
		{
			Pre = Temp;
			Temp = Temp->Next;
		}
	}
}*/