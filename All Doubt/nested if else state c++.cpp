#include<iostream>
using namespace std;
int main()
{
	int a=10,b=20,c=30;
	if(a>b)
	{
		if(a>c)
		{
			cout<<"a="<<a;
		}
		else
		{
			cout<<"c="<<c;
		}
	}
	else
	{
		if (b>c)
		{
			cout<<"b="<<b;
		}
		else
		{
			cout<<"c="<<c;
	}
	}
}
