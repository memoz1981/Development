using Strategy.Pattern.Strategy.ReportTypes;

namespace Strategy.Pattern.Strategy.RecipientTypes;
public class ExternalReportSenderStrategy : ReportSenderStrategy
{
    protected override void AssignRecipients(ReportBase report)
    {
        report.Recipients = new List<string> { "external1", "external2" };
    }
}

