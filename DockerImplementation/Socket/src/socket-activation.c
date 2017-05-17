/*
 * socket-activation - Activate a service via a socket connection
 * Bruno Mondelo Giaramita
 * 2017-05-17 Escola Del Treball De Barcelona
 * Usage: socket-activation [ORDER]...
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/select.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <errno.h>

#define PROGRAM_NAME "socket-activation"
/* The official program name */

#define PORT 10001
/* The port of the socket */

#define LOG_FILE "/var/log/socket-activation.log"
/* The log file */

static FILE * logd;
/* The log file */

static int is_running = 1;
/* The status of the program */

char *
actual_time ()
{
    /*
     * Pointer to a char determinating the actual time
     * Input: None
     * Output: char pointer
    */
    
    time_t rawtime;
    /* Time in UNIX seconds */
    
    struct tm * info;
    /* Time in natural notation */
    
    char * now_time;
    /* To erase last \n */
    
    time (&rawtime);
    info = localtime (&rawtime);
    /* Get actual time in UNIX and convert in convencional time */
    
    now_time = asctime(info);
    now_time[strlen(now_time) - 1] = '\0';
    /* Erase last character: \n */
    
    return now_time;
    
}
/* Gets the actual time */

static void
sigterm_handler (int signum)
{
  
  is_running = 0;
  fprintf(logd, "[%s]: [DEBUG]: Received SIGTERM\n",
      actual_time());
  /* Stop listening */
  
}
/* SIGTERM handler */

int
main (int argc, char * argv[])
{
  
  char ** newargv;
  /* The order to execute */
  
  char * order;
  /* The order in one line */
  
  int childpid;
  /* The PID of the child */
  
  int mainsock;
  /* The main socket descriptor */
  
  fd_set sockfd;
  /* The socket descriptors */
  
  struct timeval timeout;
  /* The select timeout */
  
  int readselect;
  /* The select result */
  
  struct sockaddr_in server_address;
  /* The server address */
  
  struct sockaddr_in client_address;
  /* The client address */
  
  int sin_size;
  /* The socket address structure size */
  
  if (argc < 2)
  {
    fprintf(stderr, "%s -- Bad arguments\n", PROGRAM_NAME);
    fprintf(stderr, "usage: %s [ORDER]...\n", PROGRAM_NAME);
    return -1;
  }
  /* Control argument usage */
  
  newargv = (char **)malloc(sizeof(char) * (argc));
  /* Alloc memory for order */
  
  for (int i = 1; i < argc; i++)
    newargv[i - 1] = argv[i];
  /* Add arguments to the list of arguments */
  
  newargv[argc - 1] = NULL;
  /* The last element must be a NULL pointer */
  
  if (signal(SIGTERM, sigterm_handler) == SIG_ERR)
  {
    fprintf(stderr, "%s -- Canno't set signal handler for SIGTERM\n",
      PROGRAM_NAME);
    return 2;
  }
  /* Set signal handlers */
  
  if ((logd = fopen(LOG_FILE, "a")) == NULL)
  {
    fprintf(stderr, "%s -- Canno't open log file: %s\n", PROGRAM_NAME,
      LOG_FILE);
    return 1;
  }
  /* Open log file descriptor */

  if ((mainsock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    fprintf(logd, "[%s]: [ERROR]: Canno't allocate memory for socket\n",
      actual_time());
    return 75;
  }
  /* Assign the socket descriptor */
  
  server_address.sin_family = AF_INET;
  /* Declare the domain of communication */
  
  server_address.sin_port = htons(PORT);
  /* Define the port */
  
  server_address.sin_addr.s_addr = INADDR_ANY;
  /* The address to listen, all addresses */
	
  memset(&(server_address.sin_zero), 0, 8);
  /* Fill memory with zeroes */
  
  if (bind(mainsock, (struct sockaddr *)&server_address,
    sizeof(struct sockaddr)) == -1)
  {
    fprintf(logd, "[%s]: [ERROR]: Canno't bind socket via port: %d\n",
      actual_time(), PORT);
    return 74;
  }
  /* Bind the socket */
  
  if (listen(mainsock, -1) == -1)
  {
    fprintf(logd, "[%s]: [ERROR]: Error seting socket to listen\n",
      actual_time());
    return 73;
  }
  fprintf(logd, "[%s]: [DEBUG]: Correct openned socket, listening on \
port: %d\n", actual_time(), PORT);
  /* Set socket to listen */
  
  while (is_running)
  {
    
    FD_ZERO(&sockfd);
    /* Set to zero the socket list */
    
    FD_SET(mainsock, &sockfd);
    /* Add the socket */
    
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    /* Set timeout to one second */
    
    readselect = select(mainsock + 1, &sockfd, NULL, NULL, &timeout);
    /* Wait for timeout or a change */
    
    if (readselect < 0)
    {
      fprintf(logd, "[%s]: [ERROR]: Error in select\n",
      actual_time());
      break;
    }
    /* Select error */
    else if (readselect == 0)
      continue;
    /* Timeout */
    
    sin_size = sizeof(struct sockaddr_in);
    /* Add the client address size */
    
    if (FD_ISSET(mainsock, &sockfd))
    {
      if (accept(mainsock, (struct sockaddr *)&client_address,
        &sin_size) == -1)
      {
        fprintf(logd, "[%s]: [ERROR]: Error accepting new connection\n");
        continue;
      }
      /* Error accepting new connection */
      
      fprintf(logd, "[%s]: [DEBUG]: Accepted connection on client: %s\n",
        actual_time(), inet_ntoa(client_address.sin_addr));
      /* Accepted connection */
      
      if (fork() == 0)
      {
        execv(newargv[0], newargv);
        return 0;
      }
      fprintf(logd, "[%s]: [DEBUG]: Executing order\n",
        actual_time());
      /* Execute the order in a new process */
    }
    /* Hand new connection */
    
  }
  /* Stay listening for new connections */
  
  close(mainsock);
  fprintf(logd, "[%s]: [DEBUG]: Closing socket via port: %d\n",
      actual_time(), PORT);
  /* Close socket */
  
  fprintf(logd, "[%s]: [DEBUG]: Closing service\n",
      actual_time());
  fclose(logd);
  /* Close log file */
  
  return 0;
  
}
