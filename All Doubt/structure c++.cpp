#include<iostream>
using namespace std;

struct stu
{
	int roll;
	char name[10];
	float marks;
}; 
int main ()
{
	struct stu s;
	cout<<"Enter student roll number :";
	cin>>s.roll;
	cout<<"Enter student name :";
	cin>>s.name;
	cout<<"Enter student marks :";
	cin>>s.marks;
	
	cout<<s.roll<<ends<<s.name<<ends<<s.marks;
	return 0;
	
}

