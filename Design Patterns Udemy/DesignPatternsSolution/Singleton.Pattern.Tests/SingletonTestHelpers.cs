using Shouldly;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace Singleton.Pattern.Tests;
public class SingletonTestHelpers
{
    public static void RunSingleThreadTests(Func<SingletonBase> singletonBase)
    {
        var instance1 = singletonBase.Invoke();
        var instance2 = singletonBase.Invoke();
        var instance3 = singletonBase.Invoke();

        instance1.Id.ShouldBe(instance2.Id);
        instance2.Id.ShouldBe(instance3.Id);
    }

    public static void RunMultiThreadTests(Func<SingletonBase> singletonBase)
    {
        //arrange
        var integerCount = new int[3];
        var instances = new List<SingletonBase>();
        var options = new ParallelOptions() { MaxDegreeOfParallelism = 3 };

        //act
        Parallel.ForEach(integerCount, options, instance =>
        {
            instances.Add(singletonBase.Invoke());
        });

        //assert
        instances[0].Id.ShouldBe(instances[1].Id);
        instances[2].Id.ShouldBe(instances[1].Id);
        instances[0].Id.ShouldBe(instances[2].Id);
    }
}
