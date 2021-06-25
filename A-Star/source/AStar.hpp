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

//�����ռ�
namespace AStar
{
    //����
    struct Vec2i
    {
        int x, y;

        bool operator == (const Vec2i& coordinates_);
    };

    using uint = unsigned int;
    using HeuristicFunction = std::function<uint(Vec2i, Vec2i)>;
    using CoordinateList = std::vector<Vec2i>;

    //�ڵ�
    struct Node
    {
        uint G, H;              
        Vec2i coordinates;      //����
        Node *parent;           //���ڵ�

        Node(Vec2i coord_, Node *parent_ = nullptr);
        //��ȡ���� ��Fֵ
        uint getScore();
    };

    using NodeSet = std::vector<Node*>;

    class Generator
    {
    public:
        //��ײ���
        bool detectCollision(Vec2i coordinates_);
        //���������Ƿ��ڼ�����
        Node* findNodeOnList(NodeSet& nodes_, Vec2i coordinates_);
        //�ͷż������нڵ�
        void releaseNodes(NodeSet& nodes_);

    public:
        Generator();
        //���õ�ͼ��С
        void setWorldSize(Vec2i worldSize_);
        //���öԽ��˶�
        void setDiagonalMovement(bool enable_);
        //����̽����ʽ
        void setHeuristic(HeuristicFunction heuristic_);
        //����·��
        CoordinateList findPath(Vec2i source_, Vec2i target_);
        //�����ײ��
        void addCollision(Vec2i coordinates_);
        //�Ƴ���ײ��
        void removeCollision(Vec2i coordinates_);
        //���������ײ��
        void clearCollisions();

    private:
        HeuristicFunction heuristic;        //��������
        CoordinateList direction, walls;    //direction����walls�ϰ��б�
        Vec2i worldSize;                    //��ͼ��С
        uint directions;                    //���������ĸ������ǰ˸�����
    };

    //������ʽ
    class Heuristic
    {
        //��ȡ����������x,y�ľ���
        static Vec2i getDelta(Vec2i source_, Vec2i target_);

    public:
        //������
        static uint manhattan(Vec2i source_, Vec2i target_);
        //ŷ�����
        static uint euclidean(Vec2i source_, Vec2i target_);
        //�˱���
        static uint octagonal(Vec2i source_, Vec2i target_);
    };
}

#endif // __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__
