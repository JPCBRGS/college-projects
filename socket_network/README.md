# Computer Networking Using Sockets
This is a project to simulate a communication between client and server using the client.py and server.py files. It applies knowledge from general network computing with sockets, and uses some other concepts such as data structures and exception handling.

## How To Run and Use The Project
First, you need to run the ***server.py*** and then, the ***client.py*** file. When you start a client, you'll be asked an username, and after you input this, the client will then be connected to the server. You can send messages just by typing anything, and your message will be shown to other clients that are connected since the server can be connected to multiple clients at the same time as the code supports threading. Also, there are several commands that can be used by the clients:\
**/LIST:** Lists all clients that are currently connected to the server;\
**/FILE:** Sends a file on the ***client_files*** folder to the server (which stores files in the *server_files* folder);\
**/GET:** Used to retrieve an image that is on the ***server_files*** folder;\
**/BYE:** Ends the connection to the server.