POINTS zuozhuan(POINTS point)
{
	point.x = point.x^point.y;
	point.y = point.x^point.y;
	point.x = point.x^point.y;
	point.y = -point.y;
	return point;
}

int zhaolu()
{
	int map[10][10];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			map[i][j] = rand() % 3;
			//1表示可以通过，0表示不能通过
		}
	}
	//从（0，0）到（9，9）
	POINTS poend = { 9, 9 };
	POINTS pnew = { 0, 0 };
	POINTS pnewt;
	POINTS sudu = { 0, 1 };
	POINTS sudut = zuozhuan(sudu);
	POINTS p[100] = { 0 };//100步以内
	for (int i = 0, j = 0; i < 99; i++)
	{
		pnewt.x = pnew.x + sudut.x;
		pnewt.y = pnew.y + sudut.y;
		if (pnewt.x >= 0 && pnewt.x < 10 && pnewt.y >= 0 && pnewt.y < 10)//判断左边
		{
			if (map[pnewt.x][pnewt.y] != 0)//此时可以左转
			{
				sudu = sudut;
				sudut = zuozhuan(sudu);
			}
		}
		pnewt.x = pnew.x + sudu.x;
		pnewt.y = pnew.y + sudu.y;
		if (pnewt.x >= 0 && pnewt.x < 10 && pnewt.y >= 0 && pnewt.y < 10)//判断左边
		{
			if (map[pnewt.x][pnewt.y] != 0)//可以向前走一格
			{
				p[j].x = pnewt.x;
				p[j].y = pnewt.y;
				j++;
			}
			else//转向
			{
				sudu.x = -sudu.x;
				sudu.y = -sudu.y;
				sudut = zuozhuan(sudu);
			}
		}
		if (p[i].x == 9 && p[i].y == 9)
		{
			break;
		}
	}
	return 0;
}