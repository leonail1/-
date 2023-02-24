//
//  main.cpp
//  C++ program
//
//  Created by 木林 on 2023/2/2.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#define END_X 30//地图边界
#define END_Y 50
string min_path;
int minn=0x7fffffff;//最短路径长度
int map[60][60];//1为障碍物，0可以通行
int vis[60][60]={0};//是否已访问
int start_x=0,start_y=0,end_x=END_X-1,end_y=END_Y-1;//起点与终点坐标
int head=1,tail=2;//队列的两个指针
int next_x,next_y;//下一个点的坐标（见后文）
bool flag=0;//终点判断
char cvt[3][3]={'0','U','0',
    'L','0','R',
    '0','D','0'
};
struct que{
    que(int a,int b,int c,int d):x(a),y(b),dis(c),from(d){}
    int x,y,dis,from;
};
vector<que> q;

bool is_legal(int x,int y){
    if(x<0||y<0||x>=END_X||y>=END_Y){
        return 0;
    }
    return 1;
}

int main(int argc, const char * argv[]) {
    ifstream ifs;
    ifs.open("map.txt",ios::in);//打开地图

    que t={start_x,start_y,0,0};//第0个队列不需要，从1开始
    q.push_back(t);
    q.push_back(t);
    vis[start_x][start_y]=1;//起点一定已访问
    
    for(int i=0;i<END_X;i++){
        for(int j=0;j<END_Y;j++){
            char c;
            ifs>>c;
            if(c=='\n')ifs>>c;
            map[i][j]=(int)(c-'0');//由于我用的地图是字符串形式，所以这么读取
        }
    }
    
    while(head<tail){
        for(int ctrl=0;ctrl<4;ctrl++){
            switch (ctrl)
            {
                case 0://D，向下
                {
                    next_x=q[head].x+1;
                    next_y=q[head].y;
                    break;
                }
                case 1://L,向左
                {
                    next_x=q[head].x;
                    next_y=q[head].y-1;
                    break;
                }
                case 2://R,向右
                {
                    next_x=q[head].x;
                    next_y=q[head].y+1;
                    break;
                }
                case 3://U,向上
                {
                    next_x=q[head].x-1;
                    next_y=q[head].y;
                    break;
                }
            }
            if(is_legal(next_x, next_y)&&!vis[next_x][next_y]&&!map[next_x][next_y])
            {
                que tmp(next_x,next_y,q[head].dis+1,head);
                q.push_back(tmp);
                vis[next_x][next_y]=1;
                tail++;
            }
            if(next_x==END_X-1&&next_y==END_Y-1){
                flag=1;
                break;
            }
        }
        if(flag){
            break;
        }
        head++;
    }
    //cout<<q[tail-1].dis<<endl;
    int present=tail-1;
    int before=q[present].from;
    while(before!=0){
        int mi_x=q[present].x-q[before].x+1;
        int mi_y=q[present].y-q[before].y+1;
        min_path+=cvt[mi_x][mi_y];
        present=before;
        before=q[before].from;
    }
    for(long i=min_path.length()-1;i>=0;i--){
        cout<<min_path[i];
    }
    return 0;
}
