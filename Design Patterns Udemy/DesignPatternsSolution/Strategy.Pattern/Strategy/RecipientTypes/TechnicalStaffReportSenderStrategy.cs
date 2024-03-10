using Strategy.Pattern.Strategy.ReportTypes;

namespace Strategy.Pattern.Strategy.RecipientTypes;
public class TechnicalStaffReportSenderStrategy : ReportSenderStrategy
{
    protected override void AssignRecipients(ReportBase report)
    {
        report.Recipients = new List<string> { "technical1", "technical2" };
    }
}
