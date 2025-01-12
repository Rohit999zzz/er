#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>

int main() {
    int udp_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024] = {0};

    // Create socket
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to IP and port
    if (bind(udp_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(1);
    }
    printf("UDP server is listening on port 8080...\n");

    // Receive data from client
    addr_size = sizeof(client_addr);
    recvfrom(udp_sock, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size);
    printf("Received from client: %s\n", buffer);

    // Send response to client
    char *response = "Hello from UDP server!";
    sendto(udp_sock, response, strlen(response), 0, (struct sockaddr*)&client_addr, addr_size);

    // Close socket
    close(udp_sock);

    return 0;
}


#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>

int main() {
    int udp_sock;
    struct sockaddr_in server_addr;
    socklen_t addr_size;
    char buffer[1024] = {0};

    // Create socket
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send data to server
    char *message = "Hello from UDP client!";
    addr_size = sizeof(server_addr);
    sendto(udp_sock, message, strlen(message), 0, (struct sockaddr*)&server_addr, addr_size);

    // Receive response from server
    recvfrom(udp_sock, buffer, 1024, 0, NULL, NULL);
    printf("Received from server: %s\n", buffer);

    // Close socket
    close(udp_sock);

    return 0;
}



