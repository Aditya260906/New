#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();     // create child process

    if(pid < 0) {
        printf("Fork failed!\n");
    }
    else if(pid == 0) {
        // Child process
        printf("This is the Child Process\n");
        printf("Child PID: %d\n", getpid());
    }
    else {
        // Parent process
        printf("This is the Parent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID returned by fork(): %d\n", pid);
    }
    return 0;
}
