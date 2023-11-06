#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main() {
    int piperw[2];

    pipe(piperw);

    int child_pid = fork();

    if (child_pid == -1) {
        exit(0);
    }
    char buffer[20];
    if (child_pid == 0) {

        read(piperw[0], &buffer, sizeof(buffer));

        int  my_pid = getpid();
        printf("Child pid = %d: prečítal: %s\n", my_pid, buffer);
	write(piperw[1], "pong", 4);

        close(piperw[0]);
	close(piperw[1]);
        exit(0);
    } else {

        write(piperw[1],"ping", 4);
        read(piperw[0], buffer, sizeof(buffer));
        int my_pid = getpid();

        printf("Parent pid = %d prečítal: %s\n", my_pid, buffer);

	close(piperw[0]);
        close(piperw[1]);
        exit(0);
    }
    exit(0);
}
