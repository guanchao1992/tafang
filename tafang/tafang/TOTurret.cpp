#include "stdafx.h"
#include "TOTurret.h"


unsigned __stdcall TurretAttackRun(void*lp)//攻击
{
	TOTurret*pTurret = (TOTurret*)lp;
	while (pTurret->GetInitTurret())
	{
		pTurret->jianceMeastarAll();
		Sleep(20);
		while (g_bPause)Sleep(100);//暂停
	}
	return 0;
}
TOTurret::TOTurret()
{
	m_bInitTurret = false;
	m_imun = 0;
	m_headListTurret = NULL;
	m_PitchOnTurret = NULL;
	m_pMap = NULL;
	m_ibutton = -1;
	m_hpen = CreatePen(PS_SOLID, 1, RGB(180, 0, 0));
	m_hFont = CreateFont(14, // nHeight 
		0 , 0, 0, 2, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		_T("黑体"));
	m_strbuffer[0] = '\0';
}

TOTurret::~TOTurret()
{
	DeleteObject(m_hFont);
	DeleteObject(m_hpen);
}

TurretList* TOTurret::CreateTurretList(const Turret *pt)
{
	TurretList *ps = (TurretList*)malloc(sizeof(TurretList));
	ps->pt = *pt;
	ps->pt.type += 1000;
	if (m_headListTurret == NULL)
	{
		ps->Next = ps;
		ps->Pre = ps;
		m_headListTurret = ps;
	}
	else
	{
		plusTurret(m_pgameslevels, 1);
		//m_pgameslevels->DrawGames();
		ps->Next = m_headListTurret;
		ps->Pre = m_headListTurret->Pre;
		m_headListTurret->Pre->Next = ps;
		m_headListTurret->Pre = ps;
	}
	//m_PitchOnTurret = ps;
	//PitchOnTurret(ps);
	return ps;
}
int TOTurret::DeleteOT(BasisList*bl)//删除成员前执行的额外的操作
{
	TurretList*pbl = ((TurretList*)bl);
	OnAttack(&pbl->pt, NULL);
	plusTurret(m_pgameslevels, -1);
	//m_pgameslevels->DrawGames();
	return 0;
}

