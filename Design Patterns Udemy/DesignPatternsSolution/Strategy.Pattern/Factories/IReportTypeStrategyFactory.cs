using Strategy.Pattern.Strategy.ReportTypes;

namespace Strategy.Pattern.Factories;
//the sole purpose of this factory design pattern is to ensure that
//both of the reportbase implementations can derive from reportbase
//it's for demonstration purposes only. 
//strategy pattern can be a full or partial solution to SOLID.
public interface IReportTypeStrategyFactory
{
    IReportTypeStrategy GetStrategy(ReportType reportType); 
}
