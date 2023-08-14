#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>

void generate_reports(void)
{
    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        syslog(LOG_ERR, "ERROR: Forking process in generate_reports.c failed");
    }
    else if (pid == 0)
    {
        syslog(LOG_INFO, "Generating reports");
        char *args[] = {"/bin/sudo", "/home/vboxuser/ca/scripts/generate_reports.sh", NULL};

        execvp(args[0], args);
    }
    else
    {

        int status;
        pid_t child_pid = wait(&status);

        if (child_pid == -1)
        {
            syslog(LOG_ERR, "generate_reports.c: wait() failed");
        }
        else if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
            {
                syslog(LOG_ERR, "ERROR: Failed to generate reports, STATUS: %d", exit_status);
            }
            else
            {
                syslog(LOG_INFO, "Generated reports successfully, STATUS: %d", exit_status);
            }
        }
        else
        {
            syslog(LOG_ERR, "ERROR: Failed to generate reports due to abnormal termination");
        }
    }
}