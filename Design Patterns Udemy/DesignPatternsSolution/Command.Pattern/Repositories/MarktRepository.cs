using Command.Pattern.Entities;

namespace Command.Pattern.Repositories;
public static class MarktRepository
{
    public static bool IsClientInMarkt(this Markt markt, string clientName) 
        => markt.Visitors.ContainsKey(clientName);
    
    public static bool IsProductAvailable(this Markt markt, string productName) 
        => markt.Products.ContainsKey(productName);

    public static void RemoveProduct(this Markt markt, string productName) 
        => markt.Products.Remove(productName);
    public static void AddProduct(this Markt markt, Product product)
        => markt.Products.Add(product.Name, product);

    public static Product GetProduct(this Markt markt, string productName)
        => markt.Products[productName];

    public static Client GetClient(this Markt markt, string clientName)
        => markt.Visitors[clientName];
}
