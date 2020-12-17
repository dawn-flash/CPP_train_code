/*
 * @Author: xt 
 * @Date: 2020-10-21 15:14:53 
 * @Last Modified by: xt
 * @Last Modified time: 2020-10-21 16:21:19
 */

//希尔排序
#include<iostream>
using namespace std;

#define MAXSIZE 11
typedef struct 
{
    int list[MAXSIZE];
    int *plist=NULL;
    int length;
}SqList;


//交换i和j位置
void Swap(SqList * l,int i,int j)
{
    int temp=0;
    temp=l->list[i];
    l->list[i]=l->list[j];
    l->list[j]=temp;
}
//输出数组
void printlist(SqList *l)
{
    cout<<"当前的数组为:"<<endl;
    for(int i=0;i<l->length;i++)
    {
        cout<<l->list[i]<<" ";
    }
    cout<<endl;
}

//希尔排序
void ShellSort(SqList *l)
{
    //设置一个增量序列，初始化为数组长度
    int increment=l->length;
    while(increment>1) //逐渐减小增量，直到增量为1
    {
        increment=increment/3+1;
        
        for (int i=increment;i<l->length;i++) //下标为[increment,l->length-1]进行直接插入排序
        {
            int temp=l->list[i];
            int j=i-increment;
            for (;temp<l->list[j]&&j>=0;j=j-increment)
            {
                l->list[j+increment]=l->list[j];
            }
            l->list[j+increment]=temp;
        }
    }
}

int main()
{
    SqList *sq=(SqList *)malloc(sizeof(SqList));
    sq->length=11;
    int a[11]={9,8,6,7,5,3,4,2,1,0,10};
    sq->plist=a;

    for(int i=0;i<11;i++)
    {
        sq->list[i]=a[i];
    }
    
    cout<<"希尔排序开始"<<endl;
    ShellSort(sq);
    printlist(sq);
    cout<<"程序结束"<<endl;
}

