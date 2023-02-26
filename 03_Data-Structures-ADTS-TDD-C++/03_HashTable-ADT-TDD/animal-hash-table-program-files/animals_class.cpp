#include "animal.h"
#include <cstring>
#include <cctype>
#include <iostream>

using namespace std;

// -------------------------------------------------------------------------
// Ryan Filgas
// Assignment_3
// Karla Fant
// CS 163
// 02/16/2021
//
// Filename:
// animals_class.cpp
//
// The purpose of this file is to manage animal class data in order to assist
// the function of the hash table class. Functions include dicplay, input, copy, 
// is_empty, and is_match.Is_match is heavily used by both the hash table and
// queue adts.
// -------------------------------------------------------------------------



//This is a constructor for the animal class, setting all values to NULL.
animals::animals()
{
    breed = NULL;
    name = NULL;
    location = NULL;
    story = NULL;
    link = NULL;
    age = NULL;

};



// This is a destructor for the animal class, clearing all allocated dynamic memory.
animals::~animals()
{
    if(breed)
    {
        delete [] breed;
        breed = NULL;
    }
    if(name)
    {
        delete [] name;
        name = NULL;
    }
    if(location)
    {
        delete [] location;
        location = NULL;
    }
    if(story)
    {
        delete [] story;
        story = NULL;
    }
    if(link)
    {
        delete [] link;
        link = NULL;
    }
    if(age)
    {
        delete [] age;
        age = NULL;
    }
};



// The display entry function takes no input, and will output all members of the calling object.
// If all objects aren't present, ot the age is 0, this function will return false.
int animals::display_entry(void)
{
    //This variable will be used to return succcess or failure.
    int success = 0;

    //If all elements are present, display them,
    if(breed && name && location && link && story && age)
    {
        cout << "Breed   : " << breed << "\n";
        cout << "Name    : " << name << "\n";
        cout << "Location: " << location << "\n";
        cout << "Story   : " << story << "\n";
        cout << "Link    : " << link << "\n";
        cout << "Age     : " << age << "\n\n";
        success = 1;
    }
    return success;
}



// The input_entry function takes in breed, name, location, and story as char arrays, and integer for age
// then copies it into the calling object.
int animals::input_entry(char breed_to_add[], char name_to_add[], char location_to_add[], char story_to_add[], char link_to_add[], char age_to_add[])
{
    //This is a variable to return success to the calling function.
    int success = 0;


    //If all items, are present, allocate dynamic memory, and copy data items.
    if(breed_to_add && name_to_add && location_to_add && story_to_add && link_to_add)
    {
        breed = new char[strlen(breed_to_add) + 1];
        strcpy(breed, breed_to_add);

        name = new char[strlen(name_to_add) + 1];
        strcpy(name, name_to_add);

        location = new char[strlen(location_to_add) + 1];
        strcpy(location, location_to_add);

        story = new char[strlen(story_to_add) + 1];
        strcpy(story, story_to_add);

        link = new char[strlen(link_to_add) + 1];
        strcpy(link, link_to_add);

        if(age)
            delete age;
        age = NULL;

        age = new char[strlen(age_to_add) + 1];
        strcpy(age, age_to_add);

        //Return success.
        success = 1;
    }
    return success;
}



// copy_entry takes in an animal object by reference, and uses the input entry function to copy data to
// the local object.
int animals::copy_entry(animals &to_copy)
{
    //This is a variable to return success to the calling function.
    int success = 0;
    success = input_entry(to_copy.breed, to_copy.name, to_copy.location, to_copy.story, to_copy.link, to_copy.age);
    return success;
}



// This is a sub-function to copy just the name and location into arrays for a hash function to use.
// it will return success.
int animals::copy_entry(char * &breed_to_fill, char * &location_to_fill)
{
    //This is a variable to return success to the calling function.
    int success = 0;

    //if breed and location to fill are empty, proceed to copy.
    if(!breed_to_fill && !location_to_fill)
    {
        location_to_fill = new char[strlen(location) + 1];
        strcpy(location_to_fill, location);

        breed_to_fill = new char[strlen(breed) + 1];
        strcpy(breed_to_fill, breed);
        success = 1;
    }
    return success;
}



// is_match takes in name, breed, and location as inputs, and compares them with the
// local objects memory, returning 1 if a match is found, and 0 if no match is found.
int animals::is_match(char * matching_name, char * matching_breed, char * matching_location)
{
    //This is a variable to return success to the calling function.
    int success = 0;

    //variable to hold 'all' if client chooses to do something with all matches.
    char temp[] = { 'a', 'l', 'l', '\0' };

    //If all values are a match, or all matches, and name is all, return success.
    if((!strcmp(matching_name, temp) || !strcmp(name, matching_name)) && !strcmp(breed, matching_breed) && !strcmp(location, matching_location))
        success = 1;

    return success;
}



//Lets client manually clear an animal object.
int animals::clear_animal(void)
{
    if(breed)
    {
        delete [] breed;
        breed = NULL;
    }
    if(name)
    {
        delete [] name;
        name = NULL;
    }
    if(location)
    {
        delete [] location;
        location = NULL;
    }
    if(story)
    {
        delete [] story;
        story = NULL;
    }
    if(link)
    {
        delete [] link;
        link = NULL;
    }
    if(age)
    {
        delete [] age;
        age = NULL;
    }
    return 1;
}



//return true if breed is null.
int animals::is_empty(void)
{
    if(!breed)
    {
        return 1;
    }
    else
        return 0;
}
