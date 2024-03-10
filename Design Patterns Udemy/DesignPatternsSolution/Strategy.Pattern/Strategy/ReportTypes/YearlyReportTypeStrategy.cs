namespace Strategy.Pattern.Strategy.ReportTypes;
public class YearlyReportTypeStrategy : IReportTypeStrategy
{
    public (string title, string body, string summary) PrepareReport()
        => ("Yearly Report", null, null);
}
