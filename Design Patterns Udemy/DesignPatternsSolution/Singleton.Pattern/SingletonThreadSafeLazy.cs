namespace Singleton.Pattern;

//Notes:
//Lazy will ensure the instance will be created on first call
//and only 1 instance will be created in multiple threaded env. 
public sealed class SingletonThreadSafeLazy : SingletonBase
{
    private static readonly Lazy<SingletonBase> _lazy 
        = new Lazy<SingletonBase>(() => new SingletonThreadSafeLazy());

    private SingletonThreadSafeLazy() : base() { }

    public static SingletonBase Instance
    {
        get => _lazy.Value; 
    }
}
