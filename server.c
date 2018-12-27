#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

int main(){
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(server_socket < 0) {
        printf("Socket creation failed.\n");
        return -1;
    }
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3000);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    int binding = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    
    if(binding < 0) {
        printf("Bind failed.\n");
        return -1;
    }
    
    int listening = listen(server_socket,1);
    
    if(listening < 0) {
        printf("Listen failed.\n");
        return -1;
    }
    
    int client_socket = accept(server_socket, NULL, NULL);

    if(client_socket < 0) {
        printf("Accept failed.\n");
        return -1;
    }

    int operation[3];
    int server_message;
    
    recv(client_socket, operation, sizeof(operation), 0);
    
    while(operation[0] != 0) {
        printf("Operation received: %d", operation[1]);
        switch(operation[0]) {
            case 1: server_message = operation[1] + operation[2];
                    printf(" + ");
                    break;
            case 2: server_message = operation[1] - operation[2];
                    printf(" - ");
                    break;
            case 3: server_message = operation[1] * operation[2];
                    printf(" * ");
                    break;
            case 4: server_message = operation[1] / operation[2];
                    printf(" / ");
                    break;
        }
        printf("%d\n", operation[2]);
        
        printf("Operation result: %d\n", server_message);
        send(client_socket, &server_message, sizeof(server_message), 0);
        
        recv(client_socket, operation, sizeof(operation), 0);
        
    }
    
    close(server_socket);
    
    return 0;
}
