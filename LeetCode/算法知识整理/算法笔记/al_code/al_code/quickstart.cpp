#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<cmath>

using namespace std;
#define eps 1e-6

//例题3-5 一元二次方程的根
void solveEqulation()
{
	double a, b, c;
	scanf("%lf:%lf:%lf", &a, &b, &c);
	if (a <= 0)
	{
		cout << "a<0" << endl;
		return;
	}
	double deta = b * b - 4 * a*c;
	if ((deta) < 0)
	{
		cout << "data小于0" << endl;
		return;
	}
	double r1, r2;
	r1 = (-1 * b + sqrt(deta))/(2*a);
	r2 = (-1 * b - sqrt(deta)) / (2 * a);
	printf("r1=%7.2f r2=%7.2f\n", r1, r2);
}

//例题3-9字符输入输出
void output_string()
{
	char str[100];
	scanf("%s", str);
	printf("%s", str);
}


void calPI()
{
	double PI=0;
	double temp=1;
	for (int i = 1; fabs(temp) >= eps; i++)
	{
		temp = pow(-1, i + 1)*(1.0 / (2.0*i - 1));
		PI += temp;
	}
	printf("%10.8f\n", 4.0*PI);
}
int main()
{
	//calPI();
	//solveEqulation();
	output_string();
	system("pause");
	return 0;
}