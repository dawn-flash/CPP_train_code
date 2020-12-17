/*
 * @Author: xt 
 * @Date: 2020-10-21 16:21:58 
 * @Last Modified by: xt
 * @Last Modified time: 2020-10-21 17:03:03
 */

//队排序
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


//调整大顶堆m为堆根节点编号，n为堆尾部节点编号
void heapAdjust(SqList *l,int m,int n)
{
    //m一直指代二叉树的根节点，j指代二叉树的儿子节点，n指代堆的最后一个节点
    int temp=l->list[m];
    for (int j=m*2;j<=n;j*=2)
    {
        //选出子节点中较大元素，标记为j
        if(j<n&&l->list[j]<l->list[j+1])
            j++;
        //根节点比子节点大，跳出循环
        if(temp>=l->list[j])
            break;
        //否则，将根节点置为子节点较大元素
        l->list[m]=l->list[j];
        //根节点标记下移，继续判断
        m=j;
    }

    l->list[m]=temp;
}

//堆排序
void HeapSort(SqList *l)
{
    //大顶堆的建立
    for (int i=l->length/2;i>=1;i--)
        heapAdjust(l,i,l->length);
    
    //大顶堆的调整
    for (int i=l->length;i>1;i--)
    {
        Swap(l,1,i);
        heapAdjust(l,1,i-1);
    }
}

int main()
{
    SqList *sq=(SqList *)malloc(sizeof(SqList));
    sq->length=10;
    //堆排序的元素从下标1开始存储
    int a[11]={9,8,6,7,5,3,4,2,1,0,10};
    sq->plist=a;

    for(int i=0;i<11;i++)
    {
        sq->list[i]=a[i];
    }
    cout<<"堆排序开始"<<endl;
    HeapSort(sq);
    printlist(sq);
    cout<<"程序结束"<<endl;
}