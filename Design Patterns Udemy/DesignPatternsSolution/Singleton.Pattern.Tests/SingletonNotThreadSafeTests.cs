using Xunit;

namespace Singleton.Pattern.Tests;
public class SingletonNotThreadSafeTests
{
    [Fact]
    public void SingleThreadedInstanceShouldReturnSameInstance()
    {
        SingletonTestHelpers.RunSingleThreadTests(
            () => SingletonNotThreadSafe.Instance);
    }

    //This test is failed on purpose to demonstrate that 
    //the design is not thread safe... (more precisely this test may somehow 
    //pass, but normally should fail... HOLD: 
    [Fact]
    public void MultiThreadedInstanceShouldReturnSameInstance()
    {
        SingletonTestHelpers.RunMultiThreadTests(
            () => SingletonNotThreadSafe.Instance);
    }
}