#include "resolutions.h"
using namespace std;

// ---------------------------------------------
// Ryan Filgas
// Assignment_1
// Karla Fant
// CS 163
// 1/18/2021
//
// FILENAME:
// tasks_class.cpp
//
// The tasks class is the smallest building block of this ADT. It manages name,
// time needed, and priority variables. It's used primarily by the
// resolutions_list class, and resides inside task nodes. Functions include
// create_entry to let a client fill up a task object, display to output the
// contents to the user, copy entry to transfer from a clients task object back
// into the data structure, and is_larger_priority to allow tasks to be sorted
// by the resolution list class.
// ---------------------------------------------



//Constructor to initiate tasks.
tasks::tasks()
{
    //This is a task name for each task in a resolution.
    name = NULL;
    //This records how much time each task will take in hours.
    time_needed = 0;
    //This records the priority that the user sets, and will be used to sort the tasks.
    priority = 0;
}



//destructor to clear dynamic memory.
tasks::~tasks()
{
    //Name is dynamically allocated, it must be deleted.
    if(name) 
        delete [] name;
    //Reset variables.
    time_needed = 0;
    priority = 0;
}



//This function takes in a char *, a float, and an int from the client, then
//inserts it into their own task object.It returns -1 if an invalid number, 1 for success and 0 for failure.
int tasks::create_entry(char * to_add_name, float to_add_time_needed, int to_add_priority)
{
    //Return success to calling routine.
    int success = 0;
    
    if(to_add_priority < 1 || to_add_priority >10)
        success = -1;

    else if(to_add_name && to_add_time_needed)
    {
        //Dynamically allocate memory, and copy into a task, then set other variables.
        //and report success.
        name = new char[strlen(to_add_name) + 1];
        strcpy(name, to_add_name);
        time_needed = to_add_time_needed;
        priority = to_add_priority;
        success = 1;
    }
    return success;
}



//This function displays the contents of a task object.
int tasks::display(void)
{
    //Return success or failure to calling function.
    int success = 0;

    if(name && time_needed)
    {
        cout << "            Task: " << name << "\n";
        cout << "Time to complete: " << time_needed << "\n";
        cout << "        Priority: " << priority << "\n";
        success = 1;
    }
    return success;
}



//This function copies the contents of a task object into the
//private data members in the calling function.
int tasks::copy_entry(const tasks & copy_from)
{
    //Return success or failure to calling function.
    int success = 0;

    //If there's a valid task, move on.
    if(copy_from.name)
    {
        //Allocate memory for name dynamically, then set other variables.
        name = new char[strlen(copy_from.name) + 1];
        strcpy(name, copy_from.name);
        time_needed = copy_from.time_needed;
        priority = copy_from.priority;
        success = 1;
    }
    return success;
}


//This task returns 1 if the task being added is larger than the private data member, and 2 if they are equal.
int tasks::is_larger_priority(tasks & to_add)
{
    //return success or failure to calling routine.
    int success = 0;

    if(to_add.priority > priority)
        success = 1;
    else if(to_add.priority == priority)
        success = 2;
    return success;
}

