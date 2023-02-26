#include "resolutions.h"
using namespace std;



// ---------------------------------------
// Ryan Filgas
// Assignment_1
// Karla Fant
// CS 163
// 1/18/2021
//
// FILENAME:
// main_resolutions.cpp
//
// This is a test program designed to error check the abstract data type
// called resolution_list. Each function is designed to test a corresponding
// function of the class.
// ---------------------------------------


// Display intro to user.
void display_intro(void);
//Display Menu to user.
void display_menu(void);
//Allow user to add resolution.
void add_resolution(char text_entry[], char * resized_entry, resolution_list & to_fill, resolutions & new_resolution);
//Allow user to enter the name of a resolution to remove, and remove it.
void remove_resolution(char to_remove[], char * resized_entry, resolution_list & to_edit);
//Allow user to choose a resolution to add a task to, and let them add task.
void add_task(resolution_list & access_resolutions, tasks & to_add);
//Allow user to choose a resolution to display tasks for.
void display_tasks(resolution_list & access_resolutions);
//Display all resolutions in the list.
void display_resolutions(resolution_list & to_display);



int main()
{

    //SIZE is used for sizing input arrays.
    const int SIZE = 100;
    //user_finished is used when user wants to exit the menu loop.
    int user_finished = 0;
    //Selection is used for the menu selection.
    int selection = 0;
    //text_entry is an array for the user to enter text in that will be copied elsewhere.
    char text_entry[SIZE];
    //resized_entry will be used to copy text+entry into a dynamically allocated array
    //to be used as an argument in other functions.
    char * resized_entry = NULL;

    //This is a list class object to load resolutions into.
    resolution_list my_resolutions;
    //This is a resolution for the calling function to load, and pass into the my_list functions.
    resolutions new_resolution;
    //This is a task class object for the calling function to load data into, and pass to the list
    //class functions as an argument.
    tasks new_task;

    display_intro();
    do
    {
        //Display menu to user, and let them make a selection.
        display_menu();
        cin >> selection;
        cin.ignore(100, '\n');
        
        //Add a resolution.
        if(selection == 1)
            add_resolution(text_entry, resized_entry, my_resolutions, new_resolution);
        //Remove a resolution.
        if(selection == 2)
            remove_resolution(text_entry, resized_entry, my_resolutions);
        //Add a task to a resolution.
        if(selection == 3)
            add_task(my_resolutions, new_task);
        //Display all tasks in a resolution.
        if(selection == 4)
            display_tasks(my_resolutions);
        //Display all resolutions.
        if(selection == 5)
            display_resolutions(my_resolutions);
        //Allow user to exit.
        if(selection == 6)
            user_finished = 1;

    }while(!user_finished);

    return 0;

};



//This will display the intro to the user.
void display_intro(void)
{
    cout << "It's that time of year again! Welcome to the Resolutions List Manager! \n";
    cout << "Below you'll see a menu. To get started, select Add a Resolution by entering \n";
    cout << "a 1. To choose any of the other options, simply enter the corrosponding number. \n\n";
}



//This is the user interface that will display.
void display_menu(void)
{
    cout << " To select an option, please enter the corresponding number. \n\n";

    cout << "1. Add a Resolution \n";
    cout << "2. Remove a Resolution \n";
    cout << "3. Add Task to Resolution \n";
    cout << "4. Display All Tasks for a Resolution \n";
    cout << "5. Display All Resolutions \n";
    cout << "6. Exit \n\n";

    return;
}



//This function will allow the user to add a resolution to the list.
void add_resolution(char text_entry[], char * resized_entry, resolution_list & to_fill, resolutions & new_resolution) 
{
    //To return different messages to user based on success of the function.
    int success = 0;
    
    cout << "Please enter the name of the resolution you wish to add" << "\n\n";
    cin.get(text_entry, 100, '\n');
   
    //Copy to dynamically allocated array.
    resized_entry = new char[strlen(text_entry) + 1];
    strcpy(resized_entry, text_entry);
    new_resolution.replace(resized_entry);

    //This is the function call testing add_resolution in the resolution_list class.
    //It will return 1, and print the success statement.
    success = to_fill.add_resolution(new_resolution);
    
    if(success)
        cout << "You've successfully added a resolution! Returning to menu." << "\n\n";
    else 
        cout << "There was a problem with the add function" << "\n\n";

    return;
}



