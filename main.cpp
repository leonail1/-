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


