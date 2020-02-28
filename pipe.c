#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(){
	int fd1[2];
    	int fd2[2];

	int num;
	
	pid_t p;
	if (pipe(fd1)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		return 1; 
	} 
	if (pipe(fd2)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		return 1; 
	} 
	printf("Enter number: ");
	scanf("%d",&num); 
	p = fork(); 

	if (p < 0) 
	{ 
		fprintf(stderr, "fork Failed" ); 
		return 1; 
	} 
	else if (p > 0) 
	{ 
		int value;
		close(fd1[0]);

		write(fd1[1],(char*)&num,sizeof(num)); 
		close(fd1[1]); 

		wait(NULL); 

		close(fd2[1]);

		read(fd2[0], (char*)&value, sizeof(num)); 
		if(value == 1){
			printf("number is divisible by 3\n");
		}else{
			printf("number is not divisible by 3\n");
		}
		close(fd2[0]); 
	} 
	else
    { 
        close(fd1[1]); 
  
       
        int value;
	int number;
        read(fd1[0], (char*)&num, sizeof(num)); 
  
    
        if(num%3 == 0){
		value = 1;
	}
	else{
		value = 2;
	}
      
        close(fd1[0]); 
        close(fd2[0]); 
  
        write(fd2[1],(char*)&value,sizeof(num)); 
        close(fd2[1]); 
  
        exit(0); 
    } 
}

	

