#include "client_item.h"
using namespace std;

// ***************************************************************
// Ryan Filgas
// CS202
// Karla Fant
// Program 1
// 4-16-21
//
// The purpose of this file is to hold the classes in a hierarchy of client items.
// The core class of this hierarchy is a client item, derived from a date. Branching
// off of these the children will handle emails, tasks, and appointments. The reason
// to use a hierarchy is to simplify the use of the code for these classes. Together 
// they are a lot to implement, but by sharing some of the responsibility with a
// parent through object oriented design reduces the amount of code significantly.
//
//
// DATE: The date class has the following functions and members.
//
// Edit date takes in 3 ints, and will return false for most invalid days and months.
// display date outputs to the user and takes no arguments.
// is_match will return true if 3 ints passed in match the local date. 
// Data members: int day, int month, int year.
//
// CLIENT ITEM: The client item class has the following functions and members.
// 
// display_recipient outputs the recipient to the user, and returns 0 if there's nothing to print.
// display_description  outputs the recipient to the user, and returns 0 if there's nothing to print.
// edit_recipient takes in a char * name to replace recipient. It returns 0 if passed a null pointer.
// edit_description takes in a char * name to replace recipient. It returns 0 if passed a null pointer.
// is_recipient takes in a char * name to match and returns true for a match.
// is_description takes in a char * name to match and returns true for a match.
// Data members: char * recipient, char * description.
//
// APPOINTMENT:
//
// edit takes in ints day, month, year, char * client, char * description. Return 0 for null pointers.
// edit_time takes in an int time, and replaces appointment time. Returns the time it replaced.
// confirm takes in a bool, and flips the confirmation either on, ot off with a 0 or a 1.
// is_confirmed takes no input, and will return true ifconfirmed is set to 1.
// display_time outputs the appointment time, and returns the appointment time.
// Data members: int appointment_time, int confirmed.
//
// EMAIL:
//
// write takes a char * new message, and returns 0 if passed a null pointer.
// display outputs the message body to the user, and returns 0 if there's nothing to display.
// mark read takes in a bool, and sets it to the marked_read variable.
// is_read returns the value of marked read as true or false.
// Data members: char * message_body, bool marked_read.
//
// ***************************************************************


//--DATE--CLASS-----------------------------------------------------------------------

//Constructors
date::date(): day(0), month(0), year(0)
{}
date::date(int new_day, int new_month, int new_year): day(new_day), month(new_month), year(new_year) 
{}
//Destructor
date::~date()
{
    day = month = year = 0;
}



//Edit date takes in 3 ints, and will return false for most invalid days and months.
int date::edit_date(int new_day, int new_month, int new_year)
{
    if(new_day < 0 || new_day > 31 || new_month < 0 || new_month > 12)
        return 0;
    day = new_day;
    month = new_month;
    year = new_year;
    return 1;
}



//Output the date to the user
void date::display_date(void)
{
    cout << "Date: " << day << "-" << month << "-" << year << "\n";
}



//Return true if the date matches the objects date.
bool date::is_match(int day_match, int month_match, int year_match)
{
    return (day == day_match && month == month_match && year == year_match);
}

//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// The client item is the base class of the others. It's primary purpose is to manage
// recipient names, item descriptions, and dates, as well as to display data.
// Data managed is a char * recipient, and a char * description.

// Constructors
client_item::client_item(): recipient(NULL), description(NULL)
{}

//Constructor: Recipient
client_item::client_item(char * new_recipient): description(NULL)
{
    recipient = new char(strlen(new_recipient) + 1);
    strcpy(recipient, new_recipient);
}

//Constructor: Recipient + Date
client_item::client_item(int new_day, int new_month, int new_year, char * new_recipient): date(new_day, new_month, new_year), description(NULL)
{
    recipient = new char[strlen(new_recipient) + 1];
    strcpy(recipient, new_recipient);
}

//Copy Constructor
client_item::client_item(const client_item & source): date(source.day, source.month, source.year)
{
    description = new char[strlen(source.description) + 1];
    strcpy(description, source.description);

    recipient = new char[strlen(source.recipient) + 1];
    strcpy(recipient, source.recipient);
}

//Destructor
client_item::~client_item()
{
    if(recipient != NULL)
        delete [] recipient;
    if(description != NULL)
        delete [] description;
    recipient = NULL;
    description = NULL;
}



//client_item: Display a recipient. This will return 0 if the description is null.
int client_item::display_recipient(void)
{
    int success = 1;
    if(!recipient)
        return 0;
    else
    {
        cout << "Recipient: " << recipient << "\n";
        return success;
    }
}



//client_item: Display a description. This will return 0 if the description is null.
int client_item::display_description(void)
{
    int success = 1;
    if(!description)
        return 0;
    else
    {
        cout << "Description: " << description << "\n";
        return success;
    }
}



//client_item:: Edit recipient by passing in a char * new name. Will return 1 if new_name isn't null.
int client_item::edit_recipient(char * new_name)
{
    int success = 1;
    if(!new_name)
        return 0;
    else
    {
        if(recipient != NULL)
        {
            delete [] recipient;
            recipient = NULL;
        }
        recipient = new char[strlen(new_name) + 1];
        strcpy(recipient, new_name);
        success = 1;
    }
    return success;
}



//client_item: edit a description by passing in a char *. This will return 0 for empty description.
int client_item::edit_description(char * new_description)
{
    int success = 0;
    if(!new_description)
        return 0;
    else
    {
        if(description != NULL)
        {
            delete [] description;
            description = NULL;
        }
        description = new char[strlen(new_description) + 1];
        strcpy(description, new_description);
        success = 1;
    }
    return success;
}



