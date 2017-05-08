/*
 * msued-service - Daemon to controll all service resources
 * Bruno Mondelo Giaramita
 * 2017-05-08 Escola Del Treball De Barcelona
*/

#include <stdio.h>
#include <unistd.h>
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

#define SERVICE_FIFO "/tmp/msued-service.socket"
/* Communicating to service process */

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
  
  serviceresource * service_list[1];
  
  serviceresource my_service;
  my_service.binary = "/bin/ls /";
  my_service.status = 0;
  service_list[0] = &my_service;
  
  serviceresource my_long_service;
  my_long_service.binary = "/bin/tree /";
  my_long_service.status = 0;
  service_list[1] = &my_long_service;
  
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
  
  return 0;
  
}
