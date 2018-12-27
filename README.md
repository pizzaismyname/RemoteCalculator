# RemoteCalculator
A remote calculator using C over Linux/UNIX OS.
# Application Manual
1. Open terminal
2. Compile each code (skip this step if you already downloaded the compiled code)
```
gcc -o server server.c
gcc -o client client.c
```
3. Run server program
```
./server
```
4. Open another tab on terminal and run client program
```
./client
```
5. Input the server's IP address (in this program I'm using localhost)
> 127.0.0.1
6. Use the calculator! Press 0 to exit.
