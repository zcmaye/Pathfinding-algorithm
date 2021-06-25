/*
    Copyright (c) 2015, Damian Barczynski <daan.net@wp.eu>
    Following tool is licensed under the terms and conditions of the ISC license.
    For more information visit https://opensource.org/licenses/ISC.
*/
#ifndef __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__
#define __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__

#include <vector>
#include <functional>
#include <set>

//命名空间
namespace AStar
{
    //坐标
    struct Vec2i
    {
        int x, y;

        bool operator == (const Vec2i& coordinates_);
    };

    using uint = unsigned int;
    using HeuristicFunction = std::function<uint(Vec2i, Vec2i)>;
    using CoordinateList = std::vector<Vec2i>;

    //节点
    struct Node
    {
        uint G, H;              
        Vec2i coordinates;      //坐标
        Node *parent;           //父节点

        Node(Vec2i coord_, Node *parent_ = nullptr);
        //获取评分 即F值
        uint getScore();
    };

    using NodeSet = std::vector<Node*>;

    class Generator
    {
    public:
        //碰撞检测
        bool detectCollision(Vec2i coordinates_);
        //查找坐标是否在集合中
        Node* findNodeOnList(NodeSet& nodes_, Vec2i coordinates_);
        //释放集合所有节点
        void releaseNodes(NodeSet& nodes_);

    public:
        Generator();
        //设置地图大小
        void setWorldSize(Vec2i worldSize_);
        //设置对角运动
        void setDiagonalMovement(bool enable_);
        //设置探索方式
        void setHeuristic(HeuristicFunction heuristic_);
        //查找路径
        CoordinateList findPath(Vec2i source_, Vec2i target_);
        //添加碰撞点
        void addCollision(Vec2i coordinates_);
        //移除碰撞点
        void removeCollision(Vec2i coordinates_);
        //清除所有碰撞点
        void clearCollisions();

    private:
        HeuristicFunction heuristic;        //启发函数
        CoordinateList direction, walls;    //direction方向，walls障碍列表
        Vec2i worldSize;                    //地图大小
        uint directions;                    //搜索方向，四个方向还是八个方向
    };

    //启发方式
    class Heuristic
    {
        //获取两个坐标点的x,y的距离
        static Vec2i getDelta(Vec2i source_, Vec2i target_);

    public:
        //曼哈顿
        static uint manhattan(Vec2i source_, Vec2i target_);
        //欧几里得
        static uint euclidean(Vec2i source_, Vec2i target_);
        //八边形
        static uint octagonal(Vec2i source_, Vec2i target_);
    };
}

#endif // __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__
