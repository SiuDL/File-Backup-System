audit_file="audit-report-$(date +'%d-%m-%Y').txt"
syslog_report="syslog-report-$(date +'%d-%m-%Y').txt"

date=$(date +'%b %-d')

sudo ausearch -ts today -k xml_audit | sudo aureport -f -i  > /home/vboxuser/ca/company_folder/system_reports/$audit_file

sudo cat /var/log/syslog | grep -a "$date.*daemon_logs" > /home/vboxuser/ca/company_folder/system_reports/$syslog_report