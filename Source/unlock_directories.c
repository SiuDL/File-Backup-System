
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>

void unlock_directories()
{
    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        syslog(LOG_ERR, "ERROR: Forking process in unlock_directories.c failed");
    }
    else if (pid == 0)
    {
        syslog(LOG_INFO, "Unlocking directories");
        char *unlock = "/home/vboxuser/ca/scripts/unlock_directories.sh";
        char *args[] = {"/bin/sh", unlock, NULL};
        execvp(args[0], args);
    }
    else
    {
        int status;
        pid_t child_pid = wait(&status);

        if (child_pid == -1)
        {
            syslog(LOG_ERR, "unlock_directories: wait() failed");
        }
        else if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
            {
                syslog(LOG_ERR, "ERROR: Unlocking directories failed, STATUS: %d", exit_status);
            }
            else
            {
                syslog(LOG_INFO, "Directories successfully unlocked, STATUS: %d", exit_status);
            }
        }
        else
        {
            syslog(LOG_ERR, "ERROR: Unlocking directories failed due to abnormal termination");
        }
    }
}
