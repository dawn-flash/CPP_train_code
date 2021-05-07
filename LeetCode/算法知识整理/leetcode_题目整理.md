

# 链表

## 707构建链表

### 1.单链表

没有头结点，结点的下标从0开始

+ 初始化链表：ListNode可以定义一个构造函数用于结构体的初始化
+ 获取下标为index的结点：i和p必须同步
+ 尾插法：需要判断head是否指向空
+ 插入下标index：需要先将index==0插入，然后寻找index的前驱结点
+ 删除下标index结点：需要先将index=0情况排除，然后寻找index的前驱结点·

```C++
class MyLinkedList {
private:
    typedef struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x):val(x),next(nullptr){}
    }ListNode;
    ListNode *head;
public:
    /** Initialize your data structure here. */
    MyLinkedList():head(nullptr){    
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        //index从0开始，同时i和指针p需要同步
        int i=0;
        ListNode *p=head;
        while (p&&i<index)
        {
            p=p->next;
            i++;
        }
        if (p) return p->val;
        else return -1;
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        ListNode *p=new ListNode(val);
        p->next=head;
        head=p;
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        ListNode *temp=new ListNode(val);
        ListNode *p=head;
        if (head==nullptr)
        {
            head=temp;
            return;
        }
        while(p->next!=nullptr)
            p=p->next;
        p->next=temp;
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        ListNode *temp=new ListNode(val);
        //index==0的情况
        if(index<=0)
        {
            temp->next=head;
            head=temp;
            return;
        }
        //寻找index-1结点
        int i=0;
        ListNode *p=head;
        while(p &&i<index-1)
        {
            p=p->next;
            i++;
        }
        //判断是否找到
        if (p)
        {
            temp->next=p->next;
            p->next=temp;
        }


    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if (head==nullptr|| index<0)
            return;
        //index==0的情况排除
        if(index==0)
        {
            head=head->next;
        }
        //寻找index-1的结点
        int i=0;
        ListNode *p=head;
        while(p && i<index-1)
        {
            p=p->next;
            i++;
        }
        //没找到直接删除
        if (!p) return;
        //找到判断是否有index结点
        if(p->next)
        {
            ListNode *del=p->next;
            p->next=del->next;
            delete del;
        }

    }
    
    int length()
    {
        int i=0;
        ListNode *p=head;
        while(p)
        {
            p=p->next;
            i++
        }
        return i;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
```

### 2循环链表

```C++
class MyLinkedList {
private:
    typedef struct ListNode{
        int val;
        ListNode *next,*prev;
        ListNode(int val):val(val),next(nullptr),prev(nullptr){}
    }ListNode;
    ListNode *head;
    ListNode *tail;
    int size=0;
public:
    /** Initialize your data structure here. */
    MyLinkedList():size(0),head(nullptr),tail(nullptr){
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if (index<0)
            return -1;
        int i=0;
        ListNode *p=head;
        while (p && i<index)
        {
            p=p->next;
            i++;
        }
        if(p)
            return p->val;
        return -1;
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        ListNode *temp=new ListNode(val);
        if(head==nullptr)
        {
            head=temp;
            tail=temp;
            size++;
            return;
        }
        temp->next=head;
        head->prev=temp;
        head=temp;
        size++;

    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        if (head==nullptr)
        {
            ListNode *temp=new ListNode(val);
            head=temp;
            tail=temp;
            size++;
            return;
        }
        ListNode *temp=new ListNode(val);
        tail->next=temp;
        temp->prev=tail;
        size++;
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if(index<=0)
        {
            addAtHead(val);
            size++;
            return;
        }
       if(index==size)
       {
           addAtTail(val);
           size++;
           return;
       }
       if(index>size) return;
       ListNode *p=head;
       int i=0;
       while(p &&i<index-1)
       {
           p=p->next;
           i++;
       }
       if (p==nullptr) return;
       ListNode *temp=new ListNode(val);
       temp->next=p->next;
       temp->prev=p;
       p->next->prev=temp;
       p->next=temp;
       size++;
        
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if(head==nullptr||index<0)
            return;
        if (index==0)
        {
            if(size==1)
            {
                ListNode *del=head;
                head=nullptr;
                tail=head;
                delete del;
                size--;
                return;
            }
            ListNode *del=head;
            head=head->next;
            head->prev=nullptr;
            delete del;
            size--;
        }
        if (index==size-1)
        {
            ListNode *temp=tail;
            temp->prev->next=nullptr;
            delete tail;
            size--;
            return;
        }
        int i=0;
        ListNode *p=head;
        while(p &&i<index-1)
        {
            p=p->next;
            i++;
        }
        if(p==nullptr) return;
        ListNode *temp=p->next;
        p->next=temp->next;
        temp->next->prev=p;
        delete temp;
        size--;
    }
    int length()
    {
        return size;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
```



## 21 合并两个有序链表

### 1.迭代实现

类似归并排序中的合并：

**关键点：**

定义一个新的链表，带头结点（方便结点操作）

```C++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(1);//结构体的初始化方法
        ListNode* ret = head;
        
        while (l1 != NULL && l2 != NULL) {
            if (l1->val < l2->val) {
                head->next = l1;
                l1 = l1->next;
            } else {
                head->next = l2;
                l2 = l2->next;
            }
            head = head->next;
        }
        head->next = l1 == NULL ? l2 : l1;
        return ret->next;
    }
};

```

### 2.递归实现

关键点：

+ 函数功能：返回 l1*l*1 指向的结点和 l2*l*2 指向的结点中，值较小的结点指针，并将下级函数的返回值链接到当前结点上
+ 函数返回值：返回结点指针
+ 函数结束条件：当 l1*l*1 为空，或 l2*l*2 为空，函数结束

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    //递归实现有序链表合并
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1==NULL)
            return l2;
        if (l2==NULL)
            return l1;
        if(l1->val<l2->val)
        {
            l1->next=mergeTwoLists(l1->next,l2);
            return l1;
        }
        else
        {
            l2->next=mergeTwoLists(l2->next,l1);
            return l2;
        }
    }
};
```

## 206 反转链表

### 1.迭代实现

注意点：

1. 前后指针单向遍历，附加一个临时指针

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre=NULL,* cur=head;
        while(cur!=NULL)
        {
            ListNode* temp=cur->next;
            cur->next=pre;
            pre=cur;
            cur=temp;
        }
        return pre;
    }
};
```

### 2.递归实现

