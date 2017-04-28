/*
 * msued - Daemon to start a set of resources
 * Bruno Mondelo Giaramita
 * 2017-04-28 Escola Del Treball De Barcelona
*/

#include <stdio.h> /* System Input Output */
#include <unistd.h> /* Misc variables and functions */
#include <stdlib.h> /* System Variables */
#include <dirent.h> /* Directory support */
#include <string.h> /* String control */
#include <time.h> /* Actual time */
#include <signal.h> /* Signal handler */
#include <fcntl.h> /* FIFO dependences */
#include <sys/stat.h> /* FIFO structure */

#define PROGRAM_NAME "msued"

#define AUTHORS \
  proper_name("Bruno Mondelo")

// #define LOG_FILE "/var/log/msued.log"
#define LOG_FILE "/tmp/msued.log"
/* The log file */

#define SYSTEM_FIFO "/tmp/msued"
/* FIFO path */

#define BUFFER_FIFO 256
/* FIFO read buffer */

//~ #define RESOURCES_FOLDER "/etc/msued/automatic"
#define AUTOMATIC_RESOURCES_FOLDER "/var/tmp/msued/automatic"
/* Folder with all the resources needed in the startup */

void
sig_handler (int signum)
{
    
  if (signum == SIGINT) {
    fprintf(stderr, "msued: HEY! Error recieved\n");
    exit(EXIT_SUCCESS);
  }
  /* Handling SIGINT signal 2 */
  
}

int
strstart (const char * phrase, const char * prefix)
{
    
  /*
   * Function to check if a string starts with a prefix
   * Input: char *, char *
   * Output: Int
              0 -> Contains
              1 -> Not contains
  */

  if (strlen(phrase) < strlen(prefix))
      return 1;
  /* The phrase is greater than the prefix */

  if (strncmp(prefix, phrase, strlen(prefix)) == 0)
      return 0;
  /* Check if the prefix is there */
      
  return 1;
    
}

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
start_resource (FILE * log_file, char * resource, FILE * resource_file)
{
  
  /*
   * Checks the resource file and determines the process to start it
   * Input: FILE stream pointer, FILE stream pointer
   * Output: Int
  */
  
  int found_type = 1;
  /* The found parameter */
  
  char * line;
  /* The readed line */
  
  size_t len;
  /* The legnth of the line */
  
  ssize_t read;
  /* The readed bytes */
  
  //~ while ((read = getline(&line, &len, resource_file)) != -1) {
    //~ printf("Line: '%s'. Found: %d\n", line, strstart(line, "TYPE"));
  //~ }
  
  while (((read = getline(&line, &len, resource_file)) != -1) && ((found_type = strstart(line, "TYPE")) != 0));
  /* Read line unless we find TYPE */
  
  if (found_type == 1) {
    fprintf(log_file, "%s: [ERROR]: Resource %s, don't contains a TYPE\n", actual_time(), resource);
    return 1;
  }
  /* TYPE not found is an error */
  
  printf("Type: '%s'\n", line);
  
  return 0;
  
}

