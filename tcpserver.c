/* tcpserver.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main()
{
        int sock, connected, bytes_recieved , true = 1,count,i,retval;  
        char send_data [5] , recv_data[1024];       

        struct sockaddr_in server_addr,client_addr;    
        int sin_size;
        socklen_t size;
        void *sockbufsize;
        
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) {
            perror("Setsockopt");
            exit(1);
        }
        
        server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(9000);     
        bzero(&(server_addr.sin_zero),8); 
        server_addr.sin_addr.s_addr = INADDR_ANY; 
       //inet_aton("192.168.4.54", &server_addr.sin_addr);
       //inet_aton("192.168.4.194", &server_addr.sin_addr);
        printf("\n %s", inet_ntoa(server_addr.sin_addr));

        if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
                                                                       == -1) {
            perror("Unable to bind");
            exit(1);
        }

        if (listen(sock, 100000) == -1) {
            perror("Listen");
            exit(1);
        }
		
	printf("\nTCPServer Waiting for client on port 9000");
        fflush(stdout);

//retval = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char *)&sockbufsize, &size);
//printf("\ngetsockopt receive = %d \n",size);

//retval = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char *)&sockbufsize, &size);
  //printf("\ngetsockopt send = %d \n",size);
      int pid = -1 ;


        while(1)
        {  
            sin_size = sizeof(struct sockaddr_in);
			int connected;
            connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

           pid = fork();
		   if ( pid == 0 )
		    {

            printf("\n I got a connection from (%s , %d)",
                   inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
            count = 0;
			  while ( 1) 
			  {
              printf("\n SEND (q or Q to quit) : ");
              gets(send_data);
             
        /*    if (strcmp(send_data , "q") == 0 || strcmp(send_data , "Q") == 0)
              {
                send(connected, send_data,strlen(send_data), 0); 
                close(connected);
                break;
              } 
               
              else */
                 sendto(connected, send_data,strlen(send_data), 0,(struct sockaddr *)&client_addr,sin_size);  
			   sleep(5);
			  }
			 }
          count++;
        }       

      close(sock);
      return 0;
} 
