#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cmath>

using namespace std;


void parseText(string& text, vector <pair<string, int>>& elements)
{
	getline(cin, text);

	int n = text.length(), power;


	for (int i = 0, j; i < n; i++)
	{
		j = i;
		while (i != n && text[i] != ' ')
		{
			i++;
		}

		switch (text[i - 1])
		{
		case '(':
			power = 10;
			break;
		case ')':
			power = 100;
			break;
		case '+':
			power = 20;
			break;
		case'-':
			power = 20;
			break;
		case'*':
			power = 30;
			break;
		case'/':
			power = 30;
			break;
		case'^':
			power = 40;
			break;

		default:
			power = 0;
		}


		elements.push_back(make_pair(text.substr(j, i - j), power));
	}
}

void makeQueue(const vector <pair<string, int>>& elements, stack <pair<string, int>>& s, queue <string>& q)
{
	for (auto element : elements)
	{
		if (element.second == 0)
		{
			q.push(element.first);
			continue;
		}

		else if (s.empty())
		{
			s.push(element);
			continue;
		}


		if (element.first == ")")
		{
			while (s.top().first != "(")
			{
				q.push(s.top().first);
				s.pop();
			}
			s.pop();
		}
		else if (element.first == "(")
			s.push(element);

		else if (s.top().second >= element.second)
		{
			while (!s.empty() && s.top().second >= element.second)
			{
				q.push(s.top().first);
				s.pop();
			}
			s.push(element);
		}
		else
			s.push(element);
	}

	while (!s.empty())
	{
		q.push(s.top().first);
		s.pop();
	}
}

bool isNumber(string& text)
{
	return (text.size() > 1 || (48 <= text[0] && text[0] <= 57));
}

int convertToInteger(string& textNumber)
{
	int  n = textNumber.length() - 1, result = textNumber[n] - 48;

	if (n == 0)
		return result;

	for (int i = 1; i <= n; i++)
	{
		result += (textNumber[n - i] - 48) * (pow(10, i));
	}
	return result;
}

int performOperation(string& op, stack <int> &stk)
{
	int ans = 0;
	int b = stk.top();
	stk.pop();
	int a = stk.top();
	stk.pop();

	switch (op[0])
	{
	case '+':
		ans = a + b;
		break;
	case'-':
		ans = a - b;
		break;
	case'*':
		ans = a * b;
		break;
	case'/':
		ans = a / b;
		break;
	case'^':
		ans = pow(a, b);
		break;
	}

	return ans;
}

void evaluateExpression(queue <string> &q, stack<int> &stk)
{
	for (int i = q.size(); i > 0; i--)
	{
		if (isNumber(q.front()))
			stk.push(convertToInteger(q.front()));

		else
		{
			stk.push(performOperation(q.front(), stk));
		}

		q.pop();
	}
}

void printResult(stack <int> s)
{
	cout << s.top();
}

int main()
{
	string text;
	vector <pair<string, int>> elements;
	parseText(text, elements);
	stack <pair<string, int>> s;
	queue <string> q;

	makeQueue(elements, s, q);
	
	stack <int> stackNumber;
	evaluateExpression(q, stackNumber);
	printResult(stackNumber);
	return 0;
}

