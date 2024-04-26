<p align="center">
  <img src="https://github.com/ayogun/42-project-badges/blob/main/badges/minitalkm.png?raw=true" alt="minitalk"/>
</p>

<p align="center">
  Score: <i>125/100</i><br>
  Finished: <i>25.04.2024</i>
</p>

# minitalk
*The purpose of this project is to code a small data exchange program
using UNIX signals.*

# How to use
Use `make` to compile the program. The server and client executables will be created.
Run the server with `./server` and the client with `./client [server_pid] [message]`.

# Example
```bash
$ ./server
Server PID: 1234
```

```bash
$ ./client 1234 "Hello, world!"
```

After recieving the whole message, the server will print it out.
The server confirms every bit as well as the reception of the whole message to the client.