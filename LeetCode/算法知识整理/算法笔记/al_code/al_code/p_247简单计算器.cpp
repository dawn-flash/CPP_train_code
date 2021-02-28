#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<map>
using namespace std;

struct node
{
	double num;
	char op;
	bool flag;
};

string str;
stack<node> s;
queue<node> q;
map<char, int> op;

//中缀表达式转换为后缀表达式
void change()
{
	double num;
	node temp;
	for (int i = 0; i < str.length();)
	{
		//如果str[i]是数字
		if (str[i] >= '0'&&str[i] <= '9')
		{
			temp.flag = true;
			temp.num = str[i] - '0';
			i++;

			//如果当前数字大于10
			while (i < str.length() && str[i] >= '0'&&str[i] <= '9')
			{
				temp.num = temp.num * 10 + (str[i] - '0');
				i++;
			}
			q.push(temp);
		}
		else 
		{//如果是操作符
			temp.flag = false;
			//只要操作符栈顶的优先级高于str操作符的优先级，
			//将操作符栈顶的元素弹出到后缀表达式队列中
			while (!s.empty() && op[str[i]] <= op[s.top().op])
			{
				q.push(s.top());
				s.pop();
			}
			temp.op = str[i];
			s.push(temp);
			i++;
		}	
	}
	//遍历结束后栈非空的话直接将所有元素直接导入队列
	while (!s.empty())
	{
		q.push(s.top());
		s.pop();
	}
}

//计算后缀表达式
double cal() {
	double temp1, temp2; //存储临时的变量
	node cur, temp;   //遍历当前结点，临时结点(存储结果)
	while (!q.empty())
	{
		//队列中取出操作数
		cur = q.front();
		q.pop();

		if (cur.flag == true)
		{//如果cur是操作数
			s.push(cur);
		}
		else
		{//如果cur是操作符
			temp2 = s.top().num;
			s.pop();
			temp1 = s.top().num;
			s.pop();
			temp.flag = true;
			if (cur.op == '+') temp.num = temp1 + temp2;
			else if (cur.op == '-') temp.num = temp1 - temp2;
			else if (cur.op == '*') temp.num = temp1 * temp2;
			else temp.num = temp1 / temp2;
			s.push(temp);
		}
	}
	return s.top().num;//栈顶元素就是后缀表达式的值
}

//int main()
//{
//	/*op['+'] = op['-'] = 1;
//	op['*'] = op['/'] = 2;
//	while (getline(cin,str),str !="0")
//	{
//		cout << str << endl;
//		for (string::iterator it = str.begin(); it != str.end(); )
//		{
//			if (*it == ' ') 
//				str.erase(it);
//			else
//				it++;
//		}
//		
//		while (!s.empty())s.pop();
//		change();
//		cout << "结果" << cal();
//	}
//	return 0;*/
//
//	system("pause");
//}