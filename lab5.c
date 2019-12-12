#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int randomNumber(int j) {
     srand(j);
       return rand()%20;
    }

int main( )
{
    int fd[2];
    int df[2];
	int fg[2];
    int child1, child2, child3;
    int a,b,c;
    int  a_rec=0 ;
    int  b_rec=0 ;
	int  c_rec=0 ;
    char buffer1[255];
    char buffer2[255];
    char buffer3[255];
    char buffer4[255];
	char buffer5[255];
    char buffer6[255];

    pipe(fd);
    pipe(df);
	pipe(fg);
	
    child1 = fork();

    if (child1 == -1) 
	{
        perror("fork");
        exit(1);
    }

    if (child1 == 0) 
	{
        close(fd[0]);
        a = 0;
        a = randomNumber(1);
        sprintf(buffer1," %i \n",a);
        printf("Child1 sends a number %s \n", buffer1);
        write( fd[1], buffer1, sizeof(buffer1) );
        exit(0);
    }
    else 
    {
        close(fd[1]);
        read(fd[0], buffer2, sizeof(buffer1));
        a_rec = atoi( buffer2 );
        printf("Father received from child1 a number: %d \n", a_rec);
        child2 = fork();
		
        if (child2 == 0) 
		{
            close(df[0]);
            b = randomNumber(2);
            sprintf(buffer3,"%i \n",b);
            printf(" Child2 number is %s \n ", buffer3);
            write(df[1], buffer3, sizeof(buffer3));
            exit(0);
        }
		else 
		{
            close(df[1]);
            read(df[0], buffer4, sizeof(buffer3));
            b_rec= atoi(buffer4);
            printf("Father gets from child2 a number: %d \n ", b_rec);
			child3 = fork();
			
	        if (child3 == 0) 
		    {
                close(fg[0]);
                c = randomNumber(2);
                sprintf(buffer5,"%i \n",c);
                printf(" Child3 number is %s \n ", buffer5);
                write(fg[1], buffer5, sizeof(buffer5));
                exit(0);
            }
		    else 
		    {
                close(fg[1]);
                read(fg[0], buffer6, sizeof(buffer5));
                c_rec= atoi(buffer6);
                printf("Father gets from child3 a number: %d \n ", c_rec);
            }
        }
		
        if (a_rec > b_rec && a_rec > c_rec)
			printf("Childs1 number is the biggest\n");
        if (b_rec > a_rec && b_rec > c_rec)
            printf("Childs2 number is the biggest\n");
		if (c_rec > a_rec && c_rec > b_rec)
            printf("Childs3 number is the biggest\n");
    }
return 0;
}

