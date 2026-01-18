#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void reverse(char str[]) {
    int i, j;
    char temp;
    for (i = 0, j = strlen(str)-1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main() {
    int sockfd;
    struct sockaddr_in server, client;
    socklen_t len;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    printf("UDP Iterative Server waiting...\n");

    while (1) {
        len = sizeof(client);
        recvfrom(sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr*)&client, &len);

        reverse(buffer);

        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr*)&client, len);
    }
}
