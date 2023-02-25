#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<math.h>
using namespace std;

int n,m;
int relationship[150][150]={0};//人际关系
int classes[150][150]={0};//第一维个考场的第二维个座位坐着谁
int min_class=0x7fffffff;//最小考场数量

void dfs(int id,int classes_num)
{
    if(classes_num>=min_class)
    {return;}//剪枝
    if(id>n)//结束
    {min_class=min(classes_num,min_class);return;}
    
    //如果考场当前位置有人并且和第id个人不认识
    
    for(int i=1;i<=classes_num;i++)//遍历每个考场，看这个人能不能坐
    {
        int position=1;
        while(classes[i][position]&&!relationship[id][classes[i][position]])
        {
            position++;
        }
        if(classes[i][position]==0)//如果某个考场的某个位置没人坐
        {
            classes[i][position]=id;
            dfs(id+1, classes_num);//这个人坐在这个考场，换下一个人分配
            classes[i][position]=0;//回溯
        }
    }
    //都不能坐，让这个人新开一个考场
    
   
    classes[classes_num+1][1]=id;
    dfs(id+1, classes_num+1);
    classes[classes_num+1][1]=0;//回溯
}

int main()
{
    cin>>n>>m;
    classes[1][1]=1;//第一考场一号是第一个人
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        relationship[a][b]=1;
        relationship[b][a]=1;
        //相互认识
    }
    dfs(2, 1);//从第二个人开始深搜
    cout<<min_class;
    return 0;
}


