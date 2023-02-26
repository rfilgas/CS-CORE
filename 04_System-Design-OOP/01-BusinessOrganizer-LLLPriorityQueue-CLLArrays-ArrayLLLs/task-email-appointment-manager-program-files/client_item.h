#include <cstring> 
#include <iostream> 
#include <cctype> 

// ***************************************************************
// Ryan Filgas
// CS202
// Karla Fant
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
// As the classes are all part of the same hierarchy, each class: email, task,
// etc. can access the member functions of the parent client item, and of the date.
// All edit functions take ints or char * arrays as arguments, and will return 0
// if the passed in pointers are null, or in some cases there is improper input.
// Any is_true funciton will return a bool if the data item inside is set to 1,
// or if certain conditions are met. The real advantage of small functions
// like this will come in their data structures. Things like mark_read, and is_match
// would allow for potential batch processing implementations in the future.
//
// ***************************************************************


// The purpose of the date class is to manage a date, confirm a date match,
// edit a date, and manage the dates data. 
class date 
{
    public:

        //Constructors and destructors
        date();
        date(int new_day, int new_month, int new_year);
        ~date();

        //Edit a date. Will return 0 if: day < 0, day >31, month < 0, month > 12
        int edit_date(int new_day, int new_month, int new_year);

        //Display the date.
        void display_date(void);

        //Returns true if the individual items match with the items in the object.
        bool is_match(int day_match, int month_match, int year_match);

    protected:

        int day;
        int month;
        int year;
};


// The client item is the base class of the others. It's primary purpose is to manage
// recipient names, item descriptions, and dates, as well as to display data.
class client_item: public date
{
    public:

        client_item(); 
        client_item(char * new_recipient);
        client_item(int new_day, int new_month, int new_year, char * new_recipient);
        client_item(const client_item & source);
        ~client_item();

        //display functions will return 0 if there is nothing to diaplay.
        int display_recipient(void);
        int display_description(void);

        // edit functions will return 0 if passed a null pointer,
        int edit_recipient(char * new_name);
        int edit_description(char * new_description);


        // Check for a recipient match and return true or false.
        bool is_recipient(char * name);
        bool is_description(char * name);
        

    protected:

        char * recipient;
        char * description;
};



//The appointment class is a child of client item, it manages creation, removal, and confirmation.
class appointment: public client_item
{
    public:

        appointment();
        appointment(int new_day, int new_month, int new_year, char * new_recipient, int new_appointment_time);
        appointment(char * new_recipient, int new_appointment_time);
        appointment(const appointment & source);
        ~appointment();


        // edit functions will return 0 if passed a null pointer,
        int edit(int new_day, int new_month, int new_year, char * client, char * description);
        int edit_time(int new_time);

        //toggle confirmation on or off.
        void confirm(bool reply);

        // Check confirmed and return the stored value.
        bool is_confirmed(void);

        //display functions will return 0 if there is nothing to diaplay.
        int display_time(void);
        

    protected:

        int appointment_time; //0800 - 24hr time
        int confirmed;
};



//The task_item class is a child of a client item. It manages editing, priority, removal, and completion
class task_item: public client_item
{

    public:

        task_item();
        task_item(int new_day, int new_month, int new_year, char * new_recipient, int num_priority);
        task_item(char * new_recipient, int num_priority);
        task_item(const task_item & source);
        ~task_item();


        //set priority to allow for sorting. 
        int set_priority(int to_replace);

        //toggle task_completed on or off.
        void mark_complete(int set_complete);

        // Check completed and return the stored value.
        bool is_complete(void);

        //Check if above the desired priority level.
        int is_priority(int level);

        //display functions will return 0 if there is nothing to diaplay.
        void display_priority(void);

        // This was used in the copy constructor to copy the list over.
        // Since I was outside of scpe, this was the only way to get the
        // value, however this doesn't give direct access to private date.
        int return_priority(void); // THIS IS FOR A COPY CONSTRUCTOR ONLY

    protected:

        int task_priority;
        int task_completed;
};



// The email class is a child of a client item. It manages send, read, save, and display functions.
class email: public client_item
{
    public:

        email();
        email(char * new_recipient);
        email(int new_day, int new_month, int new_year, char * new_recipient);
        email(const email & source);
        ~email();


        // edit functions will return 0 if passed a null pointer,
        int write(char * new_message);

        //display functions will return 0 if there is nothing to diaplay.
        int display(void);

        //toggle marked_read  on or off.
        void  mark_read(bool set_read);

        //return the value of marked_read
        bool is_read(void);

    protected:

        char * message_body;
        bool marked_read;
};
