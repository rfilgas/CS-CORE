#include "client_item.h"

// ***************************************************************
// Ryan Filgas
// CS202
// Program 1
// Karla Fant
// 4-16-21
//
// The purpose of this file is to hold data structures for tasks,
// emails, and appointments. Task list is an LLL insert sorted by priority.
// Email list is an array of LLLs sectioned into common email buckets
// like read, unread, trash, etc. Appointment list is a CLL of arrays
// with a node for each day. Each respective class has a node class it manages,
// with exception to the appointment class node which manages its own
// array through passed in input. Each of the list classes contains its own
// user interface, while helper functions do most of the dirty work of
// traversing the structure.
//
// The public functions in this data structure are plug and play. They manage
// user input, and calling of private helper functions to do most of the work.
// each of the classes has a retrieve function used heavily ro add, remove, search,
// display, etc. The retrieve functions will always return 0 if they don't find what
// they've been sent to retrieve through the argument list.
//
// At the bottom of this page is the application. It will create an object of each
// data structure, and the individual classes will take over.
//
// ***************************************************************



// A tnode is a node derived from the task class. Since it is derived, it can access
// all of the operations of its parent classes.
class tnode: public task_item 
{
    public:
        tnode();
        tnode(int new_day, int new_month, int new_year, char * new_recipient, int num_priority);
        tnode(char * new_recipient, int num_priority);
        ~tnode();

        void connect_next(tnode * connection); //set next to connect
        tnode * & to_next(void); //return nexts address
        bool if_next()const; //check if next isn't null

    protected:
        tnode * next;
};


//Manage an array of LLLs where each node is a task + more.
class task_list
{
    public:
        task_list();
        task_list(const task_list & source);
        ~task_list();

        //User interfaces and menus.
        void user_interface(void);
        void intro(void);
        void display_menu(void);

        //remove a task by name.
        int remove_task(void);
        //add a task to the list ordered by priority.
        void add_task(void);
        //display a task by name.
        void display_task(void);
        //mark a task complete.
        int complete_task(void);

        //Retrieve is used by my other functions. It didn't seem
        //a sensible thing for a user to be utilising.
        int retrieve(tnode * &to_fill, char * name);
        //Destroy all nodes.
        int remove_all(void);
        //Display all tasks.
        int display_all(void);
        
        
    private:
        //These are helper functions for the above classes.
        ////Return the requested node address through the argument list.
        int retrieve(tnode * &thead, char * to_match, tnode * &to_assign);
        //Destroy all nodes. Return the number of nodes.
        int remove_all(tnode * &thead);
        //Display all nodes. Return the number of nodes.
        int display_all(tnode * &thead);
        //Remove a task by name, and return 0 if not found.
        int remove_task(tnode * &thead, char * name);
        //Output tasks data members to the user.
        int output_task(tnode * &to_display);

        //These are general purpose helper functions.
        int copy_arr(char * &to_fill, char * copy); //This will copy an array, and return 0 for failure.
        int add_node(tnode *& thead, tnode *&temp, int priority);//This will add a node to the list.
        void get_input(char * &to_fill, int input_size); //This will store user input.

        //temporary node to be held for the user.
        tnode * retrieved;
        //head of the LLL
        tnode * head;
        //This is the input size for the get input function.
        int input_size;
};



//node for email
class enode: public email
{
    public:
        enode();
        enode(char * new_recipient);
        enode(int new_day, int new_month, int new_year,char * new_recipient);
        enode(const enode &source);
        ~enode();

        void connect_next(enode * connection); //set next to connect
        enode * & to_next(void); //return nexts address
        bool if_next()const; //check if next isn't null

    protected:
        enode * next;
};



class email_list
{
    public:
        email_list(int size = 5);
        email_list(const email_list & source);
        ~email_list();

        //User facing functions.
        void user_interface(void);
        void display_menu(void);


        //public functions
        void write_email(void); 
        void edit_draft(void);
        void send_email(void);
        void display_email(void);
        void mark_all_read(void);
        int remove_all(void);
        int display_all(void);
        //takes an email category as an in argument.
        int display_category(int ecategory);
        int remove_email(void);
        
        
    private:
        //Takes a node pointer in as an argument, and attaches it to the end
        //of the category selecteds list
        int move_to_category(enode *& to_add, int ecategory);
        //Retrieve a node address through the argument list, return 0 if not found
        int retrieve(enode * &to_fill, char * name, int ecategory);

