#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int status;
    int pid = fork();
    if (pid == 0) {
        printf("I am the child (%d)\n", getpid());
        int grandchild_pid = fork();
        if (grandchild_pid == 0) {
            printf("I am the grandchild (%d)\n", getpid());
        } else if (grandchild_pid > 0) {
            waitpid(grandchild_pid, &status, 0);
        } else {
            perror("fork");
            exit(1);
        }
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        printf("I am the parent (%d)\n", getpid());
    } else {
        perror("fork");
        exit(1);
    }
    return 0;
}