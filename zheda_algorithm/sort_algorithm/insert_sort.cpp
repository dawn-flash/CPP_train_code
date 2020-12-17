/*
 * @Author: xt 
 * @Date: 2020-10-19 16:43:17 
 * @Last Modified by: xt
 * @Last Modified time: 2020-11-12 09:56:37
 */
//直接插入排序

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
    cout<<"当前的数组为：?"<<endl;
    for(int i=0;i<l->length;i++)
    {
        cout<<l->list[i]<<" ";
    }
    cout<<endl;
}

//直接插入排序算法
void DirectInsertSort(SqList* l)
{
    for(int i=1;i<=l->length-1;i++)
    {
        if(l->list[i]<l->list[i-1])
        {
            int temp=l->list[i]; //记录需要插入的元素
            int j=i-1;
            for (;l->list[j]>temp&&j>=0;j--) //从i-1中选择插入位置，比temp大的元素通通后移
            {
                 l->list[j+1]=l->list[j];
            }
            l->list[j+1]=temp; //将temp放入j+1中
        }
    }
}


//折半插入排序法
void BInsertSort(SqList *l)
{
    for( int i=1;i<l->length;i++)
    {
        int low=0;
        int hight=i-1;
        int mid=0;
        //利用二分法寻找数字的插入位置，并将插入的位置为low
        while(low<=hight)//注意必须小于等于
        {
            mid=(low+hight)/2;
            if(l->list[i]<l->list[mid])
                hight=mid-1;
            else
                low=mid+1;
        }
        //将low到i-1之间的元素全向后移动一位
        int temp=l->list[i];
        for (int j=i-1;j>=low;j--)
        {
            l->list[j+1]=l->list[j];
        }
        //将temp放入改放的位置
        l->list[low]=temp;
    }
}

//2路插入排序
void path_2_insert_sort(SqList *l)
{
    int temparr[l->length]={};//使用一个循环数组空间
    int first=0;
    int last=0;
    int n=l->length;
    temparr[0]=l->list[0];
    for (int i=1;i<l->length;i++)
    {
        //当插入元素小于first的元素，插入到最前面
        if(l->list[i]<temparr[first])
        {
            first=(first-1+n)%n;
            temparr[first]=l->list[i];
            continue;
        }
        //当插入的元素大于last的元素，插入到最后
        if(l->list[i]>temparr[last])
        {
            last=(last+1)%n;
            temparr[last]=l->list[i];
            continue;
        }
        //当插入的元素在中间，则正常的直接插入排序
        int k=last;
        for (;temparr[k]>l->list[i];k=(k-1+n)%n)
        {
            temparr[(k+1+n)%n]=temparr[k];
        }
        temparr[(k+1)%n]=l->list[i];
        last=(last+1)%n;
    }
    //最后将结果复制到原来的数组中
    for (int i=0;i<l->length;i++)
    {
        l->list[i]=temparr[(first+i)%n];
    }
}

//设计数组链表
#define SIZE 11
typedef struct
{
    int value;
    int next;
}Node;
typedef struct
{
    Node r[SIZE];
    int length;
}List;

//对数组链表进行重新排序
void arrange(List *l)
{
    int p=l->r[0].next;//指向有序链表的第i个元素的数组位置
    for (int i=1;i<l->length;i++)//i指代数组中的第i个位置
    {
        //成立表示数组元素已经移动过，是处于正确的位置，需要寻找原来该位置的元素
        while(p<i)
            p=l->r[p].next;
        
        //记录下链表的下一个位置
        int q=l->r[p].next;
        if(p!=i)
        {
            //交换数组元素，同时将i的下标更新
            Node t;
            t=l->r[p];
            l->r[p]=l->r[i];
            l->r[i]=t;
            l->r[i].next=p;
        }
        p=q;
    }
}

//测试重新排列
void testarrange()
{
    List *SL=(List*)malloc(sizeof(List));
    SL->length=6;
    SL->r[0].value=0;
    SL->r[0].next=4;
   
    SL->r[1].value=49;
    SL->r[1].next=3;
   
    SL->r[2].value=38;
    SL->r[2].next=1;
   
    SL->r[3].value=76;
    SL->r[3].next=0;
   
    SL->r[4].value=13;
    SL->r[4].next=5;
   
    SL->r[5].value=27;
    SL->r[5].next=2;
   
    arrange(SL);
    for (int i=1; i<6; i++) {
        printf("%d ",SL->r[i].value);
    }
}

int main()
{
    // SqList *sq=(SqList *)malloc(sizeof(SqList));
    // sq->length=11;
    // int a[11]={9,8,6,7,5,3,4,2,1,0,10};
    // sq->plist=a;

    // for(int i=0;i<11;i++)
    // {
    //     sq->list[i]=a[i];
    // }
    // // DirectInsertSort(sq);
    // // BInsertSort(sq);
    // path_2_insert_sort(sq);
    // printlist(sq);

    testarrange();

    cout<<"game over"<<endl;
    cout<<"程序结束"<<endl;
    cout<<"程序结束"<<endl;

    
}