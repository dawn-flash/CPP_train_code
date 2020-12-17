/*
 * @Author: xt 
 * @Date: 2020-11-03 15:55:14 
 * @Last Modified by: xt
 * @Last Modified time: 2020-11-04 09:12:34
 */

//对栈进行设计：顺序栈，链栈，共享栈
//栈的应用：递归程序和表达式求值

#include<iostream>
#include<stack>
using namespace std;
#define MaxSize 100


//普通顺序栈的设计
typedef struct SqStack{
    int data[MaxSize];
    int top;
}SqStack;

int InitStack(SqStack *s);
int ClearStack(SqStack *s);
int StackEmpty(SqStack *s);
int StackLength(SqStack *s);
int GetTop(SqStack *s,int *element);
int Pop(SqStack *s,int *element);
int Push(SqStack *s,int element);
int StackTraverse(SqStack *s);

//顺序栈的初始化
int InitStack(SqStack *s)
{
    s->top=-1;
    return true;
}

//清空栈的所有元素
int ClearStack(SqStack *s)
{
    s->top=-1;
    return true;
}

//判断栈是否为空
int StackEmpty(SqStack *s)
{
    if(s->top==-1)
        return true;
    return false;
}

//求栈的长度
int StackLength(SqStack *s)
{
    return s->top+1;
}

//获取栈顶元素
int GetTop(SqStack *s,int *element)
{
    if(s->top==-1)
    {
        cout<<"栈为空"<<endl;
        return false;
    }
    *element=s->data[s->top];
    return true;
}

//出栈
int Pop(SqStack *s,int *element)
{
    if(s->top==-1)
    {
        cout<<"这是一个空栈"<<endl;
        return false;
    }
    *element=s->data[s->top];
    s->top--;
    return true;
}
//入栈
int Push(SqStack *s,int element)
{
    if(s->top==MaxSize-1)
    {
        cout<<"栈满"<<endl;
        return false;
    }
    s->top++;
    s->data[s->top]=element;
    return true;
}

//输出栈的逆序列
int StackTraverse(SqStack *s)
{
    if(s->top==-1)
    {
        cout<<"栈为空"<<endl;
        return false;
    }
    cout<<"栈中的逆序为："<<endl;
   for(int i=s->top;i!=-1;i--)
   {
       cout<<s->data[i]<<" ";
   }
   cout<<endl;
   return true;
}

void test1()
{
    SqStack s;
    int e;
    if(InitStack(&s))

    {
        for(int j=1;j<=10;j++)
            Push(&s,j);
    }
    cout<<"栈中的所有元素分别为"<<endl;
    StackTraverse(&s);
    Pop(&s,&e);
    GetTop(&s,&e);
    cout<<"栈顶元素"<<e<<endl;
    cout<<"栈的长度"<<StackLength(&s)<<endl;
    ClearStack(&s);
    cout<<"栈是否为空"<<endl;
    if(StackEmpty(&s))
        cout<<"空"<<endl;
    StackTraverse(&s);
}

//共享数据栈设计
typedef struct SqDoubleStack
{
    int data[MaxSize];
    int top1;
    int top2;
}SqDoubleStack;

int InitStack(SqDoubleStack *s);
int ClearStack(SqDoubleStack *s);
int StackEmpty(SqDoubleStack *s);
int StackLength(SqDoubleStack *s);
int GetTop(SqDoubleStack *s,int *element,int stackNum);
int Pop(SqDoubleStack *s,int *element,int stackNum);
int Push(SqDoubleStack *s,int element,int stackNum);
int StackTraverse(SqDoubleStack *s);

//共享栈初始化
int InitStack(SqDoubleStack *s)
{
    s->top1=-1;
    s->top2=MaxSize;
    return true;
}

//清空栈内元素
int ClearStack(SqDoubleStack *s)
{
    s->top1=-1;
    s->top2=MaxSize;
    return true;
}

//判断栈是否为空
int StackEmpty(SqDoubleStack *s)
{
    if(s->top1=-1&&s->top2==MaxSize)
        return true;
    return false;
}

//求栈的长度
int StackLength(SqDoubleStack *s)
{
    return s->top1+1+(MaxSize-s->top2);
}

