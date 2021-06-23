#include"AStarWayFinding.h"
#include<iostream>
#define ROWS   400
#define COLS   400
//二维数组描述地图		0 空地  可以行走  1 障碍 不可以行走
int map[ROWS][COLS];
void initMap(int map[ROWS][COLS],const char*fileName)
{
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		perror("文件打开失败:");
		return;
	}
	char buf[3] = { 0 };
	for (int  i = 0; i < ROWS; i++)
	{
		for (int  k= 0; k < COLS; k++)
		{
			fscanf(fp, "%d,", &map[i][k]);		
			if (k == COLS - 1)
			{			
				fread(buf, sizeof(char), 3, fp);
			}
		}
	}
	fclose(fp);
	printf("loadimg over...\n");
}

void showMap(int map[ROWS][COLS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int k = 0; k < COLS; k++)
		{
			printf("%d ", map[i][k]);
		}
		printf("\n");
	}
}

int main()
{
	initMap(map, "./五行宫殿.txt");
	printf("beg:(%d)  end(%d)\n", map[287][310], map[300][260]);
	//for (int i = 200; i < 400; i++)
	//{

	//	printf("(%d %d)  ", map[300][i],i);
	//}


	//initMap(map, "./test.txt");
	//showMap(map);

	//判断map[r][c] 是否是障碍
	auto fun = [=](int r, int c) {	return map[r][c]; };

	AStarWayFinding s(287, 310, 300, 299);
	//AStarWayFinding s(287, 310, 300, 233);
	std::deque<Point> path;
	s.wayFinding(&path, fun,0,400,0,400);

	for (auto& val : path)
	{
		std::cout <<"("<<val.x << "," << val.y << ")  ,";
	}
	std::cout << std::endl;
	path.clear();


	////重新寻路
	//s.setBegEndPos(3, 6, 9, 2);
	//s.wayFinding(&path, fun);

	//for (auto& val : path)
	//{
	//	std::cout << "(" << val.x << "," << val.y << ")  ,";
	//}


	return 0;
}
