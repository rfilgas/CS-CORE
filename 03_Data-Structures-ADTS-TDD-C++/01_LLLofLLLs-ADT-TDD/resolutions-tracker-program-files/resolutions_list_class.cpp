#include "resolutions.h"
using namespace std;


// -----------------------------------------------------------
// RYAN FILGAS
// CS 163
// KARLA FANT
// ASSIGNMENT 1
// 1-18-2021
//
//
// FILENAME:
// resolutions_list_class.cpp
//
// The resolution_list class is the core of this abstract data type. It manages everything
// top down, starting with an array of resolution nodes, and their resolution_tail
// and resolution_head pointers.It works with resolution nodes and task nodes to create linear 
// linked lists of tasks, nested inside linear linked lists of resolutions. Each resolution 
// node contains a resolution_name, a pointer to the next resolution_node, followed
// by two pointers to the contained list of tasks called task_head, and task_tail. Inside each
// task node resides a char * name, a float time_needed, and an int priority. Functions
// include add_resolution, remove_resolution, add_task, display_tasks, and display_resolutions.
//
// -----------------------------------------------------------



//This is a constructor to initiate the resolutions_list class.
resolution_list::resolution_list(void)
{
    //Set all values to NULL just in case.
    resolutions_head = NULL;
    resolutions_tail = NULL;
}



//Recursive destructor for resolution_list.
resolution_list::~resolution_list(void)
{
    //resolution node deletes the node of its next pointer,
    //this will start a chain reaction to delete
    //the rest of the nodes as each nodes destructor
    //is called.
    delete resolutions_head;
}



//Constructor for resolution_node.
resolution_node::resolution_node(void)
{
    //Set all values to Null.
    next_resolution = NULL;
    task_head = NULL;
} 

//Recursive destructor for resolution node.
resolution_node::~resolution_node(void)
{
    //Like the resolutions destructor, each task node will delete the node
    //that it's next pointer is pointing to.
    if(task_head)
        delete task_head;
    if(next_resolution)
        delete next_resolution;
}



//This function adds a resolution by copying the name from the passed in
//resolution object to the current nodes object using the transfer_name function.
int resolution_list::add_resolution(resolutions & resolution_to_add)
{
    //Report success or failure back to calling routine. 
    int success = 0; 

    //Case 1: Add to an empty list if head is null.
    if(!resolutions_head)
    {
        resolutions_head = new resolution_node;
        resolutions_tail = resolutions_head;
        resolutions_tail -> next_resolution = NULL;
        
        //This is a function call to transfer_name.
        success = resolution_to_add.transfer_name(resolutions_tail -> a_resolution);
    }

    //Case 2: Add to list with members.
    //Tail allows adding to the end of the list without traversal.
    else if(resolutions_head)
    {
        resolutions_tail -> next_resolution = new resolution_node;
        resolutions_tail = resolutions_tail->next_resolution;
        resolutions_tail->next_resolution = NULL;
       
        //This is a function call to transfer_name, and will report success or failure.
        success = resolution_to_add.transfer_name(resolutions_tail -> a_resolution);
    }

    return success;
}



//This function removes a resolution by checking each nodes list object for a matching name,
//deleting the node, and reconnecting the pointers.It uses the resolution function is_match
//to compare names.
int resolution_list::remove_resolution(char * matching_name)

{
    int success = 0;

    resolution_node * current = resolutions_head;
    resolution_node * previous = current;

    //If there aren't any resolutions to delete, throw an error code.
    if(!resolutions_head)
            success = -1;

    //If there are resolutions to traverse, start checking them.
    if(resolutions_head)
    {
        //Case 1:If heads resolution is a match.
        if(resolutions_head -> a_resolution.is_match(matching_name))
        {
            //There are more nodes to connect.
            if(current -> next_resolution)
            {
                resolutions_head = resolutions_head -> next_resolution;
                delete current;
                previous = NULL;
                current = NULL;
                success = 1;
            }

            //If head is the only node and not a match, delete, and set to null.
            else
            {
                delete resolutions_head;
                resolutions_head = NULL;
                resolutions_tail = NULL;
                previous = NULL;
                current = NULL;
                success = 1;
            }
        }

        //Case 2: The member to delete is tail.
        else if(resolutions_tail -> a_resolution.is_match(matching_name))
        {
            while(current -> next_resolution)
            {
                previous = current;
                current = current -> next_resolution;
            }
            delete resolutions_tail;
            previous -> next_resolution = NULL;
            resolutions_tail = previous;
            current = NULL;
            success = 1;
        }


        //Case 3: The node to delete is in middle. 
        else if(resolutions_head -> next_resolution)
        {
            
            while(current -> next_resolution)
            {
           
                if(current -> a_resolution.is_match(matching_name))
                {
                    previous -> next_resolution = current -> next_resolution;
                    delete current;
                    current = current -> next_resolution;
                    success = 1;
                }

                else
                {
                    previous = current;
                    current = current -> next_resolution;
                }
            }
        }
    }
    return success;
}



