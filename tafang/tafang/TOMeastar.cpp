#include "stdafx.h"
#include "TOMeastar.h"
#include "TowerDefense.h"
#include "API.h"
#include "math.h"
#include "GamesLevels.h"

unsigned __stdcall MeastarRun(void*lp)
{
	TOMeastar*pMeas = (TOMeastar*)lp;
	int idengt = 0;
	while (pMeas->GetInitMeastar())
	{
		
		MeastarList *Temp = (MeastarList *)pMeas->m_headListMeastar->Next;
		while (Temp != pMeas->m_headListMeastar)
		{
			pMeas->MeaState(&Temp->ms);
			//pMeas->Xunlu1(&Temp->ms);
			if (Temp->ms.life > 0)
				Temp = pMeas->Xunlu(Temp);
			else
				Temp=pMeas->DeleteMeastar(Temp);

			//Temp = Temp->Next;
		}
		Sleep(20);
		if (pMeas->GetParsing().num <= 0 && idengt >= 600 && pMeas->GetDengdai() <= 0)
		{
			if (pMeas->Chuguai() == 1)
			{
				//you win
				//TFMS_SHOW_WIN
				//g_ptfMapst->DrawTop(TFMS_SHOW_WIN);
				SendMessage(g_hWnd, WM_COMMAND, IDC_BUT_WIN, 0);
				g_bPause = true;
			}
			idengt = 0;
		}
		else if (pMeas->GetParsing().num >0&&pMeas->GetParsing().dengdai<idengt*20)
		{
			pMeas->GetParsing().num--;
			//pMeas->GetParsing().
			Meastar ms;
			ms.type = rand() % 6;
			ms.speed = pMeas->GetParsing().speed;//(rand() % 3+2) * 100;
			ms.life = pMeas->GetParsing().life;
			ms.lifeUp = ms.life;

			pMeas->CreateMeastar(&ms);
			idengt = 0;
			pMeas->GetDengdai() = 10000;
		}
		pMeas->GetDengdai() -= 25 *g_beilv;
		idengt += g_beilv;

		while (g_bPause)Sleep(100);//暂停
	}
	return 0;
}

TOMeastar::TOMeastar()
{
	m_headListMeastar = NULL;
	m_iMeastar = 0;
	m_plujing = NULL;
	m_bLoadPoint = NULL;
	m_pPointsHead=NULL;
	m_npoint = 0;
	m_bInitMeastar = false;
	m_ndengdai = 0;
	//m_hpen = CreatePen(PS_SOLID, 4, RGB(180, 0, 0));
}

TOMeastar::~TOMeastar()
{

}
MeastarList* TOMeastar::CreateMeastar(const Meastar *ms)
{
	MeastarList *ps = (MeastarList*)malloc(sizeof(MeastarList));
	ps->ms = *ms;
	SetEndPoint(&ps->ms, m_pPointsHead, -1);
	ps->Next = m_headListMeastar;
	ps->Pre = m_headListMeastar->Pre;
	m_headListMeastar->Pre->Next = ps;
	m_headListMeastar->Pre = ps;
	plusMeastar(m_pgameslevels,1);
	//m_pgameslevels->DrawGames();
	return ps;
}
int TOMeastar::DeleteOT(BasisList*bl)//删除成员前执行的额外的操作
{
	return 0;
}
int TOMeastar::DeleteOEnd(BasisList*bl)
{
	MeastarList* pml = (MeastarList*)bl;
	plusMeastar(m_pgameslevels, -1);
	if (pml->ms.life <= 0)
	{
		m_pStunt->Baozha(pml->ms.x, pml->ms.y, STUNT_BAOZHA);
		int gold = pml->ms.lifeUp / 100 * pml->ms.speed;
		plusGold(m_pgameslevels, gold);
	}
	else
	{
		if (plusLife(m_pgameslevels, -1) <=0)
		{
			//g_ptfMapst->DrawTop(TFMS_SHOW_DIED);
			SendMessage(g_hWnd, WM_COMMAND, IDC_BUT_DIED,0);
		}
	}
	//m_pgameslevels->DrawGames();
	return 0;
}

bool TOMeastar::DeleteOpanduan(BasisList*bl)//删除成员需要执行的额外的操作
{
	MeastarList* pml = (MeastarList*)bl;
	if (pml->ms.beida == 0 && pml->ms.life <= 0 || pml->ms.nb >= m_npoint)
		return true;
	return false;
}

