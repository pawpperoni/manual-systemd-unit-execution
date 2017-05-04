/*
 * manually-umount - Umounts a resource
 * Bruno Mondelo Giaramita
 * 2017-05-04 Escola Del Treball De Barcelona
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <errno.h>
#include <string.h>

#define PROGRAM_NAME "manually-umount"
/* The program full name */

#define AUTHORS \
  proper_name("Bruno Mondelo")
  
#define EXIT_BAD_UMOUNT 1
/* Failed umounting */

#define EXIT_BAD_ARGUMENT 147
/* Unknown argument */

#define EXIT_BAD_NUMBER_ARGUMENTS 148
/* Bad number of arguments */

void
usage (int status)
{
  if (status != EXIT_SUCCESS)
    fprintf(stderr, "Try '%s --help' for more information\n", PROGRAM_NAME);
  else
    printf("Usage: manually-umount RESOURCE\n\
Mounts a resource to the specified destination\n\
\n\
Options:\n\
  -h, --help          Shows this help and exits\n\
\n\
Examples:\n\
  manually-umount /mnt\n");
  
  exit(status);
  
}

int
strstart (const char * phrase, const char * prefix)
{
    
  /*
   * Function to check if a string starts with a prefix
   * Input: char *, char *
   * Output: Int
              1 -> Contains
              0 -> Not contains
  */

  if (strlen(phrase) < strlen(prefix))
      return 0;
  /* The phrase is greater than the prefix */

  if (strncmp(prefix, phrase, strlen(prefix)) == 0)
      return 1;
  /* Check if the prefix is there */
      
  return 0;
    
}

int
main (int argc, char ** argv)
{
  
  char * resource;
  
  if (argc != 2)
  {
    fprintf(stderr, "%s: Bad usage\n", PROGRAM_NAME);
    usage(EXIT_BAD_NUMBER_ARGUMENTS);
  }
  /* Check maximum arguments */
  
  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    usage(EXIT_SUCCESS);
  else if (strstart(argv[1], "-"))
  {
    fprintf(stderr, "%s: Unknown option %s\n", PROGRAM_NAME, argv[1]);
    usage(EXIT_BAD_ARGUMENT);
  }
  /* In case the argument is '-h' or '--help' print
     help info, if it's other option is a error */
  
  resource = argv[1];
  
  if (umount(resource) != 0) {
    fprintf(stderr, "%s: Failed umounting resource %s\n", PROGRAM_NAME,
      resource);
    fprintf(stderr, "Error (%d) info: %s\n", errno, strerror(errno));
    return EXIT_BAD_UMOUNT;
  }
  /* Umount resource */
  
  return 0;
  /* No news good news */
  
}