int TOTurret::DeleteOEnd(BasisList*bl)//删除成员后执行的额外的操作
{
	TurretList*pbl = ((TurretList*)bl);
	if (pbl->pt.zhixiang)
	{
		((PMeastar)(pbl->pt.zhixiang))->beida--;
		pbl->pt.zhixiang = NULL;
	}
	return 0;
}
bool TOTurret::DeleteOpanduan(BasisList*bl)//判断
{
	return true;
}
TurretList* TOTurret::DeleteTurretList(TurretList*bl)
{
	return (TurretList*)DeleteBasis(bl, m_headListTurret , this,true, TOBasis::DeleteOtherT, TOBasis::Deletepanduan, TOBasis::DeleteOtherOEnd);
}
/*
void TOTurret::DeleteTurretList(PTurretList pTurret)
{
	OnAttack(&pTurret->pt, NULL);
	if (pTurret->Next != pTurret)
	{
		plusTurret(m_pgameslevels, -1);
		m_pgameslevels->DrawGames();
		if (m_headListTurret == pTurret)
			m_headListTurret = pTurret->Next;
		pTurret->Next->Pre = pTurret->Pre;
		pTurret->Pre->Next = pTurret->Next;
		if (pTurret->pt.zhixiang)
		{
			((PMeastar)(pTurret->pt.zhixiang))->beida--;
			pTurret->pt.zhixiang = NULL;
		}
	}
	else
	{
		m_headListTurret = NULL;
	}
	yanshiFree(pTurret);
	//free(pTurret);
}
*/
int TOTurret::DrawOne(HDC hdc, int x, int y, int type)
{
	type = type % 1000;
	int rx = type % 10 * 32;
	int ry = type / 10 * 32;
	//以下为透明贴图代码.底色为白色
	if (m_bhdc)//此处的作用是防止贴图错位
	{
		BitBlt(m_hdcM, 0, 0, 32, 32, HDC_TURRET, rx, ry, SRCCOPY);
		BitBlt(m_hdc1, 0, 0, 32, 32, m_hdcM, 0, 0, NOTSRCCOPY);
		BitBlt(m_hdc1, 0, 0, 32, 32, HDC_TURRET, rx, ry, SRCAND);//dc1是前景

		BitBlt(m_hdc2, 0, 0, 32, 32, m_hdcM, 0, 0, SRCCOPY);
		BitBlt(m_hdc2, 0, 0, 32, 32, hdc, x / 1000, y / 1000, SRCAND);//dc2是背景

		BitBlt(hdc, x / 1000, y / 1000, 32, 32, m_hdc1, 0, 0, SRCCOPY);
		BitBlt(hdc, x / 1000, y / 1000, 32, 32, m_hdc2, 0, 0, SRCPAINT);
		m_bhdc = false;
	}
	else
	{
		BitBlt(m_hdcM, 200, 0, 32, 32, HDC_TURRET, rx, ry, SRCCOPY);
		BitBlt(m_hdc1, 200, 0, 32, 32, m_hdcM, 200, 0, NOTSRCCOPY);
		BitBlt(m_hdc1, 200, 0, 32, 32, HDC_TURRET, rx, ry, SRCAND);//dc1是前景

		BitBlt(m_hdc2, 200, 0, 32, 32, m_hdcM, 200, 0, SRCCOPY);
		BitBlt(m_hdc2, 200, 0, 32, 32, hdc, x / 1000, y / 1000, SRCAND);//dc2是背景

		BitBlt(hdc, x / 1000, y / 1000, 32, 32, m_hdc1, 200, 0, SRCCOPY);
		BitBlt(hdc, x / 1000, y / 1000, 32, 32, m_hdc2, 200, 0, SRCPAINT);
		m_bhdc = true;
	}
	return 0;
}
int TOTurret::DrawAll(HDC hdc)//turret
{
	SelectObject(hdc, m_hpen);
	SelectObject(hdc, m_hFont);
	SetTextColor(hdc, RGB(200,50,30));
	TurretList *Temp = (TurretList*)m_headListTurret->Next;
	while (Temp != m_headListTurret)
	{
		DrawOne(hdc, Temp->pt.x - 16000, Temp->pt.y - 16000,Temp->pt.type +  Temp->pt.nDraw/10*10);
		if (Temp->pt.nDraw > 98)Temp->pt.nDraw = -1;
		Temp->pt.nDraw++;
		Temp = (TurretList *)Temp->Next;
	}
	TextOutA(hdc, 5, m_pMap->m_nh * 4 - 20, m_strbuffer, strlen(m_strbuffer));//属于提升信息
	if (m_PitchOnTurret)
	{
		//DrawOne(hdc,);
		//SetBkMode(hdc, TRANSPARENT);
		//Rectangle(m_bkhdc, 0, 0, 480, h + 200);
		//Rectangle(hdc, m_PitchOnTurret->pt.x / 1000 - m_PitchOnTurret->pt.l, m_PitchOnTurret->pt.y / 1000 - m_PitchOnTurret->pt.l, m_PitchOnTurret->pt.x / 1000 + m_PitchOnTurret->pt.l, m_PitchOnTurret->pt.y / 1000 + m_PitchOnTurret->pt.l);
		RECT rect = { m_PitchOnTurret->pt.x / 1000 - m_PitchOnTurret->pt.l, m_PitchOnTurret->pt.y / 1000 - m_PitchOnTurret->pt.l, m_PitchOnTurret->pt.x / 1000 + m_PitchOnTurret->pt.l, m_PitchOnTurret->pt.y / 1000 + m_PitchOnTurret->pt.l };
		//Ellipse(hdc, m_PitchOnTurret->pt.x / 1000 - m_PitchOnTurret->pt.l, m_PitchOnTurret->pt.y / 1000 - m_PitchOnTurret->pt.l, m_PitchOnTurret->pt.x / 1000 + m_PitchOnTurret->pt.l, m_PitchOnTurret->pt.y / 1000 + m_PitchOnTurret->pt.l);
		//Arc(hdc,,)
		Arc(hdc, rect.left, rect.top, rect.right, rect.bottom, 0, 0, 0, 0);
	
		//g_dbutton->Create(m_hWnd, g_hinst, m_PitchOnTurret->pt.x / 1000, m_PitchOnTurret->pt.y / 1000 + 32, 64, 32, IDC_BUT_AddMeastar, 
		//	HDC_BUTTON, 60, 96, 60, 20, _T("up"), BR_TY_W | BR_TY_TY_1, NULL);
		//g_dbutton->Create(m_hWnd, g_hinst, m_PitchOnTurret->pt.x / 1000, m_PitchOnTurret->pt.y / 1000 + 32, 64, 32, IDC_BUT_AddMeastar,
		//	HDC_BUTTON, 60, 96, 60, 20, _T("up"), BR_TY_W | BR_TY_TY_1, NULL);
		//g_dbutton->Create(m_hWnd, g_hinst, m_PitchOnTurret->pt.x / 1000, m_PitchOnTurret->pt.y / 1000 + 32, 64, 32, IDC_BUT_AddMeastar,
		//	HDC_BUTTON, 60, 96, 60, 20, _T("up"), BR_TY_W | BR_TY_TY_1, NULL);

	}
	return 0;
}

