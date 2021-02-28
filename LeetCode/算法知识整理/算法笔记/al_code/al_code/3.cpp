#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<stdio.h>
#include<sstream>

using namespace std;

void change(string s)
{
	vector<string> vs;
	string result;
	stringstream input(s);
	while (input >> result)
		vs.push_back(result);
	string changeresult;
	for (int i = 0; i < vs.size(); i++)
	{
		if(vs[i][0]<='z'&&vs[i][0]>='a')
			changeresult += vs[i][0]-32;
		else
		{
			changeresult += vs[i][0];
		}
	}
	cout << changeresult;
	
}
//
//int main()
//{
//	int N, A, B;
//	vector<string> ai;
//
//	ai.clear();
//	string s;
//	while (getline(cin, s))
//	{
//		change(s);
//	}
//	
//
//	//system("pause");
//	return 0;
//
//}