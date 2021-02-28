#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<stdio.h>

using namespace std;

string weather(int k)
{
	if (k <= 30 && k >= 1)
		return "Good";
	else
		return "Sad";
}

//int main()
//{
//	int k;
//	while (scanf("%d", &k) != EOF)
//	{
//		cout << weather(k) << endl;
//	}
//	return 0;
//
//}