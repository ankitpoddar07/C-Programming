#include<stdio.h>
#include<conio.h>

int a; //global variable
void main()
{
	int b;         //local variable
	static int c;  //static variable
	
	printf("%d\n",a);  //0
	printf("%d\n",b);  //garbage=0
	printf("%d\n",c);  //0
	
}
