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
        int sock, connected, bytes_recieved , true = 1,count,i;  
        char send_data [1024] , recv_data[1024];       

        struct sockaddr_in server_addr,client_addr;    
        int sin_size;
        
        if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_SCTP)) == -1) {
            perror("Socket");
            exit(1);
        }
       /* if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) == -1) {
            perror("Socket");
            exit(1);
        } */

        if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) {
            perror("Setsockopt");
            exit(1);
        }
        
        server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(5000);     
        bzero(&(server_addr.sin_zero),8); 
        //server_addr.sin_addr.s_addr = INADDR_ANY; 
        //inet_aton("192.168.4.54", &server_addr.sin_addr);
        inet_aton("192.168.2.208", &server_addr.sin_addr);
        printf("\n %s", inet_ntoa(server_addr.sin_addr));

        if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
                                                                       == -1) {
            perror("Unable to bind");
            exit(1);
        }

        if (listen(sock, 5) == -1) {
            perror("Listen");
            exit(1);
        }
		
	printf("\nTCPServer Waiting for client on port 5000");
        fflush(stdout);


        while(1)
        {  

            sin_size = sizeof(struct sockaddr_in);

            connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

            printf("\n I got a connection from (%s , %d)",
                   inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
       count = 0;
            while (1)
            {
            //for(i = 0; i<10; i++)
            // send_data[i] = i;
                printf("\n SEND (q or Q to quit) : ");
                gets(send_data);
             
              if (strcmp(send_data , "q") == 0 || strcmp(send_data , "Q") == 0)
              {
                send(connected, send_data,strlen(send_data), 0); 
                close(connected);
                break;
              }
               
              else
                 send(connected, send_data,strlen(send_data), 0);  

/*

              bytes_recieved = recv(connected,recv_data,1024,0);

              recv_data[bytes_recieved] = '\0';

              if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0)
              {
                close(connected);
                break;
              }

              else 
              printf("\n RECIEVED DATA = %s " , recv_data);
              fflush(stdout);
*/
     count++;
       if (count == 100)
         break;
            }
          printf("count = %d ",count);
        }       

      close(sock);
      return 0;
} 
