using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Singleton.Pattern;
using Xunit.Microsoft.DependencyInjection.Abstracts;

namespace Tests.Common;
public class TestStartup : TestBedFixture
{
    protected override void AddServices(IServiceCollection services, IConfiguration? configuration)
    {
        services.AddSingleton<SingletonThreadSafeDependencyInjection>();
    }

    protected override ValueTask DisposeAsyncCore() => new();

    protected override string GetConfigurationFile()
        => string.Empty; 
}
