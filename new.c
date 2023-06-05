#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<assert.h>

int getval(char a){
	char x[] = {a};
	return atoi(x);
}

int cmp(char temp1[],char temp2[]){
	int i=0;
	if(temp1[3]==temp2[3])
		i=1;
	return i;
}

void write_sort(char ins1[],char ins2[],char file[]){
	char buf[1024];
	
	int fd = open(file,O_RDONLY|O_CREAT,0644);
	int nb = read(fd,buf,1024);
	close(fd);

	int i=3;
	while(getval(buf[i])<getval(ins1[3]) && i<nb){
		i=i+10;
	}
	
//	printf("\n%d\n",i);

	 i=i-3;
//	printf("\n%d %d\n",nb-1,i);

	 int j=nb-1;
	while(j>=i){
		
		buf[j+10]=buf[j];
		j=j-1;
	}


	buf[i]=ins1[0];
	buf[i+1]=ins1[1];
	buf[i+2]=ins1[2];
	buf[i+3]=ins1[3];
	buf[i+4]='\n';
	buf[i+5]=ins2[0];
	buf[i+6]=ins2[1];
	buf[i+7]=ins2[2];
	buf[i+8]=ins2[3];
	buf[i+9]='\n';
	
	printf("new file buffer %s\n",buf);
	fd = open(file,O_WRONLY,0644);
	assert(fd>0);
	nb = write(fd,buf,nb+10);
	close(fd);
}


void brain(char file1[],char file2[]){
	char buf[1024],buf2[1024];
	char temp1[4],temp2[4];
//while(1){	
	//reading from ear file and storing in buf
	int fd = open(file1,O_RDONLY|O_CREAT,0644);
	assert(fd>0);
	int nb = read(fd,buf,1024);
	close(fd);

	printf("in new\n");
	//reading from mouth file and storing in buf2
//while(1){
	int fd1 = open(file2,O_RDONLY|O_CREAT,0644);
	assert(fd1>0);
//	while(1){
	int nb1 = read(fd1,buf2,1024);
	close(fd1);
	
	int i=0,k=0;

	while(i<nb && k<nb1){
	int idx = 0;	
	for(int j=i;j<i+5;j++){
//		printf("%c\n",buf[j]);
		temp1[idx]=buf[j];
		idx++;
	}
//	printf("\n");
	idx=0;
	for(int j=k;j<k+5;j++)
	{	//printf("%c\n",buf2[j]);
		temp2[idx]=buf2[j];
		idx++;
	}
	
//	printf("\n");

	int x = cmp(temp1,temp2);
		if(x==0){
		idx = 0;
		for(int j=i+5;j<i+10;j++)
				{
//					printf("%c\n",buf[j]);
					temp2[idx]=buf[j];
					idx++;
				}
		
		write_sort(temp1,temp2,file2); 
		}
	i = i + 10;
	k = k + 10;
	}
	
	while(i<nb){
//		printf("\n");
		int idx=0;
		for(int j=i;j<i+5;j++)
		{
//			printf("%c\n",buf[j]);
			temp1[idx]=buf[j];
			idx++;
		}
		idx=0;
//		printf("\n");
		for(int j=i+5;j<i+10;j++){
			printf("%c\n",buf[j]);
			temp2[idx]=buf[j];
			idx++;
		}
		write_sort(temp1,temp2,file2);
		i=i+10;
		}
//}
//close(fd1);
}

int main(){
	brain("f1","f2");
}
