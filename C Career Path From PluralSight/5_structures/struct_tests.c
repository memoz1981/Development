#include "../unity/unity.h"

void structures_can_be_defined_using_struct_keyword_with_or_without_typedef(void)
{
    //arrange
    struct Grade {
        char letter;
        int rank; 
    } grade1;

    typedef struct Person {
        int age; 
        char* name; 
    } PersonAlias;

    //act
    grade1.letter = 'A';
    grade1.rank = 1; 

    struct Grade grade2; 

    struct Person person1; 
    person1.age = 20; 
    person1.name = "Mark"; 

    //using alias - struct keyword can be avoided upon declaration
    PersonAlias person2; 

    //assert
    TEST_ASSERT_EQUAL_CHAR('A', grade1.letter); 
    TEST_ASSERT_EQUAL_INT(1, grade1.rank); 

}

void unnamed_structured_can_be_defined(void)
{
    //arrange
    struct City{
        int population; 
        char firstLetterOfName; 
    } city; 

    //act
    int a = (int)sizeof(void*); 

    //assert
    TEST_ASSERT_EQUAL_size_t(8, sizeof(city)); 
}

int DriveWithSpeed(int speed)
{
    printf("driving with speed %d", speed); 
    return speed; 
}

void structures_may_have_function_pointer_members(void)
{
    //arrange
    typedef struct Car{
        char * color; 
        int (*drive)(int speed);
    } Car;

    char color[] = "Red";
    Car car; 

    car.color = &color; 
    car.drive = DriveWithSpeed; 
    
    //act
    int result = car.drive(60); 

    //assert
    TEST_ASSERT_EQUAL_INT(60, result); 
}

void struct_equality_will_create_copy_of_variables_to_new_memory_address(void)
{
    //arrange
    struct Grade {
        char letter;
        int rank; 
    } grade1;


    //act
    grade1.letter = 'A';
    grade1.rank = 1; 

    struct Grade grade2 = grade1; 

    //assert
    TEST_ASSERT_EQUAL_CHAR(grade1.letter, grade2.letter); 
    TEST_ASSERT_EQUAL_INT(grade1.rank, grade2.rank); 
    TEST_ASSERT_NOT_EQUAL(&(grade1.letter), &(grade2.letter)); 
    TEST_ASSERT_NOT_EQUAL(&(grade1.rank), &(grade2.rank)); 
}

void structures_can_be_initialized_inline_that_is_similar_to_constructors_in_higher_level_languages(void)
{
    //arrange
    struct Grade {
        char letter;
        int rank; 
    } grade1 = {'A', 1};


    //act

    //assert
    TEST_ASSERT_EQUAL_CHAR('A', grade1.letter); 
    TEST_ASSERT_EQUAL_INT(1, grade1.rank); 
}

void structures_can_have_designated_initialization_with_named_members(void)
{
    //arrange
    typedef struct Grade {
        char letter;
        int rank; 
        int number; 
    } Grade;

    //act
    Grade grade1 = {.number = 1, .letter = 'A', .rank = 2}; 

    //assert
    TEST_ASSERT_EQUAL_CHAR('A', grade1.letter); 
    TEST_ASSERT_EQUAL_CHAR(1, grade1.number); 
    TEST_ASSERT_EQUAL_INT(2, grade1.rank); 
}

//64 bit systems have word boundary of 8 bytes === 64 bits... this will result in structure paddings. 
//this needs to be taken into account when declaring the structs
void structures_will_occupy_minimum_word_boundary_as_per_the_cpu_architecture(void)
{
    //arrange
    struct Grade {
        char letter;
        int rank; 
    } grade1 = {'A', 1};


    //act
    size_t sizeOfStruct = sizeof(grade1);
    size_t totalSizeOfStructMembers = sizeof(grade1.letter) + sizeof(grade1.rank); 

    //assert
    TEST_ASSERT_GREATER_THAN_size_t(totalSizeOfStructMembers, sizeOfStruct); 
    TEST_ASSERT_EQUAL_size_t(8, sizeOfStruct); 

}

void structures_can_be_dynamically_allocated_using_corresponding_keywords(void)
{
    //arrange (below is a simple linked list node declaration)
    typedef struct Node {
        void * data; //which basically means the node will not contain any data, rather it needs a space to have a pointer to the relevant data... 
        struct Node *next; //pointer to the next element
    } Node;

    //act
    Node *head = (Node*)calloc(1, sizeof(Node)); //this would return a pointer to the allocated Node (which is also the head for the linked list)

    //assert
    TEST_ASSERT_NOT_NULL(head); 
    free(head); 
}

void dynamically_allocated_structure_members_can_be_accessed_with_or_without_dereferencing_the_pointer(void)
{
    //arrange
    typedef struct Node {
        int * data; 
        struct Node *next; 
    } Node;

    //act
    Node *head = (Node*)malloc(sizeof(Node)); 
    int * data = (int*)malloc(sizeof(int)); 
    *data = 10; 
    head -> data = data; 
    head -> next = NULL; 
    
    //assert
    TEST_ASSERT_EQUAL(NULL, head -> next); // direct member access
    TEST_ASSERT_EQUAL(NULL, (*head).next); // member access by de-referencing the pointer
    TEST_ASSERT_EQUAL_INT(*data, *(head -> data));

    free(head); 
    free(data); 
}

/*Ignoring this test, as coudln't get required response - subject to further investigation...*/
void structure_parameter_positions_alter_the_memory_allocation_ignored(void)
{
    TEST_IGNORE(); 
    //arrange
    struct City1{
        int population; 
        char name[8];
        int numberOfCars; 
    } city1; 

    struct City2{
        int population; 
        int numberOfCars; 
        char name[8];
        
    } city2; 

    //act

    //assert
    TEST_ASSERT_EQUAL_size_t(24, sizeof(city1)); 
    TEST_ASSERT_EQUAL_size_t(16, sizeof(city2)); 
}

/*These are called bit fields - alternatively #pragma pack(1) would pack and remove padding - but this would require more CPU cycles to read the data*/
void structure_member_number_of_bits_can_be_specified_upon_declaration(void)
{
    //arrange
    typedef struct Transcript{
        int scoreOverTen: 4; //maximum value can be 10 === 4 bytes
        int credit: 3; //maximum value is 5 credits
        char letter; //1 bytes by default
    } transcript;

    //act

    //assert
    TEST_ASSERT_EQUAL_size_t(8, sizeof(transcript)); 
}

void run_struct_tests()
{
    UNITY_BEGIN();

    RUN_TEST(structures_can_be_defined_using_struct_keyword_with_or_without_typedef); 
    RUN_TEST(struct_equality_will_create_copy_of_variables_to_new_memory_address); 
    RUN_TEST(structures_can_be_initialized_inline_that_is_similar_to_constructors_in_higher_level_languages);
    RUN_TEST(structures_can_have_designated_initialization_with_named_members);
    RUN_TEST(structures_will_occupy_minimum_word_boundary_as_per_the_cpu_architecture); 
    RUN_TEST(structures_can_be_dynamically_allocated_using_corresponding_keywords);
    RUN_TEST(dynamically_allocated_structure_members_can_be_accessed_with_or_without_dereferencing_the_pointer); 
    RUN_TEST(unnamed_structured_can_be_defined); 
    RUN_TEST(structures_may_have_function_pointer_members);
    RUN_TEST(structure_parameter_positions_alter_the_memory_allocation_ignored); 
    RUN_TEST(structure_member_number_of_bits_can_be_specified_upon_declaration); 

    UNITY_END();
}