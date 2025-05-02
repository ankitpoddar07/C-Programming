#include<stdio.h>
#include<conio.h>

void main()
{
	int marks;
	printf("Enter marks..!\n");
	scanf("%d",&marks);
	
	if (marks==100)
	{
		printf("Genius");
	}
	else if(marks >=80 &&  marks<100)
	{
		printf("Topper");
	}
	else if(marks>=60 && marks<=79)
	{
		printf("Bokachoda");
	}
	else
	{
		printf("Average Student");
	}
	
	
	
	
	
	
	
	
	
	
	
}
