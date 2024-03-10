namespace Command.Pattern.Entities;

public class Client : IUniqueNameEntity
{
    public Client(string name, decimal cash)
    {
        Name = name;
        Cash = cash;
    }
    
    public string Name { get; set; }

    public decimal Cash { get; set; }

    public Dictionary<string, Product> BasketItems { get; set; } = new();

    public Dictionary<string, Product> BoughtItems { get; set; } = new();
}