//This function will let a user remove a resolution by typing in the name. It will adjust
//for non case sensitive entries.
void remove_resolution(char to_remove[], char * resized_entry, resolution_list & to_edit)
{
    //Use list class function return to output different messages to user based on success.
    int success = 0;

    cout << "Please enter the name of the resolution you wish to remove" << "\n\n";
    cin.get(to_remove, 100, '\n');
    
    //copy to dynamically allocated array.
    resized_entry = new char[strlen(to_remove) + 1];
    strcpy(resized_entry, to_remove);

    //This is the function call for the ADT to test remove_resolution.
    success = to_edit.remove_resolution(resized_entry);

    if(success == 1)
        cout << "Resolution was successfully removed. \n\n";
    if(success == -1)
        cout << "List is empty. Please add to the list \n\n";
    if(success == 0)
        cout << "No match found. Please try again. \n\n";

    return;
}



//This function will let a user add a task and record it inside the desired resolution.
void add_task(resolution_list & access_resolutions, tasks & to_add)
{
    //Use list class function return to output different messages to user based on success.
    int success = 0;
    // User will fill this, and then it will get copied into dynamically allocated memory.
    char temp_name[100];
    //This is a temp variable for task name to be filled in by user, and copied to temp task name.
    char temp_name_task[100];
    //Dynamically allocated memory to save space. Temp name will copy into this.
    char * temp_resolution;
    //Dynamically allocated memory to save space, temp_name will copy into this.
    char * temp_task_name;
    //This is the time needed variable to pass into a task object.
    float temp_time_needed;
    //This is the piority variable to pass into task object.
    int temp_priority;

    //Dynamically allocate memory, and copy each entry into a sized char array.
    cout << "Please enter the name of the resolution you'd like to add to. \n";
    cin.get(temp_name_task, 100, '\n');
    cin.ignore(100, '\n');
    temp_resolution = new char[strlen(temp_name_task) + 1 ];
    strcpy(temp_resolution, temp_name_task);
    
    cout << "Please enter the name of the task you'd like to add. \n";
    cin.get(temp_name, 100, '\n');
    cin.ignore(100, '\n');
    temp_task_name = new char[strlen(temp_name) + 1];
    strcpy(temp_task_name, temp_name);

    cout << "Please enter the time in hours you expect your task to take. \n";
    cin >> temp_time_needed;
    cin.ignore(100, '\n');

    cout << "Please enter the priority of this task as a number between 1 & 10 \n";
    cin >> temp_priority;
    cin.ignore(100, '\n');
   
    //Load arguments into the clients task object.
    if(to_add.create_entry(temp_task_name, temp_time_needed, temp_priority) == -1)
    {
        cout << "Invalid priority value, please enter a priority between 1 and 10.\n";
        cin >> temp_priority;
        if(to_add.create_entry(temp_task_name, temp_time_needed, temp_priority) == 1)
            cout << "Success! Thank you for entering a proper number\n\n";
    }

    
    //This is the function call to test add_task. It was passed in a task object, and 
    //char array of the matching reolution node.
    success = access_resolutions.add_task(to_add, temp_resolution);
    
    if(success == 1)
        cout << "Successfully added task \n";
    if(success == -1)
        cout << "There are no resolutions to add a task to. Please add a resolution. \n";

    if(success == -2)
        cout << "Couldn't add task, there's no matching resolution name\n\n";
    if(success == 0)
        cout << "error adding task";

    return;
}



//This function displays tasks to the user from any resolution they choose..
void display_tasks(resolution_list & access_resolutions)
{
    //Use list class function to determine output to user.
    int success = 0;
    //Resolution name to pass into list class.
    char resolution_name[100];
    //Resized resolution name to keep memory use lower.
    char * resized_name;


    cout << "Please enter the resolution you'd like to display tasks for \n\n";
    cin.get(resolution_name, 100, '\n');
    cin.ignore(100, '\n');

    //Allocate memory dynamically.
    resized_name = new char[strlen(resolution_name) + 1];
    strcpy(resized_name, resolution_name);

    //This is the function call to display_tasks for the user. It takes a
    //char array as input to locate the matching resolution,
    success = access_resolutions.display_tasks(resized_name);

    if(success == 1)
        cout << "Above is a list of your tasks. Enjoy! \n\n";
    else if(success == 0)
        cout << "Empty List!";
    else if(success == -2)
        cout << "There's no resolution with a matching name.";

    return;
}



//This function displays all resolutions.
void display_resolutions(resolution_list & to_display)
{
    //Use list class function to determine output to the user.
    int success = 0;
    //Pause until user enters a value. This is for interface purposes.
    char pause;

    //This is the function call to test display_resolutions. It takes no arguments, and is all
    //managed by the resolutions_list class.
    success = to_display.display_resolutions();
    
    if(success)
        cout << "Displayed are your resolutions. Please enter a letter when you are ready to go back to the menu." << "\n\n";
    else
        cout << "No resolutions to display. Please enter a letter to continue";
    cin >> pause;
    
    return;
}
