namespace Command.Pattern.Entities;

public class Markt : IUniqueNameEntity
{
    public Markt(string name, HashSet<Client> visitors, HashSet<Product> products)
    {
        Name = name;
        Visitors = visitors.ToDictionary(m => m.Name, m => m);
        Products = products.ToDictionary(m => m.Name, m => m);
    }
    public string Name { get; set; }

    public Dictionary<string, Product> Products { get; set; } = new();

    public Dictionary<string, Client> Visitors { get; set; } = new();
}