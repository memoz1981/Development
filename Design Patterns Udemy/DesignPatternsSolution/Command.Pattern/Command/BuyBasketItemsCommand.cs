using Command.Pattern.Entities;
using Command.Pattern.Repositories;

namespace Command.Pattern.Command;
public class BuyBasketItemsCommand : ICommand
{
    Markt _markt;
    Client _client;
    public bool IsUndoAllowed => false;

    public BuyBasketItemsCommand(Markt markt, Client client)
    {
        _markt = markt;
        _client = client;
    }

    public bool CanExecute()
    {
        //1. If market contains the visitor
        if (!_markt.IsClientInMarkt(_client.Name))
            return false;

        //2. If there are any items in the client's basket
        if(!_client.GetBasketItems().Any())
            return false;

        return true; 
    }

    public void Execute()
    {
        foreach (var product in _client.GetBasketItems())
        {
            _client.RemoveCash(product.GetTotalValue());

            if (_client.DoesBoughtItemsInclude(product.Name))
            {
                var productInBoughtItems = _client.GetBoughtItem(product.Name);
                productInBoughtItems.IncreaseCount(product.Count);
            }
            else
            {
                _client.AddItemToBought(product);
            }
            _client.RemoveItemFromBasket(product.Name); 
        }
    }

    public void Undo()
    {
        throw new InvalidOperationException("Command is not allowed.");
    }
}
