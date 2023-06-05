#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<assert.h>
#include "new.c"

#define MAX_STRING_LENGTH 1024
/*
* a 1 self - id
* a 2 self - port
* a 3 self - file 1
* a 4 self - file 2
* a 5 as - id
* a 6 as - port
* a 7 as file 3
* a 8 as file 4
*/

void context(char id1[], char port1[], char id2[], char port2[], char file[]){
	
	int fd=open(file,O_WRONLY|O_APPEND|O_CREAT,0644);
	assert(fd>0);
	int nb=write(fd,id1,strlen(id1));
	nb=write(fd,"\n",1);
	nb=write(fd,port1,strlen(port1));
	nb=write(fd,"\n",1);
	nb=write(fd,id2,strlen(id2));
	nb=write(fd,"\n",1);
	nb=write(fd,port2,strlen(port2));
	nb=write(fd,"\n",1);
	close(fd);
}
int main(int x, char* arg[]){
char *a[5],*b[5];
	int i,j;
	pid_t pid = fork();
		if(pid==0){//mouth port2, file2
			b[0]="./smouth";
			b[1]=arg[6];
			b[2]=arg[4];
			b[3]=NULL;
//			sleep(5);
			j=execv("smouth",b);
			if(j==-1)
				perror("error");
		}
		else{
			pid_t npid = fork();
			
			if(npid==0){// port1, file1
			a[0]="./sear";
			a[1]=arg[2];
			a[2]=arg[3];
			//a[3]=arg[3];
			//a[4]=arg[6];
			a[3]=NULL;
			i=execv("sear",a);
				if (i==-1)
					perror("error");
			}
		}
		context(arg[1],arg[2],arg[5],arg[6],arg[4]);
		brain(arg[3],arg[4]);	
}
