/*
    This code is based stringly off of the base code provided in the
    webpage https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Defining some constants
#define DEFAULT_PROTOCOL 0
#define MAX_CONNECTIONS 5
#define BUFFLEN 256

// This function is used when a system call fails
void error(char *msg) {
    perror(msg);
    exit(1);
}

/*
 * Function:  waitForConnection
 * -----------------------------
 *  waits for a new client to connect
 *
 *  sockfd: socket file descriptor used by server
 *  cli_addr: client address
 *  clilen: client address length
 *
 *  returns: new file descriptor that is used for all new communication
 */
int waitForConnection(int sockfd, struct sockaddr_in cli_addr,
        socklen_t clilen) {
    printf("Waiting for incoming connection\n");
    int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    // accept returns -1 if an error occured
    if (newsockfd < 0) {
        error("ERROR on accept");
        return 0;
    }
    // new socket was created successfully
    else {
        printf("New Connection created with client\n");
        return newsockfd;
    }
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
    // newsockfd = new socket file descriptor
    // portno = port number
    // n = used to determine recieved messages
    int sockfd, newsockfd, portno, n;

    // clilen = client address length
    socklen_t clilen;

    // buffer = char array that holds message contents
    char buffer[BUFFLEN];

    // serv_addr = server address
    // cli_addr = client address
    // initializing these both to 0 to clear warnings
    struct sockaddr_in serv_addr, cli_addr = {0};

    // check to make sure there are enough command line arguments
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    // create new socket
    // AF_INET = internet domain for any two hosts on internet
    // SOCK_STREAM = read characters in continuous stream
    // DEFAULT_PROTOCOL = allow OS to choose appropriate protocol
    sockfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

    // socket() returns negative value if it fails
    if (sockfd < 0) {
        error("ERROR opening socket");
    }
    else {
        printf("Socket created\n");
    }

    // bzero() zeros out all values in a buffer
    // in this case it is zeroing out the server address to zeros
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;

    // INADDR_ANY allows connection to all IPs of machine
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // binds a socket to an address, negative value returned if fails
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    else {
        printf("Bind complete\n");
    }

    // listens on socket for connections
    listen(sockfd,MAX_CONNECTIONS);
    clilen = sizeof(cli_addr);

    // calls waitForConnection to create new socket
    newsockfd = waitForConnection(sockfd, cli_addr, clilen);

    // Loop here to continue the server until user terminates
    while(1) {
        printf("Your message : ");
        bzero(buffer,BUFFLEN);

        // get user input
        fgets(buffer,BUFFLEN-1,stdin);

        // attempt to write message to the socket
        n = write(newsockfd,buffer,strlen(buffer));
        if (n < 0) {
            error("ERROR writing to socket");
        }
        else {
            printf("Message sent to client\n");
        }


        bzero(buffer,BUFFLEN);
        printf("Waiting for client...\n");

        // recv returns 0 if client properly shuts down connection
        // recv returns negative val if error reading from socket
        // else recv will return positive val and message will print on screen
        int n = recv(newsockfd, buffer, BUFFLEN-1, 0);
        if (n == 0) {
            printf("Client closed connection\n");
            newsockfd = waitForConnection(sockfd, cli_addr, clilen);
        }
        else {
            if (n < 0) {
                error("ERROR reading from socket");
            }
            else {
                printf("Client : %s",buffer);
            }
        }
    }
    return 0;
}
