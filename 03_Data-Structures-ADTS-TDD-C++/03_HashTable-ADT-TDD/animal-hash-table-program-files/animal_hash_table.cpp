#include "animal.h"
#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>

using namespace std;

// -------------------------------------------------------------------------
// Ryan Filgas
// Assignment_3
// Karla Fant
// CS 163
// 02/16/2021
//
// Filename:
// animal_hash_table.cpp
//
// The purpose of this file is to implement the hash table ADT, and provide functions
// for the client to use in the implementation of the data structure to abstract
// the process of manipulating the data. The basic operation of the hash table
// is the hash function which will take in two char arrays, and use a mathematical
// algorithm to select a unique index based on those arrays where data will be inserted.
// If there are collisions in the data, that is more than one pieces of data are
// transfered to the same index, they'll be inserted at the beginning of a linear linked
// list for each index. The operations of this ADT are add, load, display, remove, retrieve,
// and remove all. As this is an ADT, only the display function outputs to the user, 
// and every function will return success back to the client program.This data structure
// is useful if you need quick data access, but are unconcerned with ordered data.
// -------------------------------------------------------------------------



//This is the node constructor and destructor for the hash table class.
node::node()
{
    next = NULL;
};

node::~node()
{
    next = NULL;
};



//This is the constructor for the hash table. It takes in a table size, creates a node**
//array, and sets each elemebts head pointer to NULL.
animal_hash_table::animal_hash_table(int size)
{
    // Initiate hash table.
    table = new node*[size];

    //Set a pointer to the beginning of the table, and iterate setting all nodes to null.
    node** ptr = table;
    for(int i = 0; i < size; ++i)
        *ptr++ = NULL;
}



//This is a destructor for the hash table ADT. This function iterates through the hash table
//checking for data, and deleting any attached linear linked lists.
animal_hash_table::~animal_hash_table()
{
    //Point temp variable to beginning of hash table.
    node ** ptr = table;

    //for each element in the hash table, if the indexes head
    //pointer isn;t null, iterate through the chain, deleting each node.
    for(int i = 0; i < tablesize; ++i)
    {
        //delete LLL
        if(*ptr)
        {
            node * current = (*ptr);
            node * follow = current;
            do
            {
                current = current -> next;
                delete follow;
                follow = current;

            }while(current);
            *ptr = NULL;
        }
        ++ptr;
    }
    delete [] table;
    table = NULL;
}



//This is the hash function for the hash table. This function takes in two char arrays,
//one for breed, and another for location. It then passes these to a helper function
//and returns the result modded by a prime number sized has table.
int animal_hash_table::hash_function(char * breed_to_hash, char * location_to_hash)
{
    //This is an int to hold the output from the hash table helper.
    int hash_number = 0;

    //If the hashing function is successful for both entries, return the caught value, and mod it
    //by the size of the table to determine the index.
    if(hash_helper(breed_to_hash, hash_number) && hash_helper(location_to_hash, hash_number))
        return hash_number % tablesize;
    else
        return 0;
}



//This is a hash_helper function to perform the calculations. Because this function can
//be called repetetively, the hash index can be changed with as many inputs as desired, without
//the need for concatenating data. The function takes in a char array to use for the hash
//algorithm, and adjusts the hash number by reference, returning success.
int animal_hash_table::hash_helper(char * to_hash, int &hash_number)
{
    //Creating a temp variable to protect head pointer.
    char * ptr = to_hash;

    //Create a dereferenced version of ptr to be the head of the list.
    int temp = *ptr;

    //Store the size of to_hash to use with for loop.
    int size = strlen(to_hash);

    //For every odd number, divide hash number by the letter, for every even number
    //cube the letter and add it to hash number.
    for(int i = 0; i < size; ++i)
    {
        temp = *ptr;
        if(i % 2 == 0)
            hash_number += (temp * temp * temp);
        else
            hash_number = (hash_number / temp - (hash_number % temp));
        ++ptr;
    }
    ptr = NULL;
    return 1;
}