int TOTurret::DrawButton(HDC hdc)
{
	if (m_PitchOnTurret)
	{
		Draw(hdc, m_buttonpoint.x, m_buttonpoint.y , 20, 20, HDC_BUTTON, 20 * 4, 96);
		Draw(hdc, m_buttonpoint.x + 20, m_buttonpoint.y , 20, 20, HDC_BUTTON, 20 * 5, 96);
		Draw(hdc, m_buttonpoint.x + 20 * 2, m_buttonpoint.y , 20, 20, HDC_BUTTON, 20 * 6, 96);
		if (m_ibutton >= 0 && m_ibutton <= 2)
			Arc(hdc, m_buttonpoint.x + m_ibutton * 20, m_buttonpoint.y, m_buttonpoint.x + m_ibutton * 20 + 20, m_buttonpoint.y+ 20,0,0,0,0 );
	}
	return 0;
}

int TOTurret::OnMove(int x, int y)
{
	if (m_PitchOnTurret)
	{
		RECT rect = { m_buttonpoint.x, m_buttonpoint.y, m_buttonpoint.x + 60, m_buttonpoint.y + 20 };
		POINT point = { x, y };
		if (PtInRect(&rect, point))
		{
			m_ibutton = (point.x - m_buttonpoint.x) / 20;
		}
		else 
			m_ibutton = -1;
	}
	return 0;
}

int TOTurret::OnButton(int x, int y)
{
	if (m_PitchOnTurret)
	{
		RECT rect = { m_buttonpoint.x, m_buttonpoint.y, m_buttonpoint.x+60, m_buttonpoint.y+20 };
		POINT point = { x, y };
		if (PtInRect(&rect, point))
		{
			switch ((point.x - m_buttonpoint.x) / 20)
			{
			case 0://UpLever
				UpLever(&m_PitchOnTurret->pt);

				break;
			case 1://DownLever
				DownLever(&m_PitchOnTurret->pt);
				break;
			case 2://Delete
				DeleteTurretList(m_PitchOnTurret);
				m_PitchOnTurret = NULL;
				break;
			}
			PitchOnTurret(m_PitchOnTurret);
			return 1;
		}
	}
	return 0;
}

