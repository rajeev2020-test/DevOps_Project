#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main()
{
int sock,bytes_read;
struct sockaddr_in client_addr;
struct hostent *host;
char recv_data[1024];

host = (struct hostent *) gethostbyname((char *)"192.168.103.77");


if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
{
perror("socket");
exit(1);
}

client_addr.sin_family = AF_INET;
client_addr.sin_port = htons(7777);
client_addr.sin_addr = *((struct in_addr *)host->h_addr);
bzero(&(client_addr.sin_zero),8);

   while (1)
   {
     bytes_read = recvfrom(sock, recv_data, strlen(recv_data), 0,
                  (struct sockaddr *)&client_addr, sizeof(struct sockaddr));
	  if (bytes_read == -1)
      {
       printf("\n ERRNO = %d\n",errno);
	   exit(0);
      }
	  recv_data[bytes_read] = '\0';

      printf("\n(%s , %d, %d) : ",inet_ntoa(client_addr.sin_addr),
                                       ntohs(client_addr.sin_port),bytes_read);
      printf("\n recevied data : %s", recv_data);
	  fflush(stdout);

   }

}
