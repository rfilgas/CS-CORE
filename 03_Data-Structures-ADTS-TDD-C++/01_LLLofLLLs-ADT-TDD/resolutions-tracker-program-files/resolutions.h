#include <cstring>
#include <cctype>
#include <iostream>


//-------------------------------------------------------------
// Ryan Filgas
// Assignment_1
// Karla Fant
// CS 163
// 1/18/2021
//
// FILENAME:
// resolutions.h
//
// The purpose of this program is to hold and manage a data
// structure consisting of new years resolutions, their
// corresponding tasks, and each tasks data. This will consist 
// of a list of lists, each sublist containing a struct of
// task data. The sole purpose of this is to create an
// abstract data type to be used by a client function. A test
// program is implemented in place of a client to check for
// errors, and ensure proper function. Each function will
// return an integer to signify success or failure when in use.
//
//
//
//INPUT:
//
// ----resolutions class----
//
// a_resolution.display(void) - none. 
//
// a_resolution.replace(char * new_name) - Char array is passed in from the client
// through the resolution_list class.
//
// a_resolution.transfer_name(resolutions & to_fill) - A resolution object is passed in
// by resolution_list class. 
//
// a_resolution.is_match(char * matching_name) - A char array is passed in by
// resolution_list class.
//
// ----tasks class----
//
// a_task.create_entry(char * to_add_name, float to_add_time_needed, int to_add_priority)
//
// For create_entry,a name, number of hours needed, and priority level
// (int 1-10) are passed in by the client through the resolution_list class.
// 
// a_task.display - none;
// 
// a_task.copy_entry(const tasks & copy_from) - For copy entry, a task object is passed in
// by the resolutions_list class.
//
// a_task.is_larger_priority(tasks & to_add) - A task object is passed in by the resolution_list class. 
//
// ----resolution_list class----
// 
// resolutions_list.add_resolution(resolutions & resolution_to_add) - This function takes
// in a resolution object from the client.
//
// resolutions_list.remove_resolution(char * matching_name) - This function takes
// in a char array from the client.
//
// resolutions_list.add_task(tasks & new_task, char * resolution name) - This function
// takes in a task class object, and char array resolution name to locate the correct
// resolution to transfer the data to.
//
// resolutions_list.display_tasks(char * resolution_name) - This function takes in
// a resolution name from the client.
//
// resolutions_list.display_resolutions(void) - none.
//
//
//OUTPUT:
//
// All functions output 1 for success, and 0 for failure, however some have exceptions.
//
// ----resolutions_class----
//
// a_resolution.display(void) - display outputs 0 for failure, and 1 for success.
// a_resolution.replace(char * new_name) - replace outputs 0 for failure, 1 for success.
// a_resolution.transfer_name - transfer_name outputs 0 for failure, 1 for success.
// a_resolution.is_match(char * matching_name) - is_match returns 1 if the argument matches
// the data inside the object.
//
// ----tasks class----
//  
// a_task.create_entry(char * to_add_name, float to_add_time_needed, int to_add_priority)
// create_entry outputs 1 for success, 0 for failure, and -1 if an invalid priority is added.
// a_task.display(void) - display outputs 1 for success and 0 for failure.
// a_task.copy_entry(const tasks & copy_from) - copy_entry returns 1 for success and 0 for failure. 
// a_task.is_larger_priority - This function outputs 1 if the passed in task has a higher priority, 2 if they are equal.
// and zero if it doesn't.
//
// ----resolutions_list class----
//
// resolutions_list.add_resolution(resolutions & resolution_to_add) - This function returns 1
// for success and zero for failure.
// 
// resolutions_list.remove_resolution(char * matching_name) - This function returns 1 if the
// resolution node was successfully removed, -1 if the list was empty, and zero if no match is found.
//
//
// resolutions_list.add_task(tasks & new_task, char * resolution name) - This function
// returns 1 is task is added, -1 if there were no resolutions to add a task to, -2 if there
// was no name match, and 0 for other failure.
//
//
// resolutions_list.display_tasks(char * resolution_name) - This function returns 1 for success,
// 0 if there's an empty list, and -2 if there's no name match.
//-------------------------------------------------------------


class resolutions
{
    public:
        
        //This is a constructor for the resolutions class, it sets resolution name to NULL.
        resolutions(void);
        //This is a destructor for the resolutions class, it deletes the resolution name
        //and deallocates its memory.
        ~resolutions(void);

        //Display will output the resolution by accessing reto the user by accessingg
        //solution_name in private section. No input necessary.
        int display(void);

        //replace clears the resolution_name if it's not empty, and copies in a new name.
        //It will need a char array as input.
        int replace(char * new_name);

        //transfer name copies from the member object into resolution to_fill.
        // a_resolution.transfer_name(resolution_to_fill)
        int transfer_name(resolutions & to_fill);

        //is_match checks if the supplied char array matches resolution node and returns True/False.
        int is_match(char * matching_name); 

    private:
        //This is the name of the resolution, and the only data member managed by the resolutions class.
        char * resolution_name;
};



class tasks
{
    public:
        
        tasks(void);
        ~tasks(void);

        //create_entry will take in a char array, a float, and an integer and store it into
        //a tasks object.
        int create_entry(char * to_add_name, float to_add_time_needed, int to_add_priority);

        //Display will display the task to the user as requested by the resolutions class.
        int display(void);

        //Copy entry will take the argument and copy it into tasks data members.
        int copy_entry(const tasks & copy_from);

        // is_larger_priority will take in a task as an argument, and return True if the arguments
        // priority is higher.
        int is_larger_priority(tasks & to_add);

    private:
        //The task name is dynamically allocated.
        char * name;
        //This float is the time needed in hours for each task.
        float time_needed;
        //This int is to record the priority of each task.
        int priority;
};


struct task_node
{
    //Task object to hold our task data.
    tasks a_task;
    //This is a pointer to attach to next node.
    task_node * next_task;
};



struct resolution_node
{
     resolution_node(void);
    ~resolution_node(void);

    //This is a resolution node to hold a resolution object; this contains resolution_name.
    resolutions a_resolution;
    //Pointer to the next resolution node. Use resolution_node->next to dereference.
    resolution_node * next_resolution;

    //Beginning of a task LLL for each resolution.
    task_node * task_head;
//    task_node * task_tail;
};



class resolution_list
{
    public:
        
        //This is a constructor for the resolution list class.
        resolution_list(void);
        //This is a destructor for the resolution list class.
        ~resolution_list(void);
        

        //add_resolution takes in a resolution object as an argument and copies the
        //data over to the resolution object inside of the resolution node.
        int add_resolution(resolutions & resolution_to_add);
        //remove_resolution takes in a matching name from the client, and finds the
        //resolution node for which it matches, then removes it from the list.
        int remove_resolution(char * matching_name);
        //add_task takes in a task object and resolution name as arguments, and adds that
        //task to the corresponding resolution.
        int add_task(tasks & new_task, char * resolution_name);
        //Display tasks takes in a resolution name as an argument, and displays all task data.
        int display_tasks(char * resolution_name);
        //display_resolutions takes no arguments, and accesses each nodes resolution
        //object to display the resolution name.
        int display_resolutions(void);

    private:
        //This is a head pointer to point to first resolution node in a resolution LLL.
        resolution_node * resolutions_head;
        //This is a tail pointer to point to last resolution node.
        resolution_node * resolutions_tail; 
}; 






