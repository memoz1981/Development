namespace Strategy.Pattern.Strategy.ReportTypes;
public abstract class ReportSenderStrategy
{
    public virtual void SendReport(ReportBase report)
    {
        AssignRecipients(report);
        SendEmail(); 
    }

    //note that below is not part of strategy pattern
    //name of the strategy TBA...
    protected abstract void AssignRecipients(ReportBase report);

    private void SendEmail()
    {
        //code to send email
    }
}
