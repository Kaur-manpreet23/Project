#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
void context(char a[][5],int x){
	
	int i=0,j=0,k=1024,m=0,y=x;
//	while(x!=0){
	static char s1[5],s2[5],s3[5],s4[5];
	while(x!=0){
		sprintf(s1,"sys%d",i);
		sprintf(s2,"%d",k);
		sprintf(s3,"con%d",j);
		sprintf(s4,"con%d",j+1);
//		*(a + m) =s1;
                strcpy(a[m],s1);
		//a[m]=s1;
		m=m+1;
	//	printf("%s\n",*(a+m));
	//	*(a + m) =s2;
	        strcpy(a[m],s2);
		//a[m]=s2;
		m=m+1;
	//	printf("%s\n",*(a+m));
	//	*(a + m) =s3;
	        strcpy(a[m],s3);
		//a[m]=s3;
		m=m+1;
	//	*(a + m) =s4;
		//a[m]=s4;
		strcpy(a[m],s4);
//		printf("i%d\n",i);
		m=m+1;
		i=i+1;
		k=k+1;
		j=j+2;
	x=x-1;
	fflush(stdin);
//	printf("a[m]:%s,m:%d,i:%d\n",a[m-4],m,i);
	}
//	printf("a[0]%s\n",a[0]);

}
int main(int l,char **b)
{	int ex;
	int x=atoi(b[1]);
	//generatecontext(x+1);
	//char *a[4*x],*pass[8];
	char a[4*x+4][5],*pass[10];
	context(a,x+1);
/*	for(int d=0;d<4*x;d++)
		{
		for(int e=0;e<4;e++)
		{
		printf("%c",str[d][e]);
		}
		printf("\n");
		}*/
	int i=0,y=x;
	while(x!=0){
	pid_t pid=fork();
	if(pid==0)
	{	pass[0]="./sbrain";
		int j=1;

		while(j<8){
			pass[j]=a[i];
			j=j+1;
			i=i+1;
		}
		pass[j]=NULL;
	
		printf("i: %d",i);
	ex = execv("sbrain",pass);
	if(ex=-1)
		perror("perror\n");
	}

	x=x-1;
	i=i+4;
	}
	
	i=y*4;
	pid_t npid = fork();
	
	if(npid==0){
		pass[0]="./uibrain";
		int j=1;
		while(j<8){
			pass[j]=a[i];
			j=j+1;
			i=i+1;
			if(i==y*4+4)
				i=0;
		}
		pass[8]=NULL;
		int l=execv("uibrain",pass);
		if(l==-1)
			perror("qerror ");
		}
	else
		{
		i=y*4;
		pass[0]="./ui";
		int j=1;
		while(j<8){
			pass[j]=a[i];
			j=j+1;
			i=i+1;
			if(i==y*4+4)
				i=0;
		}
		pass[8]=NULL;

		int q =execv("ui",pass);
			if(q==-1)
				perror("lerror ");
		}


	return 0;

}
