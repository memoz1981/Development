using Shouldly;
using System;
using System.Linq;
using Xunit;

namespace Strategy.Pattern.Tests;
public class ReportBaseTests
{
    [Theory]
    [InlineData(typeof(ReportWithoutStrategy), ReportType.Daily, "Daily Report")]
    [InlineData(typeof(ReportWithoutStrategy), ReportType.Weekly, "Weekly Report")]
    [InlineData(typeof(ReportWithoutStrategy), ReportType.Monthly, "Monthly Report")]
    [InlineData(typeof(ReportWithoutStrategy), ReportType.Yearly, "Yearly Report")]
    [InlineData(typeof(ReportWithStrategy), ReportType.Daily, "Daily Report")]
    [InlineData(typeof(ReportWithStrategy), ReportType.Weekly, "Weekly Report")]
    [InlineData(typeof(ReportWithStrategy), ReportType.Monthly, "Monthly Report")]
    [InlineData(typeof(ReportWithStrategy), ReportType.Yearly, "Yearly Report")]
    public void PrepareReport_WithEachReportType_ShouldHaveCorrespondingTitle
        (Type type, ReportType reportType, string title)
    {
        //arrange
        var report = (ReportBase)Activator.CreateInstance(type);

        //act
        report.PrepareReport(reportType);

        //assert
        report.Title.ShouldBe(title); 
    }

    [Theory]
    [InlineData(typeof(ReportWithoutStrategy))]
    [InlineData(typeof(ReportWithStrategy))]
    public void PrepareReport_WithUnknownReportType_ShouldThrowException(Type type)
    {
        //arrange
        var report = (ReportBase)Activator.CreateInstance(type);
        const int REPORT_TYPE_UNKNOWN = 10;
        Action action = () => report.PrepareReport((ReportType)REPORT_TYPE_UNKNOWN);
        
        //act

        //assert
        Should.Throw<InvalidOperationException>(action);
    }

    [Theory]
    [InlineData(typeof(ReportWithoutStrategy), RecipientType.TechnicalStaff, 
        new string[] { "technical1", "technical2" })]
    [InlineData(typeof(ReportWithoutStrategy), RecipientType.Management,
        new string[] { "management1", "management2" })]
    [InlineData(typeof(ReportWithoutStrategy), RecipientType.External,
        new string[] { "external1", "external2" })]
    [InlineData(typeof(ReportWithStrategy), RecipientType.TechnicalStaff,
        new string[] { "technical1", "technical2" })]
    [InlineData(typeof(ReportWithStrategy), RecipientType.Management,
        new string[] { "management1", "management2" })]
    [InlineData(typeof(ReportWithStrategy), RecipientType.External,
        new string[] { "external1", "external2" })]
    public void SendReport_WithEachRecipientType_ShouldHaveCorrespondingRecipients
        (Type type, RecipientType recipientType, string[] recipients)
    {
        //arrange
        var report = (ReportBase)Activator.CreateInstance(type);

        //act
        report.SendReport(recipientType);

        //assert
        report.Recipients.ShouldBeEquivalentTo(recipients.ToList());
    }

    [Theory]
    [InlineData(typeof(ReportWithoutStrategy))]
    [InlineData(typeof(ReportWithStrategy))]
    public void SendReport_WithUnknownRecipientType_ShouldThrowException(Type type)
    {
        //arrange
        var report = (ReportBase)Activator.CreateInstance(type);
        const int RECIPIENT_TYPE_UNKNOWN = 10;
        Action action = () => report.SendReport((RecipientType)RECIPIENT_TYPE_UNKNOWN);

        //act

        //assert
        Should.Throw<InvalidOperationException>(action);
    }
}
