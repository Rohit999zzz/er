#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024] = {0};

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to IP and port
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(1);
    }

    // Listen for connections
    if (listen(server_sock, 5) == -1) {
        perror("Listen failed");
        exit(1);
    }
    printf("Server is listening on port 8080...\n");

    // Accept client connection
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    if (client_sock == -1) {
        perror("Accept failed");
        exit(1);
    }
    printf("Client connected.\n");

    // Receive data from client
    recv(client_sock, buffer, 1024, 0);
    printf("Received from client: %s\n", buffer);

    // Send response to client
    char *response = "Hello from server!";
    send(client_sock, response, strlen(response), 0);

    // Close sockets
    close(client_sock);
    close(server_sock);

    return 0;
}


#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main() {
    int client_sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // Create socket
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(1);
    }
    printf("Connected to server.\n");

    // Send data to server
    char *message = "Hello from client!";
    send(client_sock, message, strlen(message), 0);

    // Receive response from server
    recv(client_sock, buffer, 1024, 0);
    printf("Received from server: %s\n", buffer);

    // Close socket
    close(client_sock);

    return 0;
}
