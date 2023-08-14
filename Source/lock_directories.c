#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>

void lock_directories()
{
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		syslog(LOG_ERR, "ERROR: Forking process in lock_directories.c failed");
	}
	else if (pid == 0)
	{
		syslog(LOG_INFO,"Locking directories");
		char *upload_dir = "/home/vboxuser/ca/company_folder/xml_reports";
		char *dashboard_dir = "/home/vboxuser/ca/company_folder/dashboard";
		char *args[] = {"/bin/chmod", "550", upload_dir, dashboard_dir, NULL};
		execvp(args[0], args);
	}
	else
	{
		int status;
        pid_t child_pid = wait(&status);

		if (child_pid == -1)
		{
			syslog(LOG_ERR, "lock_directories: wait() failed");
		}
		else if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);
			if (exit_status != 0)
			{
				syslog(LOG_ERR, "ERROR: locking directories failed, STATUS: %d", exit_status);
			}
			else
			{
				syslog(LOG_INFO, "Directories are locked until data transfer and backup is completed, STATUS: %d", exit_status);
			}
		}
		else
		{
			syslog(LOG_ERR, "ERROR: locking directories failed due to abnormal termination");
		}
	}
}