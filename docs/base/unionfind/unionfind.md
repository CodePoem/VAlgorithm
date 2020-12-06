# Union-Find

并查集算法，解决图论中“动态连通性”问题。
通俗点来讲，就是人以类聚，物以群分。分完类，方便查询。

- 合并（Union）：把两个不相交的集合合并为一个集合。
- 查询（Find）：查询两个元素是否在同一个集合中。

## 连通

连通，即归为一类。

1. 自反性：节点 A 和 B 是连通的。
2. 对称性：如果节点 A 和 B 连通，那么 B 和 A 也连通。
3. 传递性：如果节点 A 和 B 连通，B 和 C 连通，那么 A 和 C 也连通。

## 连通分量

连通分量，即类别总数。

## 核心算法

以节点指向表示节点归属分类的依据，构建出多一颗或多颗分类树。树的棵树即为分类总数，查询时，查询到树的根节点即可知晓分类。

```C++
#include <iostream>

using namespace std;

// 连通分量
int unionSize = 0;

// 节点 x 的父节点是 father[x]
int *father;

// 初始化
void init(int size)
{
    // 一开始互不连通
    unionSize = size;
    // 父节点指针初始指向自己
    father = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        father[i] = i;
    }
}

// 合并
void merge(int pointA, int pointB)
{
    int fatherA = find(pointA);
    int fatherB = find(pointB);
    father[fatherA] = fatherB;
}

// 查询
int find(int point)
{
    while (father[point] != point)
    {
        point = father[point];
    }
    return point;
}
```

极端情况下，构建的归属树可能退化成链表。问题的关键在于，如何想办法避免树的不平衡呢？

### 按秩归并

针对合并过程优化。小一些的树接到大一些的树下面，这样就能避免头重脚轻，更平衡一些。

### 按树高归并

```C++
// 等级 用于按秩归并优化
int *unionRank;

// 初始化
void init(int size)
{
    // 一开始互不连通
    unionSize = size;
    // 父节点指针初始指向自己
    father = (int *)malloc(sizeof(int) * size);
    unionRank = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        father[i] = i;
        // 初始化树的高度为1
        unionRank[i] = 1;
    }
}

// 合并
void merge(int pointA, int pointB)
{
    int fatherA = find(pointA);
    int fatherB = find(pointB);
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
}
```

### 按规模归并

```C++

// 等级 用于按秩归并优化
int *unionRank;

// 初始化
void init(int size)
{
    // 一开始互不连通
    unionSize = size;
    // 父节点指针初始指向自己
    father = (int *)malloc(sizeof(int) * size);
    unionRank = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        father[i] = i;
        // 初始化树的规模为1
        unionRank[i] = 1;
    }
}

// 合并
void merge(int pointA, int pointB)
{
    int fatherA = find(pointA);
    int fatherB = find(pointB);
    if (unionRank[pointA] <= unionRank[pointB])
    {
        father[fatherA] = fatherB;
        unionRank[fatherB] += unionRank[fatherA];
    }
    else
    {
        father[fatherB] = fatherA;
        unionRank[fatherA] += unionRank[fatherB];
    }
}
```

### 路径压缩优化

针对查找可以进行优化。（阶级管理趋于扁平化管理）

#### 第一种

在查询过程中顺带优化树每层，高度不大于 3 ，层层跨越直接父级。

```C++
// 查询
int find(int point)
{
    while (father[point] != point)
    {
        // 进行路径压缩 （第一种 不是最优）
        father[point] = father[father[point]];
        point  father[point];
    }
    return point;
}
```

#### 第二种

优化为高度为 1 的树，即每个子节点都直接指向根节点。

```C++
// 查询
int find(int point)
{
    while (father[point] != point)
    {
        // 进行路径压缩 （第二种 最优）
        father[point] = find(father[point]);
        point = father[point];
    }
    return point;
}
```

## 完整代码

```C++
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

```
