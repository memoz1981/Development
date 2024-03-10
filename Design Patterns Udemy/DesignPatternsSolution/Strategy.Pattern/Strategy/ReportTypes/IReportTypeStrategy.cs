namespace Strategy.Pattern.Strategy.ReportTypes;
public interface IReportTypeStrategy
{
    (string title, string body, string summary) PrepareReport(); 
}
