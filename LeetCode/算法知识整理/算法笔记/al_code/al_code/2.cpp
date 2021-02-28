#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<stdio.h>

using namespace std;

int min_example(int a, int b)
{
	if (a < b)
		return a;
	return b;
}
bool flag = true;
int exit_example(int N, int A,int cur,int B, vector<int> &ai,int count)
{
	if (flag != true)
	{
		return -1;
	}
	if (count >= 200)
		return -1;
	if (cur< 1 || cur> N)
		return 0;
	if (cur == B)
	{
		return 0;
	}
	
	if (cur+ai[cur-1]<=N && cur - ai[cur-1] >= 1)
	{
		return min_example(exit_example(N, A, cur + ai[cur-1], B, ai,count+1)+ 1, exit_example(N, A, cur - ai[cur-1], B, ai,count+1) + 1);
	}
	else if (cur - ai[cur-1] >= 1)
	{
		return exit_example(N, A, cur - ai[cur-1], B, ai,count+1) + 1;
	}
	else if(cur+ai[cur-1]<=N)
	{
		return exit_example(N, A, cur+ai[cur-1], B, ai,count+1) + 1;
	}
	else
	{
		flag = false;
	}
}
//
//int main()
//{
//	int N,A,B;
//	vector<int> ai;
//	while (cin >> N >> A >> B)
//	{
//		ai.clear();
//		for (int i = 0; i < N; i++)
//		{
//			int temp;
//			cin >> temp;
//			ai.push_back(temp);
//		}
//		int count = exit_example(N, A, A, B, ai, 0);
//		if(count<199)
//			cout <<count<<endl;
//		else
//		{
//			cout << -1<<endl;
//		}
//	
//	}
//	
//	system("pause");
//	return 0;
//
//}