namespace Strategy.Pattern.Strategy.ReportTypes;
public class WeeklyReportTypeStrategy : IReportTypeStrategy
{
    public (string title, string body, string summary) PrepareReport()
        => ("Weekly Report", null, null);
}
