#include "../account_object.h"
#include <gtest/gtest.h>

struct test_account_object
    : public ::testing::Test
{

}

//success
TEST(test_account_object, add_success){
    string test = "text"
    int expected = 1;
    EXPECT_EQ(
        expected,
        add(test, test, test, test, test, test)
    )
}

//test for empty string
TEST(test_account_object, add_empty){
    string test = ""
    int expected = -1;
    EXPECT_EQ(
        expected,
        add(test, test, test, test, test, test)
    )
}

//test for string of spaces
TEST(test_account_object, add_spaces){
    string test = "  "
    int expected = -1;
    EXPECT_EQ(
        expected,
        add(test, test, test, test, test, test)
    )
}

//test for string of numbers
TEST(test_account_object, add_numbers){
    string test = "12345"
    int expected = 1;
    EXPECT_EQ(
        expected,
        add(test, test, test, test, test, test)
    )
}





//===================
//How to test save? 
//Save doesn't get unit tests because it accesses a data base? 
//===================
TEST(test_account_object, save){

}





//success
TEST(test_account_object, edit_success){
    string test = "text"
    int expected = 1;
    EXPECT_EQ(
        expected,
        edit(test, test, test, test, test)
    )
}

//test for empty string
TEST(test_account_object, edit_empty){
    string test = ""
    int expected = -1;
    EXPECT_EQ(
        expected,
        edit(test, test, test, test, test)
    )
}

//test for string of spaces
TEST(test_account_object, edit_spaces){
    string test = "  "
    int expected = -1;
    EXPECT_EQ(
        expected,
        edit(test, test, test, test, test)
    )
}

//test for string of numbers
TEST(test_account_object, edit_numbers){
    string test = "12345"
    int expected = 1;
    EXPECT_EQ(
        expected,
        edit(test, test, test, test, test)
    )
}





//=======================================================
//make_provider is a trivial set function, no unit tests needed

/*TEST(test_account_object, make_provider){
    account test;
    test.make_provider();
    EXPECT_EQ(
        1,
        test.account_type
    )
}
*/



//=======================================================
//Update is a trivial set function, no unit tests needed



//=======================================================
//Copy is a trivial set function, no unit tests needed



//=======================================================
//Output does not require unit tests



//=======================================================
//Display does not require unit tests



//=======================================================
//Add service only calls a function from the service class, the funciton will be tested there. 
//No tests needed

