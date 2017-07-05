#include "stdafx.h"
#include "GamesLevels.h"
#include "API.h"

GamesLevels::GamesLevels()
{
	m_gold = 1000;//金币
	m_life = 10;//剩余生命
	m_TotalDamage = 0;//造成的总伤害。
	m_nTurret = 0;//塔个数
	m_nMeastar = 0;//怪个数
	m_pMapf = NULL;
	m_nPoint = 0;
	m_PointListHead = NULL;
	m_nbu = 0;
	m_hFont = CreateFont(14, // nHeight 
		0, 0, 0, 2, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		_T("楷体"));
}

GamesLevels::~GamesLevels()
{
	DeleteObject(m_hFont);
}
//显示关卡信息
int GamesLevels::ShowGames(HDC hdc, int x, int y)
{
	DrawGames();
	BitBlt(hdc, x, y, m_pMap->m_nw * 4, 80, m_hdc, 0, 0, SRCCOPY);

	return 0;
}
//读取关卡信息
//关卡信息{(5,30,1200,60)(30,)()}
//{(等待时间，数量，基础生命(显示时除以100)，基础速度(显示时除以100))}
int GamesLevels::SetGameLevel(int level, int gold, int life, char*buffer, int len)
{
	m_nLevel = level;
	strncpy(m_buffer, buffer, 1024);
	m_gold = gold;//金币
	m_life = life;//剩余生命
	ParsingGame(buffer, len);
	return 0;
}
int GamesLevels::DrawGames()
{
	char buf[256];
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(0, 250, 0));
	SelectObject(m_hdc, hpen);
	Rectangle(m_hdc, 1, 1, m_pMap->m_nw * 4 - 2, 80 - 2);
	SetTextColor(m_hdc, RGB(230, 10, 100));
	sprintf(buf, "关卡：%d", m_nLevel);
	TextOutA(m_hdc, 4, 4, buf, strlen(buf));
	sprintf(buf, "生命：%d", m_life);
	TextOutA(m_hdc, 84, 4, buf, strlen(buf));
	sprintf(buf, "伤害：%d", m_TotalDamage);
	TextOutA(m_hdc, 164, 4, buf, strlen(buf));
	sprintf(buf, "金币：%d", m_gold);
	TextOutA(m_hdc, 244, 4, buf, strlen(buf));
	sprintf(buf, "塔数：%d", m_nTurret); 
	TextOutA(m_hdc, 4, 24, buf, strlen(buf)); 
	sprintf(buf, "怪数：%d", m_nMeastar);
	TextOutA(m_hdc, 84, 24, buf, strlen(buf)); 
	sprintf(buf, "回合：%d", m_nbu);
	TextOutA(m_hdc, 164, 24, buf, strlen(buf));
	DeleteObject(hpen);
	return 0;
}
int GamesLevels::InitGamesLevels(TFMap*pMap)
{
	m_gold = 1000;//金币
	m_life = 10;//剩余生命
	m_TotalDamage = 0;//造成的总伤害。
	m_nTurret = 0;//塔个数
	m_nMeastar = 0;//怪个数
	m_pMapf = NULL;
	m_nPoint = 0;
	m_PointListHead = NULL;
	m_nbu = 0;
	m_hdc = CreateCompatibleDC(NULL);
	m_hbitmap = CreateBitmap(800, 100, 1, 32, NULL);
	SelectObject(m_hdc, m_hbitmap);
	SelectObject(m_hdc, m_hFont);
	m_PointListHead = (PointList*)malloc(sizeof(PointList));
	m_PointListHead->Next = m_PointListHead;
	m_PointListHead->Pre = m_PointListHead;
	m_ParsingListHead = (ParsingList*)malloc(sizeof(ParsingList));
	m_ParsingListHead->Next = m_ParsingListHead;
	m_ParsingListHead->Pre = m_ParsingListHead;
	m_pMap = pMap;
	return 0;
}
int GamesLevels::ReleaseGamesLevels()
{
	DeletePointALL();
	DeleteParsingListAll();
	free(m_ParsingListHead);
	m_ParsingListHead = NULL;
	free(m_PointListHead);
	m_PointListHead = NULL;
	DeleteDC(m_hdc);
	DeleteObject(m_hbitmap);
	m_hdc = NULL;
	m_hbitmap = NULL;
	return 0;
}
PointList* GamesLevels::AddPoint(int x, int y)
{
	PointList *ps = (PointList*)malloc(sizeof(PointList));
	ps->point.x = x;
	ps->point.y = y;
	ps->Next = m_PointListHead;
	ps->Pre = m_PointListHead->Pre;
	m_PointListHead->Pre->Next = ps;
	m_PointListHead->Pre = ps;
	return 0;
}

void GamesLevels::DeletePointALL()
{
	PointList* Temp = m_PointListHead->Next;
	PointList* Next = Temp;
	m_PointListHead->Next = m_PointListHead;
	m_PointListHead->Pre = m_PointListHead;
	while (Temp != m_PointListHead)
	{
		Next = Temp->Next;
		free(Temp);
		Temp = Next;
	}
}
//尾插法
int GamesLevels::AddParsingList(Parsing *ps)
{
	ParsingList *psl = (ParsingList*)malloc(sizeof(ParsingList));
	psl->ps = *ps;
	psl->Next = m_ParsingListHead;
	psl->Pre = m_ParsingListHead->Pre;
	m_ParsingListHead->Pre->Next = psl;
	m_ParsingListHead->Pre = psl;
	return 0;
}

