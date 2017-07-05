#ifndef __STUNT__
#define __STUNT__
#include "TOBasis.h"

#define STUNT_BAOZHA	0
#define STUNT_JIZHONG	1

//�ؼ�
struct STUNT :public Basis
{
	//int x;
	//int y;
	//int type;
	int cx;
	int cy;
	int nn;
	int nm;
	STUNT()
	{
		//x = 0;
		//y = 0;
		//type = 0;
		cx = 0;
		cy = 0;
		nn = 0;
		nm = 0;
	}
};

struct StuntList:BasisList
{
	STUNT tj;
	//struct StuntList*Next=NULL;
	//struct StuntList*Pre=NULL;
};


class TOStunt :public TOBasis
{
public:
	TOStunt();
	~TOStunt();
	int InitStunt();
	int ReleaseStunt();
	int DrawOne(HDC hdc, int x, int y, int type);
	int DrawALL(HDC hdc);
	int Baozha(int x,int y,int type);


	StuntList*CreateStuntList(STUNT *tj);
	StuntList*DeleteStuntList(StuntList*tjl);
	int DeleteOT(BasisList*bl);//ɾ����Աǰִ�еĶ���Ĳ���
	int DeleteOEnd(BasisList*bl);//ɾ����Ա��ִ�еĶ���Ĳ���
	bool DeleteOpanduan(BasisList*bl);//ɾ����Ա��Ҫִ�еĶ���Ĳ���

	unsigned int m_uStuntRunThreadID;//����ID
	StuntList *m_headListStunt;
	bool GetInitStunt()
	{
		return m_bInitStunt;
	}
private:
	HBITMAP m_hbitteji;
	HDC m_hdcteji;
	bool m_bInitStunt;

};

#endif