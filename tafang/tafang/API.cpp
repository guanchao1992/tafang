#include "stdafx.h"
#include "API.h"
namespace yanshifree
{
	struct ysfree
	{
		void*f;
		bool by = false;
		ysfree*Pre;
		ysfree*Next;
	};
	ysfree * head;
	//int num = 0;
	unsigned __stdcall yanshiFreeRun(void*lp)//��ʱfree
	{
		while (1)
		{
			ysfree *Temp = head->Next;
			ysfree *Pre = head;
			while (Temp!=head)
			{
				if (Temp->by)
				{
					free(Temp->f);
					Temp->Next->Pre = Temp->Pre;
					Temp->Pre->Next = Temp->Next;
					free(Temp);
					//num--;
					Temp = Pre->Next;
				}
				else
				{
					Temp->by = true;
				}
				Pre = Temp;
				Temp = Temp->Next;
			}
			Sleep(3000);
		}
		return 0;
	}

	bool InityanshiFree()
	{
		_beginthreadex(NULL, 0, &yanshiFreeRun, NULL, 0, NULL);
		head = (ysfree*)malloc(sizeof(ysfree));
		head->Next = head;
		head->Pre = head;
		return true;
	}
	void* CreateFreeBasis(void*lp)
	{
		//num++;
		ysfree*yf = (ysfree*)malloc(sizeof(ysfree));
		yf->f = lp;
		yf->by = false;
		yf->Next = head;
		yf->Pre = head->Pre;
		head->Pre->Next = yf;
		head->Pre = yf;
		return yf;
	}
};
int malcmp(const char*ta, const char*tb, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (*(ta)> *(tb))return 1;
		else if (*(ta) < *(tb))return -1;
		ta++;
		tb++;
	}
	return 0;
}
//strchr()��strstr�������ͬ���Ĺ���
unsigned int findstr(const char *buffer, int len, const char*str)
{
	char cbufe[1024];
	int ini = 0, n = 0;
	const char*endpos = &buffer[len];
	do
	{
		ini = (int)find(&buffer[n], endpos, str[0]);
		if (ini != -1)
		{
			n = ini - (int)&buffer[0];
			strncpy(cbufe, &buffer[n],1023);
			if (malcmp(&buffer[n],str, strlen(str)) == 0)
			{
				return ini;
			}
			n++;
		}
	} while (n<len);

	return 0;
}

unsigned int  yanshiFree(void*lp)
{
	yanshifree::CreateFreeBasis(lp);
	return 0;
}

void InityanshiFree()
{
	yanshifree::InityanshiFree();
}

bool JudgeRectTo(const LPRECT r1,const LPRECT r2)
{
	if (r1->left<r2->right&&r1->right>r2->left&&
		r1->top<r2->bottom&&r1->bottom>r2->top)
		return true;
	return false;
}

