/*
 * path-activation - Activate a service via a path access
 * Bruno Mondelo Giaramita
 * 2017-05-18 Escola Del Treball De Barcelona
 * Usage: path-activation -f|--file FILE [-a|--atime] [-m|--mtime] [-c|--ctime] ORDER...
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>


#define PROGRAM_NAME "socket-activation"
/* The official program name */

#define SLEEP_TIME 500
/* The CPU save delay */

static struct option long_options [] = {
  {"atime", no_argument, NULL, 'a'},
  {"ctime", no_argument, NULL, 'c'},
  {"file", required_argument, NULL, 'f'},
  {"help", no_argument, NULL, 'h'},
  {"mtime", no_argument, NULL, 'm'},
  {NULL, 0, NULL, 0}
};

static void
sigterm_handler (int signum)
{

  fprintf(stderr, "%s: [DEBUG]: Received SIGTERM\n", PROGRAM_NAME);
  /* Stop waiting for changes */
  
}
/* SIGTERM handler */

void
usage (int status)
{
  
  if (status == EXIT_FAILURE)
    fprintf(stderr, "Try '%s --help' for more information\n",
      PROGRAM_NAME);
  /* Bad usage */
  else
  {
    printf("Usage: -f|--file FILE [-a|--atime] [-m|--mtime] "
"[-c|--ctime] ORDER...\n", PROGRAM_NAME);
    /* Show usage */
    
    printf("Path-based activation of a process\n");
    /* Show information about the program */
    
    printf("\n\
  -a, --atime           Notify access time changes\n\
  -c, --ctime           Notify change time changes\n\
  -f, --file FILE       The file or directory to check\n\
  -h, --help            Show this help and exits\n\
  -m, --mtime           Notify modify time changes\n");
    /* Show options and parameters */
  }
  
  exit(status);
  /* End of program */
  
}
/* The usage/help command */

int
main (int argc, char * argv[])
{
  
  int opt;
  /* The argument option */
  
  int atime;
  /* Access time option */
  
  int mtime;
  /* Modify time option */
  
  int ctime;
  /* Change time option */
  
  char * filename = NULL;
  /* The filename to check */
  
  atime = 0;
  /* Set atime to not active */
  
  mtime = 0;
  /* Set mtime to not active */
  
  ctime = 0;
  /* Set ctime to not active */
  
  while ((opt = getopt_long(argc, argv, "acf:hm", long_options,
    NULL)) != -1)
  {
    switch (opt)
    {
      case 'a':
        atime = 1;
        break;
      case 'c':
        ctime = 1;
        break;
      case 'f':
        filename = optarg;
        break;
      case 'h':
        usage(EXIT_SUCCESS);
        break;
      case 'm':
        mtime = 1;
        break;
      case '?':
        if (optopt == 'f')
          fprintf(stderr, "%s: option 'f' requires an argument\n",
            PROGRAM_NAME);
        else
          fprintf(stderr, "%s: unknown option: '%c'\n", PROGRAM_NAME,
            optopt);
        usage(EXIT_FAILURE);
        break;
      default:
        abort();
    }
  }
  /* Parse arguments */
  
  if (filename == NULL)
  {
    fprintf(stderr, "%s: Required file argument\n", PROGRAM_NAME);
    usage(EXIT_FAILURE);
  }
  /* The file is a required argument */
  
}


//~ int
//~ 2main (int argc, char * argv[])
//~ {
  
  //~ struct timespec lastaccess;
  //~ /* The last access time */
  
  //~ struct stat buf;
  //~ /* The status structure */
  
  //~ char * filename;
  //~ /* The file to check the last access */
  
  //~ if (signal(SIGTERM, sigterm_handler) == SIG_ERR)
  //~ {
    //~ fprintf(stderr, "%s -- Canno't set signal handler for SIGTERM\n",
      //~ PROGRAM_NAME);
    //~ return 2;
  //~ }
  //~ /* Set signal handlers */
  
  //~ filename = "/tmp/dirtest";
  //~ /* Assign the filename */
  
  //~ if (stat(filename, &buf) != 0)
  //~ {
    //~ fprintf(stderr, "Error retrieving status of file: %s\n", filename);
  //~ }
  //~ /* Retrieve the status */
  //~ lastaccess = buf.st_atim;
  
  //~ while (1)
  //~ {
    //~ if (stat(filename, &buf) != 0)
    //~ {
      //~ fprintf(stderr, "Error retrieving status of file: %s\n", filename);
    //~ }
    //~ /* Retrieve the status */
    
    //~ if (buf.st_atim.tv_sec != lastaccess.tv_sec || buf.st_atim.tv_nsec != lastaccess.tv_nsec)
    //~ {
      //~ printf("File accessed!\n");
      //~ lastaccess = buf.st_atim;
    //~ }
    //~ /* Access time changed */
    
    //~ usleep(SLEEP_TIME);
    //~ /* A little delay for CPU usage saving */
  //~ }
  //~ /* Stay checking status */

  //~ return 0;
  
//~ }
