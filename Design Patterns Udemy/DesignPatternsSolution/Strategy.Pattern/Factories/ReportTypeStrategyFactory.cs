using Strategy.Pattern.Strategy.ReportTypes;

namespace Strategy.Pattern.Factories;
public class ReportTypeStrategyFactory : IReportTypeStrategyFactory
{
    public IReportTypeStrategy GetStrategy(ReportType reportType)
    {
        return reportType switch
        {
            ReportType.Daily => new DailyReportTypeStrategy(),
            ReportType.Weekly => new WeeklyReportTypeStrategy(),
            ReportType.Monthly => new MonthlyReportTypeStrategy(),
            ReportType.Yearly => new YearlyReportTypeStrategy(),
            _ => throw new InvalidOperationException()
        };
    }
}
