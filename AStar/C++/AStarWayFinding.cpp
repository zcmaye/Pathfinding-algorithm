#include"AStarWayFinding.h"

/*
* @Ê÷½á¹¹
*/
TreeNode::TreeNode(int x, int y) :father(nullptr)
{
	pos.r = x;
	pos.c = y;

}
TreeNode::TreeNode(const MyPoint& pos) :TreeNode(pos.r, pos.c)
{
}
int TreeNode::getH(TreeNode* endPos)
{
	pos.h = (abs(pos.r - endPos->pos.r) +
		abs(pos.c - endPos->pos.c)) * Price::ZXDJ;
	return pos.h;
}
int TreeNode::getF()
{
	return pos.f = pos.g + pos.h;
}
bool TreeNode::operator==(const TreeNode& right) const
{
	return(pos.r == right.pos.r && pos.c == right.pos.c);
}