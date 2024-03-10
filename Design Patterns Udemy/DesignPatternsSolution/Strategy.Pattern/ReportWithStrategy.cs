using Strategy.Pattern.Factories;

namespace Strategy.Pattern;

//Analysis, thoughts...
//now the classes seem much cleaner
//it's always possible to change the behaviour of the report by extending strategies
//the sole reason of having additional simple factory "design pattern" is - 
//to be able to derive both type from ReportBase, for demonstration purposes
//only... on the other hand - it's totally usual to have strategy pattern to be 
//used in conjuction with other patterns (even non patterns as simple factory)

public class ReportWithStrategy : ReportBase
{
    private readonly IReportTypeStrategyFactory _reportTypeFactory; 
    private readonly IReportSenderStrategyFactory _reportSenderFactory;

    public ReportWithStrategy(string title = null, 
        string body = null, string summary = null, string problems = null,
        IEnumerable<string> recipients = null)
        : base(title, body, summary, problems, recipients) 
    {
        _reportTypeFactory = new ReportTypeStrategyFactory(); 
        _reportSenderFactory = new ReportSenderStrategyFactory();
    }

    public ReportWithStrategy() : this(null, null, null, null, null) {}
    public override void PrepareReport(ReportType reportType)
    {
        var reportTypeStrategy = _reportTypeFactory.GetStrategy(reportType);
        (Title, Body, Summary) = reportTypeStrategy.PrepareReport();
    }

    public override void SendReport(RecipientType recipientType)
    {
        var reportSenderStrategy = _reportSenderFactory.GetStrategy(recipientType);
        reportSenderStrategy.SendReport(this);
    }
}
