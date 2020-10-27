/*
    This code is based stringly off of the base code provided in the
    webpage https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// Define constants
#define EXITSTR "!QUIT\n"
#define DEFAULT_PROTOCOL 0
#define BUFFLEN 256

// This function is used when a system call fails
void error(char *msg) {
    perror(msg);
    exit(0);
}

/*
 * Function:  main
 * ----------------
 *  driver function for program
 *
 *  argc: number of arguments passed in command line
 *  argv: array that holds values for command line arguments
 *
 *  returns: 0 once completed
 */
int main(int argc, char *argv[])
{
    // sockfd = socket file descriptor
    // portno = port number
    // n = used to determine recieved messages
    int sockfd, portno, n;

    // serv_addr = server address
    struct sockaddr_in serv_addr;

    // server = defines host computer on the internet
    struct hostent *server;

    // buffer to hold the messages
    char buffer[BUFFLEN];

    // check to make sure there are enough command line arguments
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    // convert string argument to an int for the port number
    portno = atoi(argv[2]);

    // create new socket
    // AF_INET = internet domain for any two hosts on internet
    // SOCK_STREAM = read characters in continuous stream
    // DEFAULT_PROTOCOL = allow OS to choose appropriate protocol
    sockfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }
    else {
        printf("Socket created\n");
    }

    // server val determined by command line argument
    server = gethostbyname(argv[1]);

    // check validity of server name
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    // set fields in serv_addr after zeroing them out
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
    serv_addr.sin_port = htons(portno);

    // Connect to the server
    printf("Connecting to server...\n");
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }
    else {
        printf("Connected to server\n");
    }

    // Loops in this until the user types the exit string
    while (1) {
        bzero(buffer,BUFFLEN);

        //waits for server message first
        printf("Waiting for server...\n");
        n = read(sockfd,buffer,BUFFLEN-1);
        if (n < 0) {
             error("ERROR reading from socket");
        }
        else {
            printf("Server : %s",buffer);
        }
        printf("Your message : ");
        bzero(buffer,BUFFLEN);
        char *message = fgets(buffer,BUFFLEN-1,stdin);
        // NOTE: fgets includes the new line at the end
        if (strcmp(message, EXITSTR) == 0) {
            if (shutdown(sockfd, SHUT_RDWR) == 0) {
                printf("Connection closed...\n");
                exit(0);
            }
            else {
                error("ERROR unable to close connection");
            }
        }
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0) {
            error("ERROR writing to socket");
        }
        else {
            printf("Message sent to server\n");
        }
    }
    return 0;
}
