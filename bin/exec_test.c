/* exec() test */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char argv[]) {
    
    printf("This is the parent program!\n");
    
    execl("/bin/echo", "/bin/echo", "Hello World!", (char *) 0);
    
    execl(argv, (char *) 0);
    
    printf("Bye bye\n");
    
    return 0;
    
}
