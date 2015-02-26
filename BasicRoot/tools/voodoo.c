/*
 * This tool is used to set the SUID bit on executables.
 *
 * For use in the callenge, this executable should have it's SUID bit pre-set. 
 */


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        puts("epic 13333337 SUID bit setter. \nUsage: voodoo <file>.");
	return 1;
    }

    char* cmd[1000];
    sprintf(cmd, "chmod +s %s", argv[1]);
    puts(cmd);
    system(cmd);
}
