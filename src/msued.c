/*
 * msued - Daemon to start a set of resources
 * Bruno Mondelo Giaramita
 * 2017-05-08 Escola Del Treball De Barcelona
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
//~ #include <fcntl.h>
#include <sys/stat.h>
#include "resource.h"

#define PROGRAM_NAME "msued"

#define AUTHORS \
  proper_name("Bruno Mondelo")

//~ #define LOG_FILE "/var/log/msued.log"
#define LOG_FILE "/tmp/msued.log"
/* The log file */

//~ #define RESOURCE_FOLDER "/etc/msued"
#define RESOURCE_FOLDER "/var/tmp/msued"
/* The folder containing all the resources */

#define SYSTEM_FIFO "/tmp/msued.socket"
/* Administartion FIFO path */

#define SERVICE_FIFO "/tmp/msued-service.socket"
/* Communicating to service process */

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

int
start_fifo (char * fifopath)
{
  
  /*
   * Creates a FIFO, if already exits proves the access
   * Input: char pointer
   * Output: int
             -1 - Error creating FIFO
              0 - FIFO correct
              1 - Created FIFO
  */
  
  if (access(fifopath, F_OK) == 0)
    return 0;
  /* Check the existence of the FIFO */
  
  if (mkfifo(fifopath, 0666) != 0)
    return -1;
  /* Create a FIFO, notify if fails */
  
  return 1;
  
}

int
main () 
{
  
  FILE * logd;
  /* The log file descriptor */
  
  if ((logd = fopen(LOG_FILE, "a")) == NULL)
  {
    fprintf(stderr, "msued - ERROR: Canno't open log file %s\n", LOG_FILE);
    return -1;
  }
  fprintf(logd, "%s: [DEBUG]: Started daemon!\n", actual_time());
  /* Open log file */
  
  switch (start_fifo(SYSTEM_FIFO))
  {
    case -1:
      fprintf(logd, "%s: [ERROR]: Canno't open FIFO at %s\n",
        actual_time(), SYSTEM_FIFO);
      return 60;
      break;
    case 0:
      break;
    case 1:
      fprintf(logd, "%s: [DEBUG]: Created administration FIFO at %s\n",
        actual_time(), SYSTEM_FIFO);
      break;
    default:
      fprintf(logd, "%s: [ERROR]: Abnormaly error openning FIFO at %s\n",
        actual_time(), SYSTEM_FIFO);
      return 61;
      break;
  }
  /* Start the administration FIFO */
  
  switch (start_fifo(SERVICE_FIFO))
  {
    case -1:
      fprintf(logd, "%s: [ERROR]: Canno't open FIFO at %s\n",
        actual_time(), SERVICE_FIFO);
      return 60;
      break;
    case 0:
      break;
    case 1:
      fprintf(logd, "%s: [DEBUG]: Created administration FIFO at %s\n",
        actual_time(), SERVICE_FIFO);
      break;
    default:
      fprintf(logd, "%s: [ERROR]: Abnormaly error openning FIFO at %s\n",
        actual_time(), SERVICE_FIFO);
      return 61;
      break;
  }
  /* Start the service FIFO */
  
  fclose(logd);
  /* Close log file */
  
  return 0;
  
}
