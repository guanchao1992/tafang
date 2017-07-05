
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
	//int type;//����
	int ADO;//�����˺�
	BLTTYPE AttackType[5];//���������͡��ж�(0,1).����(2,3).��Χ.
//	int size;//ռ�ش�С
	int ms;//�������
	int nms;//��������������������
	int l;//����
	int nLever;//�ȼ�
	int nDraw;//���ڻ�ͼ
	Basis *zhixiang;//ָ��������Ҫ������Ŀ��.����ǿת��Basis������
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

//��һ��˫������
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

//����
class TOTurret :public TOBasis
{
public:
	TOTurret();
	~TOTurret();

	TurretList*CreateTurretList(const Turret *pt);
	TurretList* DeleteTurretList(PTurretList pTurret);
	int DeleteOT(BasisList*bl);//ɾ����Աǰִ�еĶ���Ĳ���
	int DeleteOEnd(BasisList*bl);//ɾ����Ա��ִ�еĶ���Ĳ���
	bool DeleteOpanduan(BasisList*bl);//ɾ����Ա��Ҫִ�еĶ���Ĳ���

	TurretList* m_headListTurret;//����ͷ��,�����ͷ��һ�㲻�����κ�����
	TurretList*m_PitchOnTurret;//ѡ�еĶ���
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
	int jianceMeastarAll();//������еĿɹ���Ŀ��
	int AttackOne(const PTurret);//����һ��
	int OnAttack(PTurret,PMeastar);
	int PlaceTurret(int type,int x,int y);//����
	int SelectTurretType(int type, Turret &pt);
	bool JudgeTurretRect(const LPRECT rect);
	int OnMove(int x,int y);
	int OnButton(int x,int y);
	int UpLever(Turret *pt);//����һ��
	int UpTopLever(Turret *pt);//����������
	int DownLever(Turret*pt);//����һ��
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
	unsigned int m_uTurretAttackRunThreadID;//����ID
	bool m_bInitTurret;
//	int Select
};


#endif