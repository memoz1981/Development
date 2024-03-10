namespace Strategy.Pattern;

//Analysis, thoughts...
//the class has followings: properties to define a report, methods to prepare
//a report based on the report type, and other methods to send the report to 
//corresponding recipients based on the recipient type
//too much responsibility for a class
//any new report type and recipient type will break the code
//interface segregation not followed. 

public class ReportWithoutStrategy : ReportBase
{
    public ReportWithoutStrategy(string title = null, string body = null, string summary = null, string problems = null,
        IEnumerable<string> recipients = null) 
        : base(title, body, summary, problems, recipients) { }

    public ReportWithoutStrategy() : this(null, null, null, null, null) {}

    public override void PrepareReport(ReportType reportType)
    {
        switch(reportType) 
        {
            case ReportType.Daily:
                PrepareDailyReport();
                break;

            case ReportType.Weekly:
                PrepareWeeklyReport();
                break;
            case ReportType.Monthly:
                PrepareMonthlyReport();
                break;

            case ReportType.Yearly:
                PrepareYearlyReport();
                break;

            default:
                throw new InvalidOperationException(); 
        }; 
    }

    private void PrepareYearlyReport()
    {
        Title = "Yearly Report"; 
    }

    private void PrepareMonthlyReport()
    {
        Title = "Monthly Report";
    }

    private void PrepareWeeklyReport()
    {
        Title = "Weekly Report";
    }

    private void PrepareDailyReport()
    {
        Title = "Daily Report";
    }

    public override void SendReport(RecipientType recipientType)
    {
        switch (recipientType)
        {
            case RecipientType.TechnicalStaff:
                SendTechnicalStaffEmail();
                break;

            case RecipientType.Management:
                SendManagementEmail();
                break;
            case RecipientType.External:
                SendExternalEmail();
                break;

            default:
                throw new InvalidOperationException();
        };
    }

    private void SendExternalEmail()
    {
        Recipients = new List<string> { "external1", "external2"};
        SendEmail();
    }

    private void SendManagementEmail()
    {
        Recipients = new List<string> { "management1", "management2" };
        SendEmail();
    }

    private void SendTechnicalStaffEmail()
    {
        Recipients = new List<string> { "technical1", "technical2" };
        SendEmail();
    }

    private void SendEmail()
    {
        //code to send email
    }
}