TurretList* TOTurret::PitchOnTurret(int x, int y)
{
	//HBITMAP_Meastar
	TurretList *Temp = (TurretList *)m_headListTurret->Next;
	while (Temp != m_headListTurret)
	{
		if (Temp->pt.x -16000< x&&Temp->pt.x + 16000 > x&&Temp->pt.y -16000< y&&Temp->pt.y + 16000 > y)
		{
			//if (InBasisHBit((x - Temp->pt.x)/1000, (y - Temp->pt.y)/1000, Temp->pt.type))
			{
				return 	PitchOnTurret(Temp);
	//			m_buttonpoint.x = Temp->pt.x / 1000-16-14;//此次是左上角
	//			m_buttonpoint.y = Temp->pt.y / 1000-16+2;
	//			if (m_buttonpoint.x <0)m_buttonpoint.x = 0;
	//			if (m_buttonpoint.x>m_pMap->m_nw * 4 - 60)m_buttonpoint.x = m_pMap->m_nw * 4 - 60;
	//			if (m_buttonpoint.y > m_pMap->m_nh * 4 - 52)m_buttonpoint.y = m_buttonpoint.y - 54;
	//			return Temp;
			}
		}
		Temp = (TurretList *)Temp->Next;
	}
		
	m_strbuffer[0] = '\0';
		
	return 0;
}

TurretList* TOTurret::PitchOnTurret(TurretList*p)
{
	TurretList *Temp = m_PitchOnTurret;
	m_PitchOnTurret = p;
	if (m_PitchOnTurret &&m_pMap)
	{
		m_buttonpoint.x = m_PitchOnTurret->pt.x / 1000 - 16 - 14;//此次是左上角
		m_buttonpoint.y = m_PitchOnTurret->pt.y / 1000 + 16 + 2;
		if (m_buttonpoint.x <0)m_buttonpoint.x = 0;
		if (m_buttonpoint.x>m_pMap->m_nw * 4 - 60)m_buttonpoint.x = m_pMap->m_nw * 4 - 60;
		if (m_buttonpoint.y > m_pMap->m_nh * 4 - 22)m_buttonpoint.y = m_buttonpoint.y - 54;
		sprintf(m_strbuffer, "Type:%d Lever:%d ACK:%d AR:%-8.2f", m_PitchOnTurret->pt.type%1000+1, m_PitchOnTurret->pt.nLever + 1, m_PitchOnTurret->pt.ADO, (float)1000/m_PitchOnTurret->pt.ms);
	}
	return Temp;
}

int TOTurret::InitTurret(HWND hWnd, GamesLevels* pgame, TOBullet *pBullet, TOMeastar*pMeastar, TFMap*pMap)
{
	m_bInitTurret = true;
	m_hWnd = hWnd;
	m_pgameslevels = pgame;
	m_pBullet = pBullet;
	m_pMeastar = pMeastar;
	m_pMap = pMap;
	Turret tchead;
	tchead.ADO = 0;
	//	tchead.size = 0;
	tchead.type = 0;
	tchead.x = 0;
	tchead.y = 0;
	CreateTurretList(&tchead);//创建头部
	_beginthreadex(NULL, 0, &TurretAttackRun, (void*)this, 0, &m_uTurretAttackRunThreadID);
	return 0;
}
int TOTurret::ReleaseTurret()
{
	m_bInitTurret = false;
	//_endthreadex(m_uTurretAttackRunThreadID);
	DeleteBasisAll(m_headListTurret,this);
	free(m_headListTurret);
	m_headListTurret = NULL;
	m_hWnd = NULL;
	m_pgameslevels =NULL;
	m_pBullet = NULL;
	m_pMeastar = NULL;
	m_pMap = NULL;
	return 0;
}
//设定攻击目标
int TOTurret::OnAttack(PTurret ptc, PMeastar pms)
{
	if (ptc->zhixiang == NULL)
	{
		if (pms != NULL&&pms->life>0)
		{
			//pms->beida++;
			ptc->zhixiang = pms;
		}
	}
	else
	{

		if (((PMeastar)ptc->zhixiang)->life <= 0)
		{
			//((PMeastar)ptc->zhixiang)->beida--;
			ptc->zhixiang = NULL;
		}
		else
		{
			if (ptc->zhixiang != pms)
			{
				//((PMeastar)ptc->zhixiang)->beida--;
				//pms->beida++;
				ptc->zhixiang = pms;
			}
		}
	}
	return 0;
}
//攻击一次
int TOTurret::AttackOne(const PTurret tc)
{
	tc->nms = 0;
	if (tc->zhixiang&&PMeastar(tc->zhixiang)->life > 0)
	{
		Bullet bl;
		bl.x = tc->x;
		bl.y = tc->y;
		bl.endx = PMeastar(tc->zhixiang)->x;
		bl.endy = PMeastar(tc->zhixiang)->y;
		bl.speed = 600;
		bl.type = tc->type%1000;
		memcpy(bl.AttackType ,tc->AttackType,5);
		bl.ADO = tc->ADO;
		bl.target = tc->zhixiang;
		m_pBullet->Attack(&bl);
	}
	return 0;
}

