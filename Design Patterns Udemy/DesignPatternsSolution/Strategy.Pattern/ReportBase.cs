namespace Strategy.Pattern;
public abstract class ReportBase
{
    public ReportBase(string title, string body, string summary, string problems, 
        IEnumerable<string> recipients)
    {
        Title = title;
        Body = body;
        Recipients = recipients;
    }
    
    public string Title { get; set; }

    public string Body { get; set; }

    public string Summary { get; set; }

    public string Problems { get; set; }

    public IEnumerable<string> Recipients { get; set; }

    public abstract void PrepareReport(ReportType reportType);

    public abstract void SendReport(RecipientType recipientType); 
}