// This function takes a task object and resolution name as arguments. It will first
// traverse resolution nodes until it has found the matching resolution. It will then
// traverse and insert a task object into the list ordered by priority. It relies on
// the resolution_match function to traverse resolutions of the resolutions_class and 
// the is_larger_priority function of the task_class to traverse task nodes. The task
// traversal stops when a lower priority task is found, the node is then inserted before
//using a previous pointer when necessary.
int resolution_list::add_task(tasks & new_task, char * resolution_name)
{
   
    int success = 0;

    resolution_node * current_resolution = resolutions_head;

    task_node * current_task;
    task_node * previous_task;
    task_node * temp;
    
    //The list is empty, throw an error code and proceed.
    if(!resolutions_head)
        success = -1;

    //If the resolution list isn't empty, do the below.
    if(resolutions_head)
    {
        //While the next node isn't null, and we haven't found a match yet, keep traversing.
        while(current_resolution -> next_resolution && !current_resolution -> a_resolution.is_match(resolution_name))
        {
            if(current_resolution -> next_resolution != NULL) 
            {
                current_resolution = current_resolution -> next_resolution;
            }
        }

        // We're stopped at a resolution node, but it could be head or tail, and there
        // might not be a name match. If there's no match throw an error code.
        if(!current_resolution -> a_resolution.is_match(resolution_name))
            success = -2;

        //Verify resolution match and start traversing task list.
        if(current_resolution -> a_resolution.is_match(resolution_name))
        {

            //Case 1: There are no tasks, add one and set next to null.
            if(!current_resolution -> task_head)
            {
                current_resolution -> task_head = new task_node;
                current_resolution -> task_head -> next_task = NULL;
                current_resolution -> task_head -> a_task.copy_entry(new_task);
             //   current_resolution -> task_tail = current_resolution -> task_head;
                success = 1;
            }

            //Case 2: Insert at the beginning if the task to add is largest.
            else if(current_resolution -> task_head -> a_task.is_larger_priority(new_task))
            {
                temp = new task_node;
                temp -> next_task = current_resolution -> task_head;
                current_resolution -> task_head = temp;
                temp -> a_task.copy_entry(new_task);
                temp = NULL;
                success = 1;
            }

            //Case 3: Insert task ordered.
            else if(current_resolution -> task_head -> next_task)
            {
                current_task = current_resolution -> task_head;

                //Traverse until new_task priority is larger than current task priority (unless first task is equal),stop at end.
                //If the first task is equal, just insert. Don't traverse.
                while(!current_task -> a_task.is_larger_priority(new_task) && (current_task -> a_task.is_larger_priority(new_task) != 2))
                {   
                    if(current_task -> next_task)
                    {
                    previous_task = current_task;
                    current_task = current_task -> next_task; 
                    }
                }

                //Case 3a: If the next task is a smaller priority, insert before it.
                if(current_task -> next_task -> a_task.is_larger_priority(new_task)) // new
                { 
                temp = new task_node;
                temp -> a_task.copy_entry(new_task);
                previous_task -> next_task = temp;
                temp -> next_task = current_task;
                temp = NULL;
                success = 1;
                } 
                
                //Case 3b: Last task is larger than new task. We  already traversed this far. Let's check the last node, and add a new one.
                else if(!current_task -> next_task -> a_task.is_larger_priority(new_task))
                {
                    previous_task = current_task;
                    current_task = current_task -> next_task; 
                    current_task -> next_task = new task_node;
                    current_task = current_task -> next_task;
                    current_task -> next_task = NULL;
                    current_task -> a_task.copy_entry(new_task);
                    success = 1;
                }
            }
        }
    }
    return success;
}



//This function takes in a resolution name, and displays each tasks data.
//It first traverses the resolution list, and uses the is_match function
//from the resolution class to confirm a stopping point at the correct node.
int resolution_list::display_tasks(char * resolution_name)
{
    int success = 0;
    int is_match_temp;
    
    resolution_node * current_resolution = resolutions_head;
    task_node * current_task;
    
    //If the list is empty, throw an error code.
    if(!resolutions_head)
        success = -1; 

    //if the list has nodes, traverse them.
    if(resolutions_head)
    {

        //While next isn't null, and a match hasn't been found, keep traversing.
        while(current_resolution -> next_resolution && !current_resolution -> a_resolution.is_match(resolution_name))
        {
            if(!current_resolution -> next_resolution) 
            {
                current_resolution = current_resolution -> next_resolution;
            }
        }
        
        //Check if matching, so program doesn't have to execute match function repetitively.
        is_match_temp = current_resolution -> a_resolution.is_match(resolution_name);

        //Throw an error if this resolution name isn't a match. We may have
        //gotten to the end of the list without a match.
        if(!is_match_temp)
            success = -2; 

        //If it is a match, check to see if there is a list, and throw
        //an error code if not.
        else if(!current_resolution -> task_head)
            success = 0; // no tasks added
       
        //If resolution is a match and there's a task list, start traversing to display.
        if(is_match_temp && resolutions_head -> task_head)
        {        
            current_task = resolutions_head -> task_head;

            //Display until there's nothing left to display.
            while(current_task)
            {
                current_task -> a_task.display(); 
                current_task = current_task -> next_task;
            }
            success = 1;
        }

    }
    return success;
}



//This function traverses resolution nodes, displaying the name of each one
//using the reolution classes display function.
int resolution_list::display_resolutions(void)
{
    int success = 0;
    resolution_node * current = resolutions_head;

    //If there are nodes to traverse return True.
    if(resolutions_head)
        success = 1;
    
    //Traverse until the end displaying each node.
    while(current)
    {
        current -> a_resolution.display();
        cout << "\n";
        current = current -> next_resolution;
    }
    return success;
}


