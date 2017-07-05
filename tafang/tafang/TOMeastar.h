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
	//int x;//��ǰ���ꡣ ����������Ҫ����1000
	//int y;//��ǰ���ꡣ ����������Ҫ����1000
	//int type;//����
	int life;//����ֵ����ǰ����
	int lifeUp;//��������
	int speed;//�ٶ�//����100Ϊ��ʵ�ٶ�
	POINT fangxiang;
	int beida;//������Ŀ�ꡣ����ָ֤��Ŀ����ԡ�������Ϊ0�������޷���ɾ������
	int endx;//Ŀ��㡣 ����������Ҫ����1000
	int endy;//Ŀ��㡣 ����������Ҫ����1000
	int nb;//��ǰĿ�����ָ���·���ڵ�
	PointList *pPoint;//ָ��Ľڵ�
	BLTTYPE PersistentState[5];//���������״̬���ж�(0,1).����(2,3).
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

//Ŀǰ�ǵ����
typedef struct MeastarList:BasisList
{
	Meastar ms;//����
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
	int FindMoveTo(void *ms, int x, int y);//�����ƶ�·��
//	int DrawAll(HDC hdc);
	int InitMeastar(GamesLevels* pgame, TOStunt*ptj);	//��ʼ��
	int ReleaseMeastar();
	int SetAllEndPoint(int ex, int ey);
	int SetAllEndPoint(PointList* pPoint);
	int SetEndPoint(Meastar *ms, int ex, int ey,int speed);//�����ƶ����յ�
	int TOMeastar::SetEndPoint(Meastar *ms, PointList* pPoint, int speed);
	int Findlu1(Meastar *ms, int speed);//Ѱ·�㷨1
	int Findlu2(Meastar *ms);
	int Xunlu1(Meastar *ms);//
	PMeastarList Xunlu(PMeastarList pms);
	int MeaState(Meastar *ms);
	int SetLujing(PointList *pointsHead, int pl);
	int Chuguai();
	//��������б�����
	MeastarList*CreateMeastar(const Meastar *ms);
	MeastarList* DeleteMeastar(MeastarList*);
	int DeleteOT(BasisList*bl);//ɾ����Աǰִ�еĶ���Ĳ���
	int DeleteOEnd(BasisList*bl);//ɾ����Ա��ִ�еĶ���Ĳ���
	bool DeleteOpanduan(BasisList*bl);//ɾ����Ա��Ҫִ�еĶ���Ĳ���
	MeastarList*m_headListMeastar;
	int m_iMeastar;//�������

	//·�������趨���������(Endx,Endy);
	//int SetLu(POINTS*, int n);//�����ƶ�·��
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
	unsigned int m_uThreadID;//����ID
	bool m_bLoadPoint;
	MeastarLUJING *m_plujing;
	TOStunt*m_pStunt;
	PointList *m_pPointsHead;//ָ��·����
	int m_npoint;//·���ڵ�����
	unsigned int m_uThreadMeastarRunID;
	bool m_bInitMeastar;
	Parsing m_dengdaiparsing;//�ȴ����ֵĹ���
	GamesLevels *m_pgameslevels;
	int m_ndengdai;//�ȴ���һ�������ʱ��ms
public:
};

#endif