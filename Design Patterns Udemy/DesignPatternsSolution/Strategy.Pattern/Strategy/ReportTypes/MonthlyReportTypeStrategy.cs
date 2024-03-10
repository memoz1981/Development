namespace Strategy.Pattern.Strategy.ReportTypes;
public class MonthlyReportTypeStrategy : IReportTypeStrategy
{
    public (string title, string body, string summary) PrepareReport()
        => ("Monthly Report", null, null);
}
