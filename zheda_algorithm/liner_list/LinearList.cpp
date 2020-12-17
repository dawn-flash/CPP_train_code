/*
 * @Author: xt 
 * @Date: 2020-09-18 17:17:20 
 * @Last Modified by: xt
 * @Last Modified time: 2020-09-18 17:23:23
 */

// 顺序表的数组实现，包括的功能如下：
// + 创建空表
// + 寻找下标为i的元素
// + 在下标i上插入元素
// + 删除下标为i的元素
// + 寻找下标为k的元素
// + 求数组的长度

#include<iostream>
using namespace std;

//抽象数据类型定义
#define MaxSize 100
typedef int ElementType;
typedef struct LNode *List;
struct LNode
{
    ElementType Data[MaxSize]; //数组存放所有数据
    int Last;//存放数组中最后一个元素下标，初始为-1
};

List MakeEmptyList();//创建空表
int Find(ElementType x,List L); //寻找x 返回元素下标
void Insert(ElementType x,int i,List L); //在第i个下标插入元素x
void Delete(int i,List L); //删除下标为i的元素
ElementType FindKth(int k,List L); //寻找小标为k的元素
int length(List L); //求数组的长度


//创建空表
List MakeEmptyList()
{
    List ptrl;
    ptrl=(List) malloc(sizeof(struct LNode));
    ptrl->Last=-1;
    return ptrl;
}

//寻找x 返回元素下标
int Find(ElementType x,List L)
{
    int i=0;
    while(i<=L->Last&&L->Data[i]!=x)
    {
        i++;
    }
    if(i>L->Last)
        return -1;
    else
        return i;
}

//在第i个下标插入元素x
void Insert(ElementType x,int i,List L)
{
    //判断数组是否满
    if (L->Last+1==MaxSize) 
    {
        cout<<"数组已满"<<endl;
        return;
    }
    //判断插入位置是否合理
    if(i<0||i>L->Last+1)
    {
        cout<<"插入的位置不对"<<endl;
        return;
    }
    //将数组中下标j到i的元素全向后移动一位，
    //插入下标位于last+1 则跳过此操作
    for(int j=L->Last;j>=i;j--)
        L->Data[j+1]=L->Data[j];
    L->Data[i]=x;
    L->Last++;
    return;
}

//删除下标为i的元素
void Delete(int i,List L)
{
    //判断数组是否为空
    if(L->Last==-1)
    {
        cout<<"数组为空"<<endl;
        return;
    }
    //判断插入位置是否有误
    if(i<0||i>L->Last)
    {
        cout<<"有序表中没有该下标"<<endl;
        return;
    }
    //寻找插入位置
    for(int j=i;j<=L->Last;j++)
        L->Data[j]=L->Data[j+1];
    L->Last--;
    return;
}

//寻找下标为k的元素
ElementType FindKth(int k,List L)
{
    if(k<0||k>L->Last) 
    {
        cout<<"没有该下标"<<endl;
        return -1;
    }   
    return L->Data[k];
}

//求数组的长度
int length(List L)
{
    return L->Last+1;
}

//对所有的顺序表的功能进行测试
void test_linerlist()
{
    int i=0;
    List L=MakeEmptyList();
    cout<<"插入元素"<<endl;
    Insert(1,0,L);
    Insert(2,0,L);
    Insert(3,0,L);
    Insert(4,0,L);
    for (int j=0;j<length(L);j++)
        cout<<L->Data[j]<<" ";
    cout<<endl;
    cout<<"寻找下标为0的元素"<<FindKth(0,L)<<endl;
    cout<<"寻找下标为4的元素"<<FindKth(4,L)<<endl;
    cout<<"寻找值为1的元素下标"<<Find(1,L)<<endl;
    cout<<"寻找值为5的元素下标"<<Find(5,L)<<endl;
    cout<<"求出数组长度为"<<length(L)<<endl;

    cout<<"删除元素"<<endl;
    Delete(0,L);
    Delete(5,L);
    Delete(2,L);
    for (int j=0;j<length(L);j++)
        cout<<L->Data[j]<<" ";
    cout<<"测试结束"<<endl;
}

int main()
{
    test_linerlist();
}
