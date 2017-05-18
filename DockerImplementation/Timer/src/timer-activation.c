/*
 * timer-activation - Activate a service via a timeout
 * Bruno Mondelo Giaramita
 * 2017-05-17 Escola Del Treball De Barcelona
 * Usage: timer-activation [-t|--timeout SECONDS] [ORDER]...
 * Usage: timer-activation -h|--help
*/

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <signal.h>

#define PROGRAM_NAME "timer-activation"
/* The official program name */

static struct option long_options [] = {
  {"help", no_argument, NULL, 'h'},
  {"timeout", required_argument, NULL, 't'},
  {NULL, 0, NULL, 0}
};

static void
sigterm_handler (int signum)
{
  
  printf("%s: received SIGTERM\n", PROGRAM_NAME);
  /* Stop wait bucle */
  
  exit(0);
  
}
/* SIGTERM handler */

void
usage (int status)
{
  
  if (status == EXIT_FAILURE)
    fprintf(stderr, "Try '%s --help' for more information\n",
      PROGRAM_NAME);
  /* Bad argument, show help command */
  else
  {
    printf("Usage: %s [-t|--timeout SECONDS] [ORDER]...\n", PROGRAM_NAME);
    printf("Usage: %s -h|--help\n", PROGRAM_NAME);
    /* Show usage */
    
    printf("Executes an order by time-based activation\n");
    printf("If no timeout is specified the default is 30 seconds\n");
    /* Show information */
    
    printf("\n\
  -h, --help          Show this help message\n\
  -t, --timeout       Sets the timeout, default: 30 seconds\n");
    /* Show the arguments information */
  }
  /* Show help and usage */
  
  exit(status);
  
}

int
main (int argc, char * argv[])
{
  
  char ** newargv;
  /* The order to execute */
  
  int orderargc;
  /* The order size */
  
  char * order;
  /* The order in one line */
  
  int opt;
  /* Argument option */
  
  int seconds;
  /* The timeout seconds */
  
  seconds = 30;
  /* By default execute order every 30 seconds */
  
  if (signal(SIGTERM, sigterm_handler) == SIG_ERR)
  {
    fprintf(stderr, "%s -- Canno't set signal handler for SIGTERM\n",
      PROGRAM_NAME);
    return 2;
  }
  /* Set signal handlers */
  
  orderargc = argc - 1;
  /* Set order length not counting the executable */
  
  while ((opt = getopt_long(argc, argv, "ht:", long_options, NULL)) != -1)
  {
    switch (opt)
    {
      case 'h':
        usage(EXIT_SUCCESS);
        break;
      case 't':
        seconds = atoi(optarg);
        orderargc = orderargc - 1;
        break;
      default:
        fprintf(stderr, "%s: invalid option -- '%c'\n", PROGRAM_NAME,
          opt);
        usage(EXIT_FAILURE);
        break;
    }
    /* Check the arguments */
    
    orderargc = orderargc - 1;
    /* Erase one orderargc */
  }
  /* Parse arguments */
  
  if (seconds <= 0)
  {
    fprintf(stderr, "%s: timeout = %d: Bad seconds. Must be a natural " 
"number non-zero.\n", PROGRAM_NAME, seconds);
    return -1;
  }
  /* Bad seconds */
  
  newargv = (char **)malloc(sizeof(char) * (orderargc + 2));
  /* Alloc memory for order and arguments */
  
  printf("argc: %d\n", argc);
  printf("orderargc: %d\n", orderargc);
  printf("%d\n", argc - orderargc);

  for (int i = 0; i < argc - orderargc; i++)
    newargv[i] = argv[orderargc + i];
  /* Parse order */
  
  printf("%s\n", newargv[0]);
  return 0;
  return 0;
  newargv[argc] = NULL;
  /* The last element must be a NULL pointer */
  
  for (int i = 0; i < 10; i++)
    printf("%s\n", newargv[i]);
  
  return 0;
  
  while (1)
  {
    sleep(seconds);
    printf("Executing order\n");
  }
  /* Sleep and execute order */
  
  return 0;
  
}
