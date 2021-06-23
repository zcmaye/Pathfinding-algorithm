#include"source/AStar.hpp"
#include<iostream>
#define ROWS   400
#define COLS   400
//二维数组描述地图		0 空地  可以行走  1 障碍 不可以行走
int map[ROWS][COLS];
void initMap(int map[ROWS][COLS], const char* fileName)
{
	FILE* fp = nullptr;
	fopen_s(&fp,fileName, "r");
	if (fp == nullptr)
	{
		perror("文件打开失败:");
		return;
	}
	char buf[COLS * 2 + 3] = { 0 };
	char* cur = NULL;
	for (int i = 0; i < ROWS; i++)
	{
		fgets(buf, COLS * 2 + 3, fp);
		cur = buf;
		for (int k = 0; k < COLS; k++)
		{
			sscanf_s(cur, "%d,", &map[i][k]);
			cur += 2;
		}
	}
	fclose(fp);
	printf("loadimg over...\n");
}


int main()
{
	initMap(map, "./五行宫殿.txt");

	AStar::Generator generator;
	// Set 2d map size.
	generator.setWorldSize({ 400, 400 });

	generator.setDiagonalMovement(true);

	std::cout << "Generate path ... \n";
	// This method returns vector of coordinates from target to source.
	auto path = generator.findPath({ 51, 152 }, { 300, 299 });

	for (auto& coordinate : path) {
		std::cout << "(" << coordinate.x << "," << coordinate.y << ")" << std::endl;
	}

	return 0;
}