+ 退出条件：一个结点或者没有结点退出
+ 返回值：返回新翻转链表的头结点
+ 当前函数功能：将头结点插入到新翻转链表中

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head==NULL || head->next==NULL)
            return head;
        ListNode* newhead=reverseList(head->next);
        head->next->next=head;
        head->next=NULL;
        return newhead;
    }
};
```

## 2两数相加

+ 创建新链表存储结果（带头结点）
+ 使用一个carry数保存进位信息
+ 双指针遍历双链表，对应位置元素相加，没有元素时补上加0

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *p=l1;
        ListNode *q=l2;
        ListNode *newlist=new ListNode(-1);
        ListNode *cur=newlist;
        int carry=0;
        while(p!=NULL || q!=NULL)
        {
            //空元素加0
            int x=(p==NULL)?0:p->val;
            int y=(q==NULL)?0:q->val;
            int sum=x+y+carry;
            int result=sum%10;
            carry=sum/10;
            cur->next=new ListNode(result);
            cur=cur->next;
            if(p!=NULL) p=p->next;
            if(q!=NULL) q=q->next;
        }
        if (carry>0)
            cur->next=new ListNode(carry);
        return newlist->next;
    }
};
```

## 19 删除倒数第n个结点

> 给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
>
> 示例：
>
> 给定一个链表: 1->2->3->4->5, 和 n = 2.
>
> 当删除了倒数第二个节点后，链表变为 1->2->3->5.
> 说明：
>
> 给定的 n 保证是有效的。
>
> 进阶：能尝试使用一趟扫描实现吗？
>
> 

### 方法一：两次遍历

思路：

+ 第一次遍历求链表的长度Length
+ 第二次遍历删除第length-n+1个结点，即寻找删除结点前一个结点length-n

注意：为了有效删除，防止一些特殊情况，链表上添加头结点辅助（删除第一个结点，或者链表中只有一个结点）

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy=new ListNode(-1);
        dummy->next=head;
        int length=0;
        ListNode *p=dummy->next;
        while(p!=NULL)
        {
            p=p->next;
            length++;
        }

        int find_index=length-n;
        int j=0;
        p=dummy;
        while(j<find_index)
        {
            p=p->next;
            j++;
        }
        //ListNode *temp=p->next;
        p->next=p->next->next;
        //delete temp;
        return dummy->next;
    }
};
```

### 方法二：一次遍历

+ 使用n间隔快慢双指针，当前指针遍历到结尾时，后指针+1即为第n个结点。

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy=new ListNode(-1);
        dummy->next=head;
        ListNode *p=head;
        ListNode *q=dummy;
        //pq间隔n个结点
        for(int i=1;i<=n;i++)
            p=p->next;
        
        //p=NULL时，q为倒数第i个结点前一个结点
        while (p!=NULL)
        {
            p=p->next;
            q=q->next;
        }
        ListNode *temp=q->next;
        q->next=q->next->next;
        delete temp;
        return dummy->next;
    }
};
```

### 方法三：递归调用

+ 递归=递推+回溯，利用回溯时，对target进行判断，删除结点，
+ target使用引用，才可以进行target递减
+ 需要添加一个头结点，不然有些情况不能统一处理

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* auxil=new ListNode(0);
        auxil->next=head;  //如果删除的是头结点，不能用递归统一处理，就人为加一个prior便于处理
        removeNthFromEnd_Solition(auxil,n);
        return auxil->next;
    }
    void removeNthFromEnd_Solition(ListNode*& p,int& target){
        if(p==NULL)
            return ；
        removeNthFromEnd_Solition(p->next,target); // 递归到顶
        if(--target==-1)        // 递归后回溯，target==0的节点是要删除的节点
        p->next=p->next->next;  // 因此target==-1时的节点是待删除节点的prior
        }
    }
};

```

## 24 两两交换链表结点

> 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
>
> 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
>
> 
>
> 示例:
>
> 给定 1->2->3->4, 你应该返回 2->1->4->3.
>
> 

关键，其实是讲奇数项和偶数项交换即可。

### 1.迭代：三指针遍历

pre，first，second三指针 

pre 记录first前结点，first和second是交换结点

关键：

+ 需要添加一个头结点来保证有第一个结点有pre
+ 不能同时使用快慢双指针遍历，因为指针的步长不是1，而是2.同时遍历会越界。此时使用单指针遍历，同时加上&&，作为判断。当左边为空时不进行判断右边。

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        //建立空结点，使得有前驱结点pre（第一次交换不失普遍性）
        ListNode *dummy=new ListNode(-1);
        dummy->next=head;
        ListNode *pre=dummy;
        ListNode *p=head;
    	
        //关键点使用单指针遍历的原因，条件与的左边判断失败则不进行右边判断
        while(p!=NULL && p->next!=NULL)
        {
            //指针赋值
            ListNode *firstnode=p;
            ListNode *secondnode=p->next;
			//指针交换
            firstnode->next=secondnode->next;
            secondnode->next=firstnode;
            pre->next=secondnode;
			
            //再次初始化pre和p
            pre=firstnode;
            p=firstnode->next;
        }

        return dummy->next;
    }
};
```



### 2.递归写法

+ 退出条件：head=NULL或者head->next=NULL。
+ 返回值，返回当前链表头结点，其实就是secondNode
+ 函数功能：交换当前两个结点

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head==NULL || head->next==NULL)
            return head;
        //初始化结点
        ListNode *firstNode=head;
        ListNode *secondNode=head->next;
		//swap结点
        firstNode->next=swapPairs(secondNode->next);
        secondNode->next=firstNode;
		
        //返回当前链表头结点
        return secondNode;
    }
};
```

## 83 删除排序链表中重复元素

### 1.普通双指针法

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head==NULL|| head->next==NULL)
            return head;

        ListNode *p=head->next;
        ListNode *q=head;
        while (p!=NULL)
        {
            if (p->val==q->val)
            {
                ListNode *tem=p;
                q->next=p->next;
                //delete tem;
            }    
            else
                q=q->next;
            p=p->next;
   
        }
        return head;
    }
};
```

### 2.cur和cur->next 模拟双指针

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *cur=head;
        while (cur!=NULL && cur->next!=NULL)
        {
            if(cur->val==cur->next->val)
            {
                ListNode *temp=cur->next;
                cur->next=cur->next->next;
                delete temp;
            }
            else
            {
                cur=cur->next;
            }         
        }
        return head;
    }
};
```

## 82 删除链表中重复元素

> #### [82. 删除排序链表中的重复元素 II](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)
>
> 难度中等256
>
> 给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 *没有重复出现* 的数字。
>
> **示例 1:**
>
> ```
> 输入: 1->2->3->3->4->4->5
> 输出: 1->2->5
> ```
>
> **示例 2:**
>
> ```
> 输入: 1->1->1->2->3
> 输出: 2->3
> ```

**思路：**
三指针维护一个滑动窗口。

### **1.三指针维护**

注意事项：

+ 添加头结点：可能删除第一个结点
+ 添加标记，判断是否删除滑动窗口元素
+ 删除时判断是否提前结束

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        //无结点或者一个结点时直接退出
        if(head==NULL || head->next==NULL)
            return head;
        ListNode *dummy=new ListNode(-1);
        dummy->next=head;
        ListNode *pre=dummy;
        ListNode *cur=head;
        ListNode *post=head->next;
        //维护一个标志判断是否需要删除结点
        bool flag=false;
        while(post)
        {
            while(post && cur->val==post->val)
            {
                cur=cur->next;
                post=post->next;
                flag=true;
            }
            if(flag)
            {//判断post是否最后一个，此时可以直接结束，不然后面代码报错
                pre->next=post;
                if (post==NULL)
                    break;
                cur=post;
                post=post->next;
                flag=false;
            }
            else
            {
                pre=cur;
                cur=post;
                post=post->next;
            }
        }
        head=dummy->next;
        delete dummy;
        return head;
    }
};
```

