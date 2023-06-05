//hello this was added by talha please do not remove this or code will not workd!!


#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
int main(){
char c[1024];
//this loop will ensure the running of the program until user explicitly says exit.
while(1)
	
	{
	printf("Enter a message\n");
	
	scanf("%[^\n]s",c);
	getchar();	
	printf("message sent:  %s\n",c);
	pid_t pid = getpid();
	char s1[16];

	if (strcmp(c,"exit")==0)
	{
		sprintf(s1,"pkill -g %d",pid);
		system(s1);
	}
		fflush(stdin);
	}

}
