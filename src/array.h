/*
 * Library to create arrays
*/

#include <stdio.h>
#include <stdlib.h>

#define LIBRARY_NAME "array.h"

#define AUTHORS \
    proper_name("Bruno Mondelo")


typedef struct {
    
    char * *    a_array;    // Element
    size_t      a_used;     // Used elements
    size_t      a_size;     // Total size
    
} array;

void * a_init (array * new_array, size_t init_size) {
    
    /*
     * Function to allocate an array in memory
     * Input: array, size_t
     * Output: array pointer
    */
    
    // Initialize the array with the default parameters
    new_array -> a_array = (char * *) malloc(sizeof(char) * init_size);
    new_array -> a_used = 0;
    new_array -> a_size = init_size;
    
}

void * append (array * arrayto_add, char * new_element) {
    
    /*
     * Add a new entry in the array
     * Input: array, char *
     * Output: Pointer to the new item
    */
    
    // If we already used all array memory
    // function allocates new memory to the array
    // else it just adds the new element
    if (arrayto_add -> a_used == arrayto_add -> a_size) {
        arrayto_add -> a_size++;
        arrayto_add -> a_array = realloc(arrayto_add -> a_array, (arrayto_add -> a_size) * sizeof(char));
    }
    
    arrayto_add -> a_array[arrayto_add -> a_used++] = new_element;
    
    return &(arrayto_add -> a_array[arrayto_add -> a_used]);
    
}

// ** Add free function **
