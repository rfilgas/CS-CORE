#include "resume.h"
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;



// -------------------------------------------------------------------------
// Ryan Filgas
// Assignment_2
// Karla Fant
// CS 163
// 1/31/2021
//
// Filename:
// experience_class.cpp
//
// The experience class is responsible for managing operations on the experience class
// data members. It's members include create_entry, copy_entry, display, and clear.
// Create entry will allow the client to program to enter data ubti its own experience
// object, and then pass that object through the copy entry function to transfer the
// data into the resume_classes data structure. Clear entry can be used by the client,
// and is also used by the resume class, as is true for the display function. All functions
// will return 0 for failure and 1 for success. Failures will generally mean that input data
// was missing.
// -------------------------------------------------------------------------


//This is a constructor for the experience class, initiate all members to NULL;
experiences::experiences()
{
   employer_name = NULL;
   start_date = NULL;
   end_date = NULL;
   job_title = NULL;
   responsibilities = NULL;
};



//This is a destructor for the experience class, it will check each member for data
//and delete if there is any, then set those values to NULL;
experiences::~experiences()
{
    if(employer_name)
    {
        delete [] employer_name;
        employer_name = NULL;
    }

    if(start_date)
    {
        delete [] start_date;
        start_date = NULL;
    }

    if(end_date)
    {
        delete [] end_date;
        end_date = NULL;
    }

    if(job_title)
    {
        delete [] job_title;
        job_title = NULL;
    }

    if(responsibilities)
    {
        delete [] responsibilities;
        responsibilities = NULL;
    }
};



//The display_experience class will check that all data members are present, 
//and display them to the user. This function is used in the resume_list class
//to display all experiences. It will return 1 if the display was successful
//and 0 if experience members were missing.
int experiences::display_experience()
{
    //This is a variable to return success to the calling function.
    int success = 0;
    
    //If all class members are there, display them.
    if(employer_name && start_date && end_date && job_title && responsibilities)
    {
        cout << "Employer     : " << employer_name << "\n";
        cout << "Start date   : " << start_date << "\n";
        cout << "End date     : " << end_date << "\n";
        cout << "Job Title    : " << job_title << "\n";
        cout << "Responsibilities included : " << responsibilities << "\n";
        success = 1;
    }
    return success;
}



//The copy_entry function takes an experience object by reference, and copies it into
//the calling class objects data. It will clear any data left inside, so be careful
//not to delete anything important. The function will return 1 for success, or
//zero if either the members weren't cleared, or input data wasn't present.
int experiences::copy_entry(const experiences & copy_from)
{
    //This is a variable to return success or failure.
    int success = 0;


    //If all elements have been cleared, and are available to copy, allocate memory, and copy them.
    if(clear_experience() && copy_from.employer_name && copy_from.start_date && copy_from.end_date && copy_from.job_title && copy_from.responsibilities)
    {
        employer_name = new char[strlen(copy_from.employer_name) + 1];
        strcpy(employer_name, copy_from.employer_name);

        start_date = new char[strlen(copy_from.start_date) + 1];
        strcpy(start_date, copy_from.start_date);

        end_date = new char[strlen(copy_from.end_date) + 1];
        strcpy(end_date, copy_from.end_date);

        job_title = new char[strlen(copy_from.job_title) + 1];
        strcpy(job_title, copy_from.job_title);

        responsibilities = new char[strlen(copy_from.responsibilities) + 1];
        strcpy(responsibilities, copy_from.responsibilities);

        //Everything is copied. Return Success.
        success = 1;
    }
    return success;
}



//The create_entry function allows the client to input data into their own experience object.
//It takes 5 char arrays as input, and returns 1 for success, zero for failure.
int experiences::create_entry(char the_employer_name[], char the_start_date[], char the_end_date[], char the_job_title[], char the_responsibilities[])
{
    //This is a variable to return success or failure.
    int success = 0;

    //If data members have been cleared, allocate memory for each class member, and copy the data.
    if(clear_experience())
    {
        employer_name = new char[strlen(the_employer_name) + 1];
        strcpy(employer_name, the_employer_name);

        start_date = new char[strlen(the_start_date) + 1];
        strcpy(start_date, the_start_date);

        end_date = new char[strlen(the_end_date) + 1];
        strcpy(end_date, the_end_date);

        job_title = new char[strlen(the_job_title) + 1];
        strcpy(job_title, the_job_title);

        responsibilities = new char[strlen(the_responsibilities) + 1];
        strcpy(responsibilities, the_responsibilities);

        //Data was successfully copied, return 1.
        success = 1;
    }
    return success;
}



//This is a function to clear experience objects manually without
//calling the destructor.It will return 1 for success when complete.
int experiences::clear_experience(void)
{
    if(employer_name)
    {
        delete [] employer_name;
        employer_name = NULL;
    }

    if(start_date)
    {
        delete [] start_date;
        start_date = NULL;
    }

    if(end_date)
    {
        delete [] end_date;
        end_date = NULL;
    }
    if(job_title)
    {
        delete [] job_title;
        job_title = NULL;
    }
    if(responsibilities)
    {
        delete [] responsibilities;
        responsibilities = NULL;
    }
    return 1;

}
