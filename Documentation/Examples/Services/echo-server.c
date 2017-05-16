/*
 * echo-server.py - A echo TCP server
 * Bruno Mondelo Giaramita
 * 2017-05-15 Escola del Treball
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>


#define PORT 4113
/* Server port */

#define MAXTHREADCONNECTION 5
/* Max connections per thread */

#define MAXDATASIZE 2048
/* The message max length */

typedef struct {
  
  int   childID;                         /* The ID of the child */
  int   childcount;                      /* The clients connected to the
                                            child */
  int   childlist[MAXTHREADCONNECTION];  /* The list of childs */
  int   active;                          /* The status of the child */
  int   is_enabled;                      /* The stop child condition 
                                         0: Ok, 1: Parent stop,
                                         -1: Child error */
  
} childselect_t;

int
set_file_descriptors (fd_set descriptors, int mainsocket,
  int clientcount, int * clientsockets)
{
  
  /*
   * Sets all resources for select
   * Input: fd_set, int, int, int *
   * Output: int (the high socket)
  */
  
  int greatsocket;
  /* The higher socket */
  
  FD_ZERO(&descriptors);
  /* Clear old file descriptors */
  
  FD_SET(mainsocket, &descriptors);
  /* Add main socket */
  
  greatsocket = mainsocket;
  /* First socket to assign is the main */
  
  for (int i = 0; i < clientcount; i++)
  {
    FD_SET(clientsockets[i], &descriptors);
    if (clientsockets[i] > greatsocket)
      greatsocket = clientsockets[i];
  }
  /* Add client sockets */
  
  return greatsocket;
  
}

void
childselect (childselect_t structure)
{
  
  /*
   * The child select function
   * Input: childselect_t
   * Output: None
  */
  
  int highsock;
  /* The higher socket */
  
  fd_set socks;
  /* Socket descriptors */
  
  struct timeval timeout;
  /* The select timeout */
  
  int readsocks;
  /* The select result */
  
  int rec_bytes;
  /* Received bytes */
  
  char rec_buf[MAXDATASIZE];
  /* The receiving buffer */
  
  while (structure.is_enabled)
  {
  /* Stay listening to childs */
  
    highsock = set_file_descriptors(socks, 0, structure.childcount,
        structure.childlist);
    /* Setup the select table. We don't have main socket, so
       we just put a 0 */
    
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    /* Set timeout to one second */
    
    readsocks = select(highsock + 1, &socks, NULL, NULL, &timeout);
    /* Select with timeout */
    
    if (readsocks < 0)
    {
      fprintf(stderr, "Child with ID: %d select error\n",
        structure.childID);
      structure.is_enabled = -1;
      continue;
    }
    /* Bad select reading, causes the end of the child */
    
    for (int i = 0; i < MAXTHREADCONNECTION; i++)
    {
      if (FD_ISSET(structure.childlist[i], &socks))
      {
        if ((rec_bytes = recv(structure.childlist[i], rec_buf, MAXDATASIZE, 0)) <= 0)
        {
          close(structure.childlist[i]);
          /* Close the client */
          
          structure.childcount = structure.childcount - 1;
          /* Low by one the child count */
          
          structure.childlist[i] = 0;
          /* Let free the slot */
          
          fprintf(stderr, "Closed connection in child with ID: %d; \
free slots: %d\n", structure.childID,
MAXTHREADCONNECTION - structure.childcount);

          continue;
        }
        /* Client closed connection */
        
        rec_buf[strlen(rec_buf) - 1] = '\0';
        
        printf("Received on ID: %d : rec_buf\n", structure.childID, rec_buf);
      }
      
    }
    /* Changed status from a connected client */

  }

}

