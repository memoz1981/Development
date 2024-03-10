namespace Singleton.Pattern;
public abstract class SingletonBase
{
    public SingletonBase()
    {
        Id = Guid.NewGuid();
    }
    public Guid Id { get; private set; }
}
