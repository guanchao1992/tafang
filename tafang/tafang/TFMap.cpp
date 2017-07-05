#include "stdafx.h"
#include "TFMap.h"
#include "TowerDefense.h"

int TFMap::ReTf(TFmapShelter*ptfs)//Ë¢ÐÂµØÍ¼ÇøÓò
{
	for (int i = 0; i < m_nw; i++)
	{
		for (int j = 0; j < m_nh; j++)
		{
			tf[i][j] = TFtype_KONG;
		}
	}
	TFmapShelter *TempShelter = ptfs;
	//TFmapShelter *NextShelter;
	while (TempShelter != NULL)
	{
		if (TempShelter->type.type & 0x01)
		{
			tf[TempShelter->type.x / 32][TempShelter->type.y / 32] = TFtype_ZHEBI;
		}
		else if (TempShelter->type.type & 0x01)
		{
			tf[TempShelter->type.x / 32][TempShelter->type.y / 32] = TFtype_TU;
		}
		TempShelter = TempShelter->Next;
	}
	return 0;
}
int TFMap::ReDraw(HWND hWnd, HDC hdc, int ix, int iy)
{
	HPEN hpen = CreatePen(PS_SOLID, 1, RGB(220, 220, 100));
	HPEN hpenW = CreatePen(PS_SOLID, 1, RGB(120, 120, 80));
	HPEN oldpen = (HPEN)SelectObject(hdc, hpen);
	Rectangle(hdc, ix, iy, ix + 8 * m_nw + 1, iy + 8 * m_nh + 1);
	for (int y = 0; y <= m_nh; y++)
	{
		if (y % 4 == 0)SelectObject(hdc, hpenW);
		else SelectObject(hdc, hpen);
		MoveToEx(hdc, ix + 0, iy + y * 4, NULL);
		LineTo(hdc, ix + m_nw * 4, iy + y * 4);
	}
	for (int x = 0; x <= m_nw; x++)
	{
		if (x % 4 == 0)SelectObject(hdc, hpenW);
		else SelectObject(hdc, hpen);
		MoveToEx(hdc, ix + x * 4, iy + 0, NULL);
		LineTo(hdc, ix + x * 4, iy + m_nh * 4);
	}
	for (int x = 0; x < m_nw; x++)
	{
		for (int y = 0; y < m_nh; y++)
		{
			if (tf[x][y])
				BitBlt(hdc, ix+x * 4, iy+y * 4, 4, 4, HDC_Membit, tf[x][y] % 8 * 32, tf[x][y] / 8 * 32, SRCCOPY);

		}
	}
	SelectObject(hdc, oldpen);
	DeleteObject(hpen);
	DeleteObject(hpenW);
	RECT rect = { ix + 0, iy + 0, ix + m_nw * 4, iy + m_nh * 4 };
	InvalidateRect(hWnd, &rect, true);

	return 0;
}