MeastarList* TOMeastar::DeleteMeastar(MeastarList*bl)
{
	return (MeastarList*)DeleteBasis(bl, m_headListMeastar, this,true, TOBasis::DeleteOtherT, TOBasis::Deletepanduan, TOBasis::DeleteOtherOEnd);
}
int TOMeastar::DrawAll(HDC hdc)
{
	MeastarList *Temp = (MeastarList *)m_headListMeastar->Next;
	char buffer[256];
	int x = 0, y = 0;
	while (Temp != m_headListMeastar)
	{
		//sprintf(buffer, "%d:%d",Temp->ms.left,Temp->ms.beida);
		//TextOutA(hdc, (Temp->ms.x - 20000) / 1000, (Temp->ms.y - 20000) / 1000,
		//	buffer, strlen(buffer));
		if (Temp->ms.life > 0)
		{
			
			DrawOne(hdc, Temp->ms.x - 20000, Temp->ms.y - 20000, Temp->ms.type);
			Temp->ms.type+=10;
			if (Temp->ms.type % 100/10 ==9)
			{
				Temp->ms.type -= 100;
				Temp->ms.type += 10;
			}
			//显示血条
			x = (Temp->ms.x - 18000) / 1000;
			y = (Temp->ms.y - 20000) / 1000;
			Rectangle(hdc, x, y, x + 36, y + 5);
			BitBlt(hdc, x + 1, y + 1, 36 * Temp->ms.life / Temp->ms.lifeUp, 3,
				HDC_Meastar, 30, 400 - 5, SRCCOPY);
		}


		Temp = (MeastarList *)Temp->Next;
	}
	return 0;
}
/*
MeastarList* TOMeastar::DeleteMeastar(MeastarList* ml)
{
	MeastarList*Temp = ml->Next;
	if (ml->ms.beida == 0)
	{
		if (ml->ms.life <= 0||ml->ms.nb>=m_npoint)//判断条件
		{
			plusMeastar(m_pgameslevels, -1);
			if (ml->ms.life <= 0)
			{
				m_pStunt->Baozha(ml->ms.x, ml->ms.y, STUNT_BAOZHA);
			}
			else
			{
				plusLife(m_pgameslevels,-1 );	
			}
			m_pgameslevels->DrawGames();
			if (ml == m_headListMeastar)
			{
				m_headListMeastar = ml->Next;
			}
			else
			{
				ml->Next->Pre = ml->Pre;
				ml->Pre->Next = ml->Next;
			}
			//free(ml);
			yanshiFree(ml);
		}
	}
	return Temp;
}*/

int TOMeastar::InitMeastar(GamesLevels* pgame, TOStunt*ptj)
{
	m_bInitMeastar = true;
	m_pgameslevels = pgame;
	m_pStunt = ptj;
	m_headListMeastar = (MeastarList*)malloc(sizeof(MeastarList));

	m_headListMeastar->Next = m_headListMeastar;
	m_headListMeastar->Pre = m_headListMeastar;
	

	_beginthreadex(NULL, 0, &MeastarRun, (void*)this, 0, &m_uThreadMeastarRunID);
	return 0;
}
int TOMeastar::ReleaseMeastar()
{

	m_bInitMeastar = false;

	DeleteBasisAll(m_headListMeastar, this);
	free(m_headListMeastar);
	m_headListMeastar = NULL;
	m_pgameslevels = NULL;
	m_pStunt = NULL;
	m_dengdaiparsing.num = 0;
	return 0;
}
int TOMeastar::FindMoveTo(void *ms, int x, int y)//搜索移动路径
{
	//这里的点是真实的坐标

//	ms->x,ms->y;//point1
//	x, y;		//point2
//	ms->yansumove[0];//0101 0000 0x90
//	for (int i = 0; i < 80; i++)
//	{
//		ms->yansumove[i] =(MeastarMove)0x53;
//		ms->m_iyanshimove++;
//	}
	SetEndPoint((Meastar*)ms,x, y,-1);

	return 0;
}
int TOMeastar::DrawOne(HDC hdc, int x, int y, int type)
{

	type = type % 1000;
	int rx = type % 10 * 40;
	int ry = (type%100) / 10 * 40;
	
	//以下为透明贴图代码.底色为白色
	if (m_bhdc)//此处的作用是防止贴图错位
	{
		BitBlt(m_hdcM, 0, 0, 40, 40, HDC_Meastar, rx, ry, SRCCOPY);
		BitBlt(m_hdc1, 0, 0, 40, 40, m_hdcM, 0, 0, NOTSRCCOPY);
		BitBlt(m_hdc1, 0, 0, 40, 40, HDC_Meastar, rx, ry, SRCAND);//dc1是前景

		BitBlt(m_hdc2, 0, 0, 40, 40, m_hdcM, 0, 0, SRCCOPY);
		BitBlt(m_hdc2, 0, 0, 40, 40, hdc, x / 1000, y / 1000, SRCAND);//dc2是背景

		BitBlt(hdc, x / 1000, y / 1000, 40, 40, m_hdc1, 0, 0, SRCCOPY);
		BitBlt(hdc, x / 1000, y / 1000, 40, 40, m_hdc2, 0, 0, SRCPAINT);
		m_bhdc = false;
	}
	else
	{
		BitBlt(m_hdcM, 200, 0, 40, 40, HDC_Meastar, rx, ry, SRCCOPY);
		BitBlt(m_hdc1, 200, 0, 40, 40, m_hdcM, 200, 0, NOTSRCCOPY);
		BitBlt(m_hdc1, 200, 0, 40, 40, HDC_Meastar, rx, ry, SRCAND);//dc1是前景

		BitBlt(m_hdc2, 200, 0, 40, 40, m_hdcM, 200, 0, SRCCOPY);
		BitBlt(m_hdc2, 200, 0, 40, 40, hdc, x / 1000, y / 1000, SRCAND);//dc2是背景

		BitBlt(hdc, x / 1000, y / 1000, 40, 40, m_hdc1, 200, 0, SRCCOPY);
		BitBlt(hdc, x / 1000, y / 1000, 40, 40, m_hdc2, 200, 0, SRCPAINT);
		m_bhdc = true;
	}
	return 0;
}


