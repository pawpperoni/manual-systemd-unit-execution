/*
 * path-activation - Activate a service via a path access
 * Bruno Mondelo Giaramita
 * 2017-05-18 Escola Del Treball De Barcelona
 * Usage: path-activation -f|--file FILE [-a|--atime] [-m|--mtime] [-c|--ctime] ORDER...
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>


#define PROGRAM_NAME "path-activation"
/* The official program name */

#define SLEEP_TIME 5000
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
  
  char ** order;
  /* The order string array */
  
  struct stat buf;
  /* The file status */
  
  struct timespec lastaccess;
  /* Last access time */
  
  struct timespec lastmodify;
  /* Last modify time */
  
  struct timespec lastchange;
  /* Last change time */
  
  int atime;
  /* Access time option */
  
  int mtime;
  /* Modify time option */
  
  int ctime;
  /* Change time option */
  
  int execute;
  /* The execute parameter */
  
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
  
  order = (char **)malloc(sizeof(char *) * (argc - optind + 1));
  /* Alloc memory for order */
  
  for (int i = 0; i < argc - optind; i++)
    order[i] = argv[optind + i];
  /* Add arguments to list */
  
  order[argc - optind + 1] = NULL;
  //~ /* The last item must be a NULL pointer */
  
  if (stat(filename, &buf) != 0)
  {
    fprintf(stderr, "Error retrieving status of file: %s\n", filename);
    return 45;
  }
  /* Retrieve the start status */
  
  lastaccess = buf.st_atim;
  lastmodify = buf.st_mtim;
  lastchange = buf.st_ctim;
  /* Assign the lasts times */
  
  while (1)
  {
    
    execute = 0;
    
    if (stat(filename, &buf) != 0)
    {
      fprintf(stderr, "Error retrieving status of file: %s\n", filename);
      return 45;
    }
    /* Retrieve the start status */
    
    if (buf.st_atim.tv_sec != lastaccess.tv_sec || buf.st_atim.tv_nsec != lastaccess.tv_nsec)
      if (atime)
      {
        lastaccess = buf.st_atim;
        printf("Change access time\n");
        execute = 1;
      }
    /* Check the access time save new */
    
    if (buf.st_mtim.tv_sec != lastmodify.tv_sec || buf.st_mtim.tv_nsec != lastmodify.tv_nsec)
      if (mtime)
      {
        lastmodify = buf.st_mtim;
        printf("Change modify time\n");
        execute = 1;
      }
    /* Check the modify time save new */
    
    if (buf.st_ctim.tv_sec != lastchange.tv_sec || buf.st_ctim.tv_nsec != lastchange.tv_nsec)
      if (ctime)
      {
        lastchange = buf.st_ctim;
        printf("Change change time\n");
        execute = 1;
      }
    /* Check the change time save new */
    
    if (execute)
    {
      if (fork() == 0)
      {
        execv(order[0], order);
        return 0;
      }
      printf("Executing order\n");
    }
    /* Execute the order */
    
    usleep(SLEEP_TIME);
    /* A little delay for CPU saving */
    
  }
  /* Stay reading the changes */
  
  return 0;
  
}
