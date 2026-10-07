#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

static void print_info(const char *name, clock_t start) {
    clock_t end = clock();
    double ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    printf("%s: PID=%d PPID=%d time=%.3f ms\n",
           name, getpid(), getppid(), ms);
    fflush(stdout);
}

int main(void) {
    pid_t p1 = fork();

    if (p1 < 0) {
        perror("fork1");
        return 1;
    }

    if (p1 == 0) {
        clock_t start = clock();
        print_info("child1", start);
        exit(0);
    }

    pid_t p2 = fork();

    if (p2 < 0) {
        perror("fork2");
        return 1;
    }

    if (p2 == 0) {
        clock_t start = clock();
        print_info("child2", start);
        exit(0);
    }

 
    clock_t start = clock();
    print_info("parent", start);

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);

    return 0;
}