int TOMeastar::SetAllEndPoint(int ex, int ey)
{
	MeastarList *Temp = (MeastarList *)m_headListMeastar->Next;
	while (Temp != m_headListMeastar)
	{
		SetEndPoint(&Temp->ms, ex, ey,600);
		Temp = (MeastarList *)Temp->Next;
	}
	return 0;
}
int TOMeastar::SetAllEndPoint(PointList* pPoint)
{
	MeastarList *Temp = (MeastarList *)m_headListMeastar->Next;
	while (Temp != m_headListMeastar)
	{
		SetEndPoint(&Temp->ms,pPoint, -1);
		Temp = (MeastarList *)Temp->Next;
	}
	return 0;
}
//设置直线移动路径
int TOMeastar::SetEndPoint(Meastar *ms, PointList* pPoint, int speed)
{
	if (pPoint)
	{
		if (pPoint == m_pPointsHead)
			ms->pPoint = m_pPointsHead->Pre;
		if (speed >= 0)
			ms->speed = speed;
		ms->endx = ms->pPoint->point.x * 4 * 1000;
		ms->endy = ms->pPoint->point.y * 4 * 1000;
		ms->fangxiang.x = ms->endx - ms->x;
		ms->fangxiang.y = ms->endy - ms->y;
	}
	
	return 0;
}
//设置直线移动路径
int TOMeastar::SetEndPoint(Meastar *ms,int ex, int ey,int speed)
{	
	if (speed>=0)
		ms->speed = speed;
	ms->endx = ex * 1000;
	ms->endy = ey * 1000;
	ms->fangxiang.x = ms->endx - ms->x;
	ms->fangxiang.y = ms->endy - ms->y;
	return 0;
}

