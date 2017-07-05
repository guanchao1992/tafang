#ifndef 	__TOBASIS__
#define		__TOBASIS__
#include <process.h>
#include "API.h"
#include "GamesLevels.h"
typedef unsigned char BLTTYPE;

typedef struct Basis
{
	int x;//��ǰ���ꡣ ����������Ҫ����1000����Ϊ���ĵ�
	int y;//��ǰ���ꡣ ����������Ҫ����1000����Ϊ���ĵ�
	int type;//����//����1000��ȷ������.0��Meastar.1��TURRET��2��BULLET
}BASIS;

typedef struct BasisList
{
	struct BasisList *Pre;
	struct BasisList *Next;
	BasisList()
	{
		Next = NULL;
		Pre = NULL;
	}
	~BasisList()
	{

	}
}*PBasisList;
//��ͼ�и���Ԫ�صĻ�����
class TOBasis
{
public:
	TOBasis();
	virtual ~TOBasis();
public:
	BasisList*CreateBasis();
	void DeleteBasisAll(BasisList* head, TOBasis*b);//ͷ���ᱻ����
	BasisList* DeleteBasis(BasisList*, BasisList* head, TOBasis*b, bool bjianc/*�Ƿ�������*/, int(*)(TOBasis* b, BasisList *bl), bool(*)(TOBasis* tb, BasisList *bl), int(*)(TOBasis* b, BasisList *bl));
	virtual int DeleteOT(BasisList*bl);//ɾ����Աǰִ�еĶ���Ĳ���
	virtual int DeleteOEnd(BasisList*bl);//ɾ����Ա��ִ�еĶ���Ĳ���
	virtual bool DeleteOpanduan(BasisList*bl);//ɾ����Ա��Ҫִ�еĶ���Ĳ���

	virtual int DrawOne(HDC hdc, int x, int y,int type);
	virtual int DrawAll(HDC hdc);
	static int DeleteOtherOEnd(TOBasis* b, BasisList *bl)//���ڻص�
	{
		return b->DeleteOEnd(bl);
	}
	static int DeleteOtherT(TOBasis* b, BasisList *bl)//���ڻص�
	{
		return b->DeleteOT(bl);
	}
	static bool Deletepanduan(TOBasis* tb, BasisList *bl)
	{
		return tb->DeleteOpanduan(bl);
	}
private:
	BasisList*m_headList;
	int m_nBasisList;//����
protected:	
	int SetMoveTo();//
	int FindMoveTo(void *ms, int x, int y);//�����ƶ�·��
	void GetBasisRect(int type, LPRECT lr); 
	bool InBasisHBit(int x, int y, int type);
	int Draw(HDC hdc, int x, int y, int cx, int cy, HDC hdctop, int rx, int ry);
	int Xunlu(int *x, int *y, int endx, int endy, int speed);
	int Baozha(int type);
	bool m_bhdc;//�豸��ʹ��״̬
	HDC		m_hdcM;	//�ɰ�
	HDC		m_hdc1;	//����͸����ͼ
	HDC		m_hdc2;	//����͸����ͼ
	HBITMAP m_hbitM;//�ɰ�
	HBITMAP m_hbit1;//����͸����ͼ
	HBITMAP m_hbit2;//����͸����ͼ
	HPEN m_hpen;
	HFONT m_hFont;
	GamesLevels* m_pgameslevels;
};

//void DrawBasis(TOBasis* b,HDC hdc)
//{
//	b->DrawOne(hdc, 0,0,0);
//}

#endif