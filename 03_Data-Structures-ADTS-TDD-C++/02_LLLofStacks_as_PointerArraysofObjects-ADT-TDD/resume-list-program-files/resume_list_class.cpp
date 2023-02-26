#include "resume.h"
#include <cstring>
#include <cctype>
#include <iostream>

// -------------------------------------------------------------------------
// Ryan Filgas
// Assignment_2
// Karla Fant
// CS 163
// 1/31/2021
//
// Filename:
// resume_list_class.cpp
//
// The purpose of the resume_list class is to manage the overall structure of the ADT,
// smd provide functiond for the client to use directly in the implementation
// of the data structure to abstract the process of manipulating the data. This
// data type is a linear linked lists of experience class objects, each of which contain
// 5 char arrays of experience class members. The overall implementation is done with
// the purpose of creating a resume using a stack implementation. In other words
// the client program is able to push new objects onto the stack, pop them off, check
// if the stack is empty, display all experiences, and initiate the stack. As this
// is an ADT, only the display function outputs to the user, and every function will
// return success back to the client program.This data structure is useful if you need
// the data put in first to come out or display last.
// -------------------------------------------------------------------------


//This is a constructor for the node struct.
//It sets its next pointer to NULL.
node::node(void)
{
    next = NULL;
}



//This is a destructor for the node struct; it will delete
//it's own data, then initiate the destructor for the next node.
node::~node(void)
{
  //  if(next)
        delete next;
  //  if(experience_array)
        delete [] experience_array;
}



//This is a constructor for the resume_list class;
//it sets head to NULL, and the index for the top of the stack to 0.
resume_list::resume_list(void)
{
    head = NULL;
    index_top = 0;
}



//This is a destructor for the resume list class. It deletes head,
//and recursively calls delete on every other node through the next pointer.
//The destructor then sets its index to zero.
resume_list::~resume_list(void)
{
    delete head;
    index_top = 0;
}



// The initiate stack function will check if head is null, then allocate a new
// node if there isn't one, and allocate memory for the experience array.
// This function returns 1 for success, and 0 if the list wasn't empty.
int resume_list::initiate_stack(void)
{
    //This is a variable to return success or failure to the calling routine.
    int success = 0;

    //If head is null, make a new node,fill it, and set its next pointer to NULL.
    if(!head)
    {
        head = new node;
        head -> next = NULL;
        head -> experience_array = new experiences[MAX];
        //Report success.
        success = 1;
    }
    return success;
}



// The push function takes in an experience object from the client by reference,
// and copies it into resume_list's data structure. It returns 1 for success
// if an object has been pushed onto the stack, and 0 for failure.
int resume_list::push(const experiences & copy_from)
{
    //This variable is to return success or failure to the calling function.
    int success = 0;

    //This node is to hold onto a pointer for later use.
    node * hold;
  
    //Case 1: Empty list: If the list is empty, allocate the memory, and copy 
    //into the first nodes experience array.
    if(!head)
    {
        //use initiate_stacks return to report success.
        success = initiate_stack();
        //Copy the entry.
        head -> experience_array[index_top].copy_entry(copy_from);
        //Increment top since we added a new experience.
        ++index_top;
    }

    //Case 2: We have between 0 and 4 entries, so add data into the top of the
    //stack, and increment top.
    else if(index_top < MAX)
    {
        success = head -> experience_array[index_top].copy_entry(copy_from);
        ++index_top;
    }

    //Case 3: The node is full, make a new one, and fill index 0 of the array with data.
    else if(index_top >= MAX)
    {
        //The node is full, so reset the index to zero so we can access the top of the next
        //node's data.
        index_top = 0;

        //Hold onto heads node, make a new node with the head pointer, and recconect
        //heads next container to the old head pointer.
        hold = head;
        head = new node;
        head -> next = hold;
        head -> experience_array = new experiences[MAX];

        //Use the copy_entry's return to report success back to the push function.
        success = head -> experience_array[index_top].copy_entry(copy_from);
        //Increment top to indicate there's another data item.
        ++index_top;
    }
    return success;
}



//The display function uses the display_experience function from the experience class.
//This will return 1 for success, and 0 for an empty list.
int resume_list::display(void)
{
    //Temporary to keep track of where data is stored in relation to index_top.
    int data_index = index_top - 1;
  
    //If head is NULL, suspend execution of function.
    if(!head)
        return 0;
  
    int experience_count = 0;
    node * current = head;
  
    //Display the first nodes data.
    for(int i = data_index; i > -1; --i)
    {
           experience_count += (current -> experience_array[i].display_experience());
    }

    //If there's another node to display, traverse and display the rest of the list.
    //We can assume the next nodes will always be full, but first, we must check
    //if there are other nodes to display.
    if(current -> next)
    {
        current = current -> next;

        //Until the end of the list is reached, count the number of experiences, and
        //display each one, then traverse to the next.
        do
        {
            //Display every other nodes data from the top of the node, down to the bottom.
            //Since we already displayed the first node, we can assume the rest are full
            //because of the stack implementation.
            for(int i = (MAX - 1); i > -1; --i)
            {
                experience_count += (current -> experience_array[i].display_experience());
            }
            current = current -> next;
        }while(current);
    }
    current = NULL;
    return experience_count;
}



//The pop function clears the experience at the top of the stack, and returns the object
//by reference back to the client. It reports 1 for success, and 0 if the stack was empty.
int resume_list::pop(experiences & to_fill)
{
    int data_index = index_top - 1;
    int success = 0;
    node * hold;

    //Case 1: The list is empty, report failure,
    if(!head)
        success = 0;

    //Case 2: There is one item in the list. Return to object to the calling function,
    //report success, and delete head.
    else if(index_top == 1 && !head -> next)
    {
        success = to_fill.copy_entry(head -> experience_array[data_index]);
        delete head;
        head = NULL;
    }

    //case 3: There is one item left in first node, and multiple nodes left in stack.
    //Report success and return the object. Delete this node, and traverse head
    //to the next.
    else if(index_top == 1 && head -> next)
    {
        success = to_fill.copy_entry(head -> experience_array[data_index]);
        hold = head;
        head = head -> next;
        hold -> next = NULL;
        delete hold;
        hold = NULL;
        index_top = MAX;
    }

    //case 4: There is more than one item in stack. Copy data, clear the experience, and 
    //decrement index.
    else if(index_top > 1)
    {
        success = to_fill.copy_entry(head -> experience_array[data_index]);
        head -> experience_array[data_index].clear_experience();
        --index_top;
    }
    return success;
}



// The peek function returns the object at the top of the stack to the client by reference.
// It will return 1 if head is there, and the data is copied, 0 otherwise.
int resume_list::peek(experiences & to_fill)
{
    //This is a local variable to return success or failure to the calling routine.
    int success = 0;
    if(head)
        success = to_fill.copy_entry(head -> experience_array[index_top - 1]);
    return success;
}



//is_empty checks if head is NULL, and returns False if the list has members.
int resume_list::is_empty(void)
{
    //This is a local variable to return success or failure to the calling routine.
    int success = 1;
    //If head isn't NULL, the list is empty.
    if(head)
        success = 0;
    return success;
}
