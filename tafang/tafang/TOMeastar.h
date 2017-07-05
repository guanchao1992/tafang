#ifndef  __TOMEASTAR__
#define	 __TOMEASTAR__
#include "TOBasis.h"
#include "TOStunt.h"

#define Meastar_MOVE_MAX 1000

#define MS_TY_1 001
#define MS_TY_2 002
#define MS_TY_3 003

struct MeastarLUJING
{
	POINTS point;
	MeastarLUJING *Pre;
	MeastarLUJING *Next;
	MeastarLUJING()
	{
		Next = NULL;
		Pre = NULL;
	}
	~MeastarLUJING()
	{
		if (Next != NULL)
		{
			delete Next;
			Next = NULL;
		}
	}
};

typedef struct Meastar :public Basis
{	
	//int x;//当前坐标。 具体坐标需要除以1000
	//int y;//当前坐标。 具体坐标需要除以1000
	//int type;//类型
	int life;//生命值，当前生命
	int lifeUp;//生命上限
	int speed;//速度//除以100为真实速度
	POINT fangxiang;
	int beida;//被当作目标。（保证指针的可用性。如果此项不为0，对象将无法被删除）。
	int endx;//目标点。 具体坐标需要除以1000
	int endy;//目标点。 具体坐标需要除以1000
	int nb;//当前目标点所指向的路径节点
	PointList *pPoint;//指向的节点
	BLTTYPE PersistentState[5];//被攻击后的状态。中毒(0,1).减速(2,3).
	Meastar()
	{
		//type = 0;
		//x = 0;
		//y = 0;
		beida = 0;
		life = 1000;
		lifeUp = 10000;
		speed =400;
		x=-50 * 1000;
		y=50 * 4 * 1000;
		endx = 0;
		endy = 0;
		nb = 0;
		pPoint = NULL;
		PersistentState[0] = 0;
		PersistentState[1] = 0;
		PersistentState[2] = 0;
		PersistentState[3] = 0;
		PersistentState[4] = 0;
	}
	Meastar & operator=(const Meastar& p)
	{
		if (this == &p)
			return *this;
		this->life = p.life;
		this->lifeUp = p.lifeUp;
		this->x = p.x;
		this->y = p.y;
		this->speed = p.speed;
		this->type = p.type;
		this->beida = p.beida;
		this->endx = p.endx;
		this->endy = p.endy;
		this->fangxiang = p.fangxiang;
		this->nb = p.nb;
		memcpy(this->PersistentState , p.PersistentState,5);
		return *this;
	}
}*PMeastar;

//目前是单向的
typedef struct MeastarList:BasisList
{
	Meastar ms;//总体
	//struct MeastarList *Pre;
	//struct MeastarList *Next;
	//MeastarList()
	//{
	//	Next = NULL;
	//	Pre = NULL;
	//}
	//~MeastarList()
	//{
	//
	//}
}*PMeastarList;

class TOMeastar :public TOBasis
{
public:
	TOMeastar();
	~TOMeastar();
public:

	int DrawOne(HDC hdc, int x, int y, int type);
	int DrawAll(HDC hdc);
	int SetMoveTo();//
	int FindMoveTo(void *ms, int x, int y);//搜索移动路径
//	int DrawAll(HDC hdc);
	int InitMeastar(GamesLevels* pgame, TOStunt*ptj);	//初始化
	int ReleaseMeastar();
	int SetAllEndPoint(int ex, int ey);
	int SetAllEndPoint(PointList* pPoint);
	int SetEndPoint(Meastar *ms, int ex, int ey,int speed);//设置移动的终点
	int TOMeastar::SetEndPoint(Meastar *ms, PointList* pPoint, int speed);
	int Findlu1(Meastar *ms, int speed);//寻路算法1
	int Findlu2(Meastar *ms);
	int Xunlu1(Meastar *ms);//
	PMeastarList Xunlu(PMeastarList pms);
	int MeaState(Meastar *ms);
	int SetLujing(PointList *pointsHead, int pl);
	int Chuguai();
	//怪物对象列表链表
	MeastarList*CreateMeastar(const Meastar *ms);
	MeastarList* DeleteMeastar(MeastarList*);
	int DeleteOT(BasisList*bl);//删除成员前执行的额外的操作
	int DeleteOEnd(BasisList*bl);//删除成员后执行的额外的操作
	bool DeleteOpanduan(BasisList*bl);//删除成员需要执行的额外的操作
	MeastarList*m_headListMeastar;
	int m_iMeastar;//怪物个数

	//路径链表。设定多个连续的(Endx,Endy);
	//int SetLu(POINTS*, int n);//设置移动路径
	int OnLockPoint();
	int OffLockPoint();
	int AddPoint(int x,int y);
	int DeleteAllPoint();
	bool GetInitMeastar()
	{
		return m_bInitMeastar;
	}
	Parsing&GetParsing()
	{
		return m_dengdaiparsing;
	}
	GamesLevels *GetGamesLevels()
	{
		return m_pgameslevels;
	}
	int &GetDengdai()
	{
		return m_ndengdai;
	}
private:
	unsigned int m_uThreadID;//进程ID
	bool m_bLoadPoint;
	MeastarLUJING *m_plujing;
	TOStunt*m_pStunt;
	PointList *m_pPointsHead;//指向路径点
	int m_npoint;//路径节点总数
	unsigned int m_uThreadMeastarRunID;
	bool m_bInitMeastar;
	Parsing m_dengdaiparsing;//等待出现的怪物
	GamesLevels *m_pgameslevels;
	int m_ndengdai;//等待下一波进入的时间ms
public:
};

#endif