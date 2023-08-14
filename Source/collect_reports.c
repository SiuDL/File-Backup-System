#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>

void collect_reports(void)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        syslog(LOG_INFO, "Collecting Department Reports");
        char *args[] = {"/bin/sh", "/home/vboxuser/ca/scripts/collect_reports.sh", NULL};
        execvp(args[0], args);
    }
    else
    {
        int status;
        pid_t child_pid = wait(&status);

        if (child_pid == -1)
        {
            syslog(LOG_ERR, "collect_reports.c: wait() failed");
        }
        else if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
            {
                syslog(LOG_ERR, "ERROR: Failed to retrieve department reports, STATUS: %d", exit_status);
            }
            else
            {
                syslog(LOG_INFO, "Successfully collected reports from upload directory, STATUS: %d", exit_status);
            }
        }
        else
        {
            syslog(LOG_ERR, "ERROR: Report collection process failed due to abnormal termination");
        }
    }
}