//获取栈的元素
int GetTop(SqDoubleStack *s,int *element,int stackNum)
{
    if(stackNum==1)
    {
        if(s->top1==-1)
            return false;
        *element=s->data[s->top1];
        return true;
    }
    if(stackNum==2)
    {
        if(s->top2==MaxSize)
            return false;
        *element=s->data[s->top2];
        return true;
    }
}

//出栈
int Pop(SqDoubleStack *s,int *element,int stackNum)
{
    if(stackNum==1)
    {
        if(s->top1==-1)
            return false;
        *element=s->data[s->top1];
        s->top1--;
        return true;
    }
    if(stackNum==2)
    {
        if(s->top2==MaxSize)
            return false;
        *element=s->data[s->top2];
        s->top2++;
        return true;
    }

}
int Push(SqDoubleStack *s,int element,int stackNum)
{
    if(s->top2-s->top1==1)
    {
        cout<<"共享栈已经满"<<endl;
        return false;
    }
    if(stackNum==1)
    {
        s->top1++;
        s->data[s->top1]=element;
        return true;
    }
    if(stackNum==2)
    {
        s->top2--;
        s->data[s->top2]=element;
        return true;
    }
}

int StackTraverse(SqDoubleStack *s)
{
    cout<<"栈1的元素为";
    for(int i=s->top1;i!=-1;i--)
    {
        cout<<s->data[i]<<" ";
    }
    cout<<endl;
    cout<<"栈2的元素为";
    for(int i=s->top2;i!=MaxSize;i++)
    {
        cout<<s->data[i]<<" ";
    }
    cout<<endl;
}

//共享栈测试
void test2()
{
    int j;
    SqDoubleStack s;
    int e;
    if(InitStack(&s)==1)
    {
            for(j=1;j<=5;j++)
                    Push(&s,j,1);
            for(j=MaxSize;j>=MaxSize-2;j--)
                    Push(&s,j,2);
    }
    cout<<"共享栈中的元素为："<<endl;
    StackTraverse(&s);
    cout<<"当前栈中的元素数量为："<<StackLength(&s)<<endl;
    Pop(&s,&e,2);
    cout<<"栈2的栈顶元素为："<<e<<endl;

    cout<<"添加元素"<<endl;
    for(j=6;j<=MaxSize-2;j++)
                Push(&s,j,1);
    cout<<"输出共享栈元素"<<endl;
    StackTraverse(&s);
    ClearStack(&s);
    cout<<"栈是否为空"<<StackEmpty(&s)<<endl;
}

//链栈的设计

typedef struct StackNode
{
    int value;
    struct StackNode * next;
}StackNode;

typedef struct StackList
{
    StackNode * head;
    int length;
}StackList;

int InitStack(StackList *s);
int ClearStack(StackList *s);
int StackEmpty(StackList *s);
int StackLength(StackList *s);
int GetTop(StackList *s,int *element);
int Pop(StackList *s,int *element);
int Push(StackList *s,int element);
int StackTraverse(StackList *s);


//链栈初始化
int InitStack(StackList *s)
{
    s->head=NULL;
    s->length=0;
    return true;
}
//清空链栈
int ClearStack(StackList *s)
{
    StackNode* head=s->head;
    while(head!=NULL)
    {
        StackNode *p=head;
        head=head->next;
        free(p);
        s->length--;
    }
    s->head=NULL;
    return true;
}

//判断链栈是否为空
int StackEmpty(StackList *s)
{
    if(s->head==NULL)
        return true;
    else
        return false;
}

//栈的长度
int StackLength(StackList *s)
{
    return s->length;
}
//获取栈顶元素
int GetTop(StackList *s,int *element)
{
    if(s->length==0)
    {
        cout<<"链栈为空"<<endl;
        return false;
    }
    StackNode *head=s->head;
    *element=head->value;
    return true;
}

//弹出栈顶元素
int Pop(StackList *s,int *element)
{
    if(s->length==0)
    {
        cout<<"链栈为空"<<endl;
        return false;
    }
    StackNode *head=s->head;
    *element=head->value;

    s->head=s->head->next;
    free(head);
    s->length--;
    return true;
}
//插入元素
int Push(StackList *s,int element)
{
    StackNode *node=(StackNode*)malloc(sizeof(StackNode));
    node->next=NULL;
    node->value=element;
    
    node->next=s->head;
    s->head=node;
    s->length++;
    return true;
}
//遍历输出元素
int StackTraverse(StackList *s)
{
    StackNode * head=s->head;
    cout<<"链栈的元素为：";
    while(head!=NULL)
    {
        cout<<head->value<<" ";
        head=head->next;
    }
    cout<<endl;
    return true;
}

