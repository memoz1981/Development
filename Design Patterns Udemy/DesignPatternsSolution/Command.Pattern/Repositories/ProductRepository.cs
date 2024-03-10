using Command.Pattern.Entities;

namespace Command.Pattern.Repositories;
public static class ProductRepository
{
    public static void IncreaseCount(this Product product, int count = 1)
        => product.Count += count;

    public static void DecreaseCount(this Product product, int count = 1) 
        => product.Count -= count;

    public static bool IsAvailable(this Product product) => product.Count > 0;

    public static decimal GetTotalValue(this Product product) 
        => product.Count * product.Value;

    public static decimal GetValue(this Product product)
        => product.Value;

    public static int GetCount(this Product product)
        => product.Count;

    public static Product GetCopy(this Product product)
        => new Product(product.Name, product.Value, product.Count); 
}
