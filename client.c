#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

int main(){
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    if(client_socket < 0) {
        printf("Socket creation failed.\n");
        return -1;
    }
    
    char ip[16];
    printf("Server's IP address: ");
    scanf("%15s", ip);
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3000);
    server_address.sin_addr.s_addr = inet_addr(ip);
    
    int connection = connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    
    if(connection < 0) {
        printf("Connection failed.\n");
        return -1;
    }
    
    int operation[3];
    int server_response;
    
    printf("\nThis is a calculator.\n");
    printf("0. Exit\n");
    printf("1. +\n");
    printf("2. -\n");
    printf("3. *\n");
    printf("4. /\n");
    
    while(1) {
        printf("\nChoose an operator: ");
        scanf("%d", &operation[0]);

        if(operation[0] > 4) {
            printf("Please choose again.\n");
            continue;
        } else if(operation[0] != 0) {            
            printf("Input 1st operand: ");
            scanf("%d", &operation[1]);
            printf("Input 2nd operand: ");
            scanf("%d", &operation[2]);
        }

        if(operation[0] == 4 && operation[2] == 0) {
            printf("Division by 0. Please try again.\n");
            continue;
        } else {
            send(client_socket, operation, sizeof(operation), 0);

            if(operation[0] == 0) break;

            recv(client_socket, &server_response, sizeof(server_response), 0);
            printf("Operation result: %d\n", server_response);
        }
    }
        
    close(client_socket);
    
    return 0;
}
