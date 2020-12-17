/*
 * @Author: xt 
 * @Date: 2020-09-22 20:15:01 
 * @Last Modified by: xt
 * @Last Modified time: 2020-09-23 09:25:18
 */

// 带头结点的单链表的构造
#include<iostream>
using namespace std;
typedef int DataType;


// *************************************
// *********带头结点的单链表实现**********
// *************************************
typedef struct LNode
{
    DataType data;
    struct LNode* next;
}LNode;
typedef LNode* SinLinkList;


SinLinkList MakeEmpty(); //初始化链表 
int Length(SinLinkList L);  // 以遍历链表的方法求链表长度 
LNode* FindKth(int K,SinLinkList L);  // 按序号查找 第K个元素
LNode* Find(DataType X,SinLinkList L);  // 按值查找 
int Insert(DataType X,int i,SinLinkList L);  //将 X 插入到第 i-1(i>0) 个结点之后 
int Delete(int i,SinLinkList L); // 删除第 i(i>0) 个结点 
void Print(SinLinkList L); // 输出链表元素 

//初始化链表 
SinLinkList MakeEmpty()
{
    LNode* head=(SinLinkList)malloc(sizeof(LNode));
    head->data=0;
    head->next=NULL;
    return head;
}

// 以遍历链表的方法求链表长度 
int Length(SinLinkList L)
{
    LNode* p=L;
    int len=0;
    while (p->next!=NULL)
    {
        p=p->next;
        len++;
    }
    return len;
}

// 按序号查找 第K个元素
LNode* FindKth(int K,SinLinkList L)
{
    LNode* p=L->next;
    int i=1;
    //将K<=0的情况排除
    if(K<=0)
    {
        cout<<"没有找到第"<<K<<"个元素"<<endl;
        return NULL;
    }
    //循环判断，找到第k个位置
    while(p!=NULL && i<K)
    {
        p=p->next;
        i++;
    }
    if (p==NULL)
    {
        cout<<"没有找到第"<<K<<"个元素"<<endl;
        return NULL;
    }
    return p;
}

// 按值查找 
LNode* Find(DataType X,SinLinkList L)
{
    LNode *p=L->next;
    //循环判断，寻找X值
    while(p!=NULL && p->data!=X)
    {
        p=p->next;
    }
    if(p==NULL)
    {
        cout<<"没有找到值为"<<X<<"的节点"<<endl;
        return NULL;
    }
    return p;
}

//将 X 插入到第 i-1(i>0) 个结点之后
int Insert(DataType X,int i,SinLinkList L)
{
    LNode* p=L;
    int j=0;
    //寻找第i-1个元素
    while(p!=NULL&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(p==NULL)
    {
        cout<<"没有找到第"<<i<<"个节点"<<endl;
        return -1;
    }
    else
    {
        LNode* temp=(LNode *)malloc(sizeof(LNode));
        temp->data=X;
        temp->next=p->next;
        p->next=temp;
    }
    return 1;
}

// 删除第 i(i>0) 个结点 
int Delete(int i,SinLinkList L)
{
    LNode* p=L;
    int j=0;
    //寻找第i-1个元素
    while(p!=NULL && j<i-1)
    {
        p=p->next;
        j++;
    }
    if(p==NULL || p->next==NULL)
    {
        cout<<"没有找到第"<<i<<"个节点"<<endl;
        return -1;
    }
    else
    {
        LNode* temp=p->next;
        p->next=p->next->next;
        free(temp);
        return 1;
    }
}

//输出链表元素
void Print(SinLinkList L)
{
    LNode* p=L->next;
    cout<<"链表的元素为："<<endl;
    while(p!=NULL)
    {
        if(p->next==NULL)
            cout<<p->data<<endl;
        else
            cout<<p->data<<"->";
        p=p->next;
    }
}
    
void test()
{
    SinLinkList L=MakeEmpty();
    cout<<"链表长度"<<Length(L)<<endl;
    int i=0;
    i = Insert(11,1,L);
	i = Insert(25,1,L);
	i = Insert(33,2,L);
	i = Insert(77,3,L);
    for(int j=0;j<6;j++)
    {
        if(FindKth(j,L)!=NULL)
            cout<<FindKth(j,L)->data<<endl;
    }
    cout<<"输出链表"<<endl;
    Print(L);
    cout<<"链表长度"<<Length(L)<<endl;
    Find(22,L);
    cout<<Find(11,L)->data<<endl;
    cout<<FindKth(1,L)->data<<endl;
    FindKth(5,L);
    cout<<"删除第1个元素"<<endl;
    i = Delete(1,L);
    Print(L);
    cout<<"删除第3个元素"<<endl;
	i = Delete(3,L);
    Print(L);

    cout<<"测试结束"<<endl;
}


// *************************************
// *********带头结点的双向循环链表实现*****
// *************************************

typedef struct DLNode
{
    DataType data;
    DLNode* pre;
    DLNode* post;
}DLNode;
typedef DLNode* DLinkList;

DLinkList MakeEmptyDLinkList(); //初始化链表 
int Length(DLinkList L);  // 以遍历链表的方法求链表长度 
DLNode* FindKth(int K,DLinkList L);  // 按序号查找 第K个元素
DLNode* Find(DataType X,DLinkList L);  // 按值查找 
int Insert(DataType X,int i,DLinkList L);  //将 X 插入到第 i-1(i>0) 个结点之后 
int Delete(int i,DLinkList L); // 删除第 i(i>0) 个结点 
void Print(DLinkList L); // 输出链表元素 

//初始化链表
DLinkList MakeEmptyDLinkList()
{
    DLNode* head=(DLNode*)malloc(sizeof(DLNode));
    head->data=0;
    head->pre=NULL;
    head->post=NULL;
    return head;
}

// 以遍历链表的方法求链表长度
int Length(DLinkList L)
{
    DLNode *p=L;
    int len=0;
    while(p->post!=L)
    {
        p=p->post;
        len++;
    }
    return len;
}

// 按序号查找 第K个元素
DLNode* FindKth(int K,DLinkList L)
{
    DLNode *p=L;
    if(K<=0)
    {
        cout<<"没有第"<<K<<"个节点"<<endl;
        return NULL;
    }
    int j=0;
    while(p->post!=L && j<K)
    {
        p=p->post;
        j++;
    }
    if(j!=K)
    {
        cout<<"没有第"<<K<<"个节点"<<endl;
        return NULL;
    }
    return p;
}

// 按值查找 
DLNode* Find(DataType X,DLinkList L)
{
    DLNode* p=L->post;
    while(p!=L && p->data!=X)
        p=p->post;
    if(p==L)
    {
        cout<<"没有找到节点"<<X<<endl;
        return NULL;
    }
    return p;
}


int main()
{
    test();
    return 0;
}