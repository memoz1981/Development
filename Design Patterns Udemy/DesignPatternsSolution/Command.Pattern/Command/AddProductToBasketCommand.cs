using Command.Pattern.Entities;
using Command.Pattern.Repositories;

namespace Command.Pattern.Command;
public class AddProductToBasketCommand : ICommand
{
    Markt _markt;
    Client _client;
    Product _product;
    private bool _isExecuted = false;
    public bool IsUndoAllowed => true;

    public AddProductToBasketCommand(Markt markt, Client client, string productName, int count = 1)
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

        //2. If market contains the product
        if (!_markt.IsProductAvailable(_product.Name))
            return false;

        //3. If the market contains the product with specified count
        var productInMarket = _markt.GetProduct(_product.Name);
        if(productInMarket.GetCount() < _product.GetCount())
            return false;

        //4. Does visitor has cash available
        var cash = _client.GetCash();
        foreach (var product in _client.GetBasketItems())
        {
            cash -= product.GetTotalValue(); 
        }
        if (cash <= 0)
            return false;

        return true; 
    }

    public void Execute()
    {
        //this is not a perfect place to get the price of the product
        //also repositories not ideally implemented
        var productInMarket = _markt.GetProduct(_product.Name);
        _product.Value = productInMarket.GetValue();

        AddProductToClientBasket();
        RemoveProductFromMarkt(productInMarket);
        _isExecuted = true; 
    }

    private void AddProductToClientBasket()
    {
        if (!_client.DoesBasketItemsInclude(_product.Name))
        {
            //since each command will have a separate Product instance
            //we don't hesitate to add the instance here. 
            _client.AddItemToBasket(_product);
        }
        else
        {
            var clientProduct = _client.GetBasketItem(_product.Name);
            clientProduct.IncreaseCount(_product.Count);
        }
    }

    private void RemoveProductFromMarkt(Product productInMarket)
    {
        if (productInMarket.GetCount() > _product.Count)
            productInMarket.DecreaseCount(_product.Count);
        else
            _markt.RemoveProduct(productInMarket.Name);
    }

    public void Undo()
    {
        ValidateRequest();
        var productOfClient = _client.GetBasketItem(_product.Name); 
        RemoveProductFromClient(productOfClient);
        AddProductToMarkt();
        _isExecuted = false;
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
            // we want to have a separate instance here, otherwise there is a risk
            //that we use same instance for market and client. 
            _markt.AddProduct(_product.GetCopy());
        }        
    }

    private void RemoveProductFromClient(Product productOfClient)
    {
        if (productOfClient.GetCount() > _product.GetCount())
            productOfClient.DecreaseCount(_product.Count);
        else
            _client.RemoveItemFromBasket(_product.Name);
    }

    private void ValidateRequest()
    {
        //is executed should be true
        if (_isExecuted)
            throw new InvalidOperationException("Command has not been executed");

        if (_client.DoesBasketItemsInclude(_product.Name))
            throw new InvalidOperationException("We expected to see products here");

        var product = _client.GetBasketItem(_product.Name);

        if (product.GetCount() < _product.Count)
            throw new InvalidOperationException("We expected to see more products here");
    }
}
