namespace Strategy.Pattern.Strategy.ReportTypes;
public class DailyReportTypeStrategy : IReportTypeStrategy
{
    public (string title, string body, string summary) PrepareReport()
        => ("Daily Report", null, null); 
}
