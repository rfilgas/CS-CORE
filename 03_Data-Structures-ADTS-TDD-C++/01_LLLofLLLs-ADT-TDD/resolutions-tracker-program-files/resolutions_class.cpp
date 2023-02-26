#include "resolutions.h"
using namespace std;



// -------------------------------
// Ryan Filgas
// Assignment_1
// Karla Fant
// CS 163
// 1/18/2021
//
//
// FILENAME:
// resolutions_class.cpp
//
// The resolutions class is responsible for managing operations related to 
// the resolution name. Resolution objects reside in a resolution node which is managed by
// the resolution_list class. is_match is integral to traversing resolution nodes, and
// is heavily used. The only inputs here will be charactar arrays to compare to the
// resolution name. Outputs will include 0 for false, and 1 for true.
// -------------------------------



//Constructor to initiate resolution_name.
resolutions::resolutions(void)
{
    resolution_name = NULL;
}



//Destructor to clear dynamic memory.
resolutions::~resolutions(void)
{
    if(resolution_name)
        delete [] resolution_name;
    resolution_name = NULL;
}



//This displays the resolution by accessing resolution_name in private section.
int resolutions::display(void)
{
    //Return success or failure to the calling function.
    int success = 0;

    //If the resolution name has content, output it, and report success.
    if(resolution_name)
    {
        cout << "Resolution: " << resolution_name << "\n";
        success = 1;
    }
    return success;
}



//This clears resolution_name if it's not empty, and copies in a new name.
int resolutions::replace(char * new_name)
{
    //Report success to calling routine.
    int success = 0;

    //If the pointer isn't null, proceed.
    if(new_name)
    {
        //Make sure resolution_name is clear before copying.
        if(!resolution_name)
            resolution_name = NULL;

        //Dynamically allocate memory.
        resolution_name = new char[strlen(new_name) + 1];
        strcpy(resolution_name, new_name);
        success = 1;
    }

    //Return 1 to the calling routine if successful, 0 if there was a problem.
    return success;
}



//This function takes a resolution as input, and fills it with the new name.
int resolutions::transfer_name(resolutions & to_fill)
{
    //Return success to the calling routine. 
    return to_fill.replace(resolution_name);
}



//This function takes in a possible resolution name, moves it to temporary variables
//along with the resolution name, converts everything to lowercase for comparing,
//and returns true if the two names are a match.
int resolutions::is_match(char * matching_name)
{
    //This is a variable to convert matching_name to lowercase. 
    char * lowercase;
    //This is a variable to convert resolution_name to lowercase.
    char * match;
    //This is a control variable for 'for' loop.
    int name_size = strlen(matching_name + 1); 

    //Allocate dynamic memory for temporary variables.
    lowercase = new char[strlen(matching_name) + 1];
    match = new char[strlen(resolution_name) + 1];
    
    //Copy to temporary variables..
    strcpy(match, resolution_name);
    strcpy(lowercase, matching_name);

    //Make all letters lowercase to compare.
    if(strlen(lowercase) == strlen(match))
    {
        for(int i = 0; i < name_size; ++i)
        {
          lowercase[i] = tolower(lowercase[i]);
          match[i] = tolower(match[i]);
        }
    }

    //Return 1 for sucess, and 0 for failure to the calling routine.
    return !strcmp(match, lowercase);
}



