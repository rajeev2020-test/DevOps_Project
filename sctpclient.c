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

        int sock1,sock2, bytes_recieved,count;  
        char send_data[1024],recv_data[1024];
        struct hostent *host;
        struct sockaddr_in server_addr1;  
        struct sockaddr_in server_addr2;
        struct ifreq interface;

        //host = gethostbyname("127.0.0.1");
        host = gethostbyname("192.168.4.54");

          if ((sock1 = socket(AF_INET, SOCK_RAW, IPPROTO_SCTP)) == -1) {
            perror("Socket");
            exit(1);
        } 
       /*   if ((sock1 = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) == -1) {
            perror("Socket");
            exit(1);
        } */ 

/*
        if ((sock2 = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) == -1) {
            perror("Socket");
            exit(1);
        } */

      printf("\n sock1 = %d, sock2 = %d \n",sock1,sock2);

        server_addr1.sin_family = AF_INET;     
        server_addr1.sin_port = htons(5000);   
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


        if (connect(sock1, (struct sockaddr *)&server_addr1,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect1");
            exit(1);
        }
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
          printf("\nwait for receiving data :  \n");
          sleep(2);
          printf("\nwait for receiving data :  \n");
          bytes_recieved=recv(sock1,recv_data,10,0);
          printf("\nretval = %d \n",bytes_recieved);
           if (bytes_recieved > 0)
            count++;
          printf("\n count = %d ",count);
          recv_data[bytes_recieved] = '\0';


/*        if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0)
          {
           close(sock1);
           break;
          } 

          else */
           printf("\nRecieved data = %s " , recv_data);
           
/*
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
*/
        }   
return 0;
}