        int remove_all(enode ** &ptr);
        int remove_all(enode * &ehead);
        //remove email uses the retrieve function, and returns 0 if the object isn't found.
        int remove_email(enode * &ehead, char * name, enode * &to_fill);

        //call the output function on every node in a category
        int display_category(enode * &ehead);
        int output_email(enode * &to_display);

        //helper functions.
        int copy_arr(char * &to_fill, char * copy);
        int retrieve(enode * &ehead, char * to_match, enode * &to_assign);
        void get_input(char * &to_fill, int input_size);
        int copy_LLL(enode *&head, enode *& copy);

        enode * retrieved;
        enode ** my_emails;

        int array_size;
        const int eunread;
        const int eread;
        const int edrafts;
        const int esent;
        const int etrash;
        int input_size;
};





//        CLL of arrays- calender of each days events
class anode
{
    public:
        anode();
        anode(const anode &source);
        ~anode();

        void connect_next(anode * connection); //set next to connect
        anode * & to_next(void); //return nexts address
        bool if_next()const; //check if next isn't null



        
        //recursive remove function, takes a description, and matches with the object description
        // This will retun 0 if the object isn]t found
        int remove_appointment(char * match);
        int remove_appointment(char * match, int &max, appointment **& ptr);

        //create a new appointment through the constructor arguments
        int make_appointment(int atime, int aday, int amonth, int ayear, char * arecipient, char *adescription);
        int make_appointment(int atime, int aday, int amonth, int ayear, char * arecipient, char *adescription, int &max, appointment ** &ptr);

        //display appointment, or return 0 for failure
        int display_appointment(char * match, int &max, appointment ** &ptr);
        int display_appointment (char * match);

        //display appointment data
        int output_appointment(appointment * &to_display);
        int output_appointment_stub(appointment *&to_display);

        //Display a days worth of appointments, and retuen 0 if there's nothing to display.
        int display_day(void);
        int display_day(int &max, appointment ** &ptr);

        //retrieve an appointment object by reference, return 0 if not found.
        int retrieve(char * match, appointment * &to_fill);
        int retrieve(char * match, int &max, appointment ** &ptr, appointment *& to_fill);

        int edit(char * match, int atime, int aday, int amonth, int ayear, char * arecipient, char * adescription, int to_confirm);
        int edit_confirmation(char * to_match, int confirmation);

    protected:
        
        int destroy_array(appointment ** &ptr);
        anode * next;
        appointment ** weekday;
        int array_size;
};





//CLL of arrays- calender of each days events
class appointment_list
{
    public:
        appointment_list();
        appointment_list(const appointment_list & source);
        ~appointment_list();

        //Main menu
        void user_interface(void);
        void display_menu(void);

        //Destroy everything.
        int remove_all(void);

        //The following functions make use of anodes
        //functions to allocat and pass information.
        void make_appointment(void); 
        void remove_appointment(void);
        void display_appointment(void);
        int display_all(void);
        void retrieve(void);
        void edit_appointment(void);
        void confirm_appointment(void);


        
        
    private:

        //call anodes display day function
        int display_day(int day);
        //uses display day, returns if there is nothing to display
        int display_all(anode * &temp, int &count);
        int copy_cll(anode * &copy, anode * source, const appointment_list &origin);
        
        //Destructor helpers
        int destroy_cll(void);
        int destroy_cll(anode *& arear);

        int copy_arr(char * &to_fill, char * copy);
        void get_input(char * &to_fill, int input_size);
        int find_day(anode * &to_fill, int to_traverse);


        anode * rear;
        //indexes for each day of the week
        const int amonday;
        const int atuesday;
        const int awednesday;
        const int athursday;
        const int afriday;
        const int asaturday;
        const int asunday;
        //input size for the get input functions.
        int input_size;
};


//This class manages all of the list classes.
class task_app
{
    public:
        void launch(void);
    private:
        task_list my_tasks;
        email_list my_emails;
        appointment_list my_appointments;
};

