/*
 * @Author: xt 
 * @Date: 2020-11-16 16:07:42 
 * @Last Modified by: xt
 * @Last Modified time: 2020-11-23 14:32:39
 */

//KMPw问题的求解，从朴素的字符串匹配到KMP算法到改进的KMP算法

#include<iostream>
using namespace std;

#include<string>


//朴素的字符串匹配算法
int BF(char S[],char T[])
{
    int i=0;
    int j=0;
    while(S[i]!='\0'&&T[j]!='\0')
    {
        if(S[i]==T[j])
        {
            j++;
            i++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }  
    }
    if(T[j]=='\0')
        return i-j;
    return -1;   
}
//KMP算法详解
void GetNext(char T[],int next[])
{
    int j=0,k=-1;
    next[j]=k;
    while(T[j]!='\0')
    {
        if(k==-1||T[j]==T[k])
        {
            k++;
            j++;
            next[j]=k;
        }
        else
        {
            k=next[k];
        }  
    }
}

int KMP(int start,char S[],char T[])
{
    int i=start;
    int j=0;
    int len=sizeof(T)/sizeof(char);
    int next[len];
    GetNext(T,next);
    while(S[i]!='\0'&&T[j]!='\0')
    {
        //匹配成功，或者当前i无法匹配
        if((j==-1)||(S[i]==T[j]))
        {
            i++;
            j++;
        }
        else//继续寻找公共前后缀
        {
            j=next[j];
        } 
    }
    if(T[j]=='\0')
        return (i-j);
    else
        return -1;
}

void test1()
{
    char S[]="abcdadbc";
    char T[]="dadbc";

    // cout<<"匹配的初始位置"<<BF(S,T);
    cout<<"匹配的初始位置"<<KMP(0,S,T);

}
#include<vector>
#include<set>
#include<algorithm>
#include<string>
void getnext(string s,int next[])
{
    int j=0,k=-1;
    next[0]=-1;
    int length=s.size();
    while(j<length)
    {
        if(k==-1||s[j]==s[k])
        {
            j++;
            k++;
            next[j]=k;
        }
        else
        {
            k=next[k];
        }
    }
}
int strStr(string haystack, string needle) 
{
    if(haystack.size()==0&&needle.size()==0)
        return 0;
    int i=0,j=0;
    int next[needle.size()];
    getnext(needle,next);
    while((j==-1)||(haystack[i]!='\0'&&needle[j]!='\0'))
    {
        if(j==-1||haystack[i]==needle[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];
        }
    }
    if(needle[j]=='\0')
        return i-j;
    return -1;
        
    }

void test()
{
    string s="hello";
    string s2="ll";
    int i=strStr(s,s2);
    cout<<i<<endl;
    
}
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
string longestPalindrome(string s) {
        if(s.size()<=0)
            return {};
        int bp[s.size()][s.size()];
        int ans[2];
        for(int i=0;i<s.size();i++)
        {
            for(int j=0;j<s.size();j++)
            {
                if(j==i)
                    bp[i][j]=1;
                else if(j==i+1&&s[i]==s[j])
                    bp[i][j]=1;
                else
                    bp[i][j]=0;
                if(bp[i]==bp[j])
                {
                    ans[0]=i;
                    ans[1]=j;
                }
            }
        }
        
        for(int l=3;l<=s.size();l++)
        {
            for(int i=0;i<=s.size()-l;i++)
            {
                int j=i+l-1;
                if(s[i]==s[j])
                    bp[i][j]=bp[i+1][j-1];
                else
                    bp[i][j]=0;
                if(bp[i][j]==1)
                {
                    ans[0]=i;
                    ans[1]=j;
                }
            }
        }
        return s.substr(ans[0],ans[1]-ans[0]+1);
    }

bool canJump(vector<int>& nums) {
        if(nums.size()==0)
            return false;
        int max_length=0;
        vector<int> dp(nums.size(),0);
        dp[0]=1;
        for(int i=1;i<nums.size();i++)
        {
            for(int j=i-1;j>=0;j++)
                if(dp[j]==1&&j+nums[j]>=i)
                {
                    dp[i]=1;
                    break;
                }
        }
        // if(dp[nums.size()-1])
        //     return true;
        // else
        //     return false;
        return false;
}
int main()
{
    // test1();
    // test();
    // char c[]={'1','2'};
    // if(c[-1]=='\0')
    //     cout<<"孔"<<endl;
    // cout<<c[-1]<<endl;
    // cout<<"chenx"<<endl;
    // string s="12";
    // vector<int> nums={2,3,1,2,4,3};
    // cout<<minSubArrayLen(7,nums);
    // string s="cbbd";
    // longestPalindrome(s);
    vector<int> nums={3,2,1,0,4};
    canJump(nums);

    

}