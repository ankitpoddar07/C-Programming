#include<iostream>
using namespace std;

int main()
{
	int age;
	cout<<"Enter Your age:";
	cin>> age;
	
	if(age>=18)
	goto Vote;
	
	else
	goto notVote;
	
	Vote:
		cout<<"Eligible for vote...!";
		return 0;
		
	notVote:
		cout<<"Not Eligible for vote...!";
		return 0;
	    	
}
