using Strategy.Pattern.Strategy.ReportTypes;

namespace Strategy.Pattern.Factories;
public interface IReportSenderStrategyFactory
{
    ReportSenderStrategy GetStrategy(RecipientType recipientType);
}
