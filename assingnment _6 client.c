#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    pid_t pid;

    char buffer[BUFFER_SIZE];
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(1);
    }
    
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(1);
    }
    signal(SIGCHLD, SIG_IGN);

    printf("Server is running on port %d...\n", PORT);

    while (1)
    {
        client_fd = accept(server_fd,
                           (struct sockaddr *)&client_addr,
                           &addr_len);

        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            close(client_fd);
            continue;
        }

        if (pid == 0)
        }
            close(server_fd);

            printf("Client connected. PID = %d\n", getpid());

            while (1)
            {
                memset(buffer, 0, sizeof(buffer));

                int n = recv(client_fd, buffer,
                             BUFFER_SIZE - 1, 0);

                if (n <= 0)
                    break;

                buffer[n] = '\0';
                if (strcmp(buffer, "exit\n") == 0 ||
                    strcmp(buffer, "exit") == 0)
                    break;

                printf("Client query: %s", buffer);
                char response[BUFFER_SIZE];

                snprintf(response, sizeof(response),
                         "Server received: %s", buffer);

                send(client_fd, response,
                     strlen(response), 0);
            }

            printf("Client disconnected. PID = %d\n", getpid());

            close(client_fd);
            exit(0);
        }
        else
        {
            close(client_fd);
        }
    }

    close(server_fd);
    return 0;
}