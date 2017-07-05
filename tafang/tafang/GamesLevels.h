#ifndef   __GAMESLEVELS__
#define	  __GAMESLEVELS__
#include "TowerDefense.h"
#include "TFMap.h"
#include "API.h"

#define TFMS_SHOW_NULL  0x00000000
#define TFMS_SHOW_PAUSE 0x00010000
#define TFMS_SHOW_WIN	0x00020000
#define TFMS_SHOW_DIED  0x00030000
//移动路径
struct PointList
{
	POINTS point;
	PointList*Next;
	PointList*Pre;
	PointList()
	{
		point.x = 0;
		point.y = 0;
		Next = NULL;
		Pre = NULL;
	}
};
struct Parsing
{
	int dengdai;//等待ms
	int num;//数量
	int life;//基础生命
	int speed;//速度
	Parsing()
	{
		dengdai = 0;
		num = 0;
		life = 0;
		speed = 0;
	}
	Parsing(int d,int n,int l,int s)
	{
		dengdai = d;
		num = n;
		life = l;
		speed = s;
	}
	Parsing& operator=(Parsing&p)
	{
		this->dengdai = p.dengdai;
		this->life = p.life;
		this->num = p.num;
		this->speed = p.speed;
		return *this;
	}
};
//关卡
struct ParsingList
{
	Parsing ps;
	ParsingList*Next;
	ParsingList*Pre;
	ParsingList()
	{
		Next = NULL;
		Pre = NULL;
	}
};

class GamesLevels
{	
	friend int plusGold(GamesLevels* gl,int n);
	friend int plusLife(GamesLevels* gl, int n);
	friend int plusTotalDamage(GamesLevels* gl, int n);
	friend int plusTurret(GamesLevels *gl, int n);
	friend int plusMeastar(GamesLevels *gl, int n);
	friend int getGold(GamesLevels *gl);
	friend int getLife(GamesLevels* gl);
	friend int getTotalDamage(GamesLevels* gl);
	friend int getTurret(GamesLevels* gl);
	friend int getMeastar(GamesLevels *gl);
public:
	GamesLevels();
	~GamesLevels();
	int ShowGames(HDC hdc,int x,int y);//显示关卡信息
	int DrawGames();
	int SetGameLevel(int level, int gold, int life, char*buffer,int len);
	int InitGamesLevels(TFMap*pMap);
	int ReleaseGamesLevels();
	PointList* AddPoint(int x, int y);
	void DeletePointALL();
	int GetLujing(POINTS*point, int &lp);
	int ParsingGame(char *buffer,int len);//解析剧情
	int GetParsingOne(int &dengdai, int &num, int &life, int &speed);//获取其中的一项信息
	int GetParsingOne(Parsing &ps);
	int AddParsingList(Parsing *ps);
	int DeleteParsingList(ParsingList*pl);
	int DeleteParsingListAll();
	PointList *GetPointListHead();	//调用了该函数后，链表将不再属于GamesLevels的对象
	int GetnPoint()
	{
		return m_nPoint;
	}


private:
	HDC m_hdc;
	HBITMAP m_hbitmap;
	int m_nLevel;
	char m_buffer[1024];
	PointList *m_PointListHead;//该项在其他类中会被调用
	int m_nPoint;
	TFMap *m_pMap;
	int m_gold;//金币
	int m_life;//剩余生命
	long m_TotalDamage;//造成的总伤害。
	int m_nTurret;//塔个数
	int m_nMeastar;//怪个数
	int m_nbu;//第几波怪
	ParsingList*m_ParsingListHead;
	PointF *m_pMapf;
	HFONT m_hFont;
};

#endif