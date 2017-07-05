#include "stdafx.h"
#include "TOBullet.h"
#include "math.h"


unsigned __stdcall BulletMoveRun(void*lp)//移动
{
	TOBullet*pBullet = (TOBullet*)lp;
	while (pBullet->GetInitBullet())
	{
		BulletList *Temp = (BulletList *)pBullet->m_headListBullet->Next;
		while (Temp != pBullet->m_headListBullet)
		{
			//pMeas->Xunlu1(&Temp->ms);
			Temp = pBullet->Xunlu(Temp);
			// = Temp->Next;
		}
		Sleep(20);
		while (g_bPause)Sleep(100);//暂停
	}
	return 0;
}

TOBullet::TOBullet()
{
	m_bInitBullet = false;
}

TOBullet::~TOBullet()
{

}

int TOBullet::InitBullet(GamesLevels* pgame, MeastarList*head,TOStunt *Stunt)
{
	m_bInitBullet = true;
	m_pgameslevels = pgame;
	m_pMeastarhead = head;
	m_pStunt = Stunt;
	m_headListBullet = (BulletList*)malloc(sizeof(BulletList));
	m_headListBullet->Pre = (BasisList*)m_headListBullet;
	m_headListBullet->Next = (BasisList*)m_headListBullet;

	_beginthreadex(NULL, 0, &BulletMoveRun, (void*)this, 0, &m_uBulletMoveRunThreadID);

	return 0;
}

int TOBullet::ReleaseBullet()
{
	m_bInitBullet = false;
	//_endthreadex(m_uBulletMoveRunThreadID);
	DeleteBasisAll(m_headListBullet, this);
	yanshiFree(m_headListBullet);
	m_pgameslevels = NULL;
	m_pMeastarhead = NULL;
	m_pStunt = NULL;
	return 0;
}

int TOBullet::DrawAll(HDC hdc)
{
	BulletList *Temp = (BulletList *)m_headListBullet->Next;
	while (Temp != m_headListBullet)
	{
		DrawOne(hdc, Temp->bl.x - 12000, Temp->bl.y - 12000, Temp->bl.type);
		Temp = (BulletList *)Temp->Next;
	}
	return 0;
}
int TOBullet::DrawOne(HDC hdc, int x, int y, int type)
{
	type = type % 1000;
	int rx = type % 10 * 24;
	int ry = type / 10 * 24;
	//以下为透明贴图代码.底色为白色
	if (m_bhdc)//此处的作用是防止贴图错位
	{
		BitBlt(m_hdcM, 0, 0, 24, 24, HDC_BULLET, rx, ry, SRCCOPY);
		BitBlt(m_hdc1, 0, 0, 24, 24, m_hdcM, 0, 0, NOTSRCCOPY);
		BitBlt(m_hdc1, 0, 0, 24, 24, HDC_BULLET, rx, ry, SRCAND);//dc1是前景

		BitBlt(m_hdc2, 0, 0, 24, 24, m_hdcM, 0, 0, SRCCOPY);
		BitBlt(m_hdc2, 0, 0, 24, 24, hdc, x / 1000, y / 1000, SRCAND);//dc2是背景

		BitBlt(hdc, x / 1000, y / 1000, 24, 24, m_hdc1, 0, 0, SRCCOPY);
		BitBlt(hdc, x / 1000, y / 1000, 24, 24, m_hdc2, 0, 0, SRCPAINT);
		m_bhdc = false;
	}
	else
	{
		BitBlt(m_hdcM, 200, 0, 24, 24, HDC_BULLET, rx, ry, SRCCOPY);
		BitBlt(m_hdc1, 200, 0, 24, 24, m_hdcM, 200, 0, NOTSRCCOPY);
		BitBlt(m_hdc1, 200, 0, 24, 24, HDC_BULLET, rx, ry, SRCAND);//dc1是前景

		BitBlt(m_hdc2, 200, 0, 24, 24, m_hdcM, 200, 0, SRCCOPY);
		BitBlt(m_hdc2, 200, 0, 24, 24, hdc, x / 1000, y / 1000, SRCAND);//dc2是背景

		BitBlt(hdc, x / 1000, y / 1000, 24, 24, m_hdc1, 200, 0, SRCCOPY);
		BitBlt(hdc, x / 1000, y / 1000, 24, 24, m_hdc2, 200, 0, SRCPAINT);
		m_bhdc = true;
	}
	return 0;
}

BulletList* TOBullet::Xunlu(BulletList *bl)
{
	if (bl->bl.target)
	{
		bl->bl.endx = (PMeastar(bl->bl.target))->x;
		bl->bl.endy = (PMeastar(bl->bl.target))->y;
	}
	BulletList *Temp = (BulletList *)bl->Next;
	float nl = sqrt((float)(bl->bl.endx - bl->bl.x)*(bl->bl.endx - bl->bl.x) +
		(float)(bl->bl.endy - bl->bl.y)*(bl->bl.endy - bl->bl.y));//两点距离	
	if (nl<bl->bl.speed* g_beilv / 100 * 1000)
	{
		bl->bl.x = bl->bl.endx;
		bl->bl.y = bl->bl.endy;
		//if (bl->bl.target)
		AttackADC(&bl->bl);
			//(PMeastar(bl->bl.target))->left -= bl->bl.ADO;
		DeleteBullet(bl);
		return Temp;
	}
	else
	{
		bl->bl.x += (int)((bl->bl.endx - bl->bl.x) / nl*bl->bl.speed* g_beilv / 100 * 1000);
		bl->bl.y += (int)((bl->bl.endy - bl->bl.y) / nl*bl->bl.speed* g_beilv / 100 * 1000);
	}
	return Temp;
}

