#ifndef __TOBULLET__
#define __TOBULLET__
#include "TOBasis.h"
#include "TOMeastar.h"

//#define BLT_Poison		0x0001 //0x000F按位与。中毒有16个等级
//#define BLT_SpeedDown	0x0010 //0x00F0按位与。减速
//#define BLT_ADOScope	0x0100 //0x0F00按位与。范围



typedef struct Bullet:public Basis
{
	//int x;//当前坐标。 具体坐标需要除以1000
	//int y;//当前坐标。 具体坐标需要除以1000
	//int type;//类型
	int speed;//速度//除以100为真实速度

	int endx;//目标点。 具体坐标需要除以1000
	int endy;//目标点。 具体坐标需要除以1000
	int ADO;
	BLTTYPE AttackType[5];//攻击的类型。中毒(0 t,1 a).减速(2 t,3 a).范围(暂定为4).
	Basis *target;//指向攻击目标，指向的对象可能已经被释放，需要进行判断

	Bullet()
	{
		//type = 0;
		//x = 0;
		//y = 0;
		ADO = 0;
		target = NULL;
		speed = 1200;
		endx = 0;
		endy = 0;

	}
	Bullet & operator=(const Bullet& p)
	{
		if (this == &p)
			return *this;
		this->x = p.x;
		this->y = p.y;
		this->endx = p.endx;
		this->endy = p.endy;
		this->speed = p.speed;
		this->type = p.type;
		this->ADO = p.ADO;
		this->target = p.target;
		memcpy(this->AttackType,p.AttackType,5);
		return *this;
	}
}*PBULLET;


typedef struct BulletList :BasisList
{
	Bullet bl;//总体
	//struct BulletList *Pre;
	//struct BulletList *Next;
	//BulletList()
	//{
	//	Next = NULL;
	//	Pre = NULL;
	//}
	//~BulletList()
	//{
	//
	//}
}*PBulletList;


//子弹
class TOBullet :public TOBasis
{
public:
	TOBullet();
	~TOBullet();
	BulletList*CreateBullet(const Bullet*bl);
	BulletList* DeleteBullet(BulletList*);
	void DeleteBulletAll();
//	int DeleteO(BasisList*bl);
//	bool DeleteOpanduan(BasisList*bl);//删除成员需要执行的额外的操作
	int DeleteOT(BasisList*bl);//删除成员前执行的额外的操作
	int DeleteOEnd(BasisList*bl);//删除成员后执行的额外的操作
	bool DeleteOpanduan(BasisList*bl);//删除成员需要执行的额外的操作
	BulletList*  Xunlu(BulletList *bl);
	int DrawOne(HDC hdc, int x, int y,int type);
	int DrawAll(HDC hdc);
	int InitBullet(GamesLevels* pgame, MeastarList*head, TOStunt *Stunt);	//初始化
	int ReleaseBullet();
	int Attack(const Bullet *bl);//创建子弹
	int SetTarget(Bullet *bl,Basis*b);
	int AttackADC(Bullet *bl);
	bool IsJuli(int x1, int y1, int x2, int y2, int ln );
	BulletList*m_headListBullet;
	int m_nBasisList;//个数
	MeastarList *m_pMeastarhead;
	bool GetInitBullet()
	{
		return m_bInitBullet;
	}
private:
	unsigned int m_uBulletMoveRunThreadID;
	TOStunt *m_pStunt;
	bool m_bInitBullet;
};

#endif