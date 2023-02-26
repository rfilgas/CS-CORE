cmake_minimum_required(VERSION 3.8)

set(This ExampleTests)

set(Sources
    test_account_manager.cpp
    test_account_object.cpp
    test_chocann_access.cpp
    test_interface.cpp
    test_provider_dir_entry.cpp
    test_provider_directory.cpp
    test_service_provided.cpp
    test_utility.cpp
)

add executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    Choc_Ann
)

add_test(
    NAME ${This}
    COMMAND ${This}
)