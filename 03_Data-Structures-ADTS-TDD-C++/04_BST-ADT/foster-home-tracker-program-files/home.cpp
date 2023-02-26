#include "foster_homes.h"

#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>

using namespace std;

// -----------------------------------------------------
// Ryan Filgas
// Assignment_4
// Karla Fant
// CS163
// 2/25/2021
//
// FILENAME:
// home.cpp
//
// The purpose of the foster_homes class is to manage the user data of a foster
// home, and how it will pass information to the table class. The foster home
// class will manage home name, number of pets, time of stay, extra details,
// and animal types accepted. Member functions are add, copy, input, display home,
// display type match, and is_home_match.
// -----------------------------------------------------

// This is a constructor for my animal type struct.
animal_type::animal_type()
{
    name = NULL;
};



// This is a constructor for my animal type class.
animal_type::~animal_type()
{
    if(name)
    {
        delete [] name;
        name = NULL;
    }
}



// This is a constructor for my foster home class.
foster_home::foster_home()
{
    home_name = NULL;
    num_pets = NULL;
    time = NULL;
    details = NULL;
    types = NULL;
    num_types = 0;
};



//This is a destructor for my foster home class.
foster_home::~foster_home()
{
    if(home_name)
    {
        delete [] home_name;
        home_name = NULL;
    }
    if(num_pets)
    {
        delete [] num_pets;
        num_pets = NULL;
    }
    if(time)
    {
        delete [] time;
        time = NULL;
    }
    if(details)
    {
        delete [] details;
        details= NULL;
    }
    if(types)
    {
        delete [] types;
        types = NULL;
    }
    num_types = 0;
};



// This function allows the user to creater their own foster home object. It takes in home, time, details, and animal types as char arrays,
// an animal_type array of animal type objects, and a number of types added as an int. This function will return 1 for success and
// 0 for failure.
int foster_home::input_entry(char home_name_to_add[], char num_pets_to_add[], char time_to_add[], char details_to_add[],animal_type types_to_add[], int num_types_to_add)
{
    //This is a variable to return success to the calling function.
    int success = 0;


    //If all items, are present, allocate dynamic memory, and copy data items.
    if(home_name_to_add && num_pets_to_add && time_to_add && details_to_add && clear_entry())
    {
        home_name = new char[strlen(home_name_to_add) + 1];
        strcpy(home_name, home_name_to_add);

        num_pets = new char[strlen(num_pets_to_add) + 1];
        strcpy(num_pets, num_pets_to_add);

        time = new char[strlen(time_to_add) + 1];
        strcpy(time, time_to_add);

        details = new char[strlen(details_to_add) + 1];
        strcpy(details, details_to_add);

        types = new animal_type[num_types_to_add];

        //For each type in the type array, allocate new memory, and copy it into the local type array.
        for(int i = 0; i < num_types_to_add; ++i)
        {
            types[i].name = new char[strlen(types_to_add[i].name) + 1];
            strcpy(types[i].name, types_to_add[i].name);
        }

        num_types = num_types_to_add; 

        //Return success.
        success = 1;
    }
    return success;
}



// This function uses the input entry function to copy data from a foster home passed by reference into the local objects memory.
// This function will return 1 for success, and 0 for failure.
int foster_home::copy_entry(foster_home &to_copy)
{
    //This is a variable to return success to the calling function.
    int success = 0;
    success = input_entry(to_copy.home_name, to_copy.num_pets, to_copy.time, to_copy.details, to_copy.types, to_copy.num_types);
    return success;
}



// This function will compare a home name char array passed by reference with a home name in the local objects memory,
// then return 1 if it's a match, or 0 if there isn;t a match.
int foster_home::is_home_match(char * home_match)
{
    return (!strcmp(home_match, home_name));
}



// This function takes a char array type match as input, and will output success if there is a matching type in the local
// objects memory. This function will return 1 for success, or 0 for failure.
int foster_home::display_if_pet_match(char * type_match)
{
    //This is a variable to return success to the calling routine.
    int success = 0;

    //This is a temp char array to assist indexing into the types array for comparing.
    char temp[100];

    //For each type in the type array. Copy the type into temp, and compare with the type match passed in by
    //pointer. If there is a match, display the home name.
    for(int i = 0; i < num_types; ++i)
    {
      temp[0] = '\0';
      strcpy(temp, types[i].name);
      if(!strcmp(type_match,temp))
        success = 1;
    }

    //The for loop found a match, display the name for the user.
    if(success)
        cout << home_name << "\n";
    return success;
}



// This function will clear the contents of a foster home and return 1 for success.
int foster_home::clear_entry(void)
{
    if(home_name)
    {
        delete [] home_name;
        home_name = NULL;
    }
    if(num_pets)
    {
        delete [] num_pets;
        num_pets = NULL;
    }
    if(time)
    {
        delete [] time;
        time = NULL;
    }
    if(details)
    {
        delete [] details;
        details= NULL;
    }
    if(types)
    {
        delete [] types;
        types = NULL;
    }
    num_types = 0;
    return 1;
}



// This function will take in a foster home object to compare with the local
// objects memory. It will return a 0 if the name is the same, a negative number
// if the passed in value preceeds the local object alphabetically, and
// a positive number otherwise.
int foster_home::sort_homes(foster_home & to_compare)
{
    return (strcmp(to_compare.home_name, home_name));
}



// This function allows navigating of the binary tree via home name vs home object like the previous function.
// The outputs are the same.
int foster_home::sort_homes(char * to_compare)
{
    return (strcmp(to_compare, home_name));
}



// This function displays all members of a foster home object. It will return 1 for success, and 0 if not all
// data members are present.
int foster_home::display_home(void)
{
    //This variable will be used to return succcess or failure.
    int success = 0;

    //If all elements are present, display them,
    if(home_name && num_pets && time && details)
    {
        cout << "Home Name             : " << home_name << "\n";
        cout << "Number of Pets Allowed: " << num_pets << "\n";
        cout << "Length of Stay        : " << time << "\n";

        cout << "Animal Breeds Accepted: ";
        cout << (types[0].name);
        for(int i = 1; i < num_types; ++i)
            cout << ", " << (types[i].name);
        cout << ".\n";
        cout << "Other Information     : " << details << "\n\n";
        success = 1;
    }
    return success;
}
