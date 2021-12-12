/**
 * File Name: magic.c
 * Program get from a file/User input integers to be inserted to a table 
 * and to check wether the table is magic square according to conditions.
 * @author Avner Azoulay
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100
#define ZERO 0
#define ONE 1
#define TWO 2
#define N 3 /* N will be used to define the dimensions of magic table*/
#define NEED N*N /*N^2 Will helpus through the program for ranges*/
#define REF '0' /*Char 0 will be used as a reference number to convert chars to integers*/
#define MINUS '-' /*Will help for convert negative input*/
#define TEN 10 /*Used for integers with more than one digit*/
int magic[N][N]; 
/*Magic table has to be NxN, N will be defined before*/
/*Files are declared/created out of input function , so we can use thoses files in other functions*/
FILE *File;
FILE *read;
FILE *check;
int count = ZERO; /*Global for using in more than one functions - to count number of integers in table*/
int input(); /*Function for the input proccess*/
int inputvalid(); /*Function called to check if input is valid or not */
int convert();/*Function to convert input/file to a table*/
int ctoi(char c);/*convert char to integer*/
int printtable();
/*Functions called to proccess the check if the table is magic square*/
int checkmagic();
int checkrow();
int checkcolumn();
int checkdiagonal();

int main()
{
	input(); 
	convert();
	if(inputvalid())
	{
		printtable();
		checkmagic();
	}
	return (ZERO);
}

int input()
{
	char content[MAX];/*an array used to read the content from user*/
	char cases[MAX];/*an array used in get input for deciding which file to choose*/
	int temp = ZERO; /*A flag defines the user interest*/
	printf("Please enter %d for entering filename or %d for directly the content here: \n",ZERO,ONE);
	scanf("%d",&temp);
	if(temp == ZERO)/*we need to search the filename in the directory*/
	{ 
		printf("Please enter the filename from the same folder and hit enter \n");
		scanf("%100s",&cases);
	}	
	File=fopen(cases,"r");
	read=fopen(cases, "r");
	check = fopen(cases,"r");
	if(File == NULL) /*FIle name is not found / user requested to enter input*/
	{	
		if(temp == ZERO){perror("Error opening file");}
		File = fopen("File.txt","w");	
		printf("Please enter the Numbers here at this terminal (%d are needed for this magic square): \n", NEED);
		while(fgets(content, sizeof(content), stdin) != NULL){fprintf(File,content);}
		fclose(File);
		File=fopen("File.txt","r");
		read=fopen("File.txt","r");
		check = fopen("File.txt","r");
	}
	printf("\n");
	return(ZERO);
}

/*check if input is valid or not*/
int inputvalid()
{
		int row = ZERO;
		int col = ZERO;
		char c ;
		int flag = ONE;
		if(count != NEED) /*Not enough numbers from input*/
		{
			flag = ZERO;
		}
		while ((c = getc(check)) != EOF)
		{
				if(isalpha(c))/* a non integer has detected*/
			{
				flag = ZERO;				
			}
		}
		for(col = ZERO ; col < N ; col++)
		{
			for(row = ZERO ; row < N ; row++)
			{
			/*ranges of each table cell should be at range of (1 - N^2)*/
				if(magic[row][col]>NEED || magic[row][col]<ONE )
				{
					flag = ZERO;
				}
			}
		}
		if(flag == ZERO)
		{
			printf("\n The input is not valid for a magic square \n");
		}
		return(flag);
}


