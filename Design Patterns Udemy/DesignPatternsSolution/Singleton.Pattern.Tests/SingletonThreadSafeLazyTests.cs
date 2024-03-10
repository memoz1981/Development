using Xunit;

namespace Singleton.Pattern.Tests;
public class SingletonThreadSafeLazyTests
{
    [Fact]
    public void SingleThreadedInstanceShouldReturnSameInstance()
    {
        SingletonTestHelpers.RunSingleThreadTests(
            () => SingletonThreadSafeLazy.Instance); 
    }

    [Fact]
    public void MultiThreadedInstanceShouldReturnSameInstance()
    {
        SingletonTestHelpers.RunMultiThreadTests(
            () => SingletonThreadSafeLazy.Instance);
    }
}