#if 0
//只能寻找直线路径
int TOMeastar::Findlu1(Meastar *ms,int speed)
{
	int lw = (ms->endx - ms->x);
	int lh = (ms->endy - ms->y);
	float nl = sqrt((float)lh*lh + (float)lw*lw);
	int nw = lw * 1000 / nl;
	int nh = lh * 1000 / nl;

	int mw = 0, mh = 0;
	MeastarMove mom = (MeastarMove)0x00;//0000 0000
	for (int i = nl / 1000; i >= 0; i-=speed)
	{
		mom = (MeastarMove)0x00;//0000 0000
		mw += nw; mh += nh;
		if (mw>1000)
		{
			mw -= 1000;
			mom = (MeastarMove)((char)mom | 0x40);
		}
		else if (mw < -1000)
		{
			mw += 1000;
			mom = (MeastarMove)((char)mom | 0x80);
		}
		if (mh>1000)
		{
			mh -= 1000;
			mom = (MeastarMove)((char)mom | 0x10);
		}
		else if (mh < -1000)
		{
			mh += 1000;
			mom = (MeastarMove)((char)mom | 0x20);
		}
		mom = (MeastarMove)((char)mom | ((char)speed&0x0F));
		ms->yansumove[i] = mom;
	}
	ms->m_iyanshimove = nl / 1000/speed;
	return 0;
}
//寻路移动算法1
int TOMeastar::Xunlu1(Meastar *ms)
{
	int speed = 0;
	char m = 0;
	short lr = 0;//左右
	short tm = 0;//上下
	if (ms->m_iyanshimove > 0 && ms->m_iyanshimove < Meastar_MOVE_MAX)
	{
		//0000 0000
		speed = 0;
		--(ms->m_iyanshimove);
		m = (0xf0 & ms->yansumove[ms->m_iyanshimove]) >> 4;
		m & 0x08 ? lr-- : 0;
		m & 0x04 ? lr++ : 0;
		m & 0x02 ? tm-- : 0;
		m & 0x01 ? tm++ : 0;
		speed = (0x0f & ms->yansumove[ms->m_iyanshimove]);
		if (lr == 0 || tm == 0)
		{
			ms->x += lr*speed* g_beilv * 1000;
			ms->y += tm*speed* g_beilv * 1000;
		}
		else
		{
			ms->x += lr*speed* g_beilv * 717;
			ms->y += tm*speed* g_beilv * 717;
		}
	}
	if (ms->m_iyanshimove == 0)
	{
		int w = ms->x - ms->endx;
		int h = ms->y - ms->endy;
		if ((float)w*w + (float)h*h>1000 * 1000)
			SetEndPoint(ms, ms->endx / 1000, ms->endy / 1000);
		else
		{
			ms->x = ms->endx;
			ms->y = ms->endy;
#if _DEBUG
			int x = rand() % 400;
			int y = rand() % 400;
			SetEndPoint(ms, x, y);
#endif
		}
	}
	return 0;
}
#endif
int TOMeastar::Findlu2(Meastar *ms)
{	
	int lw = (ms->endx - ms->x);//横向
	int lh = (ms->endy - ms->y);//纵向
	ms->fangxiang.x = lw;
	ms->fangxiang.y = lh;
	return 0;
}