int GamesLevels::DeleteParsingListAll()
{
	ParsingList* Temp = m_ParsingListHead->Next;
	ParsingList* Next = Temp;
	m_ParsingListHead->Next = m_ParsingListHead;
	m_ParsingListHead->Pre = m_ParsingListHead;
	while (Temp != m_ParsingListHead)
	{
		Next = Temp->Next;
		free(Temp);
		Temp = Next;
	}
	return 0;
}
int GamesLevels::DeleteParsingList(ParsingList*pl)
{
	if (pl != m_ParsingListHead)
	{
		pl->Next->Pre = pl->Pre;
		pl->Pre->Next = pl->Next;
		yanshiFree(pl);
	}
	return 0;
}

//解析剧情(5,30,1200,60)(5,30,1700,65)
int GamesLevels::ParsingGame(char *buffer, int len)
{
	unsigned int pos0 = (unsigned int)buffer, pos1 = pos0, pos2 = 0, pos3 = 0;
	for (int i = 0; i < len; i++)
	{
		if (buffer[i] == ',')
			buffer[i] = '\0';
	}
	char*p[10];
	int n = 0;
	do
	{
		pos1 = findstr((char*)pos1, len - n, "(");
		if (pos1 == 0)break;
		pos2 = findstr((char*)pos1, len - n, ")");
		if (pos2 == 0)break;
		*(char*)pos1 = '\0';
		*(char*)pos2 = '\0';
		n = pos1 - pos0;
		p[0] = &buffer[n + 1];
		for (int i = 1; i < 4; i++)
		{

			p[i] = (char*)(p[i - 1] + strlen(p[i - 1]) + 1);
		}
		//在这里讲读取到的信息保存到链表中
		Parsing ps(atoi(p[0]), atoi(p[1]), atoi(p[2]), atoi(p[3]));
		AddParsingList(&ps);

	} while (pos1);

	POINTS p1 = { 0, m_pMap->m_nh / 2 };
	POINTS p2 = { m_pMap->m_nw - 1, m_pMap->m_nh / 2 };
	POINTS point[2000];
	int pointl = 2000;
	PointF* pMapf = (PointF*)malloc(sizeof(PointF)*m_pMap->m_nw*m_pMap->m_nh);
	PointF*Temp = pMapf;
	for (int y = 0; y < m_pMap->m_nh; y++)
	{
		for (int x = 0; x < m_pMap->m_nw; x++)
		{
			Temp = pMapf + y*m_pMap->m_nw + x;
			Temp->x = x;
			Temp->y = y;
			Temp->btrue = !(m_pMap->tf[x][y] & 0x01);
			Temp->H = (jueduizhi(x - p2.x) + jueduizhi(y - p2.y)) * 10;
			Temp->G = 0;
			Temp->Pre = NULL;
		}
	}
	pointl = xunluA(pMapf, m_pMap->m_nw, m_pMap->m_nh, p1, p2, point, pointl);
	//char buffer[256];
	//sprintf(buffer, "%d", len);
	//MessageBoxA(NULL,buffer,"",0);
	free(pMapf);
	if (pointl == 0)return -1;
	for (int i = 0; i < pointl; i++)
	{
		AddPoint(point[i].x, point[i].y);
	}
	m_nPoint = pointl;
	return 0;
}
//获取其中的一项信息
int GamesLevels::GetParsingOne(Parsing &ps)
{
	ParsingList*Temp = m_ParsingListHead->Next;
	if (Temp != m_ParsingListHead)
	{
		ps = Temp->ps;
		DeleteParsingList(Temp);
	}
	else
	{
		return 1;
	}
	m_nbu++;
	return 0;
}
//获取其中的一项信息
int GamesLevels::GetParsingOne(int &dengdai, int &num, int &life, int &speed)
{
	ParsingList*Temp = m_ParsingListHead->Next;
	if (Temp != m_ParsingListHead)
	{
		dengdai = Temp->ps.dengdai;
		num = Temp->ps.num;
		life = Temp->ps.life;
		speed = Temp->ps.speed;
		DeleteParsingList(Temp);
	}
	m_nbu++;
	//DrawGames();
	return 0;
}

int GamesLevels::GetLujing(POINTS*point, int &lp)
{
	PointList* Temp = m_PointListHead->Pre;
	int i = 0;
	while (Temp != m_PointListHead&&i <= lp)
	{
		point[i] = Temp->point;
		i++;
		Temp = Temp->Pre;
	}
	return 0;
}


//调用了该函数后，链表将不再属于GamesLevels的对象。注意释放链表
PointList *GamesLevels::GetPointListHead()
{
	PointList *head = m_PointListHead;
	m_PointListHead = (PointList*)malloc(sizeof(PointList));
	m_PointListHead->Next = m_PointListHead;
	m_PointListHead->Pre = m_PointListHead;
	return head;
}


int plusGold(GamesLevels *gl, int n)
{
	gl->m_gold += n;
	return gl->m_gold;
}
int plusLife(GamesLevels *gl, int n)
{
	gl->m_life += n;
	return gl->m_life;
}
int plusTotalDamage(GamesLevels *gl, int n)
{
	gl->m_TotalDamage += n;
	return gl->m_TotalDamage;
}
int plusTurret(GamesLevels *gl, int n)
{
	gl->m_nTurret += n;
	return gl->m_nTurret;
}
int plusMeastar(GamesLevels* gl, int n)
{
	gl->m_nMeastar += n;
	return gl->m_nMeastar;
}
int getGold(GamesLevels *gl)
{
	return gl->m_gold;
}
int getLife(GamesLevels *gl)
{
	return gl->m_life;
}
int getTotalDamage(GamesLevels *gl)
{
	return gl->m_TotalDamage;
}
int getTurret(GamesLevels *gl)
{
	return gl->m_nTurret;
}
int getMeastar(GamesLevels *gl)
{
	return gl->m_nMeastar;
}