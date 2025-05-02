#include<stdio.h>

int main()
{
	int a[2][2] , i,j;
	printf("Enter Array Element");
	
	       for (i=0; i<2; i++)
	       {
	       	   for(j=0; j<2; j++)
	       	   {
	       	   	 scanf("%d ",&a[i][j]);
				  }
		   }
		   printf("Matrix Element\n");
		   
	       for (i=0; i<2; i++)
	       {
	       	   for(j=0; j<2; j++)
	       	   {
	       	   	 printf("%d ",&a[i][j]);
				  }
				  printf("\n");
		   }
		   return 0;
}

