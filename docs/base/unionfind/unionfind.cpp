#include <iostream>
#include <vector>

using namespace std;

// 连通分量
int unionSize = 0;

// 节点 x 的父节点是 father[x]
int *father;

// 等级 用于按秩归并优化
int *unionRank;

// 初始化
void init(int size)
{
    // 一开始互不连通
    unionSize = size;
    // 初始化动态大小数组
    father = (int *)malloc(sizeof(int) * size);
    unionRank = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        // 父节点指针初始指向自己
        father[i] = i;
        // 初始化树的高度为 1
        unionRank[i] = 1;
    }
}

// 查询
int find(int point)
{
    while (father[point] != point)
    {
        // 进行路径压缩 （第一种 不是最优）
        // father[point] = father[father[point]];
        // 进行路径压缩 （第二种 最优）
        father[point] = find(father[point]);
        point = father[point];
    }
    return point;
}

// 合并
void merge(int pointA, int pointB)
{
    int fatherA = find(pointA);
    int fatherB = find(pointB);
    // 按树的高度进行合并 树高度小的合并到树高度大的
    if (unionRank[pointA] <= unionRank[pointB])
    {
        father[fatherA] = fatherB;
    }
    else
    {
        father[fatherB] = fatherA;
    }
    if (unionRank[pointA] == unionRank[pointB] && pointA != pointB)
    {
        unionRank[pointB] += 1;
    }
    unionSize--;
}

int main()
{
    init(20);
    merge(1,3);
    merge(2,4);
    merge(5,7);
    merge(3,7);
    merge(6,9);
    merge(2,6);
    cout<< unionSize << endl;
}
