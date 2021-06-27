#include"source/AStar.hpp"
#include<iostream>
#include<time.h>
#define ROWS   400
#define COLS   400
//��ά����������ͼ		0 �յ�  ��������  1 �ϰ� ����������
int map[ROWS][COLS];
//��ȡ��ͼ�ļ����ݵ�map
void initMap(int map[ROWS][COLS], const char* fileName)
{
	FILE* fp = nullptr;
	fopen_s(&fp,fileName, "r");
	if (fp == nullptr)
	{
		perror("�ļ���ʧ��:");
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
//��map�е�����д�뵽��ͼ�ļ�
void saveMap(int map[ROWS][COLS], const char* fileName)
{
	FILE* fp = fopen(fileName, "w");
	if (fp == NULL)
	{
		perror("�ļ���ʧ��:");
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
//��walls�е�����д�뵽��ͼ�ļ�
void wallsSave(AStar::Generator& gen,const char*fileName)
{
	FILE* fp = fopen(fileName, "w");
	if (!fp)
	{
		perror("�ļ���ʧ�ܣ�");
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
	initMap(map, "./���й���.txt");

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
			//�ѿ�����(0)��Χ���ϰ�(1)���뵽��ײ����� ֻ��6742���ϰ���������ķ�����Ч�ʵ�17�������ǿ�ʼ���ص�ʱ����һ��
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
			//�������ϰ����뵽��ײ����� 119172���ϰ��������Ƚ���
			if (map[i][k] == 1)
			{
				generator.addCollision({ k,i });
			}
#endif // 0		
		}
	}
	//wallsSave(generator,"res.txt");
	std::cout <<"��ʼ���ϰ����ʱ��"<< clock() - begin <<"ms"<< std::endl;


	std::cout << "Generate path ... \n";
	
	AStar::CoordinateList beg = { {154,051 },{185,276} };
	AStar::CoordinateList end = { {299,300 },{250,229} };
	int curi = 0;

	begin = clock();
	auto path = generator.findPath(beg[curi],end[curi]);
	std::cout << "Ѱ·��ʱ��" << clock() - begin << "ms" << std::endl;

	if (path.size() == 1 && path.front() == beg[curi])
		std::cout << "����ʧ��" << std::endl;
	else
	{
		for (auto& coordinate : path)
		{
			std::cout << "(" << coordinate.x << "," << coordinate.y << ")" << std::endl;
		}
	}


	return 0;
}