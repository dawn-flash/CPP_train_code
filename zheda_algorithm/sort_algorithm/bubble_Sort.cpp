/*
 * @Author: xt 
 * @Date: 2020-10-16 16:29:33 
 * @Last Modified by: xt
 * @Last Modified time: 2020-10-16 18:09:37
 */

//ð�������㷨
#include<iostream>
using namespace std;

#define MAXSIZE 11
typedef struct 
{
    int list[MAXSIZE];//Ԫ��λ�ô�1��ʼ��0Ԫ�ش���ڱ�������ʱ����
    int *plist=NULL;
    int length;
}SqList;

//��������λ��Ϊi��j��Ԫ��
void Swap(SqList * l,int i,int j)
{
    int temp=0;
    temp=l->list[i];
    l->list[i]=l->list[j];
    l->list[j]=temp;
}
void printlist(SqList *l)
{
    cout<<"�����������"<<endl;
    for(int i=0;i<l->length;i++)
    {
        cout<<l->list[i]<<" ";
    }
    cout<<endl;
}

void bubbleSort(SqList *l)
{
    bool flag=0;
    for(int i=0;i<l->length-1;i++)
    {
        flag=1;//��ʶλ����ʶĬ������
        for(int j=l->length-2;j>=i;j--)
        {
            if(l->list[j]>l->list[j+1])
            {
                Swap(l,j,j+1);
                flag=0; //��������Ĭ������ʱ����ʶλ��0
            }
        }
        if(flag)//û�н�����Ӧ����������ѭ��
            break;
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
    bubbleSort(sq);
    printlist(sq);
    cout<<"�������"<<endl;

    

}