#define _CRT_SECURE_NO_DEPRECATE
//scanf不会报错
#include<iostream>
using namespace std;
void test1()
{//测试longlong 是否>10^10需要加ll， 
	long long a = 1111111111111111111LL;
	cout << a << endl;
}
void test2()
{
	char str[10];
	scanf("%s", str);
	cout << str << endl;
	
}
void test3()
{
	//字符数组的长度
	//strlen为有效长度，不包含/0 以/0为结尾的字符串的长度
	//sizeof为真实长度，包含/0 计算编译器分配长度
	char str[] = "aaa";

	cout << "strlen(str)" << strlen(str) << endl;
	cout << "sizeof(str)" << sizeof(str) / sizeof(str[0]) << endl;

}
void test4()
{
	//sscanf(str,"%d",&n)将str以d格式输入大n中
	//sprintf(str,"d",&n) 将n以d格式输入大str中
	int n;
	char str[100]="123";
	sscanf(str, "%d", &n);
	printf("%s\n", str);
	n = 233;
	sprintf(str, "%d", n);
	printf("%s\n", str);
	double m = 233.4;
	sscanf(str, "%lf", &m);
	printf("%f\n", m);
	sprintf(str, "%f", m);
	printf("%s\n", str);
}
void test5()
{
	//输入输出
	//(1)EOF
	/*int m;
	while (scanf("%d",&m)!=EOF)
	{
		printf("%d\n", m);
	}*/

	//（2）字符串的输入，支持多行输入
	char str[100];
	while (scanf("%s",str)!=EOF)
	{
		cout << "aaaa" << endl;
		printf("%s\n", str);
	}

	//一次可以直接输入一行字符串，单行输入
	/*while (scanf("%[^\n]",str))
	{
		printf("%s\n", str);
	}*/
	
	//一次可以读入整行字符串,支持多行输入，
	/*while (gets_s(str)!=NULL)
	{
		printf("%s\n", str);
	}*/
	
	
}

//int main()
//{
//	//test1();
//	//test2();
//	//test3();
//	//test4();
//	test5();
//	system("pause");
//	return 0;
//}