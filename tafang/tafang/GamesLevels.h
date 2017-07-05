#ifndef   __GAMESLEVELS__
#define	  __GAMESLEVELS__
#include "TowerDefense.h"
#include "TFMap.h"
#include "API.h"

#define TFMS_SHOW_NULL  0x00000000
#define TFMS_SHOW_PAUSE 0x00010000
#define TFMS_SHOW_WIN	0x00020000
#define TFMS_SHOW_DIED  0x00030000
//�ƶ�·��
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
	int dengdai;//�ȴ�ms
	int num;//����
	int life;//��������
	int speed;//�ٶ�
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
//�ؿ�
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
	int ShowGames(HDC hdc,int x,int y);//��ʾ�ؿ���Ϣ
	int DrawGames();
	int SetGameLevel(int level, int gold, int life, char*buffer,int len);
	int InitGamesLevels(TFMap*pMap);
	int ReleaseGamesLevels();
	PointList* AddPoint(int x, int y);
	void DeletePointALL();
	int GetLujing(POINTS*point, int &lp);
	int ParsingGame(char *buffer,int len);//��������
	int GetParsingOne(int &dengdai, int &num, int &life, int &speed);//��ȡ���е�һ����Ϣ
	int GetParsingOne(Parsing &ps);
	int AddParsingList(Parsing *ps);
	int DeleteParsingList(ParsingList*pl);
	int DeleteParsingListAll();
	PointList *GetPointListHead();	//�����˸ú�����������������GamesLevels�Ķ���
	int GetnPoint()
	{
		return m_nPoint;
	}


private:
	HDC m_hdc;
	HBITMAP m_hbitmap;
	int m_nLevel;
	char m_buffer[1024];
	PointList *m_PointListHead;//�������������лᱻ����
	int m_nPoint;
	TFMap *m_pMap;
	int m_gold;//���
	int m_life;//ʣ������
	long m_TotalDamage;//��ɵ����˺���
	int m_nTurret;//������
	int m_nMeastar;//�ָ���
	int m_nbu;//�ڼ�����
	ParsingList*m_ParsingListHead;
	PointF *m_pMapf;
	HFONT m_hFont;
};

#endif