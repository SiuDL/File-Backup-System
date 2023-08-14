#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void backup_dashboard(void)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        syslog(LOG_INFO, "Backup Executing");
        char *args[] = {"/bin/sh", "/home/vboxuser/ca/scripts/backup_dashboard.sh", NULL};
        execvp(args[0], args);
    }
    else
    {
        int status;
        pid_t child_pid = wait(&status);

        if (child_pid == -1)
        {
            syslog(LOG_ERR, "backup_dashboard.c: wait() failed");
        }
        else if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
            {
                syslog(LOG_ERR, "ERROR: Backup process failed, STATUS: %d", exit_status);
            }
            else
            {
                syslog(LOG_INFO, "Dashboard backed up successfully, STATUS: %d", exit_status);
            }
        }
        else
        {
            syslog(LOG_ERR, "ERROR: Backup process failed due to abnormal termination");
        }
    }
}