int TOMeastar::SetLujing(PointList *pointsHead, int pl)
{
	m_npoint = 0;
	if (m_pPointsHead)
	{
		//如果链表已存在，释放掉

		PointList* Temp = m_pPointsHead->Next;
		PointList* Next = Temp;
		m_pPointsHead->Next = m_pPointsHead;
		m_pPointsHead->Pre = m_pPointsHead;
		while (Temp != m_pPointsHead)
		{
			Next = Temp->Next;
			free(Temp);
			Temp = Next;
		}
		free(m_pPointsHead);
	}
	m_pPointsHead = pointsHead;
	m_npoint = pl;
	SetAllEndPoint(m_pPointsHead);
	return 0;
}
//寻路移动算法2
PMeastarList TOMeastar::Xunlu(PMeastarList pms)
{
	int ns;
	PMeastarList Temp = (MeastarList *)pms->Next;
	float nl = sqrt((float)pms->ms.fangxiang.x*pms->ms.fangxiang.x + (float)pms->ms.fangxiang.y*pms->ms.fangxiang.y);
	if (nl == 0)return Temp;
	//float ml = sqrt((float)(pms->ms.endx - pms->ms.x)*(pms->ms.endx - pms->ms.x) + (float)(pms->ms.endy - pms->ms.y)*(pms->ms.endy - pms->ms.y));
	if (pms->ms.PersistentState[3] != 0)
		ns = pms->ms.speed* g_beilv * 1000 * (255 - pms->ms.PersistentState[2]) / 255 / 100;
	else
		ns = pms->ms.speed* g_beilv * 1000 / 100;
	if (jueduizhi(pms->ms.x - pms->ms.endx) < pms->ms.speed * g_beilv * 10 && jueduizhi(pms->ms.y - pms->ms.endy) < pms->ms.speed* g_beilv * 10)
	{
		//距离终点很近
		//if (jueduizhi(pms->ms.x + (int)(pms->ms.fangxiang.x / nl*ns)* pms->ms.speed* g_beilv * 40 - pms->ms.endx) > pms->ms.speed* g_beilv * 10 || jueduizhi(pms->ms.y + (int)(pms->ms.fangxiang.y / nl*ns)* pms->ms.speed* g_beilv * 40 - pms->ms.endy) > pms->ms.speed * g_beilv * 10)
		{
			//在下一步将会远离
			//在此次重新设置终点位置
			if (pms->ms.nb < m_npoint&&pms->ms.pPoint)
			{
				pms->ms.pPoint = pms->ms.pPoint->Pre;
				if (pms->ms.pPoint != m_pPointsHead)
				{
					pms->ms.endx = pms->ms.pPoint->point.x*4*1000;
					pms->ms.endy = pms->ms.pPoint->point.y*4*1000;
					pms->ms.fangxiang.x = pms->ms.endx - pms->ms.x;
					pms->ms.fangxiang.y = pms->ms.endy - pms->ms.y;
				}
				pms->ms.nb++;
			}
			else
			{
				
				if (pms->ms.pPoint==NULL)
				{
					pms->ms.pPoint = m_pPointsHead;
				}
				else
				{
					//寻路到达终点。删除对象,
					DeleteMeastar(pms);
				}
			}

		}
	}

	pms->ms.x += (int)(pms->ms.fangxiang.x / nl*ns);
	pms->ms.y += (int)(pms->ms.fangxiang.y / nl*ns);
	
	if (pms->ms.x < -20 && pms->ms.fangxiang.x < 0)pms->ms.fangxiang.x = -pms->ms.fangxiang.x;
	else if (pms->ms.x > 420 * 1000 && pms->ms.fangxiang.x > 0)pms->ms.fangxiang.x = -pms->ms.fangxiang.x;
	if (pms->ms.y < 0 && pms->ms.fangxiang.y < 0)pms->ms.fangxiang.y = -pms->ms.fangxiang.y;
	else if (pms->ms.y > 420 * 1000 && pms->ms.fangxiang.y > 0)pms->ms.fangxiang.y = -pms->ms.fangxiang.y;
	//if (pms->ms.fangxiang.x == 0)pms->ms.fangxiang.x = rand();
	//if (pms->ms.fangxiang.y == 0)pms->ms.fangxiang.y = rand();
	return Temp;
}


int TOMeastar::OnLockPoint()
{
	while (m_bLoadPoint)
	{
		Sleep(100);
	}
	m_bLoadPoint = true;
	return 0;
}

int TOMeastar::OffLockPoint()
{
	m_bLoadPoint = false;
	return 0;
}

int TOMeastar::AddPoint(int x, int y)
{
	OnLockPoint();
	MeastarLUJING *newpoint=new MeastarLUJING;
	newpoint->point.x = x;
	newpoint->point.y = y;
	if (m_plujing != NULL)
	{
		delete m_plujing;
	}
	MeastarLUJING *Temp=m_plujing;
	MeastarLUJING *Pre;
	while (Temp)
	{
		Pre = Temp;
		Temp = Temp->Next;
	}
	Pre->Next = newpoint;
	newpoint->Pre = Pre;
	OffLockPoint();
	return 0;
}

int TOMeastar::DeleteAllPoint()
{
	OnLockPoint();
	m_plujing = NULL;
	MeastarLUJING *Temp = m_plujing;
	MeastarLUJING *Pre;
	while (Temp)
	{
		Pre = Temp;
		Temp = Temp->Next;
		delete Pre;
	}
	OffLockPoint();
	return 0;
}


//状态。表示状态的是整型。具有4个字节。每个字节表示一种状态。
int TOMeastar::MeaState(Meastar *ms)
{
	//ms->PersistentState[0];//每次收到的伤害
	//ms->PersistentState[1];//中毒持续时间  
	//ms->PersistentState[2];//表示减速的倍率
	//ms->PersistentState[3];//剩余的减速时间
	if (ms->PersistentState[1])
	{
		ms->life -= ms->PersistentState[0];
		ms->PersistentState[1]--;
		plusTotalDamage(m_pgameslevels, ms->PersistentState[0]);
		//m_pgameslevels->DrawGames();
	}
	else
	{
		ms->PersistentState[0] = 0;
	}
	if (ms->PersistentState[3])ms->PersistentState[3]--;
	else
	{
		ms->PersistentState[2]=0;
	}

	return 0;
}
int TOMeastar::Chuguai()
{
	if (m_dengdaiparsing.num <= 0)
	{
		return m_pgameslevels->GetParsingOne(m_dengdaiparsing);
	}
	return 0;
}