int xunluA(PointF*pmap, int w, int h, POINTS p1, POINTS p2, POINTS*point, int len)
{
	PointFPList m_trueList;//�����б�
	PointFPList m_falseList;//�ر��б�

	//PointF(*pmap)[40];
	//PointF pmap[30][30];



	//pmap[p1.x][p1.y].btrue = true;
	//pmap[p2.x][p2.y].btrue = true;
	(pmap + p1.y*w + p1.x)->btrue = true;
	(pmap + p2.y*w + p2.x)->btrue = true;
	//���жϵ�ǰ����Χ�ĵ��Ƿ�Ϊ�ڱ�
	//�жϵ�ǰ����Χ�ĵ��Ƿ��ڹر��б�Ϳ����б���
	//�ڹر��б��еĲ��迼��
	//�ڿ����б��еĵ�Ƚ�ԭ��Gֵ�͵�ǰ�����Gֵ������С��

	PointF*pnew = (pmap + p1.y*w + p1.x);
	PointF*pnel;
	int x = 0, y = 0, ng = 0, ntrue = 0;
	do
	{
		for (int i = -1; i < 2; i++)					  //��һ�������߷�
		{												  //��һ�������߷�
			for (int j = -1; j < 2; j++)				  //��һ�������߷�
			{											  //��һ�������߷�
				if ((i == 0 && j == 0) || (i*j != 0))continue;//��һ�������߷�
				if (i == 0 || j == 0)ng = 10;
				else ng = 14;
				x = pnew->x + i;
				y = pnew->y + j;
				if (x >= 0 && x < w && y >= 0 && y < h)//��ȥ��ͼ��ص�
				{
					//�Ƿ����ͨ��,�Ƿ��ڹر��б���
					if ((pmap+y*w+x)->btrue&&m_falseList.InList((pmap+y*w+x)) == false)
					{
						//�Ƿ��ڿ����б���
						if (m_trueList.InList((pmap+y*w+x)))
						{
							//�ж�Gֵ��С
							if ((pmap+y*w+x)->G  > pnew->G + ng)
							{
								(pmap+y*w+x)->F = (pmap+y*w+x)->G + (pmap+y*w+x)->H;
								(pmap+y*w+x)->G = pnew->G + ng;
								(pmap+y*w+x)->Pre = pnew;
							}
						}
						else
						{
							//���ڿ����б��оͽ��õ���ӵ������б���
							(pmap+y*w+x)->G = pnew->G + ng;
							(pmap+y*w+x)->F = (pmap+y*w+x)->G + (pmap+y*w+x)->H;
							(pmap+y*w+x)->Pre = pnew;
							m_trueList.AddPointF((pmap+y*w+x));
						}
					}
				}
			}
		}
		if (pnew->x == p2.x&&pnew->y == p2.y)//����Ŀ�ĵ�
			break;
		if (m_falseList.InList(pnew) == false)
			m_falseList.AddPointF(pnew);
		pnel = pnew;
		pnew = m_trueList.GetminF();

		m_trueList.DeletePointF(pnew);
		for (int i = 0; i < ntrue; i++)
		{
			if (pnel == NULL)break;
			pnel = pnel->Pre;
			pnew = pnel;
		}
		if (pnew == NULL)
		{
			ntrue++;
		}
		else
		{
			ntrue = 0;
		}
	} while (pnew);
	int i = 0;
	for (; i < len&&pnew; i++)
	{
		point[i].x = pnew->x;
		point[i].y = pnew->y;
		pnew = pnew->Pre;
	}
	point[i + 1].x = -1;
	point[i + 1].y = -1;
	return i;
}
int pintjun()
{
	return 0;
}

int BitmapToRect(HBITMAP hbitmap,HBITMAP hbitout, SIZE& s)
{
	//����λͼ
	BITMAP bitmap,bitmap2;
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bitmap);
	GetObject(hbitout, sizeof(BITMAP), (LPSTR)&bitmap2);
	UCHAR *pbit = (UCHAR*)malloc(bitmap.bmWidthBytes*bitmap.bmHeight + 1);
	UCHAR *pbit2 = (UCHAR*)malloc(bitmap2.bmWidthBytes*bitmap2.bmHeight + 1);
	GetBitmapBits(hbitmap, bitmap.bmWidthBytes*bitmap.bmHeight + 1, pbit);
	//�����
	float fw = (float)bitmap.bmWidth / s.cx;
	float fh = (float)bitmap.bmHeight / s.cy;
	int pi1 = bitmap.bmBitsPixel / 8;
	int pi2 = bitmap2.bmBitsPixel / 8;
	s.cx = s.cx > bitmap2.bmWidth ? bitmap2.bmWidth : s.cx;
	s.cy = s.cy > bitmap2.bmHeight ? bitmap2.bmHeight : s.cy;
	if (pi2 >= 3)
	{
		for (int x = 0; x <s.cx; x++)
		{
			for (int y = 0; y < s.cy; y++)
			{
				for (int i = 0; i < pi2; i++)
				{

					*(pbit2 + pi2*x + y*bitmap2.bmWidthBytes + i) = *(pbit + (((int)(x*fw)*pi1 + (int)(y*fh)*bitmap.bmWidthBytes) + i)); //+ *(pbit + (((int)(x*fw+1)*pi1 + (int)(y*fh+1)*bitmap.bmWidthBytes) + i)))/2 ;


				//	*(pbit2 + y*bitmap2.bmWidthBytes + x) = *(pbit + (((int)(y)*bitmap.bmWidthBytes) + x));

				}
			}
		}
	}

	SetBitmapBits(hbitout, bitmap2.bmWidthBytes*bitmap2.bmHeight, pbit2);
	free(pbit);
	free(pbit2);
	

	return 0;
}