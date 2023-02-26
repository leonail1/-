/*题目描述

n 个人参加某项特殊考试。

为了公平，要求任何两个认识的人不能分在同一个考场。

求是少需要分几个考场才能满足条件。

输入描述

输入格式：

第一行，一个整数 n (1≤n≤100)，表示参加考试的人数。

第二行，一个整数 m，表示接下来有 m 行数据。

以下 m 行每行的格式为：两个整数 a,b，用空格分开 ( 1≤a,b≤n )表示第 a 个人与第 b 个人认识。

输出描述

输出一行一个整数，表示最少分几个考场。

输入输出样例

示例

输入
5
8
1 2
1 3
1 4
2 3
2 4
2 5
3 4
4 5

输出
4

运行限制

最大运行时间：1s
最大运行内存: 256M
*/
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

