Author: Jordan Menchen

Program Description:
    This program serves as a basic client-server chat application. Any user
    can run a server on a certain port, and as long as the user is on the same
    network and knows the hostname of the computer running the server, then
    they can type messages back and forth until they choose to shut down the
    server or close the connection.

How to Run:
    I have provided a Makefile for the program which makes compiling and running
    a piece of cake. Make sure to follow the steps in order.

    1) To COMPILE: Make sure you are located in the directory of the two C files
    and the Makefile and type "make" into the command line, then press enter.
    This will compile the files and return two executable files, each named
    "server" and "client" for their respective files.

    2) To START SERVER: After typing "make", simply type the following command
    into the command line: "./server PORTNUM" where PORTNUM can be any number
    between 2000 and 65535. If the port you call is already in use, the program
    will print an error message and you will just need to run the command again
    with a new port number. Upon success, the screen will print out the steps
    and end with "Waiting for incoming connection".

    3) To CONNECT CLIENT: After starting the server, the client only needs to
    know two pieces of information to connect to it: hostname and port number.
    We are assuming these pieces of information can be shared between users. To
    find the hostname of the machine running the server, the user can type the
    command "hostname" on the command line of the machine they are using as the
    server and it will print the hostname of that machine. The client will use
    this along with the port number to connect. After the client learns the
    hostname and port number, simply type the following command to connect to
    the server: "./client HOSTNAME PORTNUM" where HOSTNAME is the hostname of
    the server and PORTNUM is the port number the server is listening on. The
    program will let the user know if the connection is successful or not.

How It Works:
    Upon a successful connection between the server and client, the client will
    wait for the server to send the first message. Upon receiving the first
    message, the client can then respond back to the server, and this can be
    repeated as long as the server is still running and no errors occur. To stop
    chatting and disconnect as a CLIENT, simply respond to the server with the
    message "!QUIT" and the connection will close. Upon the CLIENT closing a
    connection, the server will recognize this and simply wait for a new
    connection.

IMPORTANT NOTES:
    - PORT NUMBER and HOSTNAME must be known information on both sides
    - Both SERVER and CLIENT MUST be on the same network
    - Server will run and listen forever until user uses the command "ctrl+c"
    - You can only send one message at a time
    - Server can handle only one connection at a time
