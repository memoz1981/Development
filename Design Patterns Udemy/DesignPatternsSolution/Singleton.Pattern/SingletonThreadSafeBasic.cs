namespace Singleton.Pattern;

//Notes:
//Sealed not to have derivatives
//private constructor - we need to ensure only 
//instance can be returned by this class
public sealed class SingletonThreadSafeBasic : SingletonBase
{
    private static SingletonBase _instance;
    private static readonly object _lock = new object();
    private SingletonThreadSafeBasic() : base() { }

    public static SingletonBase Instance
    {
        get
        {
            lock (_lock)
            {
                return _instance ??= new SingletonThreadSafeBasic();
            }
        }
    }
}