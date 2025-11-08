#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    char message[] = "Hello from Parent!";
    char buffer[50];

    if(pipe(pipefd) == -1) {
        printf("Pipe creation failed!\n");
        return 1;
    }

    pid_t pid = fork();

    if(pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }

    if(pid == 0) {
        // Child Process
        close(pipefd[1]);               // Close write end
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(pipefd[0]);
    } else {
        // Parent Process
        close(pipefd[0]);               // Close read end
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);
    }

    return 0;
}
