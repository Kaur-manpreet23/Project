#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<fcntl.h>
//#define REMOTEPORT 1235
#define BUFLEN 1024


int main(int x, char* file[])
{
  int REMOTEPORT=atoi(file[1]);
  printf("REMOTEPORT: %d\n",REMOTEPORT);
  int sockfd;
  char buffer[BUFLEN];
//  char *messageStr = "very important Good Morning message with 100s of emojis!!!";
  struct sockaddr_in   receiverAddr;
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  memset(&receiverAddr, 0, sizeof(receiverAddr));
  receiverAddr.sin_family = AF_INET;
  receiverAddr.sin_port = htons(REMOTEPORT);
  receiverAddr.sin_addr.s_addr = INADDR_ANY;
 int a=0;
 while(1)
 {
 sleep(5);
  int fd = open(file[2],O_RDONLY|O_CREAT,0644);
  int nb = read(fd,buffer,strlen(buffer));
  close(fd);
  printf("mouth string %s\n",buffer);
  printf("mouth buffer %d\n",nb);
//  if(a!=nb){
  sendto(sockfd,buffer, strlen(buffer), 0, (const struct sockaddr *) &receiverAddr, sizeof(receiverAddr));
// printf("very important good morning message sent by smouth to sear.....\n");
printf("message sent to ear is %s\n",buffer);
//	a=nb;
//}
 // getchar();
 }
  close(sockfd);
  return 0;
}

