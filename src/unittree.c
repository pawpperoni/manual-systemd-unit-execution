/*
 * Shows all the sub-targets from a unit
*/

#include <stdio.h> 
#include <stdlib.h> // System Variables
#include <getopt.h> //Argparse
#include <string.h> // Work with strings
#include "array.h" // Array

#define PROGRAM_NAME "unittree"

#define AUTHORS \
    proper_name("Bruno Mondelo")


int strstart (const char * phrase, const char * prefix) {
    
    /*
     * Function to check if a string starts with a prefix
     * Input: char *, char *
     * Output: Int
                0 -> Contains
                1 -> Not contains
    */
    
    // The phrase should be greate than the prefix
    if (strlen(phrase) < strlen(prefix))
        return 1;
    
    // Prove if the prefix characters are the same
    if (strncmp(prefix, phrase, strlen(prefix)) == 0)
        return 0;
        
    return 1;
    
}

int printm (FILE * stream, int times, char * character) {

	int printed_chars = 0;

	for (int i = 0; i < times; i++) {
		printed_chars = printed_chars + fprintf(stream, "%s", character);
	}

	return printed_chars;

}

char * afterline (char * unitname) {
    
    /*
     * Returns the after dependences given the unit name
     * Input: char *
     * Output: char *
    */
    
    FILE * ff;
    char etcfile[33] = "/etc/systemd/system/";
    char usrfile[33] = "/usr/lib/systemd/system/";
    
    char line[1024];
    
    int is_not_found = 1;
    char * after_line = malloc(sizeof(char) * 1024);
    
    // Try to open the file on '/etc', if it is not
    // possible, try to open on '/usr' if not, return
    // errror.
    strcat(etcfile, unitname);
    if ((ff = fopen(etcfile, "r")) != NULL) {
    }
    else {
        strcat(usrfile, unitname);
        if ((ff = fopen(usrfile, "r")) == NULL) {
            return NULL;
        }
    }
    
    // Search for 'After' configuration of unit
    // and search sub-dependences
    // Split first with '=' then with ' ' to get
    // all subdependences
    while (is_not_found && (fgets(line, sizeof(line), ff)) != NULL) {
        if ((strstart(line, "After=")) == 0) {
            strcpy(after_line, line);
            is_not_found = 0;
        }
    }
    
    fclose(ff);
    
    after_line[strlen(after_line) - 1] = '\0';
    
    return after_line;
    
}

array * deplist (char * depline) {
    
    /*
     * Creates an array of a dependence list
     * Input: char *
     * Output: array *
    */
    
    // Create array
    array * array_dependence;
    
    a_init(array_dependence, 0);
    
    char * token = strtok(depline, " \t");
    while (token) {
        printf("%s\n", token);
        token = strtok(NULL, " \t");
    }
    
    return NULL;
}

int dependece_tree (char * unit, int tree_level) {
    
    /*
     * Shows a tree from all the unit dependences
     * Input: char *, int
     * Output: Int
                0 -> Okey
                1 -> Canno't Open File, Unit exists?
    */
    
    // Get after line
    char * after_line = afterline(unit);
    if (after_line != NULL)
        printf("%s\n", afterline(unit));
    else
        return 1;
        
    // Convert to array
    //~ deplist(after_line);
    
    return 0;
    
}
    
int main (int argc, char * * argv) {
    
    char * argument = argv[1];
    
    printf("%s\n", argument);
    if ((dependece_tree(argument, 0)) != 0) {
        fprintf(stderr, "ERROR\n");
        return EXIT_FAILURE;
    }
    
    printf("\n");
    
    return EXIT_SUCCESS;
    
}