BulletList* TOBullet::CreateBullet(const Bullet*bl)
{
	BulletList *ps = (BulletList*)malloc(sizeof(BulletList));
	m_nBasisList++;
	ps->bl = *bl;
	ps->bl.type += 2000;
	ps->Next = NULL;
	if (ps->bl.target)
	{
		(PMeastar(ps->bl.target))->beida++;
	}
	if (m_headListBullet == NULL)
	{
		m_headListBullet = ps;
	}
	else
	{
		ps->Next = m_headListBullet;
		ps->Pre = m_headListBullet->Pre;
		m_headListBullet->Pre->Next = ps;
		m_headListBullet->Pre = ps;
	}
	return ps;
}
int TOBullet::DeleteOT(BasisList*bl)//删除成员前执行的额外的操作
{
	return 0;
}
int TOBullet::DeleteOEnd(BasisList*bl)
{
	BulletList*pbl = ((BulletList*)bl);
	if (pbl->bl.target)
	{
		(PMeastar(pbl->bl.target))->beida--;
	}
	return 0;
}
bool TOBullet::DeleteOpanduan(BasisList*bl)//删除成员需要执行的额外的操作
{
	return true;
}

BulletList* TOBullet::DeleteBullet(BulletList*bl)
{
	return (BulletList*)DeleteBasis(bl, m_headListBullet, this,true, TOBasis::DeleteOtherT, TOBasis::Deletepanduan, TOBasis::DeleteOtherOEnd);
}
/*
BulletList* TOBullet::DeleteBullet(BulletList*bll)
{
	BulletList* Temp = bll->Next;
	if (bll&&bll!=m_headListBullet)//不允许删除链表头
	{	
		m_nBasisList--;
		bll->Next->Pre = bll->Pre;
		bll->Pre->Next = bll->Next;
		//free(Temp);
		if (bll->bl.target)
		{
			(PMeastar(bll->bl.target))->beida--;
		}
		yanshiFree(bll);
	}
	return Temp;
}
*/
void TOBullet::DeleteBulletAll()
{
	BulletList*Temp = (BulletList *)m_headListBullet->Next;
	while (Temp != m_headListBullet)
	{
		DeleteBullet(Temp);
		Temp =(BulletList *) Temp->Next;
	}

}

//创建子弹
int TOBullet::Attack(const Bullet *bl)
{
	CreateBullet(bl);

	return 0;
}

int TOBullet::SetTarget(Bullet *bl, Basis*b)
{
	if (bl->target)
		(PMeastar(bl->target))->beida--;
	bl->target = b;
	if (bl->target)
		(PMeastar(bl->target))->beida++;
	return 0;
}

int TOBullet::AttackADC(Bullet *bl)
{
	//int np = (bl->AttackType & 0x000F) / BLT_Poison;//中毒等级
	//int ns = (bl->AttackType & 0x00F0) / BLT_SpeedDown;//减速等级
	//int ws = (bl->AttackType & 0x0F00) / BLT_ADOScope;//范围伤害
	BLTTYPE *p1 = bl->AttackType;
	BLTTYPE *p2 = NULL;
	if (bl->target)
	{
		p2 = (PMeastar(bl->target))->PersistentState;
		if (p1[0] > p2[0])p2[0] = p1[0];
		if (p1[1] > p2[1])p2[1] = p1[1];
		if (p1[2] > p2[2])p2[2] = p1[2];
		if (p1[3] > p2[3])p2[3] = p1[3];
		if (p1[4] > p2[4])p2[4] = p1[4];
	}
	if (bl->AttackType[4] == 0)
	{
		if (bl->target)
		{
			(PMeastar(bl->target))->life -= bl->ADO;
			plusTotalDamage(m_pgameslevels, bl->ADO);
			m_pStunt->Baozha(bl->target->x, bl->target->y,STUNT_JIZHONG);
		}

	}
	else
	{
		if (m_pMeastarhead)
		{
			//int ln = 0;
			PMeastarList Temp = (PMeastarList)m_pMeastarhead->Next;
			while (Temp != m_pMeastarhead)
			{
				if (Temp->ms.life > 0)
				{
					if (IsJuli(bl->x / 1000, bl->y / 1000, Temp->ms.x / 1000, Temp->ms.y / 1000, p1[4] * 4))
					{
						Temp->ms.life -= bl->ADO;// *(10 * p1[4] - ln) / 10 / p1[4];
						plusTotalDamage(m_pgameslevels, bl->ADO);
						p2 = Temp->ms.PersistentState;
						if (p1[0] > p2[0])p2[0] = p1[0];
						if (p1[1] > p2[1])p2[1] = p1[1];
						if (p1[2] > p2[2])p2[2] = p1[2];
						if (p1[3] > p2[3])p2[3] = p1[3];
					}
				}
				Temp = (PMeastarList)Temp->Next;
			}
		}
	}
	//m_pgameslevels->DrawGames();

	return 0;
}

bool TOBullet::IsJuli(int x1, int y1, int x2, int y2, int ln)
{
	if (x1-x2>ln||x2-x1>ln||y1-y2>ln||y2-y1>ln)
		return false;
	else
	{
		//此处判断两点距离
		if (float(x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) > ln*ln)
		{
			return false;
		}
		return true;
	}
}