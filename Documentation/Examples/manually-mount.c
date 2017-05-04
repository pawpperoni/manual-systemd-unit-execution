/*
 * manually-mount - Mounts a resource into the specified destination
 * Bruno Mondelo Giaramita
 * 2017-05-04 Escola Del Treball De Barcelona
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>

#define PROGRAM_NAME "manually-mount"
/* The program full name */

#define AUTHORS \
  proper_name("Bruno Mondelo")

#define EXIT_NO_ARGUMENT 146
/* No argument specified to option */

#define EXIT_BAD_OPTION 147
/* Unknown option */

#define EXIT_REQUIRED_ARGUMENT 150
/* Missing required argument */

#define EXIT_BAD_MOUNT 1
/* Error mounting */

static struct option long_options[] =
{
  {"destination", required_argument, 0, 'd'},
  {"file-system", required_argument, 0, 'f'},
  {"help", no_argument, 0, 'h'},
  {"source", no_argument, 0, 's'},
  {0, 0, 0, 0}
};
/* Arguments long options */

void
usage (int status)
{
  if (status != EXIT_SUCCESS)
    fprintf(stderr, "Try '%s --help' for more information\n", PROGRAM_NAME);
  else
    printf("Usage: manually-mount -s|--source DEVICE -d|--destination DIRECTORY [-f|--file-system FILESYSTEM] [-o|--options OPTIONS]\n\
Mounts a resource to the specified destination\n\
\n\
Options:\n\
  -d, --destination <directory>   The destination directory\n\
  -f, --file-system <filesystem>  The filesystem of the resource as specified in '/etc/filesystems'\n\
  -h, --help                      Shows this help and exits\n\
  -o, --options <options>         The mount options, see man mount(8) to the defined options\n\
  -s, --source <device>           The device to be mounted\n\
\n\
Examples:\n\
  manually-mount -s /dev/sdb2 -d /mnt\n\
  manually-mount -s /dev/sdc5 -d /mnt/ext-device -o rw,users -f ext2\n");
  
  exit(status);
  
}

int
main (int argc, char ** argv)
{
  
  int argstatus;
  /* Parse arguments status */
  
  char * source = NULL;
  /* The resource to be mounted */
  
  char * dest = NULL;
  /* The mount point */

  char * typefs = NULL;
  /* The type of the filesystem to be mounted */
  
  while ((argstatus = getopt_long(
    argc, argv, "d:f:hs:", long_options, NULL)) != -1)
  {
    
    switch (argstatus)
    {
      case 'd':
        dest = optarg;
        break;
      case 'f':
        typefs = optarg;
        break;
      case 'h':
        usage(EXIT_SUCCESS);
        break;
      case 's':
        source = optarg;
        break;
      case ':': /* missing argument in option */
        fprintf(stderr, "%s: Option '-%c' requires an argument\n",
          PROGRAM_NAME, argstatus);
        usage(EXIT_NO_ARGUMENT);
        break;
      case '?':
      default: /* invalid option */
        fprintf(stderr, "%s: Bad option '-%c'\n", PROGRAM_NAME, argstatus);
        usage(EXIT_BAD_OPTION);
        break;
    }
    
  }
  /* Parse arguments */
  
  if (source == NULL || dest == NULL || typefs == NULL) {
    fprintf(stderr, "%s: Missing option\n", PROGRAM_NAME);
    usage(EXIT_REQUIRED_ARGUMENT);
  }
  /* Check if there are the required options */
  
  if (mount(source, dest, typefs, 0, NULL) != 0)
  {
    fprintf(stderr, "%s: Failed mounting resource %s "
      "on %s with filesystem %s\n", PROGRAM_NAME, source, dest, typefs);
    fprintf(stderr, "Error (%d) info: %s\n", errno, strerror(errno));
    return EXIT_BAD_MOUNT;
  }
  /* Mount the resource. Failing the mount is a 
     critical error, notify and exit */

  return 0;
  /* No news good news */

}
