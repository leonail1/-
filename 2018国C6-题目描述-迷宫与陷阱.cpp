/*题目描述

小明在玩一款迷宫游戏，在游戏中他要控制自己的角色离开一间由 N×N 个格子组成的 2D 迷宫。

小明的起始位置在左上角，他需要到达右下角的格子才能离开迷宫。

每一步，他可以移动到上下左右相邻的格子中（前提是目标格子可以经过）。

迷宫中有些格子小明可以经过，我们用 '.' 表示。

有些格子是墙壁，小明不能经过，我们用 '#' 表示。

此外，有些格子上有陷阱，我们用 'X' 表示。除非小明处于无敌状态，否则不能经过。

有些格子上有无敌道具，我们用 '%' 表示。

当小明第一次到达该格子时，自动获得无敌状态，无敌状态会持续 K 步。

之后如果再次到达该格子不会获得无敌状态了。

处于无敌状态时，可以经过有陷阱的格子，但是不会拆除/毁坏陷阱，即陷阱仍会阻止没有无敌状态的角色经过。

给定迷宫，请你计算小明最少经过几步可以离开迷宫?


输入描述

第一行包含两个整数 N,K (1≤N≤1000,1≤K≤10)。

以下 N 行包含一个 N×N 的矩阵。

矩阵保证左上角和右下角是 '.'。

输出描述

一个整数表示答案。如果小明不能离开迷宫，输出 -1。

输入输出样例

示例

输入
5 3
...XX
##%#.
...#.
.###.
.....

输出
10

运行限制

最大运行时间：3s
最大运行内存: 256M
*/
#include<string>
#include<iostream>
#include<queue>
#include<fstream>
using namespace std;
struct node{
    int x;
    int y;
    int dis;
    int energy;//在当前位置无敌状态还剩多少
    node(int a,int b,int c,int f):x(a),y(b),dis(c),energy(f){}
};

int n,k;
vector<vector<char>> map;//地图
int vis[1010][1010][11]={0};//是否在能量为n的状态下访问过某个节点
queue<node> que;
int tx,ty;
char ch;//存地图的临时变量
int bfs(){
    while(que.size())//队列里还有节点
    {
        node t=que.front();
        que.pop();
        int x=t.x;
        int y=t.y;
        int m=t.energy;
        int step=t.dis;
        if(x==n-1&&y==n-1){
            return step;
        }
        for(int ctrl=0;ctrl<4;ctrl++)
        {
            switch (ctrl) {
                case 0://右
                {
                    ty=y+1;
                    tx=x;
                    break;
                }
                case 1://下
                {
                    tx=x+1;
                    ty=y;
                    break;
                }
                case 2://左
                {
                    ty=y-1;
                    tx=x;
                    break;
                }
                case 3://上
                {
                    tx=x-1;
                    ty=y;
                    break;
                }
            }//用switch代替方向向量向四个方向遍历
            if(tx<0||ty<0||tx>=n||ty>=n||map[tx][ty]=='#'){
                continue;
            }//越界或撞墙
            if(map[tx][ty]=='%')//无敌道具
            {
                //能量石没吃过
                if(!vis[tx][ty][k]){
                    vis[tx][ty][k]=1;
                    node tmp(tx,ty,step+1,k);
                    //第一次吃无敌道具，则当前节点能量要为k
                    que.push(tmp);
                }
                //吃过能量石，且此路未在此能量下走过
                if(!vis[tx][ty][max(0,m-1)]){
                    vis[tx][ty][max(0,m-1)]=1;
                    node tmp(tx,ty,step+1,max(0,m-1));
                    que.push(tmp);
                }
            }
            else if(map[tx][ty]=='X'){
                if(m&&!vis[tx][ty][max(0,m-1)])//有能量并且没在此能量下走过
                {
                    vis[tx][ty][max(0,m-1)]=1;
                    node tmp(tx,ty,step+1,max(0,m-1));
                    que.push(tmp);
                }
            }
            else{//道路
                if(!vis[tx][ty][max(0,m-1)]){
                    vis[tx][ty][max(0,m-1)]=1;
                    node tmp(tx,ty,step+1,max(0,m-1));
                    que.push(tmp);
                }
            }
        }
    }
    return -1;//遍历了队列所有节点仍没有达到终点，则终点不可达。
}

int main()
{
    
    cin>>n>>k;
    ch=getchar();//换行符
    node tmp(0,0,0,0);//起点节点先入队
    que.push(tmp);
    for(int i=0;i<n;i++)
    {
        map.push_back(vector<char>());
        for(int j=0;j<n;j++)
        {
            scanf("%c",&ch);
            if(ch=='\n')scanf("%c",&ch);
            map[i].push_back(ch);
        }
    }
    vis[0][0][0]=1;//起点一定在能量为0的状态下访问过
    
    cout<<bfs();
    
    return 0;
}