### 2.快慢双指针

+ 一：快指针寻找相同元素，慢指针保持已经完成的元素
+ 最后元素的处理：结束后快慢指针一定相邻，如果没有相邻的，还需要删除元素

```CPP
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *dumpy=new ListNode(-1);
        dumpy->next=head;
        ListNode *fast=head,*slow=dumpy;
        while(fast!=NULL &&fast->next!=NULL)//快指针用于查找相同元素
        {
            if(fast->val!=fast->next->val)
            {
                if (slow->next==fast)//快指针先前没查找到相同数
                    slow=fast;
                else
                    slow->next=fast->next;////先前查找到相同数，将出现相同数的前一个数连接到相同数后第一个不同数
            }
            fast=fast->next;
        }
        //处理fast->next==null的情况，然后最后还剩下元素没有删除的情况
        if(slow->next!=fast)  // 针对类似[1,1]的情况
            slow->next=fast->next;
        return dumpy->next;
    }
};
```

## 61 旋转链表

> 给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
>
> 示例 1:
>
> 输入: 1->2->3->4->5->NULL, k = 2
> 输出: 4->5->1->2->3->NULL
> 解释:
> 向右旋转 1 步: 5->1->2->3->4->NULL
> 向右旋转 2 步: 4->5->1->2->3->NULL
>
> 

关键点：一般移动r=k%length 位置。

1. 旋转链表后的头结点在倒数第r个位置。（前后指针法，求倒数r+1位置（尾指针位置））
2. 将链表变为环
3. 断开链表，形成新链表

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        //排除情况
        if (head==NULL || head->next==NULL)
            return head;
        
        //求链表长度
        int length=0;
        ListNode *p=head;
        while (p!=NULL)
        {
            p=p->next;
            length++;
        }
        
        //k步取余
        int remain=k%length;
        if (remain==0)
            return head;
         ListNode *pre=head;
         ListNode *cur=head;
         
         //寻找倒数第remian+1个元素
         int i=1;
         while (cur && i<remain+1)
         {
             cur=cur->next;
             i++;
         }
         while(cur->next!=NULL)
         {
             pre=pre->next;
             cur=cur->next;
         }
        
         //建立环
         p=head;
         while(p->next)
            p=p->next;
        p->next=head;
		
        //头结点重新取值
        head=pre->next;
        pre->next=NULL;
        return head;


    }
};
```

## 160 相交链表

最推荐双指针法；

暴力比较容易 实现

哈希表法：根本上减少了匹配查找的时间，但是增加了空间

1. 暴力法，直接匹配ab两个链表

   时间复杂度：O(mn)

   空间：O(1)

```C++
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headB==NULL || headA==NULL)
            return NULL;
        ListNode *pa=headA;
        
        while(pa)
        {
            ListNode *pb=headB;//注意
            while(pb)
            {
                if(pa!=pb)
                    pb=pb->next;
                else
                    return pa;
            }
            pa=pa->next;
        }
        return NULL;
        
    }
};
```

2.双指针法

遍历a，a为空，a=headb

遍历b，b为空，b=heada

循环两次后，两者一定同时到达null，或者提前到达相等位置。

时间复杂度：O（n）

空间复杂度：O（1）

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headB==NULL || headA==NULL)
            return NULL;
        ListNode *pa=headA;
        ListNode *pb=headB;
        while(pa!=pb)
        {
            pa=(pa==nullptr? headB: pa->next);
            pb=(pb==nullptr? headA: pb->next);
        }
        return pa;


        
    }
};
```

3.哈希表法

使用一个hash set  遍历一个链表，set中存放其所有指针， 遍历另一个链表，去set中找相同指针
时间复杂度O(m + n)    空间复杂度O(m) 或 O(n)

> 使用哈希set的原因，查找和删除添加快

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA==NULL || headB==NULL)
            return NULL;
        std::unordered_set<ListNode *> pset;
        ListNode *pa=headA;
        ListNode *pb=headB;
        while(pa)
        {
            pset.insert(pa);
            pa=pa->next;
        }
        while(pb)
        {
            if (pset.find(pb)!=pset.end())
                return pb;
            pb=pb->next;
        }
        return NULL;
    }
};
```

## 141 环形链表

1. 快慢双指针法

   快指针一次两步，

   慢指针一次一步。

注意：退出条件判断，需要first和first->next

​			先让快指针走一步，避免开始一样。

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head==nullptr ||head->next==nullptr)
            return false;
        ListNode *first=head->next;
        ListNode *second=head;
        while (first && first->next)
        {   
            if(first==second)
                return true;
            first=first->next->next;
            second=second->next;
            
        }
        return false;
        
    }
};
```

2.哈希表法

使用unorder_set保存遍历过的结点，提高查找效率

> 哈希表的查找，删除，增加，都是O(1)时间复杂度

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head==NULL|| head->next==NULL)
            return false;
        unordered_set<ListNode *> pset;
        ListNode *p=head;
        while(p)
        {
            if(pset.find(p)!=pset.end())
                return true;
            pset.insert(p);
            p=p->next;
        }
        return false;
    }
};
```

## 203 移除元素

> 删除链表中等于给定值 ***val\*** 的所有节点。
>
> **示例:**
>
> ```
> 输入: 1->2->6->3->4->5->6, val = 6
> 输出: 1->2->3->4->5
> 
> ```

### 1.双指针法。

注意：

1. 使用dummy头结点，可以要删除第一个元素。
2. 前指针遍历，后指针记录前一个位置，同时遍历。

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if(head==NULL)
            return head;
        ListNode *dummy=new ListNode(-1);
        dummy->next=head;
        ListNode *pre=dummy;
        ListNode *cur=head;

        while(cur)
        {
            if(cur->val==val)
            {
                ListNode *temp=cur;
                cur=cur->next;
                pre->next=cur;
                delete temp;
                continue;
            }
            cur=cur->next;
            pre=pre->next;
        }

        head=dummy->next;
        return head;
    }
};
```

### 2.递归

> 1. 返回条件
> 2. 返回值
> 3. 当前函数需要做的事情。

