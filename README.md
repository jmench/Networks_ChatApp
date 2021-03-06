# __Networks_ChatApp__
### Author: Jordan Menchen

__Program Description:__  
This program serves as a basic client-server chat application. Any user can run
a server on a certain port, and as long as the user is on the same network and
knows the hostname of the computer running the server, then they can type
messages back and forth until they choose to shut down the server or close the
connection.

__How to Run:__  
I have provided a _Makefile_ for the program which makes compiling and running
a piece of cake. Make sure to follow the steps in order:

1. __To COMPILE:__ Make sure you are located in the directory of the two C files
and the Makefile and type `make` into the command line, then press enter.
This will compile the files and return two executable files, each named
"server" and "client" for their respective files.

2. __To START SERVER:__ After typing "make", simply type the following command
into the command line: `./server PORTNUM` where `PORTNUM` can be any number
between 2000 and 65535. If the port you call is already in use, the program
will print an error message and you will just need to run the command again
with a new port number. Upon success, the screen will print out the steps
and end with "Waiting for incoming connection".

3. __To CONNECT CLIENT:__ After starting the server, the client only needs to
know two pieces of information to connect to it: hostname and port number.
We are assuming these pieces of information can be shared between users. To
find the hostname of the machine running the server, the user can type the
command "hostname" on the command line of the machine they are using as the
server and it will print the hostname of that machine. The client will use
this along with the port number to connect. After the client learns the
hostname and port number, simply type the following command to connect to
the server: `./client HOSTNAME PORTNUM` where `HOSTNAME` is the hostname of
the server and `PORTNUM` is the port number the server is listening on. The
program will let the user know if the connection is successful or not.

__How It Works:__  
Upon a successful connection between the server and client, the client will
wait for the server to send the first message. Upon receiving the first
message, the client can then respond back to the server, and this can be
repeated as long as the server is still running and no errors occur. To stop
chatting and disconnect as a CLIENT, simply respond to the server with the
message `!QUIT` and the connection will close. Upon the CLIENT closing a
connection, the server will recognize this and simply wait for a new
connection.

__IMPORTANT NOTES:__
* PORT NUMBER and HOSTNAME must be known information on both sides
* Both SERVER and CLIENT MUST be on the same network
* Server will run and listen forever until user uses the command "ctrl+c"
* You can only send one message at a time (server send, then client, then
    server, so on...)
* Server can handle only one connection at a time
