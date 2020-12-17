/*
 * @Author: xt 
 * @Date: 2020-10-19 16:09:41 
 * @Last Modified by: xt
 * @Last Modified time: 2020-10-19 16:16:45
 */
//简单选择排序算法

#include<iostream>
using namespace std;

#define MAXSIZE 11
typedef struct 
{
    int list[MAXSIZE];//元素位置从1开始，0元素存放哨兵或者临时变量
    int *plist=NULL;
    int length;
}SqList;

//将数组中位置为i和j的元素
void Swap(SqList * l,int i,int j)
{
    int temp=0;
    temp=l->list[i];
    l->list[i]=l->list[j];
    l->list[j]=temp;
}
//输出数组中的所有元素
void printlist(SqList *l)
{
    cout<<"输出有序序列"<<endl;
    for(int i=0;i<l->length;i++)
    {
        cout<<l->list[i]<<" ";
    }
    cout<<endl;
}

//选择排序算法
void SelectSort(SqList *l)
{
    for(int i=0;i<l->length-1;i++)
    {
        int temp=i;//记录当前最小值的下标，初始为第一个元素
        for (int j=i+1;j<l->length;j++)
        {
            if(l->list[j]<l->list[temp])
                temp=j;
        }
        if(i!=temp)//如果最小值和i不等，则交换位置
            Swap(l,i,temp);
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
    SelectSort(sq);

    printlist(sq);
    cout<<"程序结束"<<endl;
    

    

}