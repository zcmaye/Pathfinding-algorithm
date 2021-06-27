#include"source/AStar.hpp"
#include<iostream>
#include<time.h>
#define ROWS   400
#define COLS   400
//二维数组描述地图		0 空地  可以行走  1 障碍 不可以行走
int map[ROWS][COLS];
//读取地图文件数据到map
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
//把map中的数据写入到地图文件
void saveMap(int map[ROWS][COLS], const char* fileName)
{
	FILE* fp = fopen(fileName, "w");
	if (fp == NULL)
	{
		perror("文件打开失败:");
		return;
	}
	for (int i = 0; i < ROWS; i++)
	{
		for (int k = 0; k < COLS; k++)
		{
			fprintf(fp, "%d,", map[i][k]);
		}
		fputc('\n', fp);
	}
	fclose(fp);
	printf("save over...\n");
}
//把walls中的数据写入到地图文件
void wallsSave(AStar::Generator& gen,const char*fileName)
{
	FILE* fp = fopen(fileName, "w");
	if (!fp)
	{
		perror("文件打开失败：");
		return;
	}
	for (int i = 0; i < ROWS; i++)
	{
		for (int k = 0; k < COLS; k++)
		{
			if (gen.detectCollision({ k,i }))
			{
				fputs("1,", fp);
			}
			else
			{
				fputs("  ", fp);
			}
		}
		fputc('\n', fp);
	}
	fclose(fp);
}
int main()
{
	initMap(map, "./五行宫殿.txt");

	AStar::Generator generator;
	// Set 2d map size.
	generator.setWorldSize({ ROWS, COLS });
	generator.setDiagonalMovement(true);

	clock_t begin = clock();
	for (int i = 0; i < ROWS; i++)
	{
		for (int k = 0; k < COLS; k++)
		{
#if 1		
			//把可行走(0)周围的障碍(1)加入到碰撞检测中 只有6742个障碍，是下面的方法的效率的17倍，但是开始加载的时候慢一点
			if (map[i][k] == 0)
			{
				for (int r = i - 1; r <= i + 1; r++)
				{
					for (int c = k - 1; c <= k + 1; c++)
					{
						if (r >= 0 && r < ROWS && c >= 0 && c < COLS)
						{
							if (map[r][c] && !generator.detectCollision({ c,r }))
							{
								generator.addCollision({ c,r });
							}
						}
					}
				}
			}
#else		
			//把所有障碍加入到碰撞检测中 119172个障碍，遍历比较慢
			if (map[i][k] == 1)
			{
				generator.addCollision({ k,i });
			}
#endif // 0		
		}
	}
	//wallsSave(generator,"res.txt");
	std::cout <<"初始化障碍物耗时："<< clock() - begin <<"ms"<< std::endl;


	std::cout << "Generate path ... \n";
	
	AStar::CoordinateList beg = { {154,051 },{185,276} };
	AStar::CoordinateList end = { {299,300 },{250,229} };
	int curi = 0;

	begin = clock();
	auto path = generator.findPath(beg[curi],end[curi]);
	std::cout << "寻路耗时：" << clock() - begin << "ms" << std::endl;

	if (path.size() == 1 && path.front() == beg[curi])
		std::cout << "查找失败" << std::endl;
	else
	{
		for (auto& coordinate : path)
		{
			std::cout << "(" << coordinate.x << "," << coordinate.y << ")" << std::endl;
		}
	}


	return 0;
}