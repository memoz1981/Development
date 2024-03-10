using Command.Pattern.Entities;
using Command.Pattern.Repositories;

namespace Command.Pattern.Command;
public class RemoveProductFromBasketCommand : ICommand
{
    Markt _markt;
    Client _client;
    Product _product;
    private bool _isExecuted = false;

    public bool IsUndoAllowed => true;

    public RemoveProductFromBasketCommand(Markt markt, Client client, string productName, int count = 1)
    {
        _markt = markt;
        _client = client;
        _product = new Product() { Name = productName, Count = count };
    }

    public bool CanExecute()
    {
        //1. If market contains the visitor
        if (!_markt.IsClientInMarkt(_client.Name))
            return false;

        //2. Does the visitor has the product in the basket
        if (!_client.DoesBasketItemsInclude(_product.Name))
            return false;

        //3. The count of the products in the basket should be more than requested
        var product = _client.GetBasketItem(_product.Name);
        if (product.GetCount() < _product.GetCount())
            return false; 

        return true;
    }

    public void Execute()
    {
        var productOfClient = _client.GetBasketItem(_product.Name);
        RemoveProductFromClient(productOfClient, _product.Count);
        AddProductToMarkt(); 
        _isExecuted = true;
    }

    private void RemoveProductFromClient(Product productOfClient, int productCount)
    {
        if (productOfClient.GetCount() > productCount)
            productOfClient.DecreaseCount(productCount);
        else
            _client.RemoveItemFromBasket(productOfClient.Name);
    }

    private void AddProductToMarkt()
    {
        if (_markt.IsProductAvailable(_product.Name))
        {
            var productInMarkt = _markt.GetProduct(_product.Name);
            productInMarkt.IncreaseCount(_product.Count);
        }
        else
        {
            //Again we want to have a copy instance here, we use product
            //to add to client rather.
            _markt.AddProduct(_product.GetCopy());
        }
    }

    public void Undo()
    {
        ValidateUndoRequest();
        AddProductToClientBasket();

        var marktProduct = _markt.GetProduct(_product.Name); 
        RemoveItemFromMarkt(marktProduct);
        _isExecuted = false;
    }

    private void RemoveItemFromMarkt(Product marktProduct)
    {
        if (marktProduct.GetCount() > _product.GetCount())
            marktProduct.DecreaseCount(_product.GetCount());
        else
            _markt.RemoveProduct(_product.Name); 
    }

    private void AddProductToClientBasket()
    {
        if (!_client.DoesBasketItemsInclude(_product.Name))
            _client.AddItemToBasket(_product);
        else
        {
            var clientProduct = _client.GetBasketItem(_product.Name);
            clientProduct.IncreaseCount(_product.Count);
        }
    }

    private void ValidateUndoRequest()
    {
        //is executed should be true
        if (_isExecuted)
            throw new InvalidOperationException("Command has not been executed");

        if (_markt.IsProductAvailable(_product.Name))
            throw new InvalidOperationException("We expected to see products here");

        var product = _markt.GetProduct(_product.Name);

        if (product.GetCount() < _product.Count)
            throw new InvalidOperationException("We expected to see more products here");
    }
}
