using Strategy.Pattern.Strategy.RecipientTypes;
using Strategy.Pattern.Strategy.ReportTypes;

namespace Strategy.Pattern.Factories;
public class ReportSenderStrategyFactory : IReportSenderStrategyFactory
{
    public ReportSenderStrategy GetStrategy(RecipientType recipientType)
    {
        return recipientType switch
        {
            RecipientType.TechnicalStaff => new TechnicalStaffReportSenderStrategy(),
            RecipientType.Management => new ManagementReportSenderStrategy(),
            RecipientType.External => new ExternalReportSenderStrategy(),
            _ => throw new InvalidOperationException()
        };
    }
}
