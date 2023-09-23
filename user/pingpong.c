#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int pipes[2]; // Pole pre rúry, index 0 je pre čítanie, index 1 je pre zápis

    pipe(pipes);

    int child_pid = fork(); // Vytvorenie detského procesu

    if (child_pid == -1) {
        exit(0);
    }
    char buffer[20];
    if (child_pid == 0) { // Detský proces

        read(pipes[0], &buffer, sizeof(buffer));

        int  my_pid = getpid();
        printf("%d: received ping\n", my_pid, buffer);
	write(pipes[1], "pong", 4);


        close(pipes[0]);
	close(pipes[1]);
        exit(0);
    } else { // Rodičovský proces


        write(pipes[1],"ping", 4);
        read(pipes[0], buffer, sizeof(buffer));
	int my_pid = getpid();
        printf("%d: received %s\n", my_pid, buffer);

	close(pipes[0]);
        close(pipes[1]); // Zatvoriť zápisný koniec rúry
        exit(0);
    }

    exit(0);
}
