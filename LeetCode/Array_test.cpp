/*
 * @Author: xt 
 * @Date: 2020-11-12 09:23:58 
 * @Last Modified by: xt
 * @Last Modified time: 2020-11-12 16:23:06
 */

//leetcode的数组和链表练习

#include<iostream>
using namespace std;
#include<vector>

//二分查找
int search(vector<int>& nums,int target)
{
    int low=0;
    int high=nums.size();
    int mid=0;
    while(low<high)
    {
        mid=low+(high-low)>>2;
        if(nums[mid]==target)
            return mid;
        else if (nums[mid]<target)
            low=mid+1;
        else
            high=mid;
    }
    return -1;
}
//35搜索插入的位置
int searchInsert(vector<int> &nums,int target)
{
    int front=0;
    int rear=nums.size()-1;
    while(front<=rear)
    {
        // int mid=(front+rear)/2;
        int mid=((rear-front)>>1)+front;
        if(target<nums[mid])
            rear=mid-1;
        else if(target>nums[mid])
            front=mid+1;
        else
            return mid;
          
    }
    return front;
}
void test1()
{
    vector<int> nums={1,3,5};
    int target[4]={5,2,7,0};
    for(int i=0;i<nums.size();i++)
    {
        cout<<nums[i]<<" ";
    }
    for(int i=0;i<4;i++)
    {
        cout<<"目标值"<<target[i]<<endl;
        cout<<"插入位置:"<<searchInsert(nums,target[i])<<endl;
    }
    

}

int main()
{
    test1();
}
