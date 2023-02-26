#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<math.h>
using namespace std;

unsigned long long result=0;
int vis[4][4]={0};

int dx[4]={0,1,0,-1};//右下左上
int dy[4]={1,0,-1,0};

bool check(int x,int y)
{
    if(vis[x][y]||x<0||y<0||x>3||y>3)
    {
        return 0;
    }
    return 1;
}

void dfs(int x,int y,int step)
{
    if(step==16)
    {
        result++;
        return;
    }
    for(int i=0;i<4;i++)
    {
        int tx=x+dx[i];
        int ty=y+dy[i];
        if(check(tx, ty))
        {
            vis[tx][ty]=1;
            dfs(tx, ty, step+1);
            vis[tx][ty]=0;
        }
    }
}

int main()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            vis[i][j]=1;//注意此处，开始搜索的坐标点必须已访问
            dfs(i, j, 1);
            vis[i][j]=0;
        }
    }
    cout<<result;
    return 0;
}


