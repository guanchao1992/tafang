
#ifndef __Turret__
#define __Turret__

#include "TOBasis.h"
#include "TOBullet.h"
#include "TOMeastar.h"
#include "TFMap.h"

#define Turret_MAKE_TYPE  0x0001
#define Turret_MAKE_ADO   0x0002
#define Turret_MAKE_SIZE  0x0004
#define Turret_MAKE_POINT 0x0008

#define Turret_BUT_UP		0x01
#define Turret_BUT_DOWN	0x02
#define Turret_BUT_DELETE	0x03
#define Turret_BUT_UPTOP	0x04


typedef struct Turret :public Basis
{
	//int x;
	//int y;
	//int type;//类型
	int ADO;//基础伤害
	BLTTYPE AttackType[5];//攻击的类型。中毒(0,1).减速(2,3).范围.
//	int size;//占地大小
	int ms;//攻击间隔
	int nms;//攻击计数，攻击后置零
	int l;//距离
	int nLever;//等级
	int nDraw;//用于绘图
	Basis *zhixiang;//指向炮塔将要攻击的目标.可用强转成Basis的子类
	Turret()
	{
		nLever = 0;
		zhixiang = NULL;
		nms = 0;
		ms = 10;
		//x = 0;
		//y = 0;
		//type = 0;
		ADO = 10;
		l = 100;
		nDraw = 0;
		//memcpy(AttackType,"00000",4);
		//memchr(AttackType, 0, 5);
		for (int i = 0; i < 5; i++)
			AttackType[i] = 0;
		//strncpy((char*)this->AttackType, (char*)p.AttackType, 5);
//		size = 0x00040004;
	}

}*PTurret;

//是一个双向链表
typedef struct TurretList :BasisList
{
	Turret pt;
	//struct TurretList*Next;
	//struct TurretList*Pre;
	//TurretList()
	//{
	//	Pre = NULL;
	//	Next = NULL;
	//}
}*PTurretList;

//炮塔
class TOTurret :public TOBasis
{
public:
	TOTurret();
	~TOTurret();

	TurretList*CreateTurretList(const Turret *pt);
	TurretList* DeleteTurretList(PTurretList pTurret);
	int DeleteOT(BasisList*bl);//删除成员前执行的额外的操作
	int DeleteOEnd(BasisList*bl);//删除成员后执行的额外的操作
	bool DeleteOpanduan(BasisList*bl);//删除成员需要执行的额外的操作

	TurretList* m_headListTurret;//链表头部,链表的头部一般不保存任何内容
	TurretList*m_PitchOnTurret;//选中的对象
	int m_imun;


	TurretList* PitchOnTurret(int x, int y);
	TurretList* PitchOnTurret(TurretList*p);
	int DrawOne(HDC hdc, int x, int y, int type);
	int DrawAll(HDC hdc);
	int DrawButton(HDC hdc);
	int Shanghai();
	int InitTurret(HWND hWnd, GamesLevels* pgame, TOBullet *pBullet, TOMeastar*pMeastar, TFMap*pMap);
	int ReleaseTurret();

	TOBullet *m_pBullet;
	TOMeastar*m_pMeastar;
	int jianceMeastarAll();//检测所有的可攻击目标
	int AttackOne(const PTurret);//攻击一次
	int OnAttack(PTurret,PMeastar);
	int PlaceTurret(int type,int x,int y);//放置
	int SelectTurretType(int type, Turret &pt);
	bool JudgeTurretRect(const LPRECT rect);
	int OnMove(int x,int y);
	int OnButton(int x,int y);
	int UpLever(Turret *pt);//提升一级
	int UpTopLever(Turret *pt);//提升至顶级
	int DownLever(Turret*pt);//降低一级
	bool GetInitTurret()
	{
		return m_bInitTurret;
	}
private:
	HWND m_hWnd;
	POINTS m_buttonpoint;
	TFMap *m_pMap;
	int m_ibutton;
	char m_strbuffer[256];
	unsigned int m_uTurretAttackRunThreadID;//进程ID
	bool m_bInitTurret;
//	int Select
};


#endif