//检测所有的可攻击目标
int TOTurret::jianceMeastarAll()
{
	int l = 0; 
	int w = 0;
	int nl;
	TurretList *TempA = (TurretList *)m_headListTurret->Next;
	MeastarList *TempB = (MeastarList *)m_pMeastar->m_headListMeastar->Next;
	while (TempA!=m_headListTurret)
	{
		TempB = (MeastarList *)m_pMeastar->m_headListMeastar->Next;
		if (TempA->pt.zhixiang == NULL)
		{
			while (TempB != m_pMeastar->m_headListMeastar)
			{
				l = (TempA->pt.x - TempB->ms.x) / 1000;
				w = (TempA->pt.y - TempB->ms.y) / 1000;
				nl = l*l + w*w;
				if (nl < TempA->pt.l*TempA->pt.l&&TempB->ms.life>0)//距离的平方
				{
					OnAttack(&TempA->pt, &TempB->ms);
					if (TempA->pt.nms >= TempA->pt.ms)
					{
						AttackOne(&(TempA->pt));
						break;
					}
					TempA->pt.nms += 20 * g_beilv;
					break;
				}
				TempB = (MeastarList *)TempB->Next;
			}
		}
		else
		{
			l = (TempA->pt.x - ((Meastar*)(TempA->pt.zhixiang))->x) / 1000;
			w = (TempA->pt.y - ((Meastar*)(TempA->pt.zhixiang))->y) / 1000;
			nl = l*l + w*w;
			if (nl < TempA->pt.l*TempA->pt.l)
			{
				OnAttack(&TempA->pt, (Meastar*)(TempA->pt.zhixiang));
				if (TempA->pt.nms >= TempA->pt.ms)
				{
					AttackOne(&(TempA->pt));
				}
				else
					TempA->pt.nms += 20 * g_beilv;
			}
			else
			{
				//((Meastar*)(TempA->pt.zhixiang))->beida--;
				TempA->pt.zhixiang = NULL;
			}
		}
		TempA = (TurretList *)TempA->Next;
	}
	return 0;
}

