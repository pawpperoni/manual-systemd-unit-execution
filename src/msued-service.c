/*
 * msued-service - Daemon to controll all service resources
 * Bruno Mondelo Giaramita
 * 2017-05-08 Escola Del Treball De Barcelona
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "resource.h"

#define PROGRAM_NAME "msued-service"

#define AUTHORS \
  proper_name("Bruno Mondelo")

//~ #define LOG_FILE "/var/log/msued-service.log"
#define LOG_FILE "/tmp/msued-service.log"
/* The log file */

#define BUFFER_SIZE_FIFO 255
/* The size of the FIFO buffer */

#define SERVICE_FIFO "/tmp/msued-service.socket"
/* Communicating to service process */

static serviceresource * service_list;

void
childhandler (int signum)
{
  
  pid_t pid;
  
  pid = wait(NULL);
  
  printf("Child with PID %d Exited!\n", pid);
  
}

int
main ()
{
  
  signal(SIGCHLD, childhandler);
  /* Children status handler */
  
  int fifod;
  /* The FIFO descriptor */
  
  char buf[BUFFER_SIZE_FIFO];
  /* The FIFO buffer */
  
  if ((fifod = open(SERVICE_FIFO, O_RDONLY)) == -1)
    return 1;
  /* Open the Service FIFO */
  
  read(fifod, buf, BUFFER_SIZE_FIFO);
  /* Read from the FIFO */
  
  printf("Received: %s\n", buf);
  
  close(fifod);
  /* Close FIFO descriptor */
  
  FILE * ff;
  ff = fopen("/tmp/msued-service.log", "w");
  
  while (1)
  {
    fprintf(ff, "HEY!\n");
    sleep(10); 
  }
  
  return 0;
  
  service_list = realloc(service_list, sizeof(serviceresource));
  
  serviceresource my_service;
  my_service.binary = "/bin/ls /";
  my_service.status = 0;
  service_list[0] = my_service;
  
  service_list = realloc(service_list, 2 * sizeof(serviceresource));
  
  serviceresource my_long_service;
  my_long_service.binary = "/bin/tree /";
  my_long_service.status = 0;
  service_list[1] = my_long_service;
  
  if (fork() == 0)
  {
    int fd = open("/tmp/testfile", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    
    dup2(fd, 1);
    dup2(fd, 2);
    
    close(fd);
    
    execl("/bin/ls /", (char *)NULL);
    
    return 0;
    
  }
  /* Child process */
  
  while (1);
  /* Parent */
  
  free(service_list);
  
  return 0;
  
}
