/*
 * Challenge is won by running this with an EUID of 0.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	if(getuid() == 0){
	    puts("You have won. 99999999 internet points to you!");
	}else{
		puts("Nope, not allowed.");
	        return 1;
	}

    system("/bin/sh"); //Drop to root shell, calling /bin/sh rather than /bin/bash bypasses the normal uid/euid checks that bash normally does
}
