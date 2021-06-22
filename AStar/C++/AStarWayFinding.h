#pragma once
#include<vector>
#include<deque>


enum Price { ZXDJ = 10, XXDJ = 14 };	//ZXDJ直线代价 XXDJ斜线代价
//点类型
struct MyPoint {
	MyPoint(int r =0,int c = 0)
	{
		this->r = r;
		this->c = c;
		f = 0;
		g = 0;
		h = 0;
	}
	int r;		//x
	int c;		//y
	int f;
	int g;
	int h;
};

//树结构
struct  TreeNode 
{
	TreeNode(int x, int y);
	TreeNode(const MyPoint& pos);
	int getH(TreeNode* endPos);
	int getF();
	bool operator==(const TreeNode& right) const;
	MyPoint		pos;		//当前点
	TreeNode*	father;	//指向父节点的指针
};

struct Point
{
	Point(TreeNode* node)
	{
		x = node->pos.r;
		y = node->pos.c;
	}
	short x;
	short y;
};

//A*寻路算法
class AStarWayFinding
{
	
public:
	AStarWayFinding(int begx, int begy, int endx, int endy):curNode(nullptr),childNode(nullptr)
	{
		begNode = new TreeNode(begx, begy);
		endNode = new TreeNode(endx, endy);

		close_list.push_back(begNode);
		curNode = begNode;
	}
	//可以重新开始从begin到endx寻路
	void setBegEndPos(int begx, int begy, int endx, int endy)
	{
		begNode->pos = MyPoint(begx, begy);
		endNode->pos = MyPoint(endx, endy);

		close_list.clear();
		close_list.push_back(begNode);
		curNode = begNode;

		open_list.clear();
		if (childNode)
		{
			delete childNode;
			childNode = nullptr;
		}
	}
	//传入障碍物判断函数
	template<typename Compare>
	bool wayFinding(std::deque<Point> *result,Compare fun,int minx=0,int maxx= 999999,int miny=0,int maxy=999999)
	{	
		while (true)
		{
			//找到当前点周围能走的点(遍历以当前点为中心的九宫格)
			for (int x = curNode->pos.r - 1; x <= curNode->pos.r + 1; x++)
			{
				for (int y = curNode->pos.c - 1; y <= curNode->pos.c + 1; y++)
				{
					if ((x >= minx && x<maxx  && y>=miny &&  y < maxy)) //越界处理，此时不需要
					{
						childNode = new TreeNode(x, y);
						//判断是直线还是斜线,计算g值
						if (x == curNode->pos.r || y == curNode->pos.c)
						{
							childNode->pos.g += Price::ZXDJ;
						}
						else
						{
							childNode->pos.g += Price::XXDJ;
						}
						//计算h值
						childNode->getH(endNode);
						//计算f值
						childNode->getF();

						//入树,加入open_list,加入close_list,标记走过
						if (canWalk(childNode, fun))
						{															
							childNode->father = curNode;
							open_list.push_back(childNode);
							/*printf("(%d,%d) %3d=%3d+%3d    ", childNode->pos.r, childNode->pos.c,
								childNode->pos.f, childNode->pos.g, childNode->pos.h);*/
						}
						else
						{
							//printf("                     ");
							delete childNode;
							childNode = nullptr;
						}

					}
				}
				//printf("\n");
			}
			//printf("\n");
			//找出数组中f值最小的点
			auto itMin = open_list.begin();
			for (auto it = open_list.begin(); it != open_list.end(); it++)
			{
				if ((*it)->pos.f < (*itMin)->pos.f)
					itMin = it;
			}
			//设置为当前点
			curNode = *itMin;
			open_list.erase(itMin);
			close_list.push_back(curNode);
					
			//找到终点啦
			if (findDest()) 
			{
				while (curNode)
				{
					result->push_front(Point(curNode));				
					curNode = curNode->father;
				}
				return true;
			}
			//到不了目的地
			if (open_list.empty())
			{
				return false;
			}				
		}
	}
private:
	template<typename Compare>
	bool canWalk(TreeNode* node,Compare fun)
	{
		//已经走过了
		bool isok = std::find_if(close_list.begin(), close_list.end(), 
			[=](auto& item) ->bool{return (*item) == (*node); })!=close_list.end();
		if (isok)
		{
			return false;
		}
		//是障碍
		if (fun(node->pos.r,node->pos.c))
		{
			return false;
		}
		return true;
	}
	//判断是否找到了目的地
	bool findDest()
	{
		if (curNode->pos.r == endNode->pos.r &&
			curNode->pos.c == endNode->pos.c) 
		{
			return true;
		}
		return false;
	}
private:
	TreeNode* begNode;	//开始点
	TreeNode* endNode;	//结束点
	TreeNode* curNode;	//当前点
	TreeNode* childNode;

	std::vector<TreeNode*> open_list;	
	std::vector<TreeNode*> close_list;
};