int
start_automatic (FILE * log_file)
{
    
  /*
   * Starts all startup dependences that system may need
   * Input: File descriptor of the log-file
   * Output: Int
  */
  
  int startup_status = 0;
  /* The exit code */
  
  DIR * dd;
  /* Directory descriptor */
  
  FILE * ff;
  /* Resource descriptor */
  
  struct dirent * filein;
  /* The directory files */
  
  char buffer[100];
  char * resource_filename;
  /* The resource absolute path */
  
  if ((dd = opendir(AUTOMATIC_RESOURCES_FOLDER)) == NULL)
  {
    fprintf(log_file,
          "%s: [ERROR]: Canno't open automatic resources directory: %s\n",
          actual_time(), AUTOMATIC_RESOURCES_FOLDER);
    return 1;
  }
  /* Open directory, not opening is a fatal error */

  while ((filein = readdir(dd)) != NULL)
  {
  /* Read all files from directory */
    if (!strcmp (filein -> d_name, "."))
      continue;
    if (!strcmp (filein -> d_name, ".."))
      continue;
    /* Don't read actual directory and parent dir files */  
    
    resource_filename = malloc(strlen(AUTOMATIC_RESOURCES_FOLDER) + strlen(filein -> d_name) + 2);
    sprintf(resource_filename, "%s/%s", AUTOMATIC_RESOURCES_FOLDER, filein -> d_name);
    /* Create the absolute path of the resource file */
    
    if ((ff = fopen(resource_filename, "r")) == NULL)
    {
      fprintf(log_file, "%s: [ERROR]: Canno't open resource file: %s\n",
                actual_time(), filein -> d_name);
    }
    else {
      if (start_resource(log_file, filein -> d_name, ff) != 0)
      {
        fprintf(log_file, "%s: [ERROR]: Resource %s not started\n",
                actual_time(), filein -> d_name);
      }
      /* Process the resource, notify if it fails */
      
      fclose(ff);
      /* Close file */
    }
    /* Open the resource file, and if works process it */
  }
  
  closedir(dd);
  /* Close directory */

  return startup_status;
    
}

int 
main ()
{
  
  int fifod;
  /* FIFO control */
  
  FILE * logd;
  /* The log-file descriptor */
  
  char commandfifo[BUFFER_FIFO];
  /* The buffer of receiving FIFO */
  
  if ((logd = fopen(LOG_FILE, "a")) == NULL)
  {
    fprintf(stderr, "msued - ERROR: Canno't open log file %s\n", LOG_FILE);
    return -1;
  }
  fprintf(logd, "%s: [DEBUG]: Started daemon!\n", actual_time());
  /* Open log file */
  
  if ((signal(SIGINT, sig_handler)) == SIG_ERR)
    fprintf(logd, "%s: [ERROR]: Can't catch SIGINT\n", actual_time());
  /* Start signal handler */
  
  if (access(SYSTEM_FIFO, F_OK) != 0)
  {
    if ((mkfifo(SYSTEM_FIFO, 0666)) == 0) {
      fprintf(logd, "%s: [DEBUG]: Created FIFO at %s\n", actual_time(), SYSTEM_FIFO);
    }
    else {
      fprintf(logd, "%s: [ERROR]: Canno't create FIFO ad %s\n", actual_time(), SYSTEM_FIFO);
        return 1;
    }
  }
  /* Create FIFO */
  /* If FIFO doesn't exist is a critical error */
  
  if ((fifod = open(SYSTEM_FIFO, O_RDWR)) == -1)
  {
    fprintf(logd, "%s: [ERROR]: Canno't open FIFO at %s\n", actual_time(), SYSTEM_FIFO);
    return 1;
  }
  fprintf(logd, "%s: [DEBUG]: Openned FIFO: %s\n", actual_time(), SYSTEM_FIFO);
  /* Open FIFO in read mode */
  
  if (start_automatic(logd) != 0)
  {
    fprintf(logd, "%s: [ERROR]: Not all startup resources started\n", actual_time());
  }
  /* Start all startup resources */
  /* The startup is a critical point of the process */
  /* If it fails we should notify, that's why is in the same process */
  /* Starting resources after the startup should be in another fork or exec */
  
  return 600;
  
  fprintf(logd, "%s: [DEBUG]: Listening on FIFO: %s\n", actual_time(), SYSTEM_FIFO);
  while (read(fifod, commandfifo, BUFFER_FIFO) > 0)
  {
  /* Stay daemon listening on FIFO */
    commandfifo[strlen(commandfifo) - 1] = '\0';
    /* Erase last '\n' */
    
    fprintf(logd, "%s: [DEBUG]: Received '%s'\n", actual_time(), commandfifo);
    fflush(logd);
    /* Write to log and flush it */
  }
  
  close(fifod);
  /* Close FIFO */
  
  fclose(logd);
  /* Close log file */
  
  fprintf(logd, "%s: [DEBUG]: Ended daemon!\n", actual_time());
  /* Notify log of the end */
  
  return EXIT_SUCCESS;
  
}
