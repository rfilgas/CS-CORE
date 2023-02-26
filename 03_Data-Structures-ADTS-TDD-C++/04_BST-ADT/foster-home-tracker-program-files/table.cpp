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
// table.cpp
//
// The purpose of this program is to implement a searchable list of foster homes
// as a binary search tree. The tree will perform operations to remove all homes,
// display homes in order, display matches for animal type supported, add a home,
// and remove a home by name. The BST will consist of nodes where each member
// holds a class object of type foster home. Each home will contain a name,
// number of pets, time to add in months, relevant details as a char array, and
// animal types supported. The foster_homes_table class will be responsible
// for managing the overall allocation of nodes in the tree, whereas the work of
// managing the actual data is left to the foster_homes class.
// -----------------------------------------------------

// This is a constructor for the node of a binary tree.
node::node()
{
    left = NULL;
    right = NULL;
};



// This is a destructor for the node of a binary tree.
node::~node()
{
    left = NULL;
    right = NULL;
};



// This is a constructor for a foster homes table.
foster_homes_table::foster_homes_table(void)
{
    root = NULL;
};



//This is a destructor for a foster homes table. It uses a recursive
//function to destroy every nod ein the tree.
foster_homes_table::~foster_homes_table(void)
{
    remove_all_recursive(root);
};



// This is a remove_all function that piggy backs on the destructors recursive remove
// function to destroy the tree.
int foster_homes_table::remove_all(void)
{
    return remove_all_recursive(root);
}



// The remove all recursive function will check if root is null, then call itself on left
// and right nodes, deleting each node on the return of the recursive call. This function
// will return the number of nodes deleted.
int foster_homes_table::remove_all_recursive(node *&root)
{
    //Return success to the calling function.
    int success = 0;

    //If there's no root, return failure.
    if(!root)
        return 0;

    //Call the recursive function on the left branch of the tree.
    success += remove_all_recursive(root -> left);

    //Call the recursive function on the right branch of the tree.
    success += remove_all_recursive(root -> right);

    //Count the removed node.
    ++success;

    //Remove node, and set pointer to null.
    delete root;
    root = NULL;

    return success;;
}



// This function takes in a home to add, and passes it to the foster home class to put it in
// the local objects memory.
int foster_homes_table::add_home(foster_home &to_add)
{
    //Return success to the calling function.
    int success = 0;

    //Catch return from the add home function in the foster home class, and return it for this function.
    success = add_home(root, to_add);
    return success;
}



// This a recursive function to add a home to the BST. It will return 1 for success, or 0 for failure.
int foster_homes_table::add_home(node * &root, foster_home &to_add)
{
    //Return success to the calling function.
    int success = 0;

    //If root is null, make a new node, fill it, and set its left and right pointers to null.
    if(!root)
    {
        root = new node;
        root -> a_home.copy_entry(to_add);
        root -> left = root -> right = NULL;
        return 1;
    }

    // If the home to add is smaller alphabetically, traverse left, if it's the same size
    // or larger, traverse right.
    if((root-> a_home.sort_homes(to_add)) < 0)
        
        success = add_home(root -> left, to_add);
    else
        success = add_home(root -> right, to_add);

    //return success.
    return success;
}



// This is a recursive wrapper function for displaying a home. It needs a char array home to find
// ass input, and will output 1 for success or 0 for failure.
int foster_homes_table::display_home(char home_to_find[])
{
    return display_home(root, home_to_find);
}



// This function displays a home by recursively traversing the BST until it finds a match. It will return 1 for success or 0 for failure.
int foster_homes_table::display_home(node * &root, char home_to_find[])
{
    
    //If root is empty, return 0;
    if(!root)
        return 0;

    //Return success to calling function.
    int success = 0;

    //If a match is found, display it, and return the output from the display function.
    if(root -> a_home.is_home_match(home_to_find))
    {
        return root -> a_home.display_home();
    }


    //If target is larger, traverse left, else traverse right.
    if((root-> a_home.sort_homes(home_to_find)) < 0)
        success += display_home(root -> left, home_to_find);
    else
        success += display_home(root -> right, home_to_find);
    return success;
}



// This is a recursive wrapper function to find matching homes. It will take a char array as input,
// and will return the number of matches.
int foster_homes_table::display_foster_matches(char type_to_match[])
{
    return display_foster_matches(root, type_to_match);

}



// This a recursive function to count matches. It works by traversing the BST in order, and returning 1 to a success
// variable whenever it finds a match, after displaying the home name the match belongs to.
int foster_homes_table::display_foster_matches(node * root, char type_to_match[])
{
    //If root is null, return 0;
    if(!root)
        return 0;

    //Catch the number of matches.
    int success = 0;

    //Traverse left.
    success = display_foster_matches(root -> left, type_to_match);

    //If we found a match, display it, and count the match.
    if(root -> a_home.display_if_pet_match(type_to_match))
        ++success;

    //Traverse right.
    success += display_foster_matches(root -> right, type_to_match);

    //Return the number of captured matches.
    return success;
}



// This is a recursive wrapper function to remove a node by name. It takes a char array by input, and outputs the number
// of nodes removed.
int foster_homes_table::remove_home(char home_to_remove[])
{
    return remove_home(root, home_to_remove);
}



