#include"AStarWayFinding.h"
#include<iostream>
#define ROWS   10
#define COLS   10
//二维数组描述地图		0 空地  可以行走  1 障碍 不可以行走
int map[ROWS][COLS] = {
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 1, 1, 1, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }
};

int main()
{
	//判断map[r][c] 是否是障碍
	auto fun = [=](int r, int c) {	return map[r][c]; };

	AStarWayFinding s(2, 2, 4, 8);
	std::deque<Point> path;
	s.wayFinding(&path, fun);

	for (auto& val : path)
	{
		std::cout <<"("<<val.x << "," << val.y << ")  ,";
	}
	std::cout << std::endl;
	path.clear();


	//重新寻路
	s.setBegEndPos(3, 6, 9, 2);
	s.wayFinding(&path, fun);

	for (auto& val : path)
	{
		std::cout << "(" << val.x << "," << val.y << ")  ,";
	}


	return 0;
}
