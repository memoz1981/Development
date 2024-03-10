namespace Command.Pattern.Entities;

public class Product : IUniqueNameEntity
{
    public Product() {}

    public Product(string name, decimal value, int count)
    {
        Name = name;
        Value = value;
        Count = count;
    }
    
    public string Name { get; set; }

    public decimal Value { get; set; }

    public int Count { get; set; }
}
