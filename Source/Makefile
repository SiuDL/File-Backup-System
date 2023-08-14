CC = gcc
CFLAGS = -Wall -Wextra
objects = daemon.o collect_reports.o backup_dashboard.o lock_directories.o unlock_directories.o generate_reports.o check_file_uploads.o sig_handler.o update_timer.o 
headers = daemon_tasks.h

daemon: $(objects)
	$(CC) $(CFLAGS) -o daemon $(objects)

daemon.o: daemon.c $(headers)
	$(CC) $(CFLAGS) -c daemon.c

collect_reports.o: collect_reports.c $(headers)
	$(CC) $(CFLAGS) -c collect_reports.c 

backup_dashboard.o: backup_dashboard.c $(headers)
	$(CC) $(CFLAGS) -c backup_dashboard.c 

lock_directories.o: lock_directories.c $(headers)
	$(CC) $(CFLAGS) -c lock_directories.c	 

unlock_directories.o: unlock_directories.c $(headers)
	$(CC) $(CFLAGS) -c unlock_directories.c

generate_reports.o: generate_reports.c $(headers)
	$(CC) $(CFLAGS) -c generate_reports.c

check_file_uploads.o: check_file_uploads.c $(headers)
	$(CC) $(CFLAGS) -c check_file_uploads.c
	

sig_handler.o: sig_handler.c $(headers)
	$(CC) $(CFLAGS) -c sig_handler.c

update_timer.o: update_timer.c $(headers)
	$(CC) $(CFLAGS) -c update_timer.c

clean:
	rm -f $(objects) daemon
