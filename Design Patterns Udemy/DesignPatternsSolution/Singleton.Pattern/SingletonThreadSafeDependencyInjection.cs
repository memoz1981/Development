namespace Singleton.Pattern;

//this will just return the value, needs to be added as singleton lifetime dependencys
public sealed class SingletonThreadSafeDependencyInjection : SingletonBase 
{
    public SingletonThreadSafeDependencyInjection() : base() { }
}
