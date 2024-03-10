namespace Singleton.Pattern;

//Notes:
//Sealed not to have derivatives
//private constructor - we need to ensure only 
//instance can be returned by this class
public sealed class SingletonThreadSafeImproved : SingletonBase
{
    private static SingletonBase _instance;
    private static readonly object _lock = new object();
    private SingletonThreadSafeImproved() : base() { }

    public static SingletonBase Instance
    {
        get
        {
            if (_instance != null)
                return _instance; 
            
            lock (_lock)
            {
                return _instance = new SingletonThreadSafeImproved();
            }
        }
    }
}