int
main ()
{
  
  int sock;
  /* The socket descriptor */
  
  int highsock;
  /* The highest socket descriptor */

  int * connectlist;
  /* List of connected clients */
  
  fd_set socks;
  /* Socket descriptors to wake up with select */
  
  struct sockaddr_in server_address;
  /* The server address */
  
  struct sockaddr_in client_address;
  /* The client address */
  
  socklen_t sin_size;
  /* The size of socket structure */
  
  struct timeval timeout;
  /* The select timeout */
  
  int readsocks;
  /* Socket ready for reading */
  
  int new_connection;
  /* Handler for new connections */
  
  int rec_bytes;
  /* Received bytes */
  
  char rec_buf[MAXDATASIZE];
  /* The receiving buffer */
  
  childselect_t childs[1];
  /* List of childs */
  
  childselect_t newchild;
  /* The new child */
  
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    fprintf(stderr, "Socket error\n");
    return 75;
  }
  /* Assign the socket descriptor */
  
  //~ setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse_addr,
    //~ sizeof(reuse_addr));
   
  //~ Non blocking routine
    
  server_address.sin_family = AF_INET;
  /* Declare the domain of communication */
  
  server_address.sin_port = htons(PORT);
  /* Define the port */
  
  server_address.sin_addr.s_addr = INADDR_ANY;
  /* The address to listen, all addresses */
	
  memset(&(server_address.sin_zero), 0, 8);
  /* Fill memory with zeroes */
  
  if (bind(sock, (struct sockaddr *)&server_address,
    sizeof(struct sockaddr)) == -1)
  {
    fprintf(stderr, "Bind error\n");
    return 74;
  }
  /* Bind the socket */

  if (listen(sock, -1) == -1)
  {
    fprintf(stderr, "Listen error\n");
    return 73;
  }
  fprintf(stderr, "Correct created!\n");
  
  highsock = sock;
  /* Assign the highest socket to main socket */
  
  connected_clients = 0;
  //~ memset((char *) &connectlist, 0, sizeof(connectlist));
  
  while (1)
  {
    /* Stay listening */
    
    highsock = set_file_descriptors(socks, sock, connected_clients,
      connectlist);
    /* Setup the select table */
    
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    /* Set timeout to one second */
    
    //~ readsocks = select(highsock + 1, &socks, NULL, NULL, &timeout);
    /* Select with timeout */
    readsocks = select(highsock + 1, &socks, NULL, NULL, NULL);
    /* Select */
    
    if (readsocks < 0)
    {
      fprintf(stderr, "Select error\n");
      return 1; 
    }
    /* Bad reading */
    else if (readsocks == 0)
      fprintf(stderr, ".\n");
    /* Timeout */
    
    sin_size = sizeof(struct sockaddr_in);
    /* Assign the socket address size */
    
    if (FD_ISSET(sock, &socks))
    {
      if ((new_connection = accept(sock,
        (struct sockaddr *)&client_address, &sin_size)) == -1)
        fprintf(stderr, "Error accepting new connection\n");
      else
      {
        connected_clients++;
        connectlist = realloc(connectlist,
            sizeof(int) * connected_clients);
        connectlist[connected_clients - 1] = new_connection;
        fprintf(stderr, "Added new client with IP: %s\n",
          inet_ntoa(client_address.sin_addr));
      }
    }
    /* New connection */
   
   printf("actual clients: %d\n", connected_clients);
   
   for (int i = 0; i < connected_clients; i++)
   {
     if (FD_ISSET(connectlist[i], &socks))
     {
       if ((rec_bytes = recv(connectlist[i], rec_buf,
        MAXDATASIZE, 0)) <= 0)
       {
         fprintf(stderr, "Closed connection connection: FD: %d, Slot: %d\n",
              new_connection, i);
         close(connectlist[i]);
         /* Close socket */
         
         connectlist[i] = 0;
         /* Let a free slot */
         
         continue;
       }
       /* Closed connection */
       
       send(connectlist[i], rec_buf, rec_bytes, 0);
       /* Echo back message */
     }
     else
       printf("No ISSET\n");
   }
   /* Changed status from connected sockets */
    
  }
  
  return 0;
  
}