// This is a recursive function to remove a node by name. It traverses until it finds a match, then deletes
// and reconnects, or replaces its data with the inorder successor, and deletes the inorder successor,
// reconnecting any connected nodes to the previous node.
int foster_homes_table::remove_home(node * &root, char home_to_remove[])
{
    //If no list, return 0 for failure.
    if(!root)
        return 0;
    
    //return success to calling function.
    int success = 0;

    //If there isn't a match, check where the data went by comparing the name,
    //and traverse left or right if the name is alphabetically smaller or larger.
    if(!root -> a_home.is_home_match(home_to_remove))
    {
        //If data was added left, traverse left.
        if(root -> a_home.sort_homes(home_to_remove) < 0)
            success += remove_home(root -> left, home_to_remove);
        //Data wasn't sent left, traverse right.
        else
            success += remove_home(root -> right, home_to_remove);
    }


    // The home to remove is a match.
    else if(root -> a_home.is_home_match(home_to_remove))
    {
        //The home to remove is a leaf.
        if(!root -> left && !root -> right)
        {
            delete root;
            root = NULL;
            ++success;;
        }
        
        //The home to remove is the left child, and there is no right child. Remove it and reconnect.
        else if(root -> left && !root -> right)
        {
            node * temp = root;
            root = root -> left;
            delete temp;
            temp = NULL;
            ++success;
        }
        //The home to remove is the right child, and there is no left child. Delete it and reconnect.
        
        else if(!root -> left && root -> right)
        {
            node * temp = root;
            root = root -> right;
            delete temp;
            temp = NULL;
            ++success;
        }
        //The node to delete has two children, IOS is right child. Clear it, and copy in order successors data before deleting
        //the inorder successor, and reconnecting any childeren it has to the previous node.
        else
        {
            node * current = root -> right;
            if(!current -> left)
            {
                if(root -> a_home.clear_entry())
                    root -> a_home.copy_entry(current -> a_home);
                root -> right = current -> right;;
                delete current;
                current = NULL;
                ++success;
            }

            //Two children, need to find inorder successor, copy data, and delete inorder successor.
            else
            {
                node * previous;
                while(current -> left)
                {
                    previous = current;
                    current = current -> left;
                }
                if(root -> a_home.clear_entry())
                    root -> a_home.copy_entry(current -> a_home);
                previous -> left = current -> right;
                delete current;
                current = NULL;
                previous = NULL;
                ++success;
            } //end else
        } //end else
    } // end else if
    return success;
} //end function



// This is a wrapper function for a display sorted function. It will return the number of nodes, and takes no input.
int foster_homes_table::display_sorted(void)
{
    if(!root)
        return 0;
    return display_sorted(root);
}    



// This is a recursive display sorted function for the above wrapper. It recursively traverses left, displays
// the foster home, then calls itself on the right branch before returning.
int foster_homes_table::display_sorted(node * root)
{
    //No tree, return 0 since there is no node to display.
    if(!root)
        return 0;
    //Catch the number of nodes on the return.
    int success = 0;
    //Call the recursive funtion on the left branch.
    success = display_sorted(root -> left);
    //If the node diaplys properly, count it.
    if(root -> a_home.display_home())
        ++success;
    //Call the recursive function on the right branch, and count the return.
    success += display_sorted(root -> right);
    //Return the result up through the stack.
    return success;
}



//Load a data file of any name. 
// The format is house_name|num_animals|breed1,breed2,breed_n,|length_stay|other_info\n
int foster_homes_table::load_file(char filename[])
{
    //Temporary home to store file output.
    foster_home temp_home;

    //control allowed input size.
    int input_size = 100;

    //Temp variables to store user input.
    char temp_home_name[input_size];
    char temp_num_pets[input_size];
    char temp_time[input_size];
    char temp_details[input_size];

    //Temp animal array to pass into add function.
    animal_type temp_types[100];
    //Temp array to assist with copying type data.
    char temp[100];

    ifstream file_in; // read from a file
    int i = 0;
    int type_count = 0;
    
    file_in.open(filename);
    
    if (file_in)
    {
      file_in.get(temp_home_name, input_size, '|');
      file_in.ignore(100, '|'); 
    
      while(!file_in.eof())
      {
        file_in.get(temp_num_pets, input_size, '|');
        file_in.ignore(100, '|'); 
    
        while(file_in.peek() != '|')
        {    
          file_in.get(temp, input_size, ',');
          file_in.ignore(100, ','); 
          temp_types[type_count].name = new char[strlen(temp) + 1];
          strcpy(temp_types[type_count].name, temp);
          temp[0] = '\0';
          ++type_count;
        }
        file_in.ignore(1, '|');
    
        file_in.get(temp_time, input_size, '|');
        file_in.ignore(100, '|'); 
        file_in.get(temp_details, input_size, '\n');
        file_in.ignore(100, '\n'); 
          //int input_entry(char home_name_to_add[], char num_pets_to_add[], char time_to_add[], char details_to_add[],animal_type types_to_add[], int num_types_to_add);
    
        temp_home.input_entry(temp_home_name, temp_num_pets, temp_time, temp_details, temp_types, type_count);
        add_home(temp_home);
        temp_home.clear_entry();
    
        temp_home_name[0] = '\0';
        temp_num_pets[0] = '\0';
        temp_time[0] = '\0';
        temp_details[0] = '\0';
        for(int a = 0; a < type_count; ++a)
        {
            if(temp_types[a].name)
            {
              delete [] temp_types[a].name;
              temp_types[a].name = NULL;
            }
        }
        type_count = 0;
    
        ++i;
        
        file_in.get(temp_home_name, input_size, '|');
        file_in.ignore(100, '|'); 
      }
      file_in.close();
    }
    return i;
}



//This is a wrapper function for the recursive get height function. It will return the height.
int foster_homes_table::get_height(void)
{
    if(!root)
        return 0;
    return get_height(root);
}



//The function will return the height of the tree by comparing each branch from the bottom
//up through the top, and adding the greater of the two branches to the return as it goes up the stack.
int foster_homes_table::get_height(node * root)
{
    if(!root)
        return 0;
    int left = get_height(root -> left) + 1;
    int right = get_height(root -> right) + 1;
    return max(left, right);
}
