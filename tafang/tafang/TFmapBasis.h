#ifndef    __TFMAPBASIS__
#define	   __TFMAPBASIS__
#include "resource.h"

//0x0000
//第一位1表示无法通行；0表示可以通行


#define TYPE_KONG   0x00	//空		0000 0000
#define TYPE_ZHEBI	0x01	//遮蔽物	0000 0001
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
	UINT type;//遮蔽物类型
	UINT icheng;//0表示最前面，10表示最后面
	int x;	//位置
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

//地图遮蔽物。需要动态添加以及删除，因此使用链表
struct TFmapShelter
{
	TFAttribute type;//总体
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

//地图基础类
class TFmapBasis
{
public:
	TFmapBasis(void);
	~TFmapBasis(void);
// 	int m_width;
// 	int m_height;
	int InitInstance();//初始化地图类
	int setBkbitmap(HBITMAP hbitmap);//初始化背景贴图
	int addShelter(TFmapShelter* type,int iPors);//添加Shelter，要求type为new的变量
	int deleteShelter(int iPors);
	int setTFAttribute(TFAttribute* type,int iPors);
	int getTFAttribute(TFAttribute* type,int iPors);
	int paint(HDC hdc);
protected:
	
	TFmapShelter *m_tfattribute;//链表头部
	int m_tfipos;		//链表中元素个数
	HBITMAP m_hBKbitmap;//背景贴图
	HBITMAP m_hbitmap;//保存遮蔽物
	HDC m_hBKdc;		//背景图DC
	HDC m_hdc;			//遮蔽物DC
	int m_width;
	int m_height;

public:
	//单个的元素

};

#endif