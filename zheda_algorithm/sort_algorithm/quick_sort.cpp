/*
 * @Author: xt 
 * @Date: 2020-10-23 16:40:14 
 * @Last Modified by: xt
 * @Last Modified time: 2020-10-23 16:58:13
 */

//快速排序

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

//选取标准点，将标准点归位
int parttition(SqList *l,int low,int high)
{
    int pivotkey=l->list[low];
    while(low<high)
    {
        //将比标准点小的元素移到左边
        while(low<high&&l->list[high]>=pivotkey)
            high--;
        Swap(l,low,high);
        //将比标准点大的元素移到右边
        while(low<high&&l->list[low]<=pivotkey)
            low++;
        Swap(l,low,high);
    }
    
    return low;
}
void QSort(SqList *l,int low,int high)
{
    int povit;
    if (low<high)
    {
        //选取标准点
        povit=parttition(l,low,high);
        cout<<"povit"<<povit<<endl;
        //将标准点左侧递归
        QSort(l,low,povit-1);
        //将标准点右侧递归
        QSort(l,povit+1,high);
    }
}
void QuickSort(SqList *l)
{
    QSort(l,0,l->length-1);
}

int main()
{
    SqList *sq=(SqList *)malloc(sizeof(SqList));
    sq->length=11;
    //堆排序的元素从下标1开始存储
    int a[11]={9,8,6,7,5,3,4,2,1,0,10};
    sq->plist=a;

    for(int i=0;i<11;i++)
    {
        sq->list[i]=a[i];
    }
    cout<<"快速排序开始"<<endl;
    // MergeSort(sq);
    QuickSort(sq);
    cout<<"快速排序结束"<<endl;
    printlist(sq);
    cout<<"程序结束"<<endl;
}