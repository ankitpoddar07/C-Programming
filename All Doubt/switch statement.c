#include<stdio.h>
#include<conio.h>

void main()
{
	int a,b,c;
	int choice;
	printf("Enter two numbers");
	scanf("%d%d", &a, &b);
	
	printf("Enter choice");
	scanf("%d", & choice);
	
	switch(choice)
	{
		case 1: c= a+b;
		        printf("%d",c);
		break;
	    case 2: c= a-b;
		        printf("%d",c);
		break;        
		case 3: c= a*b;
		        printf("%d",c);
		break;        
		case 4: c= a/b;
		        printf("%d",c);
		break; 
		default : ("Invalid choice");               
	}
}