step1: 如果传入链表为空，直接返回空值即可
step2: 假设removeElements已经实现，则只需将头结点与删除元素后的链表相连即可
step3: 判断头结点是否为要删除的元素，如果是返回head->next; 否则返回head；

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (head==NULL)
            return NULL;
        head->next=removeElements(head->next,val);
        return head->val==val?head->next:head;
    }
};
```

## 234回文链表

> 请判断一个链表是否为回文链表。
>
> **示例 1:**
>
> ```
> 输入: 1->2
> 输出: false
> ```
>
> **示例 2:**
>
> ```
> 输入: 1->2->2->
> ```



### 1. 使用vector辅助

> //使用reverse_copy函数将v倒置到v1.
>
> reverse_copy(v.begin(),v.end(),v1.begin());

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 #include<vector>
 #include<algorithm>
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head==NULL)
            return true;
        std::vector<int> v;
        ListNode *p=head;
        while(p)
        {
            v.push_back(p->val);
            p=p->next;
        }
        //1.方法1 使用algorithm的方法
        vector<int> v1=v;
        //使用reverse_copy函数将v倒置到v1.
        reverse_copy(v.begin(),v.end(),v1.begin());
        if(v1==v)
            return true;
        return false;   
        
        //2.使用下标直接判断
        for(int i=0;i<v.size()/2;i++)
        {
            if(v[i]!=v[v.size()-1-i])
            {
                return false;
            }
        }
        return true;
    }
};
```

### 2.使用翻转链表判断

+ 快慢指针找中点（不用区分偶奇 ）可以观察图像
+ 翻转后半部分链表（双指针加临时指针）
+ 比较两个链表

[参考](https://leetcode-cn.com/problems/palindrome-linked-list/solution/c-shi-yong-shu-zu-fan-zhuan-lian-biao-by-zuo-10/)

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head==NULL || head->next==NULL)
            return true;
        
        //快慢双指针找中点
        ListNode *fast=head;
        ListNode *slow=head;
        while(fast && fast->next)
        {
            fast=fast->next->next;
            slow=slow->next;
        }
        //链表翻转
        ListNode *pre=slow;
        ListNode *cur=pre->next;
        while(cur)
        {
            ListNode *temp=cur->next;
            cur->next=pre;
            pre=cur;
            cur=temp;
        }
        slow->next=nullptr;

        //比较两端是否相等
        ListNode *p=head;
        while(p && pre)
        {
            if(p->val!=pre->val)
                return false;
            p=p->next;
            pre=pre->next;
        }
        return true;

    }
};
```

## 237  删除链表中结点

> 请编写一个函数，使其可以删除某个链表中给定的（非末尾）节点，你将只被给定要求被删除的节点。
>
> 现有一个链表 -- head = [4,5,1,9]，它可以表示为:
>
> 示例 1:
>
> 输入: head = [4,5,1,9], node = 5
> 输出: [4,1,9]
> 解释: 给定你链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.

难点，无法获取当前结点的前一个结点，只可以修改结点中的元素，然后删除最后一个结点。

==我服了，想错了==

> 只需要删除当前结点的下一个结点便可

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode *cur=node;
        ListNode *post=node->next;
        while(post)
        {
            cur->val=post->val;
            if (post->next==NULL)
                break;
            cur=post;
            post=post->next;
        }
        cur->next=post->next;
    }
};
//新的解法
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val=node->next->val;
        node->next=node->next->next;
    }
};
```

## 328 奇偶链表

> 给定一个单链表，把所有的奇数节点和偶数节点分别排在一起。请注意，这里的奇数节点和偶数节点指的是节点编号的奇偶性，而不是节点的值的奇偶性。
>
> 请尝试使用原地算法完成。你的算法的空间复杂度应为 O(1)，时间复杂度应为 O(nodes)，nodes 为节点总数。
>
> 示例 1:
>
> 输入: 1->2->3->4->5->NULL
> 输出: 1->3->5->2->4->NULL
>
> 

### 奇偶指针遍历

+ 形成奇数链和偶数链，然后奇偶合并

> 注意循环条件和拆链，建链的过程

