namespace Singleton.Pattern;

//Notes:
//Sealed not to have derivatives
//private constructor - we need to ensure only 
//instance can be returned by this class
public sealed class SingletonNotThreadSafe : SingletonBase
{
    private static SingletonBase _instance;
    private SingletonNotThreadSafe() : base() {}

    public static SingletonBase Instance
    {
        get => _instance ??= new SingletonNotThreadSafe();
    }
}
