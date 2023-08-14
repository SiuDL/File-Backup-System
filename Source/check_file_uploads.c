#include <unistd.h>
#include <syslog.h>

void check_file_uploads(void)
{
   char *distribution_xml = "/home/vboxuser/ca/company_folder/xml_reports/distribution_report.xml";

   char *manufacturing_xml = "/home/vboxuser/ca/company_folder/xml_reports/manufacturing_report.xml";

   char *sales_xml = "/home/vboxuser/ca/company_folder/xml_reports/sales_report.xml";

   char *warehouse_xml = "/home/vboxuser/ca/company_folder/xml_reports/warehouse_report.xml";

   char *files[] = {distribution_xml, manufacturing_xml, sales_xml, warehouse_xml};

   syslog(LOG_INFO, "Checking for department reports");

   for (int i = 0; i < 4; ++i)
   {
      if (access(files[i], F_OK) == -1)
      {
         syslog(LOG_INFO, "File %s has not been uploaded", files[i]);
      }
      else
      {
         syslog(LOG_INFO, "File %s has been uploaded", files[i]);
      }
   }
}
