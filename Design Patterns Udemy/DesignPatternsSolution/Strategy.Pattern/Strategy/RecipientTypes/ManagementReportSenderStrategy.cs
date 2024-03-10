using Strategy.Pattern.Strategy.ReportTypes;

namespace Strategy.Pattern.Strategy.RecipientTypes;
public class ManagementReportSenderStrategy : ReportSenderStrategy
{
    protected override void AssignRecipients(ReportBase report)
    {
        report.Recipients = new List<string> { "management1", "management2" };
    }
}

