#include "../unity/unity.h"
enum CarType { cabriolet = 10, sedan = 20, SUV = 30 }; 

void enum_types_can_be_declared_using_enum_keyword(void)
{
    //arrange
    

    //act
    int type_of_my_car = (enum CarType) cabriolet; 

    //assert
    TEST_ASSERT_EQUAL_INT(10, type_of_my_car); 
}

void run_enum_tests()
{
    UNITY_BEGIN(); 

    RUN_TEST(enum_types_can_be_declared_using_enum_keyword); 

    UNITY_END(); 
}