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
// favorites_list.cpp
//
// The purpose of this file is to manage the favorites class which is an
// implementation of a queue. It includes functions enqueu, dequeue,
// display all, peek, and is_empty. The implementation takes the form
// of a circular linked list where each node holds an animals class
// object. When data is loaded, it's added to the back, and when it's
// removed, data is added to the front. This is a good adt to use
// if you need your data to follow the first in first out order. All
// functions in the adt will return success or failue back to the client.
// -------------------------------------------------------------------------



//This is the node constructor for the favorites list class.
qnode::qnode()
{
    next = NULL;
};



//This is a node destructor for the favorite list class.
qnode::~qnode()
{
    next = NULL;
};



//This is a constructor for the favorite list class.
favorite_list::favorite_list(void)
{
    rear = NULL;
}



//This is a destructor for the favorites list class, it
//checks the list if null, then sets rear to null, and
//iterates through the list, deleting each node.
favorite_list::~favorite_list(void)
{
    if(rear)
    {
        qnode * temp = rear -> next;
        rear -> next = NULL;
        while(temp)
        {
            rear = temp;
            temp = temp -> next;
            delete rear;
        }
        temp = NULL;
        rear = NULL;
    }
}



// the initiate function will return 1 if the list is initiated, and 0 if there exists a list.
int favorite_list::initiate_queue(void)
{
    //This is a variable to return success to the callign function.
    int success = 0;

    // if rear is null, allocate a new node, and set the next pointer to rear.
    if(!rear)
    {
        rear = new qnode;
        rear -> next = rear;
        success = 1;
    }
    return success;
}



//enqueue will take in an animal object by reference, and copy it into a new node
//at the end of the list. Enqueue will return 1 for success, and 0 for failure.
int favorite_list::enqueue(animals &to_add)
{
    // This is a variable to return success.
    int success = 0;

    //This is a pointer to assist with holding and traversal.
    qnode * current = rear;

    //CASE 1: List is empty.
    if(!rear)
    {
        if(initiate_queue())
            success = rear -> animal.copy_entry(to_add);
    }

    // CASE 2: List is full.
    else 
    {
        current = new qnode;
        current -> next = rear -> next;
        rear -> next = current;
        rear = current;
        current = NULL;
        success = rear -> animal.copy_entry(to_add);
    }
    return success;
}


//The dequeue function will take an animal to fill by reference, copy the first
//nodes data, delete the first node, then return success. 
int favorite_list::dequeue(animals &to_fill)
{
    // This is a variable to return success.
    int success = 0;
    
    //This is a pointer to assist with holding and traversal.
    qnode * hold;

    //Case 1: List is NULL;
    if(!rear)
        return 0;

    //Case 2: 1 Node Left
    hold = rear -> next;
    if(rear == rear -> next)
    {
        success = to_fill.copy_entry(rear -> animal);
        rear -> next = NULL;
        delete rear;
        rear = NULL;
    }

    //Case 2:List is full.
    else
    {
        rear -> next = hold -> next;
        success = to_fill.copy_entry(hold -> animal);
        delete hold;
        hold = NULL;
        //Case 3: We deleted the last node, and need to set rear to NULL.
        //Since hold will have deleted the same node rear is pointing to,
        //the next pointer will have been set to NULL, and rear points to garbage.
        if(!rear || !rear -> next)
            rear = NULL;
    }
    return success;
}



//This function iterates through the CLL displaying each node until it hits the end,
//and it will return the number of nodes displayed.
int favorite_list::display_all(void)
{
    // This is a variable to return success.
    int success = 0;

    //This is a pointer to assist with holding and traversal.
    qnode * current = rear;
    
    //Case 1: rear is NULL
    if(!rear)
        return 0;

    //Display each entry, traversing until current is at rear, while summing each displayed node.
    do
    {
        success += current -> animal.display_entry();
        current = current -> next;
    }while(current != rear);

    return success;
}



//This function will fill an animal object passed by reference with the data from the first
//node.
int favorite_list::peek(animals & to_fill)
{
    // This is a variable to return success.
    int success = 0;

    //If list is empty, return failure.
    if(!rear)
        return 0;
    //if list has more than one node, copy next nodes data and return success.
    if(rear != rear -> next)
        success = (to_fill.copy_entry(rear -> next -> animal));
    //If list has more than one item,copy heads data and return success. 
    else
        success = (to_fill.copy_entry(rear -> animal));
    return success;
}



// is_empty will return 1 if rear is null.
int favorite_list::is_empty(void)
{
    int success = 0;
    if(!rear || (rear -> animal.is_empty()))
        success = 1;
    return success;
}