//client_item: is_recipient will take in a name, and return 1 if it's a match, 0 if it isn't.
bool client_item::is_recipient(char * name)
{
    if(!recipient)
        return 0;
    return (!strcmp(recipient, name));
}



//client_item: is_description will take in a name, and return 1 if it's a match, 0 if it isn't.
bool client_item::is_description(char * name)
{
    if(!description)
        return 0;
    return (!strcmp(description, name));
}

//----------------------------------------------------------------------------------------------





//----------------------------------------------------------------------------------------------
//The appointment class is a child of client item, it manages creation, removal, and confirmation.
// Data items include appointment_time && confirmed, both ints.


//Default Constructor
appointment::appointment(): appointment_time(0), confirmed(0)
{}


//Default Destructor
appointment::~appointment()
{}


//Constructor: client_item(ints day, month, year) + appointment_time(int in 24hr time)
appointment::appointment(int new_day, int new_month, int new_year, char * new_recipient, int new_appointment_time): client_item(new_day, new_month, new_year, new_recipient), appointment_time(new_appointment_time), confirmed(0)
{}


//appointment: client_item(char *) + appointment_time(int) 
appointment::appointment(char * new_recipient, int new_appointment_time): client_item(new_recipient), appointment_time(new_appointment_time), confirmed(0) 
{}



//Copy Constructor
appointment::appointment(const appointment & source): client_item(source.day, source.month, source.year, source.recipient) 
{
    edit_description(source.description);
    confirmed = source.confirmed;
}



//Use the built in edit functions, and if they all return true, return true.
int appointment::edit(int new_day, int new_month, int new_year, char * client, char * description)
{
    return (edit_date(new_day, new_month, new_year) && edit_recipient(client) && edit_description(description));
}



//Toggle confirmed to true or false.
void appointment::confirm(bool reply)
{
    confirmed = reply;
    return;
}



//Return value of confirmed as true or false.
bool appointment::is_confirmed(void)
{
    return confirmed;
}



//output time to user, and return the time.
int appointment::display_time(void)
{
    cout << "Time: " << appointment_time << "\n";
    return appointment_time;
}



//edit atime by replacing member with passed in int. Return old time.
int appointment::edit_time(int new_time)
{
    int temp = appointment_time;
    appointment_time = new_time;
    return temp;
}
//----------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------
//The task_item class is a child of a client item. It manages editing, priority, removal, and completion
// it manages task_priority and task_completed. both are ints.

//Default constructor
task_item::task_item(): task_priority(0), task_completed(0){}

//Default Destructor
task_item::~task_item(){}

//Constructor: Date(ints day, month, year) + Task_Priority
task_item::task_item( int new_day, int new_month, int new_year, char * new_recipient, int num_priority): client_item(new_day, new_month, new_year, new_recipient), task_priority(num_priority), task_completed(0){}

//Constructor: client_item(char * recipient) + task_priority(int)
task_item::task_item(char * new_recipient, int num_priority): client_item(new_recipient), task_priority(num_priority), task_completed(0){}

//Copy Constructor
task_item::task_item(const task_item & source): client_item(source.day, source.month, source.year, source.recipient), task_priority(source.task_priority), task_completed(source.task_completed)
{
    description = new char[strlen(source.description) + 1];
    strcpy(description, source.description);
}



//Return false if the priority is 0. Invalid.
int task_item::set_priority(int to_replace)
{
    if(!to_replace)
        return 0;
    task_priority = to_replace;
    return to_replace;
}



//Toggle completion status to true or false.
void task_item::mark_complete(int set_complete)
{
    task_completed = set_complete;
    return;
}



//Return true if task is marked complete.
bool task_item::is_complete(void)
{
    return task_completed;
}



//Check if above the desired priority level.
int task_item::is_priority(int level)
{
    return(task_priority >= level);
}



//Display task_priority. Tell user if it was never set.
void task_item::display_priority(void)
{
    if(!task_priority)
        cout << "No priority set.\n";
    cout << "Priority: " << task_priority << "\n";
    return;
}



//for the lists copy constructor, so it can sort.
int task_item::return_priority(void)
{
    return task_priority;
}

//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// The email class is a child of a client item. It manages send, read, save, and display functions.
// Data members manages include char * message_body and bool marked_read;



//Default Constructor
email::email(): message_body(NULL), marked_read(0){}

//Constructor recipient(char *)
email::email(char * new_recipient): client_item(new_recipient), message_body(NULL), marked_read(0){}

//Constructor: client_item(ints day, month, year, char * recipient);
email::email(int new_day, int new_month, int new_year, char * new_recipient): client_item(new_day, new_month, new_year, new_recipient), message_body(NULL), marked_read(0){}

//Copy Constructor
email::email(const email & source): client_item(source.day, source.month, source.year, source.recipient), marked_read(source.marked_read)
{
    message_body = new char[strlen(source.message_body) + 1];
    strcpy(message_body, source.message_body);
}

//Destructor
email::~email()
{
    if(message_body != NULL)
        delete [] message_body;
    message_body = NULL;
    marked_read = 0;
}



//Replace message_body with new message, and return 0 if a null pointer was passed in.
int email::write(char * new_message)
{
    if(!new_message)
        return 0;
    if(message_body != NULL)
        delete [] message_body;
    message_body = new char[strlen(new_message) + 1];
    strcpy(message_body, new_message);
    return 1;
}



//Display message body, and return 0 if null.
int email::display(void)
{
    if(!message_body)
        return 0;
    cout << "Message: " << message_body << "\n";
    return 1;
}



//mark an email read with a passed in bool.
void email::mark_read(bool set_read)
{
    marked_read = set_read;
    return;
}



//return true if marked_read is set to 1
bool email::is_read(void)
{
    return marked_read;
}
//----------------------------------------------------------------------------------------------