int TOTurret::SelectTurretType(int type, Turret &pt)
{
	pt.ADO = 20;
	//	pt.size = 0x00100010;//16*16.需要乘以4
	pt.type = 0; type % 1000;

	for (int i = 0; i < 5; i++)
	{
		pt.AttackType[i] = 0;
	}
	//memchr(pt.AttackType, 0, 5);
	0x000000ff;//种类
	0x0000ff00;//等级
	int la = 0x00ff & type;
	int lb = (0x0000ff00 & type) >> 8;
	pt.type = la;
	pt.nLever = lb;

	//其中的ms表示。
	switch (la)//首要考虑0到10等级
	{
	case 0://A - 1:普通的炮塔。廉价的。 
		pt.l = 80 + lb * 2;//80-100
		pt.ADO = 400 + lb * 70;//400-1100
		if (lb > 10)lb = 10;
		pt.ms = 1000 - lb * 80;//1000-200
		break;
	case 1:	//B - 1 : 阻挡方块。阻挡敌人移动。
		//暂时不予考虑
		pt.l = 0;
		pt.ADO = 0;
		pt.ms = 100000000;
		break;
	case 2://C - 1 : 减速的炮塔。低攻击，中攻速。单体减速。
		pt.l = 80 + lb * 3;//80-110
		pt.ADO = 200 + lb * 30;//200-500
		pt.AttackType[3] = 100;//以20ms为单位
		if (lb<10)
			pt.AttackType[2] = 180 - 6 * (10 - lb);
		else
			pt.AttackType[2] = 180 + 40 * lb / 255;
		if (lb > 10)lb = 10;
		pt.ms = 1200 - lb * 70;//1200-500
		break;
	case 3://D - 1 : 强力的炮塔。高攻击，低攻速。
		pt.l = 90 + lb * 5;//100-140
		pt.ADO = 1000 + lb * 410;//1000-5100;
		if (lb>10)lb = 10;
		pt.ms = 1800 - lb * 70;//1800-1100
		break;
	case 4:	//E - 1 : 群攻的炮塔。中攻击，低攻速。
		pt.l = 120 + lb * 4;//120-160
		pt.ADO = 250 + 60 * lb;//250-850
		pt.AttackType[4] = 10 + lb;//l*4的范围 40-80
		if (lb > 10)lb = 10;
		pt.ms = 1400 - lb * 80;//1400-600
		break;
	case 5:	//F - 1 : 群减速炮塔。低攻击，低攻速。群体减速。
		pt.l = 100 + lb * 1;//100-110
		pt.ADO = 400 + lb * 70;//400-1100
		pt.AttackType[4] = 10 + lb*2;//l*4的范围 40-120
		pt.AttackType[3] = 60;
		if (lb<10)
			pt.AttackType[2] = 100 - 100 * (10 - lb);
		else
			pt.AttackType[2] = 100 + 60 * lb / 255;
		if (lb > 10)lb = 10;
		pt.ms = 1400 - lb * 80;//1400-600
		break;
	case 6://G-1：//毒的塔
		pt.l = 80 + lb * 2;//80-100
		pt.ADO = 12 + lb * 3;//120-420
		pt.AttackType[0] = 4 + lb * 2;//4-24
		pt.AttackType[1] = 220;
		pt.ms = 1400 - lb * 80;//1400-600
		break;
	default:
		return -1;
		break;
	}
	return 0;
}

int TOTurret::PlaceTurret(int type, int x, int y)
{
	if (x - 16 < 0)x = 16;
	if (y - 16 < 0)y = 16;
	Turret tc;
	tc.x = x / 4 * 4 * 1000;
	tc.y = y / 4 * 4 * 1000;
	SelectTurretType(type, tc);
	CreateTurretList(&tc);
	return 0;
}

bool TOTurret::JudgeTurretRect(const LPRECT rect)
{
	RECT r;
	TurretList *Temp = (TurretList *)m_headListTurret->Next;
	while (Temp != m_headListTurret)
	{
		r.left = Temp->pt.x / 1000 - 16;
		r.top = Temp->pt.y / 1000 - 16;
		r.right = Temp->pt.x / 1000 + 16;
		r.bottom = Temp->pt.y / 1000  + 16;
		if (JudgeRectTo(rect, &r))
			return false;
		Temp = (TurretList *)Temp->Next;
	}
	return true;
}

int TOTurret::UpLever(Turret *pt)
{
	if (pt->nLever < 9)
	{
		SelectTurretType((pt->type % 1000)|((pt->nLever+1) << 8), *pt);
		pt->type += 1000;
	}
	else
		return -1;

	return pt->nLever;
}

int TOTurret::UpTopLever(Turret *pt)
{
	int oldLever = pt->nLever;
	SelectTurretType((pt->type % 1000) | (10 << 8), *pt);
	pt->type += 1000;

	return oldLever;
}

int TOTurret::DownLever(Turret*pt)
{
	if (pt->nLever >0)
	{
		SelectTurretType((pt->type % 1000) | ((pt->nLever - 1) << 8), *pt);
		pt->type += 1000;
	}
	else
		return -1;

	return pt->nLever;
}