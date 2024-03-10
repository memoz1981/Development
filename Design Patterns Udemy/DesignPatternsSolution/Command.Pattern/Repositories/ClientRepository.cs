using Command.Pattern.Entities;

namespace Command.Pattern.Repositories;

public static class ClientRepository
{
    public static bool DoesBasketItemsInclude(this Client client, string productName) 
        => client.BasketItems.ContainsKey(productName);

    public static bool DoesBoughtItemsInclude(this Client client, string productName)
        => client.BoughtItems.ContainsKey(productName);

    public static void AddItemToBasket(this Client client, Product product) 
        => client.BasketItems.Add(product.Name, product);

    public static void RemoveItemFromBasket(this Client client, string productName)
        => client.BasketItems.Remove(productName);

    public static void AddItemToBought(this Client client, Product product)
        => client.BoughtItems.Add(product.Name, product);

    public static void RemoveItemFromBought(this Client client, string productName)
        => client.BoughtItems.Remove(productName);

    public static decimal GetCash(this Client client) => client.Cash;

    public static void AddCash(this Client client, decimal cash) => client.Cash += cash;

    public static void RemoveCash(this Client client, decimal cash) => client.Cash -= cash;

    public static IEnumerable<Product> GetBasketItems(this Client client)
    {
        foreach (var product in client.BasketItems)
        {
            yield return product.Value;
        }
    }

    public static Product GetBasketItem(this Client client, string productName)
        => client.BasketItems[productName];

    public static Product GetBoughtItem(this Client client, string productName)
        => client.BoughtItems[productName];
}
