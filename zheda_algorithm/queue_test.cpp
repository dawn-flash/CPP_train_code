/*
 * @Author: xt 
 * @Date: 2020-11-10 16:38:17 
 * @Last Modified by: xt
 * @Last Modified time: 2020-11-11 10:22:25
 */

//实现循环队列和链队列

#include<iostream>
using namespace std;

#define MaxSize 100
typedef struct CircularQueue
{
    int data[MaxSize];
    int front;
    int rear;
}CircularQueue;

//循环队列实现
int InitQueue(CircularQueue *cqueqe);
int ClearQueue(CircularQueue * cqueue);
int QueueEmpty(CircularQueue *cqueue);
int QueueLength(CircularQueue *cqueue);
int GetHead(CircularQueue *cqueue,int * element);
int EnQueue(CircularQueue *cqueue,int element);
int DeQueue(CircularQueue *cqueue,int *ele);
int QueueTraverse(CircularQueue *cqueue);

//队列的初始化
int InitQueue(CircularQueue *cqueqe)
{
    cqueqe->front=0;
    cqueqe->rear=0;
    return true;
}
//清空队列
int ClearQueue(CircularQueue * cqueue)
{
    cqueue->front=0;
    cqueue->rear=0;
    return true;
}
//判断队列是否为空
int QueueEmpty(CircularQueue *cqueue)
{
    if(cqueue->front==cqueue->rear)
        return true;
    return false;
}
//求队列的长度
int QueueLength(CircularQueue *cqueue)
{
    return (cqueue->rear-cqueue->front +MaxSize)%MaxSize;
}
//获取头元素
int GetHead(CircularQueue *cqueue,int *element)
{
    if(QueueEmpty(cqueue))
        return false;
    *element=cqueue->data[cqueue->front];
    return true;
}
//元素入队
int EnQueue(CircularQueue *cqueue,int element)
{
    //队列空
    if(cqueue->front==(cqueue->rear+1)%MaxSize)
    {
        cout<<"队列已经满"<<endl;
        return false;
    }
    cqueue->data[cqueue->rear]=element;
    cqueue->rear=(cqueue->rear+1)%MaxSize;
    
    return true;
}
//元素出队
int DeQueue(CircularQueue *cqueue,int *ele)
{
    if(QueueEmpty(cqueue))
    {
        cout<<"队列空"<<endl;
        return false;
    }
    *ele=cqueue->data[cqueue->front];
    cqueue->front=(cqueue->front+1)%MaxSize;
    return true;
}
//从队列头开始遍历所有的队列元素
int QueueTraverse(CircularQueue *cqueue)
{
   if(QueueEmpty(cqueue))
    {
        cout<<"队列为空"<<endl;
        return false;
    }
    int front=cqueue->front;
    int rear=cqueue->rear;
    cout<<"队列中的所有元素为"<<endl;
    while((front)%MaxSize!=rear)
    {
        cout<<cqueue->data[front]<<" ";
        front=(front+1)%MaxSize;
    }
    cout<<endl;
    return true;
}


//链队列实现
typedef struct Node
{
    int value;
    struct Node* next;
}Node;

typedef struct LinkQueue
{
    Node *front;
    Node *rear;
}LinkQueue;
int InitQueue(LinkQueue *lqueqe);
int ClearQueue(LinkQueue *lqueue);
int QueueEmpty(LinkQueue *lqueue);
int QueueLength(LinkQueue *lqueue);
int GetHead(LinkQueue *lqueue,int * element);
int EnQueue(LinkQueue *lqueue,int element);
int DeQueue(LinkQueue *lqueue,int *ele);
int QueueTraverse(LinkQueue *lqueue);

int InitQueue(LinkQueue *lqueqe)
{
    Node *head=(Node*)malloc(sizeof(Node));
    head->value=0;
    head->next=NULL;
    lqueqe->front=head;
    lqueqe->rear=head;
    return true;
}

int ClearQueue(LinkQueue *lqueue)
{
    Node *p=lqueue->front->next;
    Node *temp=NULL;
    while(p!=NULL)
    {
        temp=p;
        p=p->next;
        free(temp);
    }
    lqueue->rear=lqueue->front;
    return true;
}

int QueueEmpty(LinkQueue *lqueue)
{
    if(lqueue->front==lqueue->rear)
        return true;
    return false;
}
int QueueLength(LinkQueue *lqueue)
{
    int length=0;
    Node *p=lqueue->front;
    while(p!=lqueue->rear)
    {
        p=p->next;
        length++;
    }
    return length;
}
int GetHead(LinkQueue *lqueue,int *element)
{
    if(QueueEmpty(lqueue))
    {
        cout<<"队列为空，没有头元素"<<endl;
        return false;
    }
    *element=lqueue->front->value;
    return true;
}
int EnQueue(LinkQueue *lqueue,int element)
{
    Node *temp=(Node*)malloc(sizeof(Node));
    temp->value=element;
    temp->next=NULL;
    lqueue->rear->next=temp;
    lqueue->rear=lqueue->rear->next;
    return true;

}
int DeQueue(LinkQueue *lqueue,int *ele)
{
    if(QueueEmpty(lqueue))
    {
        cout<<"队列为空"<<endl;
        return false;
    }
    Node *temp=lqueue->front->next;
    lqueue->front->next=temp->next;
    if(temp==lqueue->rear)
        lqueue->rear=lqueue->front;
    free(temp);

}
int QueueTraverse(LinkQueue *lqueue)
{
    Node *p=lqueue->front->next;
    while(p!=NULL)
    {
        cout<<p->value<<" ";
        p=p->next;
    }
    return true;
}

int test_ciycularQueue()
{
    CircularQueue cqueue;
    InitQueue(&cqueue);
    cout<<"队列是否为空"<<QueueEmpty(&cqueue);
    for(int i=0;i<=10;i++)
    {
        EnQueue(&cqueue,i);
    }
    cout<<"队列长度"<<QueueLength(&cqueue)<<endl;
    int ele=0;
    cout<<"队列头元素"<<GetHead(&cqueue,&ele)<<" "<<ele;
    for(int i=0;i<5;i++)
    {
        DeQueue(&cqueue,&ele);
    }
    cout<<"输出所有队列元素"<<endl;
    QueueTraverse(&cqueue);
    return 0;
}

int testLinkQueue()
{
    //队列结构体，函数外初始化
    LinkQueue lqueue;
    InitQueue(&lqueue);
    cout<<"队列是否为空"<<QueueEmpty(&lqueue);
    for(int i=0;i<=10;i++)
    {
        EnQueue(&lqueue,i);
    }
    cout<<"队列长度"<<QueueLength(&lqueue)<<endl;
    int ele=0;
    cout<<"队列头元素"<<GetHead(&lqueue,&ele)<<" "<<ele;
    for(int i=0;i<5;i++)
    {
        DeQueue(&lqueue,&ele);
    }
    cout<<"输出所有队列元素"<<endl;
    QueueTraverse(&lqueue);
    return 0;
}

int main()
{
    // test_ciycularQueue();
    testLinkQueue();

    return 1;
    
    
}