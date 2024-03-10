namespace Singleton.Pattern;

//Notes:
//Sealed not to have derivatives
//private constructor - we need to ensure only 
//instance can be returned by this class
public sealed class SingletonThreadSafeStaticConstructor : SingletonBase
{
    private static SingletonBase _instance;
    private static readonly object _lock = new object();
    private SingletonThreadSafeStaticConstructor() : base() { }

    static SingletonThreadSafeStaticConstructor() {}

    public static SingletonBase Instance
    {
        get => _instance ??= new SingletonThreadSafeStaticConstructor(); 
    }
}