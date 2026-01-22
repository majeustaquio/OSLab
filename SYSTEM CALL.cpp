#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  // Needed for wait() function

int main(int argc, char *argv[])
{
    pid_t pid;  // Variable to store process ID

    // First fork: create a child process
    pid = fork();

    if (pid < 0) // fork() returns negative if it fails
    {
        printf("First fork failed\n");
        exit(1);
    }
    else if (pid == 0) // This block is executed by the **child process**
    {
        printf("Child process: PID=%d, Parent PID=%d\n", getpid(), getppid());

        // Second fork: create a grandchild process from the child
        pid_t gpid = fork();

        if (gpid < 0) // Check if grandchild creation failed
        {
            printf("Second fork failed\n");
            exit(1);
        }
        else if (gpid == 0) // This block is executed by the **grandchild**
        {
            printf("Grandchild process: PID=%d, Parent PID=%d\n", getpid(), getppid());

            // Example of executing a command in grandchild
            execlp("whoami", "whoami", NULL);  // Executes 'whoami' command
            // If execlp fails, this line runs
            printf("execlp failed\n");
            exit(1);
        }
        else // This block is executed by the **child** (after creating grandchild)
        {
            // Wait for grandchild to finish
            wait(NULL);
            printf("Child process finished waiting for grandchild\n");
            exit(0); // Child exits
        }
    }
    else // This block is executed by the **parent process**
    {
        printf("Parent process: PID=%d\n", getpid());
        // Wait for child to finish
        wait(NULL);
        printf("Parent process finished waiting for child\n");
        exit(0); // Parent exits
    }
}

//whoami will simply show which user the grandchild is running under.