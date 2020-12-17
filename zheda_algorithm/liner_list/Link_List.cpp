/*
 * @Author: xt 
 * @Date: 2020-09-19 16:33:50 
 * @Last Modified by: xt
 * @Last Modified time: 2020-09-21 14:58:07
 */

// 链表的实现：不带头结点的链表
// 功能如下：
// LinkList MakeEmpty(); //初始化链表 
// int Length(LinkList L);  // 以遍历链表的方法求链表长度 
// LinkList FindKth(int K,LinkList L);  // 按序号查找 
// LinkList Find(ElementType X,LinkList L);  // 按值查找 
// LinkList Insert(ElementType X,int i,LinkList L);  //将 X 插入到第 i-1(i>0) 个结点之后 
// LinkList Delete(int i,LinkList L); // 删除第 i(i>0) 个结点 
// void Print(LinkList L); // 输出链表元素 

#include<iostream>
using namespace std;
#include<string>

typedef struct LNode* LinkList; //*结构体的定义必须带上struct
typedef int ElementType;
typedef struct LNode{
    ElementType data;
    LinkList next;
}LNode;

LinkList MakeEmpty(); //初始化链表 
int Length(LinkList L);  // 以遍历链表的方法求链表长度 
LNode* FindKth(int K,LinkList L);  // 按序号查找 第K个元素
LNode* Find(ElementType X,LinkList L);  // 按值查找 
LinkList Insert(ElementType X,int i,LinkList L);  //将 X 插入到第 i-1(i>0) 个结点之后 
LinkList Delete(int i,LinkList L); // 删除第 i(i>0) 个结点 
void Print(LinkList L); // 输出链表元素 


//初始化链表
LinkList MakeEmpty()
{
    LinkList L=NULL;
    return L;
}

//求链表长度
int Length(LinkList L)
{
    int len=0;
    LinkList p=L;
    while (p!=NULL)
    {
        len++;
        p=p->next;
    }
    return len;
}

//查找第K个元素 返回元素对应的指针
LNode* FindKth(int k,LinkList L)
{
    LinkList p=L;
    int i=1;
    //同时遍历p和i，当p=NULL或者i=k跳出循环
    while (p!=NULL&& i<k)
    {
        /* code */
        p=p->next;
        i++;
    }
    //没找到第k个元素
    if(p==NULL)
    {
        cout<<"在链表中没有找到"<<k<<"元素"<<endl;
        return NULL;
    }
    //找到第k个元素
    else
    {
        return p;
    }
}

//寻找值为x的元素，返回元素指针
LNode* Find(ElementType X,LinkList L)
{
    LinkList p=L;
    //同时遍历链表p，当遍历完p=NULL或者找到X时结束循环
    while (p!=NULL && p->data!=X)
    {
        p=p->next;
    }
    //链表结束，未找到
    if(p==NULL)
    {
        cout<<"没有找到值为"<<X<<"的元素"<<endl;
        return NULL;
    }
    //找到X
    return p;  
}

//在第i个位置插入节点X
LinkList Insert(ElementType X,int i,LinkList L)
{
    LinkList p=L;
    LinkList temp=NULL;
    //未带头结点，插入第一个节点，需要对头指针进行操作
    if(i==1)
    {
        temp=(LinkList)malloc(sizeof(struct LNode));
        temp->next=p;
        temp->data=X;
        return temp; //返回新的头指针
    }
    //寻找第i-1个节点
    p=FindKth(i-1,L);
    if(p==NULL)
    {
        cout<<"插入的位置不存在"<<endl;
        return L;
    }
    else
    {
        temp=(LinkList)malloc(sizeof(struct LNode));
        temp->next=p->next;
        temp->data=X;
        p->next=temp;
        return L;  //指针未修改，考虑一致性，返回
    }
}

//删除第i个节点
LinkList Delete(int i,LinkList L) // 删除第 i(i>0) 个结点 
{
    LinkList p=L;
    LinkList temp=NULL;
    //第一个节点需要分开操作
    if(i==1)
    {
        temp=p;
        p=p->next;
        free(temp);
        return p;
    }
    //寻找前驱节点
    LinkList pre=FindKth(i-1,L);
    if(pre==NULL || pre->next==NULL )
    {
        cout<<"没有第i个节点"<<endl;
        return L;
    }//找到当前节点
    else
    {
        temp=pre->next;
        pre->next=temp->next;
        free(temp);
        return L;
    }   
}

//输出所有元素
void Print(LinkList L)
{
    LinkList p=L;
    while (p!=NULL)
    {
        if(p->next==NULL)
            cout<<p->data<<endl;
        else
            cout<<p->data<<"->";
        p=p->next;
    }
}

//测试所有的链表函数
void testSList()
{
    LinkList L=MakeEmpty();
    cout<<"链表长度"<<Length(L)<<endl;
    L = Insert(11,1,L);
	L = Insert(25,1,L);
	L = Insert(33,2,L);
	L = Insert(77,3,L);
    cout<<"输出链表"<<endl;
    Print(L);
    cout<<"链表长度"<<Length(L)<<endl;
    Find(22,L);
    cout<<Find(33,L)->data<<endl;
    cout<<FindKth(1,L)->data<<endl;
    FindKth(5,L);
    cout<<"删除第1个元素"<<endl;
    L = Delete(1,L);
    Print(L);
    cout<<"删除第3个元素"<<endl;
	L = Delete(3,L);
    Print(L);

    cout<<"测试结束"<<endl;
}
int main()
{
   testSList();
   return 0;
}