//This was an experimental adaptation of the hashing function. I discovered that multiplying
//the data by certain fixed amounts can cause more data clustering than my previous method.
/*
int animal_hash_table::hash_helper(char * to_hash, int &hash_number)
{
    char * ptr = to_hash;
    int temp = *ptr;
    int size = strlen(to_hash);

    //For every odd number,multiply by 7 and divide hash number by the letter, for every even number
    //multiply by digits of pi and 87.
    for(int i = 0; i < size; ++i)
    {
        temp = *ptr;
        if(i % 2 == 0)
            hash_number += (temp * 3.14159265 * 87);
        else
            hash_number = (7 * hash_number / temp - (hash_number % temp));
        ++ptr;
    }
    ptr = NULL;
    return 1;
}
*/



// The add animal function will take an animals object as input, run the animal through the hash
// function where it will insert the object into the array. This function will return the number of
// animals in the chain.
int animal_hash_table::add_animal(animals &to_add)
{
    // These are temporary node pointers to assist with adding.
    node * temp = NULL;
    node * current = NULL;

    //These are temporary arrays to assist with using the hash function to find the index.
    char * temp_location = NULL;
    char * temp_breed = NULL;

    //Return success to the calling function.
    int success = 0;

    //This is to hold the hash index for inserting.
    int index = 0;

    //If passed in object has data, copy it, and return success, then proceed to
    //execute the rest of the function.
    if(to_add.copy_entry(temp_breed, temp_location))
    {
        //Find the index to add to.
        index = hash_function(temp_breed, temp_location);

        //If the head at the desired index is null, initiate the node, and fill it.
        if((*(table + index)) == NULL)
        {
            (*(table + index)) = new node;
            success = (*(table + index)) -> animal.copy_entry(to_add);
        }
        //Otherwise insert at the beginning, reconnect nodes, and copy data into node.
        else
        {
            temp = (*(table + index));
            current = temp -> next;
            temp -> next = new node;
            temp = temp -> next;
            temp -> next = current;

            //Copy entry and catch returned value to give to client.
            success = temp -> animal.copy_entry(to_add);
        }
    }

    //Deallocate dynamic memory.
    delete [] temp_location;
    delete [] temp_breed;
    temp_location = NULL;
    temp_breed = NULL;

    return success;    
}



//The display_animal function will access the hash table via the hash function by taking in
//matching_breed, and matching_location from the client. It will return the number of matches.
int animal_hash_table::display_animal(char matching_breed[], char matching_location[])
{
    //This is a variable to keep track of indexed location in table.
    node ** temp = table;

    //This is a node pointer to assist with traversal of LLLs.
    node * current = NULL;

    //This is a variable to return success to the user.
    int success = 0;

    //This is a variable to keep track of returned hash table index.
    int index = 0;

    //This will allow the client to input all instead of a name, in order to display
    //multiple matchs.
    char temp_name[] = { 'a', 'l', 'l', '\0' };
    char * new_name;
    new_name = new char[strlen(temp_name) + 1];
    strcpy(new_name, temp_name);

    //Use the hash function to retrieve the proper index by passing in breed, and location.
    index = hash_function(matching_breed, matching_location);

    //Set current node to hashed index.
    current = *(temp + index);

    //while there is data to traverse, check each node for matches, and diaplay
    //data for each match.
    if(current)
    {
        while(current)
        {
            if(current -> animal.is_match(new_name, matching_breed, matching_location))
                success += current -> animal.display_entry();
            current = current -> next;
        }
    }
        current = NULL;
        temp = NULL;
        delete [] new_name;
        new_name = NULL;

    return success;
}



//The remove animal function takes in name, breed, and location from the calling function,
//uses the breed and location to find it's index in the hash table, then checks each piece of data
//if there is a chain, deleting the match, or all matches if 'all' is the input. This function
//returns the number of animal objects removed.
int animal_hash_table::remove_animal(char matching_name[], char matching_breed[], char matching_location[])
{
    //This is a node pointer to assist with LLL traversal.
    node * current;

    //This is a variable to return success to the calling function.
    int success = 0;

    //Keep track of hash index.
    int index = 0;

    //Get index location by passing in breed and location to hash function.
    index = hash_function(matching_breed, matching_location);

    //Set current to the returned index.
    current = *(table + index);

    //If there isn't anything, we have no match. Return failure.
    if(!current)
        success = 0;

    //If head is a match, delete it, and set the pointer to NULL.
    else if(current -> animal.is_match(matching_name, matching_breed, matching_location)&& !current -> next)
    {
       delete *(table+index);
       *(table+index) = NULL;
       success = 1;
    }
    else
        //Call recursive helper function to remove any matches, and catch returned value.
        success = remove_animal(current, matching_name, matching_breed, matching_location); 
    return success;
}



