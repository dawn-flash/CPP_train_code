/*
 * @Author: xt 
 * @Date: 2020-10-22 09:42:21 
 * @Last Modified by: xt
 * @Last Modified time: 2020-10-23 16:54:16
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

//将有序的数组SR[s,m]和[m+1,n]合并到TR[s,n]中
void Merge(int SR[],int TR[],int s,int m,int n)
{
    int i,j,k;
    for(i=s,j=m+1,k=s;i<=m&&j<=n;k++)//同时遍历两段数组，直到一段数组遍历完
    {
        if(SR[i]<SR[j])
            TR[k]=SR[i++];
        else 
        {
            TR[k]=SR[j++];
        }     
    }
    //第一个数组没有遍历完，将剩余元素复制到目标数组
    if(i<=m)
    {
        for(;i<=m;i++)
        {
            TR[k++]=SR[i];
        }
    }
    //第二个数组没有遍历完，将剩余元素复制到目标数组
    if(j<=n)
    {
        for(;j<=n;j++)
        {
            TR[k++]=SR[j];
        }
    }
}

//递归归并排序，将SR中的元素归并到TR1，
void MSort(int SR[],int TR1[], int s,int t)
{
    int TR2[MAXSIZE];
    //递归到耽搁元素，直接将元素归并到目标数组
    if(s==t)
    {
        // cout<<"序列头"<<s<<" "<<t<<endl;
        TR1[s]=SR[s];
    }
    else
    {
        int m=(s+t)/2;
        // cout<<"序列头"<<s<<" "<<t<<endl;
        MSort(SR,TR2,s,m);
        MSort(SR,TR2,m+1,t);
        Merge(TR2,TR1,s,m,t);
    }
    
    
}

//归并排序主代码
void MergeSort(SqList *l)
{
    MSort(l->list,l->list,0,l->length-1);
}


//将SR中的所有的序列按照s子序列两两合并到TR中，n为序列最后一个元素下标
void MergePass(int SR[],int TR[],int s,int n)
{
    int i=0;
    //i为序列起点，当剩余序列能满足完整的两个s子序列合并
    for(;i<=n-2*s+1;i=i+2*s)
        Merge(SR,TR,i,i+s-1,i+2*s-1);
    
    //当序列只满足一个s之序列和长度小于s子序列合并
    if(i<=n-s)
        Merge(SR,TR,i,i+s-1,n);
    else//当序列只满足一个s子序列合并
    {
        for(int j=i;j<=n;j++)
            TR[j]=SR[j];
    }
}

//非递归归并排序 主代码
void MergeSort2(SqList* l)
{
    int* TR=(int*)malloc(l->length*sizeof(int));
    //k为子序列长度，当子序列长度Wielength时，可跳出循环
    int k=1;
    while(k<l->length)
    {
        //将l->list两两归并到TR
        MergePass(l->list,TR,k,l->length-1);
        k=2*k;
        //将TR两两归并到l->list
        MergePass(TR,l->list,k,l->length-1);
        k=2*k;
    }
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
    cout<<"归并排序开始"<<endl;
    // MergeSort(sq);
    MergeSort2(sq);
    printlist(sq);
    cout<<"程序结束"<<endl;
}