[参考](https://leetcode-cn.com/problems/odd-even-linked-list/solution/qi-ou-lian-biao-by-leetcode/)

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(head==nullptr || head->next==nullptr || head->next->next==nullptr)
            return head;
        ListNode *odd=head;
        ListNode *even=head->next;
        ListNode *evenhead=even;
        while(even && even->next)
        {
            odd->next=even->next;
            odd=even->next;
            even->next=odd->next;
            even=even->next ;
        }
        odd->next=evenhead;
        return head;

    }
};
```



# 数组

## [724. 寻找数组的中心索引](https://leetcode-cn.com/problems/find-pivot-index/)

> 给定一个整数类型的数组 nums，请编写一个能够返回数组 “中心索引” 的方法。
>
> 我们是这样定义数组 中心索引 的：数组中心索引的左侧所有元素相加的和等于右侧所有元素相加的和。
>
> 如果数组不存在中心索引，那么我们应该返回 -1。如果数组有多个中心索引，那么我们应该返回最靠近左边的那一个。 
>
> 示例 1：
>
> 输入：
> nums = [1, 7, 3, 6, 5, 6]
> 输出：3
> 解释：
> 索引 3 (nums[3] = 6) 的左侧数之和 (1 + 7 + 3 = 11)，与右侧数之和 (5 + 6 = 11) 相等。
> 同时, 3 也是第一个符合要求的中心索引。
> 示例 2：
>
> 输入：
> nums = [1, 2, 3]
> 输出：-1
> 解释：
> 数组中不存在满足此条件的中心索引。
>
> 来源：力扣（LeetCode）
> 链接：https://leetcode-cn.com/problems/find-pivot-index
> 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

方法：前缀和

> + 先统计总和，
>
> + 进行遍历，一直记录下标i的前缀和，当left*2==sum-num[i],游戏结束

```C++
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        if(nums.size()==0)
            return -1;
        int left_sum=0;
        int right_sum=0;
        for(int i=0;i<nums.size();i++)
            right_sum+=nums[i];
        
        for(int i=0;i<nums.size();i++)
        {
            if((left_sum*2)==right_sum-nums[i])
                return i;
            left_sum+=nums[i];
        }
        return -1;
    }
};
```

**复杂度**

+ 时间O(N)
+ 空间O(1)

## [56. 合并区间](https://leetcode-cn.com/problems/merge-intervals/)

> 给出一个区间的集合，请合并所有重叠的区间。
>
> 示例 1:
>
> 输入: intervals = [[1,3],[2,6],[8,10],[15,18]]
> 输出: [[1,6],[8,10],[15,18]]
> 解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
> 示例 2:
>
> 输入: intervals = [[1,4],[4,5]]
> 输出: [[1,5]]
> 解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。
> 注意：输入类型已于2019年4月15日更改。 请重置默认代码定义以获取新方法签名。
>
> 来源：力扣（LeetCode）
> 链接：https://leetcode-cn.com/problems/merge-intervals
> 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

**方法**：

1. 排序+单指针遍历：单个依次合并

2. 排序+双指针遍历：多个元素同时合并

### 方法一、排序+单指针遍历

+ 对列表按照左端点大小排序

+ 新建列表，遍历目标列表，合并：一次将一个元素合并

  > + 第一个元素直接加入
  > + 第二个元素开始‘
  >   + 尾元素<L,直接加入
  >   + 尾元素>L,合并max（back[1]，L）

```C++
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size()==0)
            return {};

        //按照左端点排序
        sort(intervals.begin(),intervals.end());

        vector<vector<int>> temp;
        //遍历目标列表
        for(int i=0;i<intervals.size();i++)
        {
            int L=intervals[i][0],R=intervals[i][1];
            if(!temp.size()||temp.back()[1]<L) // 空或者尾小于L 直接加入
                temp.push_back(intervals[i]);
            else//非空，或者尾》L，修改尾
            {
                temp.back()[1]=max(temp.back()[1],R);
            }
        }
        return temp;
    }
};
```

### 方法二、排序+双指针遍历

+ 对原列表按照左端点排序

+ 使用双指针，左指针记录合并区间左端，右指针探索可合并区间右端

  > 一次将所有可合并的序列同时合并加入到新列表

```C++
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size()==0)
            return {};

        //按照左端点排序
        sort(intervals.begin(),intervals.end());

        vector<vector<int>> temp;
        //遍历目标列表
        for(int i=0;i<intervals.size();)
        {
            int j=i+1;//i指向左端点，j指向探索右端点
            int t=intervals[i][1];//记录当前区间的最大元素
            while(j<intervals.size()&&t>=intervals[j][0])
            {
                t=max(t,intervals[j][1]);
                j++;
            }
            temp.push_back({intervals[i][0],t});
            i=j;
        }
        return temp;
    }
};
```

## [面试题 01.07. 旋转矩阵](https://leetcode-cn.com/problems/rotate-matrix-lcci/)

> 给你一幅由 N × N 矩阵表示的图像，其中每个像素的大小为 4 字节。请你设计一种算法，将图像旋转 90 度。
>
> 不占用额外内存空间能否做到？
>
> 示例 1:
>
> 给定 matrix = 
> [
> [1,2,3],
> [4,5,6],
> [7,8,9]
> ],
>
> 原地旋转输入矩阵，使其变为:
> [
> [7,4,1],
> [8,5,2],
> [9,6,3]
> ]

### 用翻转代替旋转

+ 水平翻转
+ 主对角线翻转

最终的效果，矩阵旋转90度。

```C++
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int row=matrix.size(),column=matrix[0].size();
        vector<int> temp={};
        //竖直方向折叠
        for(int i=0;i<row/2;i++)
        {
            temp=matrix[i];
            matrix[i]=matrix[row-1-i];
            matrix[row-1-i]=temp;
        }
        //矩阵对称
        int temp_int=0;
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<i;j++)
            {
                temp_int=matrix[i][j];
                matrix[i][j]=matrix[j][i];
                matrix[j][i]=temp_int;
            }
        }
    }
};
```

复杂度

+ 时间复杂度：O(n2)
+ 空间复杂度O(1)

## [面试题 01.08. 零矩阵](https://leetcode-cn.com/problems/zero-matrix-lcci/)

### 开辟布尔数组

+ 开辟两个布尔数组保存行列是否为零

```C++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int row=matrix.size(),column=matrix[0].size();
        vector<bool> row_vec(row,false);
        vector<bool> col_vec(column,false);
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<column;j++)
            {
                if(matrix[i][j]==0)
                {
                    row_vec[i]=true;
                    col_vec[j]=true;
                }
            }
        }
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<column;j++)
            {
                if(row_vec[i]||col_vec[j])
                    matrix[i][j]=0;
            }
        }

    }
};
```

复杂度：

+ 时间O(N^2)
+ 空间O(N)

### 巧用第一行和第一列存储数据

+ 使用第一行和第一列存储该行和该列是否为零的信息

```C++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int row=matrix.size(),column=matrix[0].size();
        bool row_zero=false;
        bool column_zero=false;
        //遍历数组，寻找信息
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<column;j++)
            {
                if(matrix[i][j]==0)
                {
                    if(i==0)
                        row_zero=true;
                    if(j==0)
                        column_zero=true;
                    matrix[i][0]=0;
                    matrix[0][j]=0;
                }
            }
        }
        //将对应行置零
        for(int i=1;i<row;i++)
        {
            if(matrix[i][0]==0)
            {
                for(int j=1;j<column;j++)
                {
                    matrix[i][j]=0;
                }
            }  
        }
         //将对应列置零
        for(int j=1;j<column;j++)
        {
            if(matrix[0][j]==0)
            {
                for(int i=1;i<row;i++)
                {
                    matrix[i][j]=0;
                }
            }  
        }
        //第一行是否请零
        if(row_zero)
        {
            for(int j=0;j<column;j++)
                matrix[0][j]=0;
        }
        //第一列是否清零
        if(column_zero)
        {
            for(int i=0;i<row;i++)
                matrix[i][0]=0;
        }

    }
};
```

复杂度

+ 时间复杂度O(N^2)
+ 空间复杂度O(1)

## [498. 对角线遍历](https://leetcode-cn.com/problems/diagonal-traverse/)

> 给定一个含有 M x N 个元素的矩阵（M 行，N 列），请以对角线遍历的顺序返回这个矩阵中的所有元素，对角线遍历如下图所示。
>
> 示例:
>
> 输入:
> [
> [ 1, 2, 3 ],
> [ 4, 5, 6 ],
> [ 7, 8, 9 ]
> ]
>
> 输出:  [1,2,4,7,5,3,6,8,9]

方法：观察数组的特点

+ 一共进行row+col-1趟输出
+ 每趟的行列和等于定值
+ x和y右上，x减少，y增大；xy左下，x增大，y减少。

```C++
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        if(matrix.size()==0)
            return {};

        int row=matrix.size(),column=matrix[0].size();
        int count=row+column;
        vector<int> temp_vec;
        //进行count-1趟输出
        for(int i=0;i<count-1;)
        {
            //输出右上对角线
            int x1=i<row?i:row-1;
            int y1=i-x1;
            while(x1>=0&&y1<column)
            {
                temp_vec.push_back(matrix[x1][y1]);
                x1--;
                y1++;
            }
            i++;
            if(i>=count-1)
                break;
            //输出左下对角线
            y1=i<column?i:column-1;
            x1=i-y1;
            while(y1>=0&&x1<row)
            {
                temp_vec.push_back(matrix[x1][y1]);
                y1--;
                x1++;
            }
            i++;
        }
        return temp_vec;
    }
};
```

## [14. 最长公共前缀](https://leetcode-cn.com/problems/longest-common-prefix/)

> 编写一个函数来查找字符串数组中的最长公共前缀。
>
> 如果不存在公共前缀，返回空字符串 ""。
>
> 示例 1:
>
> 输入: ["flower","flow","flight"]
> 输出: "fl"
> 示例 2:
>
> 输入: ["dog","racecar","car"]
> 输出: ""
> 解释: 输入不存在公共前缀。

### 方法一：横向扫描:迭代法

依次遍历字符串，求两两字符串之间的公共前缀，

LCP（s1,s2,s3,...sn)=LCP(LCP(LCP(LCP(s1,s2),s3),s4),,,sn)

**复杂度：**

+ 时间复杂度：O(mn)
+ 空间复杂度：O(1)

```C++
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()==0)
            return "";
        string comPrefix=strs[0];
        for(int i=1;i<strs.size();i++)
        {
            comPrefix=longestCommonPrefix(comPrefix,strs[i]);
            //公共前缀为空时，直接跳出判断
            if(comprefix.size()==0)
                break;
        }
        return comPrefix;

    }
   
    //寻找两个字符串的最大公共前缀
    string longestCommonPrefix(string& strs1,string& strs2)
    {
        if(strs1.size()==0||strs2.size()==0)
            return "";
        int min_size=min(strs1.size(),strs2.size());
        int i=0;
        for(;i<min_size;i++)
        {
            if(strs1[i]!=strs2[i])
                break;
        }
        return strs1.substr(0,i);
    }
};
```



### 方法二：纵向扫描

依次比较所有字符串上每个位置的字符，

从前往后遍历所有字符串的每一列，比较相同列上的字符是否相同，如果相同则继续对下一列进行比较，如果不相同则当前列不再属于公共前缀，当前列之前的部分为最长公共前缀。

```C++
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()==0)
            return "";
        vector<int> str_size;
        int temp_size;
        
        int min_size=strs[0].size();
        int i=0;
        //单个字符逐个比较
        for(;i<min_size;i++)
        {
            int temp_char=strs[0][i];
            int j=0;
            for(;j<strs.size();j++)
            {
                if(strs[j][i]!=temp_char)
                    break;
            }
            if(j!=strs.size())
                break;
        }
        if(i==0)
            return "";
        return strs[0].substr(0,i);

    }
};
```

**复杂度**

+ 时间复杂度：O(mn)
+ 空间复杂度：O(1)

### 分治法

+ LCP问题的求解满足结合律：LCP(s1,s2,s3,...,sn)=LCP(LCP(s1,s2,s3..sk),LCP(sk+1,sk+2,,,,sn))
+ 将大问题分为若干子问题LCP(s1,sn)分解为LCP（s1,smid)和LCP(smid+1.sn)

```C++
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()==0)
            return "";
       
        return longestCommonPrefix(strs,0,strs.size()-1);
    }

    string longestCommonPrefix(vector<string>&strs ,int low,int high)
    {
        if(low==high)
            return strs[low];
        else
        {
            int mid=low+(high-low)/2;
            string s1=longestCommonPrefix(strs,low,mid);
            string s2=longestCommonPrefix(strs,mid+1,high);
            return longestCommonPrefix(s1,s2);
        }
    }

    //寻找两个字符串的最大公共前缀
    string longestCommonPrefix(string& strs1,string& strs2)
    {
        if(strs1.size()==0||strs2.size()==0)
            return "";
        int min_size=min(strs1.size(),strs2.size());
        int i=0;
        for(;i<min_size;i++)
        {
            if(strs1[i]!=strs2[i])
                break;
        }
        return strs1.substr(0,i);
    }
};
```

## [151. 翻转字符串里的单词](https://leetcode-cn.com/problems/reverse-words-in-a-string/)

> 给定一个字符串，逐个翻转字符串中的每个单词。
>
> 说明：
>
> 无空格字符构成一个 单词 。
> 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
> 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
>
>
> 示例 1：
>
> 输入："the sky is blue"
> 输出："blue is sky the"

### 方法一、利用字符流处理字符分割问题

+ 单词分割
+ 逆序拼接

==stringstream流可以自动将字符串中的单词分割==

```C++
class Solution {
public:
    string reverseWords(string s) {
        string str,ans;
        stringstream ss(s);
        vector<string> str_vec;
        while(ss>>str)
            str_vec.push_back(str+" ");
        for(int i=str_vec.size()-1;i>=0;i--)
            ans+=str_vec[i];
        return ans.size()?string(ans.begin(),ans.end()-1):"";
    }
};
```

+ 时间复杂度：O(N)

+ 空间复杂度：O(N)

### 方法二、列表存储，逆序输出

+ 单词分割
+ 逆序输出

```C++
class Solution {
public:
    string reverseWords(string s) {
        //字符串切割，删除空节点
        int length=s.size();
        vector<string> str_vec;
        for(int i=0;i<length;)
        {
            string temp="";
            while(i<length&&s[i]==' ')
                i++;
            if(i>=length)
                break;
            while(i<length&&s[i]!=' ')
            {
                temp+=s[i];
                i++;
            }
            if(temp.size()!=0)
                str_vec.push_back(temp);
        }
        
        //字符串逆序拼接
        string temp="";
        for(int i=str_vec.size()-1;i>=0;i--)
        {
            temp+=str_vec[i];
            if(i!=0)
                temp+=" ";
        }
        return temp;
    }
};
```

### 方法三：原地翻转

+ 整体翻转
+ 逐个单词翻转
+ 处理首尾空格，和中间的空格

```C++
class Solution {
public:
    string reverseWords(string s) {
        //整体逆序
        reverse(s.begin(),s.end());
        int start=0,end=s.size()-1;

        //删除首尾的空格
        while(start<=end&&s[start]==' ')
            start++;
        while(end>=0&&s[end]==' ')
            end--;
        if(start>end)
            return "";
        
        //单词逆序
        for(int l=start;l<=end;)
        {
            while(l<=end&&s[l]==' ')
                l++;
            int r=l;
            while(r<=end&&s[r]!=' ')
                r++;
            reverse(s.begin()+l,s.begin()+r);
            l=r;
        }
        //处理内部单词空格
        int tail=start;
        for(int i=start;i<=end;i++)
        {
            if(s[i]==' '&&s[i-1]==' ')
                continue;
            s[tail++]=s[i];
        }
        return s.substr(start,tail-start);
    }
};
```

+ 时间复杂度O(n)
+ 空间复杂度O(1)

## [344. 反转字符串](https://leetcode-cn.com/problems/reverse-string/)

方法：首尾双指针

交换元素方式：

+ 使用临时变量
+ 使用reverse
+ 使用异或

```C++
class Solution {
public:
    void reverseString(vector<char>& s) {
        for(int i=0,j=s.size()-1;i<j;i++,j--)
        {
            char temp;
            temp=s[i];
            s[i]=s[j];
            s[j]=temp;
            // （1）swap(s[i],s[j]); 使用函数进行交换
            //（2）使用异或进行原地交换
            // s[i]=s[i]^s[j];
            // s[j]=s[i]^s[j];
            // s[i]=s[i]^s[j];
        }
    }
};
```

## [561. 数组拆分 I](https://leetcode-cn.com/problems/array-partition-i/)

> 输入：nums = [1,4,3,2]
> 输出：4
> 解释：所有可能的分法（忽略元素顺序）为：
>
> 1. (1, 4), (2, 3) -> min(1, 4) + min(2, 3) = 1 + 2 = 3
> 2. (1, 3), (2, 4) -> min(1, 3) + min(2, 4) = 1 + 2 = 3
> 3. (1, 2), (3, 4) -> min(1, 2) + min(3, 4) = 1 + 3 = 4
>    所以最大总和为 4

方法：先排序：然后取奇数元素和

```C++
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int ans=0;
        for(int i=0;i<nums.size();i+=2)
        {
            ans+=nums[i];
        }
        return ans;
    }
};
```

## [167. 两数之和 II - 输入有序数组](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/)

> 输入: numbers = [2, 7, 11, 15], target = 9
> 输出: [1,2]
> 解释: 2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 。

### 方法一：暴力求解

两重循环：

+ 外循环遍历第一个值，同时得到新的target
+ 内循环，从i右边开始寻找新的target；

```C++
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        for(int i=0;i<numbers.size();i++)
        {
            int new_target=target-numbers[i];
            for(int j=i+1;j<numbers.size();j++)
            {
                if(new_target==numbers[j])
                    return {i+1,j+1};
            }
        }
        return {-1,-1};

    }
};
```

时间复杂度O(n^2)

空间复杂度O(1)

### 方法二：哈希表

背景：空间换时间

方法一中，寻找newtarget需要大量时间，使用哈希表将时间复杂度有O(n)降低为O(1)

+ 对数组元素进行遍历

  > 在哈希表中寻找newtarget，找到返回，没找到添加。

```C++
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        unordered_map<int,int> hash_table;
        for(int i=0;i<numbers.size();i++)
        {
            int new_target=target-numbers[i];
            auto it=hash_table.find(new_target);
            if(it!=hash_table.end())
                return {it->second,i+1};
           	//将元素添加到哈希表中
            hash_table[numbers[i]]=i+1;   
        }
        return {-1,-1};

    }
};
```

+ 时间复杂度：O(N)
+ 空间复杂度：O(N)

### 方法三：二分法

背景：考虑到数组有序，使用二分法查找。

```C++
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        for(int i=0;i<numbers.size();i++)
        {
            int new_target=target-numbers[i];
            int low=i+1,high=numbers.size()-1;
            while(low<=high)
            {
                int mid=(high - low) / 2 + low;
                if(numbers[mid]==new_target)
                {
                    return {i+1,mid+1};
                }   
                else if(numbers[mid]>new_target)
                {
                    high=mid-1;
                }  
                else
                    low=mid+1;
            }
        }
        return {-1,-1};

    }
};
```

时间复杂度：O(nlogn)

空间复杂度：O(1)

### 方法四：首尾双指针，不断逼近。

```C++
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int low=0,high=numbers.size()-1;
        while(low<high)
        {
            int sum=numbers[low]+numbers[high];
            if(sum==target)
                return {low+1,high+1};
            else if(sum>target)
                high--;
            else
                low++;
        }
        return {-1,-1};
    }
};
```

+ 时间复杂度：O(N)
+ 空间复杂度O(1)

## [27. 移除元素](https://leetcode-cn.com/problems/remove-element/)

> 给你一个数组 *nums* 和一个值 *val*，你需要 **[原地](https://baike.baidu.com/item/原地算法)** 移除所有数值等于 *val* 的元素，并返回移除后数组的新长度
>
> 给定 nums = [3,2,2,3], val = 3,
>
> 函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。
>
> ==元素的顺序可以改变，你不需要考虑数组中超出新长度后面的元素==。

### 方法：快慢双指针：复制元素

+ 快指针寻找元素，慢指针指向已经遍历好的元素
+ 将快指针不等于目标值的元素复制到慢指针。

```C++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int first=0,second=0;
        for(;second<nums.size();second++)
        {
            if(nums[second]!=val)
                nums[first++]=nums[second];
                
        }
        return first;
    }
};
```

### 方法：首尾双指针，复制最后一个元素

方法一需要大量的元素交换：

因为元素的顺序可以改变，因此首尾双指针减少交换。

+ 使用首尾双指针将目标值相等的元素，最后一个元素交换。

```C++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int head=0,rear=nums.size()-1;
        while(head<=rear)
        {
            if(nums[head]==val)
            {
                nums[head]=nums[rear];
                rear--;
            }
            else
            {
                head++;
            }
        }
        return head;
    }
};
```

时间复杂度：O(n)

空间复杂度：O(1)

## [485. 最大连续1的个数](https://leetcode-cn.com/problems/max-consecutive-ones/)

> 给定一个二进制数组， 计算其中最大连续1的个数。
>
> 示例 1:
>
> 输入: [1,1,0,1,1,1]
> 输出: 3
> 解释: 开头的两位和最后的三位都是连续1，所以最大连续1的个数是 3.

### 方法一：快慢双指针，使用快慢双指针夹住所有的1；

```C++
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int fast=0,slow=0;
        int length=0;
        for(;fast<nums.size();)
        {
            if(nums[fast]==0)
            {
                length=max(length,fast-slow);
                fast++;
                slow=fast;
            }
            else
            {
                fast++;
            }
        }
        length=max(length,fast-slow);
        return length;
    }
};
```

时间复杂度：O(n)

空间复杂度：O(1)

### 方法二：单指针遍历，count计数

```C++
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int count=0,maxcount=0;
        for(int i=0;i<nums.size();i++)
        {
            if(nums[i]==0)
            {
                maxcount=max(maxcount,count);
                count=0;
            }    
            else
                count++;
        }
        maxcount=max(maxcount,count);
        return maxcount;
    }
};
```

时间复杂度：O(n)

空间复杂度O(1)；

## [209. 长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/)

> 给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。
>
> 
>
> 示例：
>
> 输入：s = 7, nums = [2,3,1,2,4,3]
> 输出：2
> 解释：子数组 [4,3] 是该条件下的长度最小的子数组。

方法一：快慢双指针

+ 快指针探寻元素，慢指针寻找满足条件的最小区间。for，while实现。

```C++
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int slow=0,fast=0;
        int count=INT_MAX,sum=0;
        for(;fast<nums.size();fast++)
        {
            sum+=nums[fast];
            while(sum>=s)
            {
                count=min(count,fast-slow+1);
                sum-=nums[slow];
                slow++;
                
            }
        }
        return count==INT_MAX?0:count;
    }

};
```

方法二：滑动窗口

+ 使用双指针维持一个滑动窗口

```C++
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int slow=0,fast=0;
        int count=INT_MAX,sum=0;
        for(;sum>=s||fast<nums.size();)
        {
            if(sum<s)
            {
                sum+=nums[fast];
                fast++;
            }
            else
            {
                count=min(count,fast-slow);
                sum-=nums[slow];
                slow++;
            }
        }
        return count == INT_MAX ? 0 : count;
    }

};
```

### 方法三：前缀和+二分查找

+ 使用一个sum数组存储前i个元素的和sum[i]表示从num[0]+到nums[i-1]；得到前缀和。
+ 遍历nums中的每一个元素，找到从num[i]开始到nums结尾中第一个大于target的值（二分查找）

使用二分查找的理由：sum数组是前缀和，递增，可用二分查找

```C++
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n=nums.size();
        if(n==0)
            return 0;
        vector<int> sum(n+1,0);
        for(int i=1;i<=n;i++)
        {
            sum[i]=sum[i-1]+nums[i-1];
        }
        int ans=INT_MAX;
        for(int i=1;i<=n;i++)
        {
            int target=s+sum[i-1];
            auto bound=lower_bound(sum.begin(),sum.end(),target);//使用二分查找，找到第一个大于该元素的下标
            if(bound!=sum.end())//没找到，不用更新
                ans=min(ans,int(bound-sum.begin())-i+1);
        }
        return ans==INT_MAX?0:ans;
    }
};
```

+ 时间复杂度：O(logn)
+ 空间复杂度：O(n)

## [118. 杨辉三角](https://leetcode-cn.com/problems/pascals-triangle/)

解法一：遍历

```C++
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        if(numRows==0)
            return ans;
        for(int i=0;i<numRows;i++)
        {   vector<int> ans_row;
            for(int j=0;j<=i;j++)
            {
                if(j==0||j==i)
                    ans_row.push_back(1);
                else
                    ans_row.push_back(ans[i-1][j-1]+ans[i-1][j]);
            }
            ans.push_back(ans_row);   
        }
        return ans;
    }
};
```

解法二：动态规划

## [119. 杨辉三角 II](https://leetcode-cn.com/problems/pascals-triangle-ii/)

参考：https://leetcode-cn.com/problems/pascals-triangle-ii/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--28/

+ 杨辉三角由组合数组成，求每一行的所有组合数。
+ 利用组合数的递推公式。

```C++
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if(rowIndex<0)
            return {};
        vector<int> ans;
        ans.push_back(1);
        long pre=1;
        for(int i=1;i<=rowIndex;i++)
        {
            long cur=pre*(rowIndex-i+1)/i;
            ans.push_back(cur);
            pre=cur;
        }
        return ans;
    }
};
```

## [153. 寻找旋转排序数组中的最小值](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/)

> 假设按照升序排序的数组在预先未知的某个点上进行了旋转。例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] 。
>
> 请找出其中最小的元素。
>
> 示例 1：
>
> 输入：nums = [3,4,5,1,2]
> 输出：1

解法一：暴力

遍历元素直接求解

解法二：二分法

旋转排序算法的二分法求解。

```C++
class Solution {
public:
    int findMin(vector<int>& nums) {
        if(nums.size()==0)
            return -1;
        int left=0,right=nums.size()-1;
        if(nums[left]<nums[right])
            return nums[0];
        int mid;
        while(left<=right)
        {
            mid=(left+right)/2;
            if(nums[mid]>=nums[right])
                left=mid+1;
            else
                right=mid;
        }
        return nums[right];
    }
};
```

## [283. 移动零](https://leetcode-cn.com/problems/move-zeroes/)

给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:

输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
说明:

必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。

方法：快慢双指针

```C++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slow=0,fast=0;
        for(;fast<nums.size();)
        {
            if(nums[fast]!=0)
                nums[slow++]=nums[fast++];
            else
                fast++;
        }
        for(;slow<nums.size();slow++)
            nums[slow]=0;
    }
};
```

## [53. 最大子序和](https://leetcode-cn.com/problems/maximum-subarray/)

> 给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
>
> 示例:
>
> 输入: [-2,1,-3,4,-1,2,1,-5,4]
> 输出: 6
> 解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。

### 方法一：暴力法，双指针

```C++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.size()==0)
            return 0;
        int ans=nums[0];
        for(int i=0;i<nums.size();i++)
        {   
            int sum=0;
            for(int j=i;j<nums.size();j++)
            {
                sum+=nums[j];
                ans=max(sum,ans);
            }
        }
        return ans;
    }
};
```

### 方法二：分治法

思想：类似归并排序，先归递归，后合并。

连续子序列的最大和主要由这三部分子区间里元素的最大和得到：

+ 第 1 部分：子区间 [left, mid]；
+ 第 2 部分：子区间 [mid + 1, right]；
+ 第 3 部分：包含子区间[mid , mid + 1]的子区间，即 nums[mid] 与nums[mid + 1]一定会被选取。

[![53最大子序和](D:/all_document/document/document/note/c++/CPP_train_code/LeetCode/算法知识整理/{figure}/53最大子序和.png)]()

```C++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        return maxSubArray_cur(nums,0,nums.size()-1);
    }
    int maxSubArray_cur(vector<int> nums,int left,int right)
    {
        if(left==right)
            return nums[left];

        int mid=(left+right)/2;

        int left_sum=maxSubArray_cur(nums,left,mid);
        int right_sum=maxSubArray_cur(nums,mid+1,right);
        int merge_sum=merge_max_sub_array(nums,left,mid,right);
        return max(max(left_sum,right_sum),merge_sum);
    }
	//寻找包含mid和mid+1子序列的最大值
    int merge_max_sub_array(vector<int>nums,int left,int mid,int right)
    {
        int left_sum=0,left_max=nums[mid];//初值必须包含mid
        for(int i=mid;i>=left;i--)
        {
            left_sum+=nums[i];
            left_max=max(left_max,left_sum);
        }
        int right_sum=0,right_max=nums[mid+1];//初值必须设置为mid+1
        for(int i=mid+1;i<=right;i++)
        {
            right_sum+=nums[i];
            right_max=max(right_max,right_sum);
        }
        return left_max+right_max;
    }
};
```

注意：初值不能随便设置。

### 方法三：动态规划

dp定义：dp[i]表示以i结尾的最大子序和，（必须包含i）

转移：

+ 只有一个元素，就是i
+ 由前一个元素新的子序和加上

状态转移方程：

![image-20201127095808794](D:/all_document/document/document/note/c++/CPP_train_code/LeetCode/算法知识整理/{figure}/image-20201127095808794.png)

最终只要求dp[i]中的最大值即可。

```C++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.size()==0)
            return 0;
        if(nums.size()==1)
            return nums[0];
        int pre=0;
        int ans=nums[0];
        for(const auto &num:nums)
        {
            pre=max(num,num+pre);
            ans=max(pre,ans);
        }
        return ans;
    }
};
```