//This is a recursive helper function to assist in removing animal objects. It takes in
//a head pointer in addition to the normal matching data.
int animal_hash_table::remove_animal(node * &head, char matching_name[], char matching_breed[], char matching_location[])
{
    if(!head)
        return 0;

    //If match is found, delete node, and connect previous and next node together, counting the
    //deleted node in the return.
    if(head -> animal.is_match(matching_name, matching_breed, matching_location))
    {
        node * temp = head;
        head = head -> next;
        delete temp;
        return 1 + remove_animal(head, matching_name, matching_breed, matching_location);
    }
    else
        //Return without counting, there isn't a match.
        return remove_animal(head -> next, matching_name, matching_breed, matching_location);
}



//This is a function to retrieve an animal object from the hash table. It takes in name, breed, and location as charr arrays, an empty array from the client to fill, and the clients array size. It will return the number of items retrieved. The function works by using breed and location to find the index using the hash function, then it will check each piece of data at that index, and load any matches into the
//passed in array.
int animal_hash_table::retrieve_animal(char matching_name[], char matching_breed[], char matching_location[], animals * &array, int &array_size)
{
    //This is a node pointer to assist with traversal.
    node * current;

    //This is a variable to return success to the calling funciton.
    int success = 0;

    //Store hash index from hash function.
    int hash_index = 0;

    //Store current top index of array to fill.
    int array_index = 0;

    //retrieve hash index using hash funciton.
    hash_index = hash_function(matching_breed, matching_location);

    //Set current to indexed location in hash table.
    current = table[hash_index];

    //while there is data to copy, and there's room in the clients array, copy matches, and
    //count each success for the return.
    while(current && array_index < array_size)
    {
        if(current -> animal.is_match(matching_name, matching_breed, matching_location))
        {
            success += array[array_index].copy_entry(current -> animal);
            ++array_index;
        }
        current = current -> next;
    }
    return success;
}



//This is the remove_all function, and works exactly like the destructor. It will let the
//client clear the table without deleting it.
int animal_hash_table::remove_all(void)
{
    int removed = 0;
    node ** ptr = table;
    for(int i = 0; i < tablesize; ++i)
    {
        //delete LLL
        if(*ptr)
        {
            node * current = (*ptr);
            node * follow = current;
            do
            {
                current = current -> next;
                delete follow;
                ++removed;
                follow = current;

            }while(current);
            *ptr = NULL;
        }
        ++ptr;
    }
    return removed;
}



//This function will let the client load data from a file into the table, and it will return
//the number of data entries loaded.
int animal_hash_table::load_from_file(char filename[])
{
  animals  an_animal;
  int input_size = 100;
  char temp_breed[input_size];
  char temp_name[input_size];
  char temp_location[input_size];
  char temp_story[input_size];
  char temp_link[input_size];
  char temp_age[input_size];

  ifstream file_in; // read from a file
  int i = 0;
  file_in.open(filename);

  if (file_in)
  {
    file_in.get(temp_breed, input_size, '|');
    file_in.ignore(100, '|'); 

    while(!file_in.eof())
    {
      file_in.get(temp_name, input_size, '|');
      file_in.ignore(100, '|'); 
      file_in.get(temp_location, input_size, '|');
      file_in.ignore(100, '|'); 
      file_in.get(temp_story, input_size, '|');
      file_in.ignore(100, '|'); 
      file_in.get(temp_link, input_size, '|');
      file_in.ignore(100, '|'); 
      file_in.get(temp_age, input_size, '\n');
      file_in.ignore(100, '\n'); 

      an_animal.input_entry(temp_breed, temp_name, temp_location, temp_story, temp_link, temp_age);
      add_animal(an_animal);

      an_animal.clear_animal();
      temp_breed[0] = '\0';
      temp_name[0] = '\0';
      temp_location[0] = '\0';
      temp_story[0] = '\0';
      temp_link[0] = '\0';
      temp_age[0] = '\0';

      ++i;
      
      file_in.get(temp_breed, input_size, '|');
      file_in.ignore(100, '|'); 
    }
    file_in.close();
//    file_in.clear();
  }
  return i;
}