void test3()
{
    int j;
    StackList s;
    int e;
    if(InitStack(&s)==1)
            for(j=1;j<=10;j++)
                    Push(&s,j);
    cout<<"链中的元素为："<<endl;
    StackTraverse(&s);
    Pop(&s,&e);
    cout<<"栈顶元素为"<<e<<endl;
    cout<<"栈是否为空"<<StackEmpty(&s)<<endl;

    GetTop(&s,&e);
    cout<<"栈顶元素为"<<e<<endl;
    ClearStack(&s);
    cout<<"栈是否为空"<<StackEmpty(&s)<<endl;
}

//斐波那契数列实现
//（1）非递归实现

void Fbi_no_recur(int num)
{
    int fbi[MaxSize];
    fbi[0]=0;
    fbi[1]=1;
    for(int i=2;i<40;i++)
    {
        fbi[i]=fbi[i-1]+fbi[i-2];
    }
    cout<<"输出斐波那契数列"<<endl;
    for(int i=0;i<40;i++)
        cout<<fbi[i]<<" ";
    cout<<endl;
}

int fbi_recur(int num)
{
    if(num<=2)
        return num==1?0:1;
    return fbi_recur(num-1)+fbi_recur(num-2);
}

void test4()
{
    cout<<"非递归的斐波那契"<<endl;
    Fbi_no_recur(40);
    cout<<"递归的斐波那锲"<<endl;
    for (int i=1;i<=40;i++)
    {
        cout<<fbi_recur(i)<<" ";
    }
    cout<<endl;
}


//利用双栈解决表达式求值
//判断运算符的优先级
int Priority(char oper)
{
    switch (oper)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '%':
    case '/':
        return 2;
    case '(':
    case ')':
        return 0;
    default:
        return -1;
    }
}

void calcilate_express()
{
    //输入表达式
    string expr;
    int strsize=0;
    int num1;
    int num2;
    stack<int> numstack;
    stack<int> operstack;
    cout<<endl<<"请输入需要输入的表达式"<<endl;
    cin>>expr;

    //依次遍历表达式串
    strsize=expr.size();
    for(int i=0;i<strsize;i++)
    {
        num1=0;
        num2=0;

        //将一个或者多个字符转换为一个数
        while(expr[i]>='0'&&expr[i]<='9')
        {
            num1=expr[i]-'0';
            num2=num2*10+num1;
            i++;
        }
        //操作数入栈
        numstack.push(num2);
        //初始时操作栈为空，需要将操作符入栈
        if(operstack.empty())
        {
            operstack.push(expr[i]);
            continue;
        }
        //操作符为左括号，或者表达式的优先级高于栈顶，则操作符入栈
        if(Priority(expr[i])>Priority(operstack.top())||expr[i]=='(')
        {
            operstack.push(expr[i]);
            continue;
        }
        //操作符优先级小于等于栈顶，进行计算
        while(Priority(expr[i])<=Priority(operstack.top()))
        {
            num1=numstack.top();
            numstack.pop();
            num2=numstack.top();
            numstack.pop();
            char oper=operstack.top();
            operstack.pop();
            switch (oper)
            {
                case '+':
                    num2+=num1;
                    break;
                case '-':
                    num2-=num1;
                    break;
                case '*':
                    num2*=num1;
                    break;
                case '/':
                    num2/=num1;
                    break;
                case '%':
                    num2%=num1;
                    break;
            }
            numstack.push(num2);
            //字符为')'时，‘（’出栈
            if(expr[i]==')')
            {
                operstack.pop();
                i++;
            }
            //栈为空，直接入栈其他字符
            if(operstack.empty())
                break;
            //栈顶为‘（’ 入栈其他字符
            if(operstack.top()=='(')
                break;   
        }
        
        if(i<strsize)
            operstack.push(expr[i]);
    }
    cout<<"结果"<<numstack.top()<<endl;
}
int main()
{
    // test2();
    // test3();
    // test4();
    calcilate_express();
    return 0;

}