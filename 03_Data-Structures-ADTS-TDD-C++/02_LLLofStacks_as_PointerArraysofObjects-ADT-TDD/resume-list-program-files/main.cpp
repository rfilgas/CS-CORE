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
// main.cpp
//
// This program is designed to test the abstract data type resume_list. It will allow
// the testing of each function within the class, including push, pop, peek, display,
// and is_empty. Each function returns an integer, and that return will be used or
// displayed in each test. In addition, the pop, and peek functions both fill an
// experience class passed by reference to be filled by the ADT; these wil be
// used and displayed as well. Initiate_stack is a resume_list function used
// here in the add_experience function. This can be used to allocate the first
// experience object ahead of time, but otherwise, this is used inside of the
// push function when the list is empty.
// -------------------------------------------------------------------------



// This struct is to hold data to be used in main; a resume object to hold
// the data structure, and an experience object for the client to fill
// with the relevant data to pass into the ADT, in addition to an int
// to hold the user selection for the menu.
struct main_data
{
    //This is a resume_list object to hold a stack of experiences.
    resume_list a_resume;
    //This is an experience object to hold each experience's data.
    experiences an_experience;
    //This is a selection variable to hold the users menu choice.
    int selection = 0;

};



// Welcome user to the program.
void welcome_user(main_data & data);

// Display a menu for the user, and take in input.
void display_menu(main_data & data);

// add_experience tests the push function in the experience_list class.
void add_experience(main_data & data);

//peek experience tests the peek function in the experience_list class.
void peek_experience(main_data & data);

//delete_last tests the pop function in the experience_list class.
void delete_last(main_data & data);

//display+list tests the display function in the experience_list class.
void display_list(main_data & data);

//is_it_empty tests the is_empty function in the experience>list class.
void is_it_empty(main_data & data);



int main()
{
    //Hold mains data.
    main_data data;

    //Welcome user.
    welcome_user(data);

    //Run through menu items until user selects
    //6 to exit.
    while(data.selection != 6)
    {
        display_menu(data);
        if(data.selection == 1)
            add_experience(data);
        if(data.selection == 2)
            peek_experience(data);
        if(data.selection == 3)
            delete_last(data);
        if(data.selection == 4)
            display_list(data);
        if(data.selection == 5)
            is_it_empty(data);
    }
    return 0;

}



//Welcome user to program.
void welcome_user(main_data & data)
{
    cout << "Welcome to the Resume Builder! \n";
    cout << "In this resume builder you will be able to add, subtract, check if empty,display, ";
    cout << "and look at the top entry\n";
    cout << "Please start by entering 1 to add an experience\n\n";

}



//Display menu to user.
void display_menu(main_data & data)
{
     cout << "Please select an option from below\n\n";
     cout << "1. Add Experience\n";
     cout << "2. Peek Experience\n";
     cout << "3. Delete Last Experience\n";
     cout << "4. Display List\n";
     cout << "5. Check if list is empty\n";
     cout << "6. Exit\n";
     cin >> data.selection;
     cin.ignore(100, '\n');
}



//Test push function, by letting user input data, copying that into an
//experience object, then passing it into the resume class member.
void add_experience(main_data & data)
{
        //These are self documenting temp variables to be entered
        //by the user, and copied into the resume's data structure.
        char temp_employer[100];
        char temp_start[100];
        char temp_end[100];
        char temp_title[100];
        char temp_duties[100];

        //Initiate the stack, and output a message if successful. We are testing the initiate function.
        if(data.a_resume.initiate_stack())
            cout << "Initiating resume... Please Wait...\n\n";

        //For each local variable take input from user, and clear buffer.
        cout << "Please enter Employer        : \n";
        cin.get(temp_employer, 100, '\n');
        cin.ignore(100, '\n');
        cout << "Please enter Start date      : \n";
        cin.get(temp_start, 100, '\n');
        cin.ignore(100, '\n');
        cout << "Please enter End date        : \n";
        cin.get(temp_end, 100, '\n');
        cin.ignore(100, '\n');
        cout << "Please enter Job Title       : \n";
        cin.get(temp_title, 100, '\n');
        cin.ignore(100, '\n');
        cout << "Please enter Responsibilities: \n";
        cin.get(temp_duties, 100, '\n');
        cin.ignore(100, '\n');

        //If creating an entry is successful, tell user; this tests the create_entry function.
        if(data.an_experience.create_entry(temp_employer, temp_start, temp_end, temp_title, temp_duties))
            cout << "Entry created successfully\n";
        else
            cout << "Couldn't create entry\n";
        
        //If transferring data into the ADT was successful, tell user; this tests the push function.
        if(data.a_resume.push(data.an_experience))
            cout << "Experience added successfully\n";
        else
            cout << "Couldn't add experience\n";
}



//Test peek function of the ADT, and display success, or
//display message that list is empty; this tests the peek function.
void peek_experience(main_data & data)
{
    //If the peek function returns success, tell user.
    if(data.a_resume.peek(data.an_experience))
    {
        cout << "Data peeked successfully, you sneaky bugger\n";

        //Test peeks return of an experience by reference.
        if(data.an_experience.display_experience())
            cout << "Data passed to client successfully";
    }
    else
        cout << "We encountered an error peeking data, the list is empty\n";
}



//Test display function of the ADT, and return the number of experiences as a message to user if
//successful, or tell the user that the list is empty.
void display_list(main_data & data)
{
    //This is a local variable to catch the display functions output, and output it to the user..
    int num_experiences = 0;

    //This is a test of the display function. Displays return is stored in num_experiences.
    num_experiences = data.a_resume.display();
    
    //If there was an experience to display, tell the user how many, or that the list is empty.
    if(num_experiences)
        cout << "Resume displayed " << num_experiences << " experiences successfully\n";
    else
        cout << "Empty list!";
}



//Test the pop function of the ADT, and output the popped data to the user if successful,
//otherwise tell the user there's nothing left to delete.
void delete_last(main_data & data)
{
    //If pop is successful, display the popped value, and tell the user the operation was successful.
    if(data.a_resume.pop(data.an_experience))
    {
        if(data.an_experience.display_experience())
            cout << "Data popped successfully, here it is.\n\n";
    }
    else
        cout << "Nothing to delete!";
}



//Test the is_empty function in the ADT. Output a message to the user in both cases.
void is_it_empty(main_data & data)
{
    if(data.a_resume.is_empty())
        cout << "List is empty!\n";
    else
        cout << "List isn't empty!\n";

}
