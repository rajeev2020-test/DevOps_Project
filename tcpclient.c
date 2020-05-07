/* tcpclient.c */
/*
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <unistd.h>
#include <fcntl.h>
//#include <asm-i386/socket.h>
//#include <asm-alpha/socket.h>
#include <errno.h>
#include <unistd.h>

/***
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
*****/

int main()

{

        int sock1,sock2, bytes_recieved,count,retval;  
        char send_data[1024],recv_data[5];
        struct hostent *host;
        struct sockaddr_in server_addr1;  
        struct sockaddr_in server_addr2;
        struct ifreq interface;
        socklen_t size;
        int   bufsize;
        void *sockbufsize;

        //host = gethostbyname("127.0.0.1");
        host = gethostbyname("192.168.4.54");

        if ((sock1 = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        } 

      printf("\n sock1 = %d, sock2 = %d \n",sock1,sock2);

        server_addr1.sin_family = AF_INET;     
        server_addr1.sin_port = htons(9034);   
        server_addr1.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(server_addr1.sin_zero),8); 

        server_addr2.sin_family = AF_INET;     
        server_addr2.sin_port = htons(5001);   
        server_addr2.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(server_addr2.sin_zero),8); 

   /*     strncpy(interface.ifr_ifrn.ifrn_name, "eth0", IFNAMSIZ);
        if (setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE,
                       (char *)&interface, sizeof(interface)) < 0)
        {
          perror("bindtodevice ");
          close(sock);
          exit(0);
        } */

   struct timeval tv;

//     retval = getsockopt(sock1, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));
//     printf("\ngetsockopt RCVTIMO = %d %d \n",tv.tv_usec,tv.tv_sec);
//
//     retval = getsockopt(sock1, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv));
//     printf("\ngetsockopt SNDTIMO = %d %d \n",tv.tv_usec,tv.tv_sec);
//
//     retval = getsockopt(sock1, SOL_SOCKET, SO_RCVBUF, (char *)&sockbufsize, &size);
//     printf("\ngetsockopt = %d %d\n",sockbufsize,size);
//
//      bufsize = 5120;
//
//     retval = setsockopt(sock1, SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof(bufsize));
//
//     retval = getsockopt(sock1, SOL_SOCKET, SO_RCVBUF, (char *)&sockbufsize, &size);
//     printf("\ngetsockopt = %d %d\n",sockbufsize,size);

        if (connect(sock1, (struct sockaddr *)&server_addr1,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect1");
            exit(1);
        }

     retval = getsockopt(sock1, SOL_SOCKET, SO_RCVBUF, (char *)&sockbufsize, &size);
     printf("\ngetsockopt = %d \n",retval);
/*
        if (connect(sock2, (struct sockaddr *)&server_addr2,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect2");
            exit(1);
        }
*/
    count = 0;
        while(1)
        {
          //printf("\nWait for Receiving Data \n");
          //sleep(2);
          //printf("\nWait for Receiving Data \n");
          bytes_recieved=recv(sock1,recv_data,5,0);
          printf("\n bytes_recieved = %d errno = %d",bytes_recieved,
				     errno);
		  if (bytes_recieved == -1)
		  {
		   printf("\n Error in recieve %d \n",errno);
		   sleep(1);
		  }
           if (bytes_recieved > 0)
            count++;
          printf("\n count = %d ",bytes_recieved);
          recv_data[bytes_recieved] = '\0';

 
          if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0)
          {
           close(sock1);
           break;
          } 

         else
           printf("\nRecieved data = %s " , recv_data);
           

           printf("\nSEND (q or Q to quit) : ");
           gets(send_data);
           
          if (strcmp(send_data , "q") != 0 && strcmp(send_data , "Q") != 0)
           send(sock1,send_data,strlen(send_data), 0); 

          else
          {
           send(sock1,send_data,strlen(send_data), 0);   
           close(sock1);
           break;
          }

        }/* while(1) */   
return 0;
}
