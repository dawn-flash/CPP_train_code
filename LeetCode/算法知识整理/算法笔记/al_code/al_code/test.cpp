#define _CRT_SECURE_NO_DEPRECATE
//scanf���ᱨ��
#include<iostream>
using namespace std;
void test1()
{//����longlong �Ƿ�>10^10��Ҫ��ll�� 
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
	//�ַ�����ĳ���
	//strlenΪ��Ч���ȣ�������/0 ��/0Ϊ��β���ַ����ĳ���
	//sizeofΪ��ʵ���ȣ�����/0 ������������䳤��
	char str[] = "aaa";

	cout << "strlen(str)" << strlen(str) << endl;
	cout << "sizeof(str)" << sizeof(str) / sizeof(str[0]) << endl;

}
void test4()
{
	//sscanf(str,"%d",&n)��str��d��ʽ�����n��
	//sprintf(str,"d",&n) ��n��d��ʽ�����str��
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
	//�������
	//(1)EOF
	/*int m;
	while (scanf("%d",&m)!=EOF)
	{
		printf("%d\n", m);
	}*/

	//��2���ַ��������룬֧�ֶ�������
	char str[100];
	while (scanf("%s",str)!=EOF)
	{
		cout << "aaaa" << endl;
		printf("%s\n", str);
	}

	//һ�ο���ֱ������һ���ַ�������������
	/*while (scanf("%[^\n]",str))
	{
		printf("%s\n", str);
	}*/
	
	//һ�ο��Զ��������ַ���,֧�ֶ������룬
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