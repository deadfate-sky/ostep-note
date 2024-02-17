#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("Parent process (pid:%d)\n", (int)getpid());

    int rc1 = fork();
    if (rc1 < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc1 == 0)
    {
        // first child process
        printf("First child process (pid:%d)\n", (int)getpid());
        sleep(1);
    }
    else
    {
        // parent process
        int rc2 = fork();
        if (rc2 < 0)
        {
            // fork failed; exit
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        else if (rc2 == 0)
        {
            // second child process
            printf("Second child process (pid:%d)\n", (int)getpid());
            sleep(2);
        }
        else
        {
            // parent process
            int wc = wait(NULL);
            printf("Child process %d has ended\n", wc);
            wc = wait(NULL);
            printf("Child process %d has ended\n", wc);
        }
    }

    return 0;
}