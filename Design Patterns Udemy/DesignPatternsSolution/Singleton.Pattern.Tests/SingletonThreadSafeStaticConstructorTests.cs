using Xunit;

namespace Singleton.Pattern.Tests;
public class SingletonThreadSafeStaticConstructorTests
{
    [Fact]
    public void SingleThreadedInstanceShouldReturnSameInstance()
    {
        SingletonTestHelpers.RunSingleThreadTests(
            () => SingletonThreadSafeStaticConstructor.Instance);
    }

    [Fact]
    public void MultiThreadedInstanceShouldReturnSameInstance()
    {
        SingletonTestHelpers.RunMultiThreadTests(
            () => SingletonThreadSafeStaticConstructor.Instance);
    }
}