/*will convert the file to integers */
int convert()
{
	char c;
	int temp = ZERO;
	int j=ZERO;
	int i=ZERO;
	int row=ZERO;
	int col=ZERO;
	int min = ZERO;
	while ((c = getc(read)) != EOF)
		{
			if(isdigit(c))/*Only integers will be converted*/
			{
				/*A case when the integer has more than one digit*/
				if(j > ZERO)
				{
					temp = (temp * TEN) + ctoi(c); 	
				}
				else
				{
					temp = ctoi(c);
					j++;
					count++;
				}
			}	
			if(c == MINUS)
			{
				min++;
			}
			/*A whitespace will be a sign to insert last integer detected*/
			if(isspace(c) && j > ZERO)
			{
				/*A case when a negative number*/
				if(min == ONE)
				{
					min = ZERO;
					temp = (temp * (-ONE)) ;
				}
				j = ZERO;
				if(row==N && col<N)
				{
					row=ZERO;
					col++;
					magic[row][col] = temp;
					
				}
				
				if(row<N && col<N)
				{
					magic[row][col] = temp;
					row++;
					
				}
			}	 
		}
	return(ZERO);
}

int ctoi(char c)
{
	return(c - REF);
}

int printtable()
{
	int i,j;
	printf("\nThe table is : \n");
	for(i=ZERO ; i< N ; i++)
	{
		for(j=ZERO ; j< N ; j++)
		{
			printf("%d ",magic[j][i]);	
		}
		printf("\n");
	}
}

int checkmagic()
{
	if(checkrow() && checkcolumn() && checkdiagonal() )
	{
		printf("\n Congrats you have a magic square \n");
		return(ONE);
	}
	else
	{
	printf("\n Sorry, but this is not a magic square \n");
	return(ZERO);}
}

int checkdiagonal()
{
	int flag = ONE;
	int sumfirst = ZERO;
	int sumsecond = ZERO;
	int row = ZERO;
	int col = ZERO;
	/*check if minmum sum is valid M=n(n^2+1)/2 at diagonal*/
	
		for(col = ZERO,row = ZERO ; col < N ; col++,row++)
		{
			sumfirst = sumfirst + magic[row][col];
		}
		for(col = ZERO,row = N-ONE ; col < N ; col++,row--)
		{
			sumsecond = sumsecond + magic[row][col];
		}
		if(sumfirst < (N*(NEED + ONE)/TWO) || sumsecond < (N*(NEED + ONE)/TWO))
		{
			flag = ZERO;
		}
		if(sumfirst != sumsecond)/*at least one sum of diagonal is diffrent will end loop*/
		{
			flag = ZERO;
		}
	return(flag);
}

int checkcolumn()
{
	int tempsum[N];
	int flag = ONE;
	int sum = ZERO;
	int row = ZERO;
	int col = ZERO;
	int i = ZERO;
	/*check if minmum sum is valid M=n(n^2+1)/2 at column*/
	for(row = ZERO ; row < N ; row++)
	{
		for(col = ZERO ; col < N ; col++)
		{
			sum = sum + magic[row][col];
		}
		if(sum < (N*(NEED + ONE)/TWO))
		{
			/*row = N;*/
			flag = ZERO;
		}
		tempsum[row] = sum;
		sum = ZERO;
	}
	sum = tempsum[N-ONE] ;
	for(i = ZERO ; i < N-ONE ; i++)
	{
		if(tempsum[i] != sum)/*at least one sum of column is diffrent will end loop*/
		{
			i = N;
			flag = ZERO;
		}
	}
	return(flag);
}
int checkrow()
{
	int tempsum[N];
	int flag = ONE;
	int sum = ZERO;
	int row = ZERO;
	int col = ZERO;
	int i = ZERO;
	/*check if minmum sum is valid M=n(n^2+1)/2 at lines*/
	for(col = ZERO ; col < N ; col++)
	{
		for(row = ZERO ; row < N ; row++)
		{
			sum = sum + magic[row][col];
		}
		if(sum < (N*(NEED + ONE)/TWO))
		{
			col = N;
			flag = ZERO;
		}
		tempsum[col] = sum;
		sum = ZERO;
	}
	sum = tempsum[N-ONE] ;
	for(i = ZERO ; i < N-ONE ; i++)
	{
		if(tempsum[i] != sum)/*at least one sum of line is diffrent will end loop*/
		{
			i = N;
			flag = ZERO;
		}
	}
	return(flag);
}
