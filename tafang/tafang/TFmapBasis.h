#ifndef    __TFMAPBASIS__
#define	   __TFMAPBASIS__
#include "resource.h"

//0x0000
//��һλ1��ʾ�޷�ͨ�У�0��ʾ����ͨ��


#define TYPE_KONG   0x00	//��		0000 0000
#define TYPE_ZHEBI	0x01	//�ڱ���	0000 0001
#define TYPE_TU		0x11	//			

enum TFtype:char
{
	TFtype_KONG ,
	TFtype_ZHEBI,
	TFtype_TU,
	//TFtype_0000=10000,
	//TFtype_000q = 102000
};
//0000 0000;
struct TFAttribute
{
	UINT type;//�ڱ�������
	UINT icheng;//0��ʾ��ǰ�棬10��ʾ�����
	int x;	//λ��
	int y;
	TFAttribute()
	{
		x = 0;
		y = 0;
		type = 0;
		icheng = 5;
	}
	TFAttribute & operator=(TFAttribute& p)
	{
		if(this == &p) 
			return *this;
		this->type=p.type;
		this->x=p.x;
		this->y=p.y;
		this->icheng=p.icheng;
		return *this;
	}
};

//��ͼ�ڱ����Ҫ��̬����Լ�ɾ�������ʹ������
struct TFmapShelter
{
	TFAttribute type;//����
	TFmapShelter *Pre;
	TFmapShelter *Next;
	TFmapShelter()
	{
		Next=NULL;
		Pre=NULL;
	}
	~TFmapShelter()
	{
		if (Next!=NULL)
		{
			delete Next;
			Next=NULL;
		}
	}
};

//��ͼ������
class TFmapBasis
{
public:
	TFmapBasis(void);
	~TFmapBasis(void);
// 	int m_width;
// 	int m_height;
	int InitInstance();//��ʼ����ͼ��
	int setBkbitmap(HBITMAP hbitmap);//��ʼ��������ͼ
	int addShelter(TFmapShelter* type,int iPors);//���Shelter��Ҫ��typeΪnew�ı���
	int deleteShelter(int iPors);
	int setTFAttribute(TFAttribute* type,int iPors);
	int getTFAttribute(TFAttribute* type,int iPors);
	int paint(HDC hdc);
protected:
	
	TFmapShelter *m_tfattribute;//����ͷ��
	int m_tfipos;		//������Ԫ�ظ���
	HBITMAP m_hBKbitmap;//������ͼ
	HBITMAP m_hbitmap;//�����ڱ���
	HDC m_hBKdc;		//����ͼDC
	HDC m_hdc;			//�ڱ���DC
	int m_width;
	int m_height;

public:
	//������Ԫ��

};

#endif