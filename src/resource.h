/*
 * msued - Set of structs for resources
 * Bruno Mondelo Giaramita
 * 2017-05-08 Escola Del Treball De Barcelona
*/

#include <stdio.h>

struct socketresource {
  
  char *    service; /* Service to start on socket-based activation */
  
};


typedef struct serviceresource_t serviceresource;
struct serviceresource_t {
  
  pid_t     pid;    /* The PID of the order */
  char *    binary; /* The path of the binary file to start */
  int       status; /* The status of the service, 0 - dead, 1 - alive */
  
};
