#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(2, "Usage: sleep <number of seconds>\n");
        exit(1);
    }
    int seconds = atoi(argv[1]);
    if (seconds <= 0) {
        fprintf(2, "Invalid number of seconds: %s\n", argv[1]);
        exit(1);
    }
    fprintf(1, "Wait %s second\n", argv[1]);
    int ticks = seconds * 100;
    sleep(ticks);
    exit(0);
}
