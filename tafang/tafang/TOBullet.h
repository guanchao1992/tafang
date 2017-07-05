#ifndef __TOBULLET__
#define __TOBULLET__
#include "TOBasis.h"
#include "TOMeastar.h"

//#define BLT_Poison		0x0001 //0x000F��λ�롣�ж���16���ȼ�
//#define BLT_SpeedDown	0x0010 //0x00F0��λ�롣����
//#define BLT_ADOScope	0x0100 //0x0F00��λ�롣��Χ



typedef struct Bullet:public Basis
{
	//int x;//��ǰ���ꡣ ����������Ҫ����1000
	//int y;//��ǰ���ꡣ ����������Ҫ����1000
	//int type;//����
	int speed;//�ٶ�//����100Ϊ��ʵ�ٶ�

	int endx;//Ŀ��㡣 ����������Ҫ����1000
	int endy;//Ŀ��㡣 ����������Ҫ����1000
	int ADO;
	BLTTYPE AttackType[5];//���������͡��ж�(0 t,1 a).����(2 t,3 a).��Χ(�ݶ�Ϊ4).
	Basis *target;//ָ�򹥻�Ŀ�ָ꣬��Ķ�������Ѿ����ͷţ���Ҫ�����ж�

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
	Bullet bl;//����
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


//�ӵ�
class TOBullet :public TOBasis
{
public:
	TOBullet();
	~TOBullet();
	BulletList*CreateBullet(const Bullet*bl);
	BulletList* DeleteBullet(BulletList*);
	void DeleteBulletAll();
//	int DeleteO(BasisList*bl);
//	bool DeleteOpanduan(BasisList*bl);//ɾ����Ա��Ҫִ�еĶ���Ĳ���
	int DeleteOT(BasisList*bl);//ɾ����Աǰִ�еĶ���Ĳ���
	int DeleteOEnd(BasisList*bl);//ɾ����Ա��ִ�еĶ���Ĳ���
	bool DeleteOpanduan(BasisList*bl);//ɾ����Ա��Ҫִ�еĶ���Ĳ���
	BulletList*  Xunlu(BulletList *bl);
	int DrawOne(HDC hdc, int x, int y,int type);
	int DrawAll(HDC hdc);
	int InitBullet(GamesLevels* pgame, MeastarList*head, TOStunt *Stunt);	//��ʼ��
	int ReleaseBullet();
	int Attack(const Bullet *bl);//�����ӵ�
	int SetTarget(Bullet *bl,Basis*b);
	int AttackADC(Bullet *bl);
	bool IsJuli(int x1, int y1, int x2, int y2, int ln );
	BulletList*m_headListBullet;
	int m_nBasisList;//����
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