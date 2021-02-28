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

//��׺���ʽת��Ϊ��׺���ʽ
void change()
{
	double num;
	node temp;
	for (int i = 0; i < str.length();)
	{
		//���str[i]������
		if (str[i] >= '0'&&str[i] <= '9')
		{
			temp.flag = true;
			temp.num = str[i] - '0';
			i++;

			//�����ǰ���ִ���10
			while (i < str.length() && str[i] >= '0'&&str[i] <= '9')
			{
				temp.num = temp.num * 10 + (str[i] - '0');
				i++;
			}
			q.push(temp);
		}
		else 
		{//����ǲ�����
			temp.flag = false;
			//ֻҪ������ջ�������ȼ�����str�����������ȼ���
			//��������ջ����Ԫ�ص�������׺���ʽ������
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
	//����������ջ�ǿյĻ�ֱ�ӽ�����Ԫ��ֱ�ӵ������
	while (!s.empty())
	{
		q.push(s.top());
		s.pop();
	}
}

//�����׺���ʽ
double cal() {
	double temp1, temp2; //�洢��ʱ�ı���
	node cur, temp;   //������ǰ��㣬��ʱ���(�洢���)
	while (!q.empty())
	{
		//������ȡ��������
		cur = q.front();
		q.pop();

		if (cur.flag == true)
		{//���cur�ǲ�����
			s.push(cur);
		}
		else
		{//���cur�ǲ�����
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
	return s.top().num;//ջ��Ԫ�ؾ��Ǻ�׺���ʽ��ֵ
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
//		cout << "���" << cal();
//	}
//	return 0;*/
//
//	system("pause");
//}