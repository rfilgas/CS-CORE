#include "foster_homes.h"

#include <cstring>
#include <iostream>

using namespace std;

// -----------------------------------------------------
// Ryan Filgas
// Assignment_4
// Karla Fant
// CS163
// 2/25/2021
//
// FILENAME:
// main.cpp
//
// The purpose of this file is to test the foster_home_table class which is a
// binary tree implementation. It will test functions to add a home, load data
// from a file, remove a home by name, display matches for an animal type,
// delete the list, retrieve the tree height, and display homes sorted. In doing so
// every class function of the BST will be tested for input, and output. As this is
// an ADT, the ADT itself will not display unless requested, and the client will
// not have to know about the inner workings of the data structure in order to use
// it. The name for the default data file to load is 'foster_homes.txt'. Happy testing!
// -----------------------------------------------------

//This struct will hold data passed to functions used in main.
struct main_data
{
    //This is a foster homes table object to hold data entries.
    foster_homes_table my_table;

    //This is a foster home object for the user to input data into, and for the
    //client to pass to the table.
    foster_home my_home;

    //This variable is to control input size.
    int SIZE = 100;

    //This is a temp variable to use in main.
    int temp = 0;

    //This variable records user selection.
    int selection = 0;
};


//welcome user
void welcome_user(main_data &data);
//display menu
void display_menu(main_data &data);
//add home
void add_home(main_data &data);

int main()
{
    main_data data;
    //Welcome user.
    welcome_user(data);

    //hold array for choosing file to open.
    char temp[100];

    //Run through menu items until user selects
    //13 to exit.
    while(data.selection != 9)
    {
        //Display Menu.
        display_menu(data);

        //Add Home.
        if(data.selection == 1)
            add_home(data);

        //Load Data from File.
        if(data.selection == 2)
        {
             cout << "Please enter the name of the text file you wish to load,";
             cin.get(temp, 100, '\n');
             cin.ignore(100, '\n');
             data.temp = data.my_table.load_file(temp);
             cout << "there are " << data.temp << " values loaded\n";
        }

        //Clear Table.
        if(data.selection == 3)
        {
            cout << "You've chosen to delete all data. Now deleting.\n";
            data.temp = data.my_table.remove_all();
            cout << data.temp << " items have been removed.\n";
            data.temp = 0;
        }

        //Remove home by name.
        if(data.selection == 4)
        {
            cout << "Please enter a home name you'd like to remove\n";
            cin.get(temp, 100, '\n');
            cin.ignore(100, '\n');
            if(data.my_table.remove_home(temp))
                cout << "Item successfully removed\n";;
            temp[0] = '\0';
        }

        //Display home by name.
        if(data.selection == 5)
        {
            cout << "Please enter a home name you'd like to display\n";
            cin.get(temp, 100, '\n');
            cin.ignore(100, '\n');
            if(data.my_table.display_home(temp))
                cout << "Item successfully displayed\n";
            temp[0] = '\0';
            data.temp = 0;
        }

        //Display all house names which take in a given animal.
        if(data.selection == 6)
        {
            cout << "Please enter a type of animal you'd like to find homes for\n";
            cin.get(temp, 100, '\n');
            cin.ignore(100, '\n');
            data.temp = data.my_table.display_foster_matches(temp);
            cout << data.temp << " matches were found.\n";
            temp[0] = '\0';
            data.temp = 0;
        }

        //Display every home sorted.
        if(data.selection == 7)
        {
           data.temp =  data.my_table.display_sorted();
           cout << data.temp << "items are displayed\n";
           data.temp = 0;
        }

        if(data.selection == 8)
        {
            data.temp = data.my_table.get_height();
            cout << data.temp << "is tree height\n";
           data.temp = 0;
        }
    }
    return 0;
}



//welcome user
void welcome_user(main_data &data)
{
    cout << "Welcome to the Foster Homes Database! \n";
    cout << "In this database you will be able to add a foster home, load homes from a text\n";
    cout << "file, remove all homes, remove a home by name, display a home by name, display\n";
    cout << "all homes willing to take a specific type of animal, and display all homes sorted.\n";
}



//Display Menu to user.
void display_menu(main_data &data)
{
     cout << "Please select an option from below\n\n";
     cout << "1. Add Foster Home\n";
     cout << "2. Load From File\n";
     cout << "3. Remove All Homes\n";
     cout << "4. Remove a Foster Home\n";
     cout << "5. Display a Foster Home\n";
     cout << "6. Display Foster Home Matches (all homes willing to take a dog?)\n";
     cout << "7. Display All Homes Sorted\n";
     cout << "8. Get Height\n";
     cout << "9. Exit\n";

     cin >> data.selection;
     cin.ignore(100, '\n');
}



//add home
void add_home(main_data &data)
{
    int success = 0;

    //Temp variables to let user enter data before allocating memory.
    char new_home_name[data.SIZE];
    char new_num_pets[data.SIZE];
    char new_time[data.SIZE];
    char new_details[data.SIZE];
    animal_type new_types[100];
    int num_new_types = 0;

    //Flag to let the user keep adding entries until finished.
    char type_flag = 'y';

    // Temp array to assist with copying data.
    char temp[100];

    //Get user input.
    cout << "Please note all entries are case sensitive. Every name and type starts with a capital letter.\n\n";
    cout << "Please enter the foster homes name : \n";
    cin.get(new_home_name, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Please enter number of pets allowed: \n";
    cin.get(new_num_pets, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Please enter adoption duration     : \n";
    cin.get(new_time, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Please enter any relevant details you'd like to include: \n";
    cin.get(new_details, 100, '\n');
    cin.ignore(100, '\n');

    cout << "Please enter what types of animals this home will take. Entries must start with a\n";
    cout << "capital letter, and be lowercase thereafter. In addition, types must not be plural.\n";
    cout << "Example: 'Dog'. You will have an opportunity to enter multiple animals.\n\n";
    
    //Loop until user says no, or the array is full. Copy any input they add into the new types array.
    do
    {
        cout << "Please enter in an animal type\n\n";
        
        temp[0] = '\0';
        cin.get(temp, 100, '\n');
        cin.ignore(100, '\n');

        new_types[num_new_types].name = new char[strlen(temp) + 1];

        strcpy(new_types[num_new_types].name, temp);

        cout << "Thank you. Would you like to enter another? Please enter 'y' for yes, or 'n' for no\n";
        cin >> type_flag;
        cin.ignore(100, '\n');
        ++num_new_types;
    }
    while(type_flag == 'y' && num_new_types < 100);

    //Create a new home object, and catch it's return value for an output message.
    success = data.my_home.input_entry(new_home_name, new_num_pets, new_time, new_details, new_types, num_new_types); 
    if(success)
        cout << "Entry successfully created by input function\n";
    else
        cout << "There was an issue copying data into a home\n";

    //Add home to table, and catch the add home functions return for an output message.
    success = data.my_table.add_home(data.my_home);
    cout << success << " Entry was added successfully to table.\n";
    
    //Clear home.
    data.my_home.clear_entry();
}
