using System.Threading.Tasks;
using Tests.Common;
using Xunit;
using Xunit.Abstractions;
using Xunit.Microsoft.DependencyInjection.Abstracts;

namespace Singleton.Pattern.Tests;

//Notes: Singleton instance using microsofts built in dependency
//injection should ensure only 1 instance is there. 
//i used third party package xunit.microsoft.dependencyinjection
//seems that this test is failing - if one can understand why
//appreciate if he/she tells me. 
//asked question in stack overflow
//https://stackoverflow.com/questions/76504559/xunit-microsoft-dependencyinjection-singleton-instance-not-singleton

[CollectionDefinition("Dependency Injection")]
public class SingletonThreadSafeDependencyInjectionTests : TestBed<TestStartup>
{

    public SingletonThreadSafeDependencyInjectionTests(ITestOutputHelper testOutputHelper, TestStartup fixture)
        : base(testOutputHelper, fixture)
    {
        
    }

    [Fact]
    public void SingleThreadedInstanceShouldReturnSameInstance()
    {
        SingletonTestHelpers.RunSingleThreadTests(
            () => _fixture.GetService<SingletonThreadSafeDependencyInjection>(_testOutputHelper));
    }

    [Fact]
    public void MultiThreadedInstanceShouldReturnSameInstance()
    {
        SingletonTestHelpers.RunMultiThreadTests(
            () => _fixture.GetService<SingletonThreadSafeDependencyInjection>(_testOutputHelper));
    }

    protected override void Clear() {}

    protected override ValueTask DisposeAsyncCore()
    {
        throw new System.NotImplementedException();
    }
}
