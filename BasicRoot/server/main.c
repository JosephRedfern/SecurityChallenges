/*
 * Vulnerable "echo" server.
 *
 * Based on code taken from here: http://www.binarytides.com/server-client-example-c-sockets-linux/
 */

#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

int main(int argc , char *argv[])
{

    printf("ARGC: %d\n", argc);
    printf("ARGV[1]: %s\n", argv[1]);

    if(argc < 2){
	puts("Need a port, please.");
	return 1;
    }	

    int socket_desc , client_sock , c;
    ssize_t read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
    
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
    
    //Prepare the sockaddr_in structure
    int port = atoi(argv[1]);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( port );
    
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("Bind failed with error");
        return 1;
    }

    printf("Binded to %d...\n", port);
    
    //Listen
    listen(socket_desc , 3);
    
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted, sending MOTD");

    char* MOTD = "Using ground-breaking LINUX Bash Shell technology, we are able to provide you with this ultra-secure echo server implementation.\nSimply enter your message, hit enter and we'll print it right back!\n\n\n";
    write(client_sock, MOTD, strlen(MOTD));

    puts("MOTD Sent, awaiting input");
    
    //Receive a message from client
    char* buffer[10000];

    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
	char command[10000];
	client_message[strlen(client_message)-1] = '\0';

	sprintf(command, "echo %s", client_message);
	
	printf("Running: \"%s\"\n", command);

        FILE* pipe = popen(command, "r");
        if (!pipe){
		perror("Failed to open pipe");
		return 1;
	}

    fgets(buffer, 10000, pipe);
	pclose(pipe);

	puts(buffer);
	write(client_sock, buffer, strlen(buffer));

    memset(client_message, 0, sizeof(client_message)); //Zero out
	memset(buffer, 0, sizeof(buffer)); //Zero out

    }
    
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
    
    return 0;
}
