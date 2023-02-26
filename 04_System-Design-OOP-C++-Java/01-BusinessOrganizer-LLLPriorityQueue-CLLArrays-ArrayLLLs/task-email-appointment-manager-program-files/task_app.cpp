#include "item_structures.h"
#include "iostream"
using namespace std;

// ***************************************************************
// Ryan Filgas
// CS202
// Karla Fant
// Program 1
// 4-16-21
//
// The purpose of this document is to hold the task application
// that manages all three data structures including tasks,
// emails, and appointments. This application can manage it all!
//
// ***************************************************************


void task_app::launch(void)
{
    int response = 0;
    do
    {
        cout << "Welcome to the Task App! What would you like to do?\n";
        cout << "Please select a number\n\n";
        cout << "1. Manage my Tasks\n";
        cout << "2. Manage my Appointments\n";
        cout << "3. Manage my Emails\n";
        cout << "4. Exit\n";
        cin >> response;
        cin.ignore(100, '\n');

        if(response == 1)
            my_tasks.user_interface();
        else if(response == 2)
            my_appointments.user_interface();
        else if(response == 3)
            my_emails.user_interface();
        cout << "\n\n\n\n\n\n\n";
    }while(response != 4);
};

