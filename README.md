# Basic TCP Socket

## Project Description

Uses TCP sockets to transmit messages between the server in the client using to different processes.

## Installation 

Step-by-step instructions on how to install and setup this project locally.

```
# clone the repository
git clone https://github.com/elijahnash4-droid/basic-tcp-readme-submission.git

# Navigate to the project directory
cd basic-tcp-client-elijahnash4-droid
```

## Usage/Examples
- Open two terminals, make sure they're both in the project directory
- Run `./tcp_server` first on one terminal
- Then run `./tcp_client` on the second terminal
- input a message to send to server

If done correctly here's an example of how it should look on each terminal

### Server side
```
Server is listening on port 43251
Client connected
Message sent: hi
```

### Client side
```
Connected to the server
Enter message: hi
Response from server: Hello, Client!
```

To run the project input `./tcp_server & ./tcp_client` in the terminal.