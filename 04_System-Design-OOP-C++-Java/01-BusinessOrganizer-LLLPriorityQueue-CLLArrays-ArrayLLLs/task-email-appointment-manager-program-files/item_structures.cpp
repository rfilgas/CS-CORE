#include "item_structures.h"
using namespace std;


// ***************************************************************
// Ryan Filgas
// CS202
// Karla Fant
// Program 1
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
// ***************************************************************


//TABLE OF CONTENTS-----------------------------------------------
//
// To find a section of the file, search for its identifier.
// The following example will take you to the task lists constructors 
// and destructors. Use 'n' to continue.
// Example: :/tla
//
// TASK_LIST---------------------------------
//
// TLX --> THIS LINE <------
// EM(X) --> Go to emails(remove parens).
// AP(X) --> Go to appointments(remove parens).
//
// tla --> TASK NODES CONSTRUCTOR & DESTRUCTOR
// tlb --> TASK LISTS CONSTRUCTOR & DESTRUCTOR
// tlc --> USER MAIN
// tld --> DISPLAY MENU
// tle --> REMOVE TASK - search by description, return 0 if not found
// tlf --> ADD TASK - also contains add_node. 
// tlg --> DISPLAY TASK - search by description and return 0 if not found,
// tlh --> REMOVE ALL
// tli --> DISPLAY ALL
// tlj --> COMPLETE TASK - mark task complete, or not complete
// tlk --> HELPER FUNCTIONS - output_task, retrieve, get input, copy arr
// tll --> THE_END_OF_TASKLIST
//
// NNN --> NEXT DATA STRUCTURE---------------->
//
// ------- TASK_LIST---------
//
// The purpose of the task list class is to manage a priority sorted list of tasks.
// This class is an insert sorted linear linked list that puts the most important tasks
// first. All of the functions above are supported, and will let the user
// search via task description for anything they would like to edit, display, delete,
// etc.


//tla--tnode_CONSTRUCTORS_&_DESTRUCTORS---------------------------------- 

//JUST ADDED
tnode::tnode(): next(NULL){}

tnode::tnode(int new_day, int new_month, int new_year, char * new_recipient, int num_priority): task_item(new_day, new_month, new_year, new_recipient, num_priority), next(NULL){}

tnode::tnode(char * new_recipient, int num_priority): task_item(new_recipient, num_priority), next(NULL){}

//destructor
tnode::~tnode(){}


//connect node to another node passed in
void tnode::connect_next(tnode * connection)
{
    next = connection; 
}


//check if next node isn;t null
bool tnode::if_next()const 
{
    return(next != NULL);
}


//return address of next pointer
tnode * & tnode::to_next()
{
    return next;
}


// --------------------------------------------------------------


//tlb--TASK_LIST_CONSTRUCTORS_&_DESTRUCTORS----------------------------
task_list::task_list()
{
    input_size = 100;
    retrieved = NULL;
    head = NULL;
//    temp_string = NULL;
}



//COPY CONSTRUCTOR
task_list::task_list(const task_list & source) 
{
    tnode * current = source.head;
    tnode * temp;
    if(source.head)
    {
        while(current)
        {
            temp = new tnode(*current);
            add_node(head, temp, temp -> return_priority());
            current = current -> to_next();
            temp = NULL;
        }
        current = NULL;
    }
}


//Destructor
task_list::~task_list() 
{
    if(retrieved)
        delete retrieved;
    retrieved = NULL;
    remove_all(); //search for :/tlh. I'll put it under the destructor next time.
    input_size = 0;
}
//-----------------------------------------------------------------------



//tlc--USER_MAIN--------------------------------------------------------------
//Main menu for user interface.
void task_list::user_interface(void)
{
    int selection = 0;
    do
    {
        do
        {
            selection = 0;
            cout << "Welcome to the task manager, what would you like to do?\n\n";
            display_menu();
            cin >> selection;
            cin.ignore(100, '\n');
            if(selection < 1 || selection > 7)
            {
                cout << "\nEat slugs Malfoy!\n";
                cout << "I kid. Please enter a valid menu item this time.\n\n";
            }
        }while(selection < 1 || selection > 7);

        if(selection == 1)
            add_task();
        else if(selection == 2)
            remove_task();
        else if(selection == 3)
            display_task();
        else if(selection == 4)
            complete_task();
        else if(selection == 5)
            remove_all();
        else if(selection == 6)
            display_all();
    }while(selection != 7);
}
//-----------------------------------------------------------------------



//tld--DISPLAY_MENU-----------------------------------------------------------------------
//Helper function for main menu to help display.

void task_list::display_menu(void)
{
    cout << "Choose from the following:\n\n";
    cout << "1. Add a task\n";
    cout << "2. Remove a task\n";
    cout << "3. Display a task\n";
    cout << "4. Toggle Completion \n";
    cout << "5. Remove All\n";
    cout << "6. Display ALL\n";
    cout << "7. Exit\n\n";
}



//tle--REMOVE_TASK--------------------------------------------------------------------------
//Remove a task by name after getting input from the user.

int task_list::remove_task(void)
{
    int success = 0;
    char * name;
    cout << "Enter a task(description) to remove.\n";
    get_input(name, input_size); 
    
    if(head == NULL)
    {
        cout << "Empty list!\n";
        return 0;
    }
    success = remove_task(head, name);
    if(!success)
        cout << "A matching task doesn't exist.\n";
    else
        cout << "Successfully deleted\n";
    if(name != NULL)
    {
        delete [] name;
        name = NULL;
    }
    return success;
}



//Helper function to return success for a removed task, and failure if not found.
int task_list::remove_task(tnode * &thead, char * name)
{
    if(thead == NULL)
        return 0;
    int success = remove_task(thead -> to_next(), name);
    if(!success && thead->is_description(name))
    {
        tnode * hold = thead;
        thead = thead -> to_next();
        if(hold != NULL)
            delete hold;
        hold = NULL;
        ++success;
    }
    return success;
}



//tlf---ADD_TASK---------------------------------------------------------------------------------
//Get task input from the user, and insert it recursively.

void task_list::add_task()
{
    //task class variables
    int tday = 0;
    int tmonth = 0;
    int tyear = 0;
    int tpriority;
    char * my_description = NULL;
    char * trecipient = NULL;
    //Get user menu input.
    char response = '\0';
    //Temporary node to attach to list.
    tnode * temp;
    
    cout << "You've chosen to add a task!\n";
    cout << "Do you wish add a date? ( 'y' or 'n').\n";
    cin >> response;
    cin.ignore(100, '\n');

    //let user add date. add a date please.
    if(response == 'y' || response == 'Y')
    {
        cout << "Please enter the day, month, and year. One at a time.(10 12 2020)\n";
        cin >> tday >> tmonth >> tyear;
        cin.ignore(100, '\n');
        response = '\0';
    }


    cout << "Thank you. This task must be assigned to someone, please enter their name.\n";
    get_input(trecipient, input_size);
    cout << "Please enter the priority level of the task as an integer\n";
    cin >> tpriority;
    cin.ignore(100, '\n');
    //Allocate new node.
    temp = new tnode(tday, tmonth, tyear, trecipient, tpriority);

    cout << "Please enter the task description\n";
    get_input(my_description, input_size);
    temp->edit_description(my_description);

    //if head is null
    if(!head)
        head = temp;
    else
    {
        //insert at beginning
        if(!(head -> is_priority(tpriority)))
        {
            temp -> connect_next(head);
            head = temp;
        }
        //Insert everywhere else recursively.
        else
            add_node(head, temp, tpriority);
    }

    //deallocate memory
    if(trecipient)
        delete [] trecipient;
    if(my_description)
        delete [] my_description;

    my_description = NULL;
    trecipient = NULL;
    temp = NULL;
}



//This is a recursive helper function to insert a node sorted by priority
//High priority is inserted at the beginning followed by low.
int task_list::add_node(tnode *& thead, tnode *&temp, int priority)
{
    if(!thead)
        return 0;
    int success = add_node(thead -> to_next(), temp, priority);
    if(!success && (thead -> is_priority(priority)))
    {
        tnode * hold = thead -> to_next();
        thead -> connect_next(temp);
        temp -> connect_next(hold);
        hold = NULL;
        ++success;
    }
    return success;
}



//tlg--DISPLAY_TASK---------------------------------------------------------------------------------
//Use the retrieve function passing in a name to display, and display the returned task.

void task_list::display_task(void)
{
    char * task_name;
    tnode * to_fill;

    cout << "Please enter the description of the task to display\n";
    get_input(task_name, input_size);

    if(head == NULL)
    {
        cout << "There are no tasks, please add a task.\n";
        if(task_name != NULL)
            delete [] task_name;
        task_name = NULL;
        return;
    }
    else
    {
        //retrieve function does the traversing, gets the address, then output displays.
        if(retrieve(head, task_name, to_fill))
            output_task(to_fill);
        else
            cout << "The task you're looking for isn't available.\n";
    }

    if(task_name != NULL)
    {
        delete [] task_name;
        task_name = NULL;
    }
    to_fill = NULL;

    return;
}



//tlh---REMOVE_ALL----------------------------------------------------
//Remove all tasks from the list.

int task_list::remove_all(void)
{
    if(head == NULL)
        return 0;
    int success = remove_all(head);
    return success;
}



//recursive helper function.
int task_list::remove_all(tnode *&thead)
{
    if(thead == NULL)
        return 0;
    int success = 1 + remove_all(thead -> to_next());
    delete thead;
    thead = NULL;
    return success;
}


//tli---DISPLAY_ALL-------------------------------------------------------
//Display all tasks.

int task_list::display_all(void)
{
    if(head == NULL)
        return 0;
    return display_all(head);
}



//Recursive display. Outputs task, catches the return, and adds it to the total.
int task_list::display_all(tnode * &thead)
{
    if(thead == NULL)
        return 0;
    return output_task(thead) + display_all(thead -> to_next());
}



//tlj---COMPLETE_TASK------------------------------------------------------------
//Uses the retrieve function to retrieve a node by name, and mark complete.
int task_list::complete_task(void)
{
    tnode * temp;
    int success = 0;
    char * to_match;

    cout << "Please enter the task you'd like to toggle complete status\n";
    get_input(to_match, input_size);

    //retrieve node address to toggle complete.
    if(!retrieve(head, to_match, temp)) 
        cout << "Task not found.\n";
    else
    {
        cout << "Success!";
        temp -> mark_complete(!temp -> is_complete());
        if(to_match != NULL)
            delete [] to_match;
        to_match = NULL;
        temp = NULL;
    }
    return success;
}



//tlk---HELPER FUNCTIONS---------------------------------------------------

//Display the contents of a task passed in by reference.
int task_list::output_task(tnode *& to_display)
{
    if(!to_display)
        return 0;
    if(!to_display->display_description())
        cout << "Description: None\n";
    if(!to_display->display_recipient())
        cout << "Recipient: None\n";
    to_display->display_priority();
    to_display->display_date();
    if(to_display->is_complete())
        cout << "Completed: YES!\n";
    else
        cout << "Completed: no :/\n\n";
    return 1;
}



//RETRIEVE -- Search by Description
int task_list::retrieve(tnode * &thead, char * to_match, tnode * &to_assign)
{
    if(thead == NULL)
        return 0;
    if(thead -> is_description(to_match))
    {
        to_assign = thead;
        return 1;
    }
    return retrieve(thead -> to_next(), to_match, to_assign);
}



//This allows retrieving with just a task node pointer and name passed by reference. It hides
//the data structure from the public section.
int task_list::retrieve(tnode * &to_fill, char * name)
{
    return retrieve(head, name, to_fill);
}



//General purpose get input function to take care of char * arrays.
void task_list::get_input(char * &to_fill, int input_size)
{
    char temp_char[input_size];
    cin.get(temp_char, input_size, '\n');
    cin.ignore(100, '\n');
    to_fill = new char[strlen(temp_char) + 1];
    strcpy(to_fill, temp_char);
}



//Copy an array.
int task_list::copy_arr(char * &to_fill, char * copy)
{
    if(!copy)
        return 0;
    to_fill = new char[strlen(copy) + 1];
    strcpy(to_fill, copy);
    return 1;
}


//**********************************************************************************************
//******tll-- END OF TASK LIST 
//**********************************************************************************************


//TABLE OF CONTENTS-----------------------------------------------
//
// To find a section of the file, search for its identifier.
// The following example will take you to the task lists constructors 
// and destructors. Use 'n' to continue.
// Example: :/tla

// EMAIL_LIST---------------------------------
//
// EMX --> THIS LINE <------
// AP(X) --> Go to appointment list(remove parens).
// TL(X) --> Go to task list (remove parens).
//
// ema --> EMAIL NODES DESTRUCTOR
// emb --> EMAIL LISTS CONSTRUCTOR & DESTRUCTOR 
// emc --> USER MAIN 
// emd --> DISPLAY MENU
// eme --> WRITE MENU
// emf --> EDIT DRAFT
// emh --> DISPLAY EMAIL(S)
// emi --> MARK ALL READ //Not implemented. Read functionality is used in display.
// emj --> REMOVE_ALL
// emk --> DISPLAY ALL
// eml --> REMOVE ONE
// emm --> HELPER FUNCTIONS: retrieve, display_all, remove_email, copy_arr, add_node, output, input}
// emn ------- END OF EMAIL LIST---------
//
// NNN --> NEXT DATA STRUCTURE---------------->
//
// ------- EMAIL_LIST---------
//
// The purpose of the email list class is to organize emails into different
// commonly used categories for a user. In this case they can add emails to
// unread, read, drafts, sent, and trash. The program gives the user flexibility
// to save a draft of an email, and send it later. They can also choose when
// deleting an email to delete permanently or move to the trash. Structure wise
// this is an array of linear linked lists. The primary workhorses to move
// and find data are the retrieve, and remove function, which are used pretty
// heavily. The remove function will disconnect a node where it can then be
// reattached elsewhere to transfer an email to the trash for example. The above
// functions are supported.



//ema---EMAIL_NODES_CONSTRUCTOR_&_DESTRUCTOR---------------------------------------------------

//Constructors
enode::enode(): next(NULL){}
enode::enode(int new_day, int new_month, int new_year, char * new_recipient): email(new_day, new_month, new_year, new_recipient), next(NULL){}
enode::enode(char * new_recipient): email(new_recipient), next(NULL){}

//Copy Constructor
enode::enode(const enode & source): email(source), next(NULL){}

//Destructor
enode::~enode(){}



//connect to a node.
void enode::connect_next(enode * connection){
    next = connection; 
}



//Check if the next node is there. (There are no look aheads, but just in case.)
bool enode::if_next()const {
    return(next != NULL);
}



//Return the address to the next node.
enode * & enode::to_next()
{
    return next;
}



//emb---EMAIL_LISTS_CONSTRUCTOR_&_DESTRUCTOR---------------------------------------------------

email_list::email_list(int size): eunread(0), eread(1), edrafts(2), esent(3), etrash(4), input_size(100)
{
    array_size = size;
    my_emails = new enode*[size];
    for(int i = 0; i < size; ++i)
        my_emails[i] = NULL;
}



//copy constructor
email_list::email_list(const email_list & source): eunread(0), eread(1), edrafts(2), esent(3), etrash(4), input_size(100)
{
    //enode * temp;
    my_emails = new enode*[source.array_size];
    for(int i = 0; i < (source.array_size); ++i)
    {
        my_emails[i] = NULL;
        copy_LLL(my_emails[i], source.my_emails[i]); 
    }
}



//Helper function for copy constructor.
int email_list::copy_LLL(enode *& ehead, enode * &copy)
{
    if(!copy)
        return 0;
    if(copy != NULL)
        ehead = new enode(*copy);
    return 1 + copy_LLL(ehead -> to_next(), copy -> to_next()); 
}



//Destructor
email_list::~email_list()
{
    remove_all(my_emails); //search :/emj --will place after destructor next time.
    delete [] my_emails;
}



//emc---USER_MAIN---------------------------------------------------
void email_list::user_interface(void)
{
    int selection = 0;
    do
    {
        do
        {
            selection = 0;
            cout << "Welcome to the email manager, what would you like to do?\n\n";
            display_menu();
            cin >> selection;
            cin.ignore(100, '\n');
            if(selection < 1 || selection > 6)
            {
                cout << "\nEat slugs Malfoy!\n";
                cout << "I kid. Please enter a valid menu item this time.\n\n";
            }
        }while(selection < 1 || selection > 6);

        if(selection == 1)
            write_email();
        else if(selection == 2)
            edit_draft();
        else if(selection == 3)
            display_email();
        else if(selection == 4)
            remove_all();
        else if(selection == 5)
            remove_email();

    }while(selection != 6);
}



//emd---DISPLAY_MENU---------------------------------------------------

void email_list::display_menu(void)
{
    cout << "Choose from the following:\n\n";
    cout << "1. Write Email -- allows send, or save to drafts.\n";
    cout << "2. Edit Draft -- supports full editing of data members, and moving to sent.\n";
    cout << "3. Display email(s) -- Supports display, and display all. Marks emails read.\n";
    cout << "4. Remove All\n";
    cout << "5. Remove ONE\n";
    cout << "6. Exit\n\n";
}



//eme---WRITE_EMAIL---------------------------------------------------
void email_list::write_email(void)
{
    //email class variables to edit
    int eday;
    int emonth;
    int eyear;
    int save_or_send;
    char * erecipient = NULL;
    char * my_description = NULL;
    char * emessage = NULL;

    //Get user input for menu.
    char response = '\0';
    //node * to catch nodes address for editing.
    enode * temp;
    
    cout << "You've chosen to write an email!\n";
    cout << "Do you wish add a date? ( 'y' or 'n').\n";
    cin >> response;
    cin.ignore(100, '\n');
    if(response == 'y' || response == 'Y')
    {
        cout << "Please enter the day, month, and year. One at a time.(10 12 2020)\n";
        cin >> eday >> emonth >> eyear;
        cin.ignore(100, '\n');
        response = '\0';
    }
    cout << "Thank you, please enter a recipient.\n";
    get_input(erecipient, input_size);

    //Create a new node to attach.
    temp = new enode(eday, emonth, eyear, erecipient);

    //Enter description, and insert into node.
    cout << "Please enter the email description. This is how you will find the email later.\n";
    cout << "Brief descriptions such as 'school work' are reccomended.\n";
    get_input(my_description, input_size);
    if(!temp -> edit_description(my_description))
        cout << "No description added\n";

    //enter message
    cout << "Please enter the message you'd like to send.\n";
    get_input(emessage, input_size);
    if (temp -> write(emessage))
    {
        cout << "Would you like this message saved as a draft or sent?\n\n";
        cout << "1. Save\n";
        cout << "2. Send\n";
        cin >> save_or_send; 
        cin.ignore(100, '\n');
        if(save_or_send == 1)
        {
            //Attach node to drafts list.
            if(move_to_category(temp, edrafts))
            {
                cout << "Saved Successfully\n\n";
                temp = NULL;
            }
            else
                cout << "Email couldn;t be saved\n\n";
        }
        else if(save_or_send == 2)
        {
            //Attach node to sent list.
           if( move_to_category(temp, esent))
           {
               cout << "Sent Successfully\n\n";
               temp = NULL;
           }
           else
               cout << "Email couldn't be sent.\n\n";
        }
    }
    //Deallocate memory. Might be good to write a function for this.
    if(erecipient != NULL)
    {
        delete [] erecipient;
        erecipient = NULL;
    }
    if(my_description != NULL)
    {
        delete [] my_description;
        my_description = NULL;
    }
    if(emessage != NULL)
    {
        delete [] emessage;
        emessage = NULL;
    }
    if(temp != NULL)
    {
        delete temp;
        temp = NULL;
    }
    return;
}



//emf---EDIT_DRAFT---------------------------------------------------
void email_list::edit_draft(void)
{
    //email class variables
    int eday;
    int emonth;
    int eyear;
    char * erecipient;
    char * edescription;
    char * ebody;

    //Get user input for menus
    char * user_input;
    int choice;
    char exit_edit = 'n';

    //Catch node address
    enode * temp;
    enode * to_send;
    
    if(my_emails[edrafts] == NULL)
        cout << "There are no draft emails to edit. Returning to main menu.\n";

    else
    {
        cout << "Here are your emails:\n\n";
        display_category(edrafts);
        cout << "Please enter the description of the email you would like to edit.";
        get_input(user_input, input_size);
        if(!retrieve(temp, user_input, edrafts))
            cout << "The email you are looking for isn't here.\n";
        else
        {
            do
            {
               output_email(temp); //display description, and recipient.
               temp -> display(); //display email body
               temp -> display_date(); //display date
               cout << "\n\nWhat would you like to change?\n\n";
               cout << "1. Description\n";
               cout << "2. Recipient\n";
               cout << "3. Message Body\n";
               cout << "4. Date\n";
               cout << "5. Send Email.\n";
               cout << "6. Exit Edit Menu\n";
               cin >> choice;
               cin.ignore(100, '\n');
               if(choice == 1)
               {
                   cout << "Please enter the new description.\n"; 
                   get_input(edescription, input_size);

                   //Edit description
                   temp -> edit_description(edescription);

                   //Clear memory
                   if(edescription != NULL)
                   {
                       delete [] edescription;
                       edescription = NULL;
                   }
               }
               else if(choice == 2)
               {
                   cout << "Please enter the new recipient.\n"; 
                   get_input(erecipient, input_size);

                   //edit recipient
                   temp -> edit_recipient(erecipient);
                   
                   //clear memory
                   if(erecipient != NULL)
                   {
                       delete [] erecipient;
                       erecipient = NULL;
                   }
               }
               else if(choice == 3)
               {
                   cout << "Please enter the new message body.\n"; 
                   get_input(ebody, input_size);

                   //edit email body
                   temp -> write(ebody);

                   //clear memory
                   if(ebody != NULL)
                   {
                       delete [] ebody;
                       ebody = NULL;
                   }
               }
               else if(choice == 4)
               {
                   //edit date
                   cout << "Please enter the new date as three integers (example: 08 17 2021).\n"; 
                   cin >> eday >> emonth >> eyear;
                   cin.ignore(100, '\n');
                   temp -> edit_date(eday, emonth, eyear);
               }
               else if(choice == 5)
               {
                   //Use remove fection to diconnect email node, and get address.
                   if(!remove_email(my_emails[edrafts], user_input, to_send))
                       cout << "Email was not found.\n";
                   else
                   {
                       //add node to sent category.
                       move_to_category(to_send, esent);
                       cout << "\nEmail sent.\n";
                       exit_edit = 'y';
                       to_send = NULL;
                   }
               }
               else if(choice == 6)
                   exit_edit = 'y';

            }while(exit_edit == 'n');
        }
        //clear memory
        if(user_input != NULL)
        {
            delete [] user_input;
            user_input = NULL;
        }
    }
    return;
}



//emh---DISPLAY_EMAIL---------------------------------------------------
void email_list::display_email(void)
{
    //name of email to display
    char * to_display;
    
    //Menu helpers
    char exit_display = 'n';
    int displayed;
    int response;

    //node * to fetch address
    enode * temp;

    do
    {
        cout << "Please select the section you'd like to view emails for by entering\n";
        cout << "in the corresponding section number.\n\n";
        cout << "1. Unread Emails\n"; 
        cout << "2. Read Emails\n";
        cout << "3. Drafts\n";
        cout << "4. Sent Emails\n"; 
        cout << "5. Trash Can\n";
        cout << "6. DISPLAY ALL\n";
        cin >> response;
        cin.ignore(100, '\n');
        if(response == 6)
        {
           displayed = display_all();
           cout << "Displayed " << displayed << " emails.\n\n";
           displayed = 0;
        }
        else
        {
            display_category((response - 1)); //Categories are an index.
            cout << "\n\nEnter the description of the email you'd like to view.\n";
            get_input(to_display, input_size);
            if(!retrieve(temp, to_display, (response-1)))
                cout << "The description you entered can't be found, please try again.\n";
            else
            {
                output_email(temp); //display description, and recipient.
                temp -> display(); //display email body
                temp -> display_date(); //display date
                if(!temp -> is_read())
                {
                    temp -> mark_read(1); //mark read
                }
            }
            if(to_display != NULL)
            {
                delete [] to_display;
                to_display = NULL;
            }
            if(temp != NULL)
                temp = NULL;
        }
        cout << "\n\nWould you like to display another? ('y' or 'n')\n";
        cin >> exit_display;
        cin.ignore(100, '\n');
        response = 0;
    }while(exit_display == 'y' || exit_display == 'Y');
    return;
}

//emi---MARK_ALL_READ---------------------------------------------------
// Not implemented. Read all functionality is used in display however.
void email_list::mark_all_read(void)
{

}

//emj---REMOVE_ALL---------------------------------------------------

//to hide nodes from public functions
int email_list::remove_all(void)
{
    return remove_all(my_emails);
}

//recursive wrapper to remove all.
int email_list::remove_all(enode ** &ptr)
{
    int total = 0;
    for(int i = 0; i < array_size; ++i)
    {
        if(ptr[i] != NULL)
            total += remove_all(ptr[i]);
    }
    return total;
}

int email_list::remove_all(enode * &ehead)
{
    if(ehead == NULL)
        return 0;
    int success = 1 + remove_all(ehead -> to_next());
    delete ehead;
    ehead = NULL;
    return success;
}


//emk---DISPLAY_ALL---------------------------------------------------

//Loop iteratively through the array, and call recursive function to
//delete each LLL.
int email_list::display_all(void)
{
    int count = 0;
    for(int i = 0; i < array_size; ++i)
        count += display_category(i);
    return count;
}



//recursive wrapper to display a category of emails
int email_list::display_category(int ecategory)
{
    enode * current = my_emails[ecategory];
    if(current == NULL)
        return 0;
    return display_category(current);
}



//Output email in the return and count it.
int email_list::display_category(enode * &ehead)
{
    if(ehead == NULL)
        return 0;
    return output_email(ehead) + display_category(ehead -> to_next());
}



//eml---REMOVE_ONE---------------------------------------------------

int email_list::remove_email(void)
{
    //return success
    int success = 0;
    //email description to remove
    char * to_remove;
    //user response to menu
    int response;
    //node pointer to catch address
    enode * to_fill;

    cout << "Please select the section you'd like to remove emails from by entering\n";
    cout << "in the corresponding section number.\n\n";
    cout << "1. Unread Emails\n"; 
    cout << "2. Read Emails\n";
    cout << "3. Drafts\n";
    cout << "4. Sent Emails\n"; 
    cout << "5. Trash Can\n";
    cin >> response;
    cin.ignore(100, '\n');

    if(!display_category((response - 1))) //Categories are an index.
    {
            cout << "There are no entries to display!\n";
    }
    else
    {
        cout << "\n\nEnter the description of the email you'd like to view.\n";
        get_input(to_remove, input_size);
        //use helper function to remove email, subtract 1 for the index.
        success = remove_email(my_emails[(response - 1)], to_remove, to_fill);

        if(!success)
            cout << "There was a problem removing email.\n";
        else 
        {
            cout << "Email removed!";
            cout << "Would you like to delete the email, or move it to the trash?\n";
            cout << "1. Delete email.\n";
            cout << "2. Move to trash.\n";
            cin >> response;
            cin.ignore(100, '\n');
            if(response == 1)
            {
                if(to_fill != NULL)
                    delete to_fill;
                to_fill = NULL;
            }
            else
            {
                //move node to trash.
                move_to_category(to_fill, etrash);
                to_fill = NULL;
            }
        }
        if(to_remove != NULL)
        {
            delete [] to_remove;
            to_remove = NULL;
        }
    }
    return success;
}



//helper function to remove an email recursively.
int email_list::remove_email(enode * &ehead, char * name, enode *& to_fill)
{
    if(ehead == NULL || name == NULL)
        return 0;
    int success = remove_email(ehead -> to_next(), name, to_fill);
    if(!success && ehead->is_description(name))
    {
        to_fill = ehead;
        ehead = ehead -> to_next();
        ++success;
    }
    return success;
}



//emm---HELPER_FUNCTIONS---------------------------------------------------

//retrieve an email by name and categoty. Will return 0 for a null pointer, or
//unsuccessful search.
int email_list::retrieve(enode * &to_fill, char * name, int ecategory)
{
    enode * current = my_emails[ecategory];
    if(current == NULL)
        return 0;
    return retrieve(current, name, to_fill);
}



//recursive helper function to retrieve an email address.
int email_list::retrieve(enode * &ehead, char * to_match, enode * &to_assign)
{
    if(ehead == NULL)
        return 0;
    if(ehead -> is_description(to_match))
    {
        to_assign = ehead;
        return 1;
    }
    return retrieve(ehead -> to_next(), to_match, to_assign);
}


//copy an array
int email_list::copy_arr(char * &to_fill, char * copy)
{
    if(!copy)
        return 0;
    to_fill = new char[strlen(copy) + 1];
    strcpy(to_fill, copy);
    return 1;
}


//Output email using the class hierarchies functions.Return 0 if either isn't there.
int email_list::output_email(enode * &to_display)
{
    return(to_display -> display_description() && to_display -> display_recipient());
}



//get user input
void email_list::get_input(char * &to_fill, int input_size)
{
    char temp_char[input_size];
    cin.get(temp_char, input_size, '\n');
    cin.ignore(100, '\n');
    to_fill = new char[strlen(temp_char) + 1];
    strcpy(to_fill, temp_char);
}



//Move a node to another category in the email list.
int email_list::move_to_category(enode *& to_add, int ecategory)
{
    int success = 0;
    enode * hold = my_emails[ecategory];

    if(hold == NULL)
    {
        my_emails[ecategory] = to_add;
        success = 1;
    }
    else
    {
        my_emails[ecategory] = to_add;
        my_emails[ecategory] -> to_next() = hold;
        success = 1;
    }
    return success;
}

        
        
        
//**********************************************************************************************
//******eml-- END OF EMAIL LIST 
//**********************************************************************************************


//TABLE OF CONTENTS-----------------------------------------------
//
// To find a section of the file, search for its identifier.
// The following example will take you to the task lists constructors 
// and destructors. Use 'n' to continue.
// Example: :/tla

// APPOINTMENT_LIST---------------------------------
//
// APX --> THIS LINE <------
// EM(X) --> Go to email(remove parens).
// TL(X) --> Go to task list (remove parens).
//
// apa --> APPOINTMENT NODES CONSTRUCTOR AND DESTRUCTOR
// apb --> OUTPUT APPOINTMENT (ANODE)
// apc --> REMOVE APPOINTMENT (ANODE)
// apd --> DISPLAY_DAY (ANODE)
// ape --> RETRIEVE (ANODE)
// apf --> EDIT (ANODE) 
// apg --> MAKE APPOINTMENT (ANODE) 
// aph --> APPOINTMENT LIST DESTRUCTOR AND CONSTRUCTORS
// api --> REMOVE_ALL -- used by destructor
// apj --> USER MAIN
// apk --> DISPLAY MENU
// apkx --> MAKE APPOINTMENT
// aplx --> EDIT APPOINTMENT
// apm --> DISPLAY APPOINTMENT
// apn --> CONFIRM APPOINTMENT
// apo --> DISPLAY_ALL
// appx --> DISPLAY_DAY
// apq --> REMOVE APPOINTMENT
// apr --> RETRIEVE
// aps --> HELPER FUNCTIONS: get input, copy arr, find day
//
// NNN --> TO TASK LIST---------------->
//
// ------- APPOINTMENT_LIST---------
//
// Appointment list is a circular linked list of arrays.
// The purpose of the appointment list class is to store the events from a seven day week.
// As they only have limited time, there are also limited timeslots to add in. Unlike the
// other two structures, the node class is working with it's data, and the list class is
// managing the node, and passing it arguments to do the necessary work. The node class
// for the most part has functions that manage their own traversal, however some
// do rely on a retrieve function within the node class. The list class has a retrieve
// function called find day that is used to locate nodes in the CLL. From there, all
// of the nodes public functions can be called.


// apa---APPOINTMENT NODES CONSTRUCTOR AND DESTRUCTOR-----------------------------------------


// default constructor
anode::anode(): next(NULL), array_size(10)
{
    weekday = new appointment *[array_size];
    for(int i = 0; i < array_size; ++i)
    {
        weekday[i] = NULL;
    }
}



//copy constructor
anode::anode(const anode &source): next(source.next), array_size(source.array_size)
{
    appointment ** new_arr = source.weekday;
    weekday = new appointment*[array_size];
    for(int i = 0; i < array_size; ++i)
    {
            weekday[i] = new_arr[i];
    }
}



//destructor
anode::~anode()
{
    if(weekday != NULL)
    {
        for(int i = 0; i < array_size; ++i)
        {
            if(weekday[i] != NULL)
            {
                delete weekday[i];
                weekday[i] = NULL;
            }
        }
        delete [] weekday;
        weekday = NULL;
    }
}



//connect to another node
void anode::connect_next(anode * connection)
{
    next = connection; 
}



// check if next pointer is null
bool anode::if_next()const {
    return(next != NULL);
}


//return address of next pointer
anode * & anode::to_next()
{
    return next;
}




// apb---OUTPUT APPOINTMENT-----------------------------------------
int anode::output_appointment(appointment* &to_display)
{
    if(!to_display)
        return 0;
    if(!to_display->display_description())
        cout << "Description: None\n";
    if(!to_display->display_recipient())
        cout << "Recipient: None\n";
    to_display->display_date();
    to_display -> display_time();
    if(to_display->is_confirmed())
        cout << "Confirmed: YES!\n";
    else
        cout << "\nConfirmed: no :/\n\n";
    return 1;
}


// Output description and date information to let user choose which to display fully.
int anode::output_appointment_stub(appointment * &to_display)
{
    if(to_display != NULL && !to_display->display_description())
        return 0;
    to_display->display_date();
    to_display -> display_time();
    return 1;
}



// Recursive wrapper function to display an appointment
int anode::display_appointment(char * match)
{
    int countdown = array_size;
    appointment ** ptr = weekday;
    return display_appointment(match,countdown,ptr); 
}



// Recursive display.
// If theres a matchng appointment, display it.
int anode::display_appointment(char * match, int &max, appointment **& ptr)
{
    if(max == 0)
        return 0;
    //(*ptr) is there just to make sure we don;t dereference a null pointer.
    if((*ptr) != NULL && (*ptr)-> is_description(match))
    {
        output_appointment(*ptr);
        return 1;
    }
    return display_appointment(match, --max, ++ptr);
}



// apc---REMOVE APPOINTMENT-----------------------------------------

// This is a recursive wrapper function to remove an appointment;
int anode::remove_appointment(char * match)
{
    int countdown = array_size;
    appointment ** ptr = weekday;
    if(!weekday)
        return 0;
    return remove_appointment(match,countdown,ptr); 
}

//If a description matches, delete it, and set it to null.
int anode::remove_appointment(char * match, int &max, appointment **& ptr)
{
    if((*ptr) != NULL && (*ptr)-> is_description(match))
    {
        delete (*ptr);
        (*ptr) = NULL;
        return 1;
    }
    if(max == 1)
        return 0;
    return remove_appointment(match, --max, ++ptr);
}




// apd---DISPLAY_DAY-----------------------------------------

// Recursive wrapper to display
int anode::display_day(void)
{
    int countdown = array_size;
    appointment ** ptr = weekday;
    if(weekday == NULL)
        return 0;
    return display_day(countdown, ptr);
}



//For each appointment in the array, display it.
//Return 0 if appointment isn't found.
int anode::display_day(int &max, appointment ** &ptr)
{
    if(!max)
        return 0;
    if((*ptr) != NULL)
    {
        output_appointment_stub(*ptr);
    }
    return display_day(--max, ++ptr);
}


// ape---RETRIEVE-----------------------------------------

// retrieve an appointment, and pass back the address through the argument list.
// return 0 if not found.
int anode::retrieve(char * match, appointment * &to_fill)
{
    int countdown = array_size;
    appointment ** ptr = weekday;
    if(!weekday)
        return 0;
    return retrieve(match,countdown,ptr, to_fill); 
}

int anode::retrieve(char * match, int &max, appointment ** &ptr, appointment *& to_fill)
{
    if((*ptr)-> is_description(match))
    {
        to_fill = (*ptr);
        return 1;
    }
    if(max == 1)
        return 0;
    return retrieve(match, --max, ++ptr, to_fill);
}






// apf---EDIT-----------------------------------------

// This is a recursive wrapper to edit an appointment. It will return 0 if not found.
int anode::edit(char * match, int atime, int aday, int amonth, int ayear, char * arecipient, char * adescription, int to_confirm)
{
    appointment * to_fill;
    if(retrieve(match,to_fill))
    {
        to_fill -> edit(aday, amonth, ayear, arecipient, adescription);
        to_fill -> confirm(to_confirm);
        to_fill -> edit_time(atime);
        return 1;
    }
    return 0;
}

int anode::edit_confirmation(char * to_match, int confirmation)
{
    appointment * to_fill;
    if(retrieve(to_match,to_fill))
    {
        to_fill -> confirm(confirmation);
        return 1;
    }
    return 0;
}



// apg---MAKE APPOINTMENT-----------------------------------------
// This is a recursive wrapper to create an appointment. It will return 0 if not found.


int anode::make_appointment(int atime, int aday, int amonth, int ayear, char * arecipient, char *adescription)
{
    appointment ** ptr = weekday;
    int countdown = array_size;
    if(!(*ptr))
    {
        (*ptr) = new appointment(aday, amonth, ayear, arecipient, atime);
        (*ptr) -> edit_description(adescription);
        return 1;
    }
    return make_appointment(atime, aday, amonth, ayear, arecipient, adescription, countdown, ptr);
}



int anode::make_appointment(int atime, int aday, int amonth, int ayear, char * arecipient, char *adescription, int &max, appointment ** &ptr)
{
    if(!max)
        return 0;
    if(!(*ptr))
    {
        (*ptr) = new appointment(aday, amonth, ayear, arecipient, atime);
        (*ptr) -> edit_description(adescription);
        return 1;
    }
    return make_appointment(atime, aday, amonth, ayear, arecipient, adescription, --max, ++ptr);
}



//aph---APPOINTMENT LIST CONSTRUCTOR AND DESTRUCTOR--------------------------
appointment_list::appointment_list(): rear(NULL), amonday(0), atuesday(1), awednesday(2), athursday(3), afriday(4), asaturday(5), asunday(6), input_size(100)
{
    rear = new anode;
    anode * temp = rear;
    for(int i = 0; i <= asunday; ++i)
    {
        temp -> to_next() = new anode;
        temp = temp -> to_next();
    }
    temp -> connect_next(rear);
    temp = NULL;
}



//copy constructor
appointment_list::appointment_list(const appointment_list & source): amonday(source.amonday), atuesday(source.atuesday), awednesday(source.awednesday), athursday(source.athursday), afriday(source.afriday), asaturday(source.asaturday), asunday(source.asunday), input_size(source.input_size)
{
    if(source.rear)
    {
        rear = new anode(*source.rear);
        copy_cll(rear -> to_next(), source.rear->to_next(), source);
    }
}



//recursive helper for copy constructor
int appointment_list::copy_cll(anode * &copy, anode * source, const appointment_list &origin)
{
    if(!source)
        return 0;
    if(source == origin.rear)
    {
        copy = rear;
        return 1;
    }
    copy = new anode(*source);
    return 1 + copy_cll(copy -> to_next(), source -> to_next(), origin);
}



//destructor
appointment_list::~appointment_list()
{
    destroy_cll();//under remove all below.
}



//api---REMOVE ALL---------------------------------------------------



//hide node structure from public functions
int appointment_list::remove_all(void)
{
    return destroy_cll();
}


//recursively destroy a CLL
int appointment_list::destroy_cll(void)
{
    int deleted = 0;
    if(!rear)
        return 0;

    if(rear  == rear -> to_next())
    {
        delete rear;
        rear = NULL;
        return 1;
    }
    //recursive call
    deleted = destroy_cll(rear -> to_next());
    delete rear;
    rear = NULL;
    return deleted;
}

//rear is an alias for the previous pointers next pointer.
//by setting it to null, and deleting as the stack unwinds,
//the entire CLL is deleted.
int appointment_list::destroy_cll(anode *& arear)
{
    if(arear == this -> rear)
    {
        arear = NULL;
        return 0;
    }
    int success = destroy_cll(arear -> to_next());
        delete arear;
        arear = NULL;
        ++success;
    return success;
}



//apj---USER_MAIN---------------------------------------------------
void appointment_list::user_interface(void)
{
    int selection = 0;
    int menu_size = 9;
    do
    {
        do
        {
            selection = 0;
            cout << "Welcome to the appointment manager, what would you like to do?\n\n";
            display_menu();
            cin >> selection;
            cin.ignore(100, '\n');
            if(selection < 1 || selection > menu_size)
            {
                cout << "\nEat slugs Malfoy!\n";
                cout << "I kid. Please enter a valid menu item this time.\n\n";
            }
        }while(selection < 1 || selection > menu_size);

        if(selection == 1)
            make_appointment();
        else if(selection == 2)
            edit_appointment();
        else if(selection == 3)
            display_appointment();
        else if(selection == 4)
            confirm_appointment();
        else if(selection == 5)
            remove_appointment();
        else if(selection == 6)
            remove_all();
        else if(selection == 7)
            display_all();
        else if(selection == 8)
            retrieve();
    }while(selection != menu_size);
    return;
}



//apk---DISPLAY_MENU---------------------------------------------------

void appointment_list::display_menu(void)
{
    cout << "Choose from the following:\n\n";
    cout << "1. Add Appointment.\n"; 
    cout << "2. Edit Appointment.\n";
    cout << "3. Display Appointment.\n";
    cout << "4. Confirm or cancel an appointment.\n";
    cout << "5. Remove_appointment\n";
    cout << "6. Remove_all\n";
    cout << "7. Display All\n";
    cout << "8. Retrieve and display an item. //Proof of concept. Wouldn't be user facing normally\n";
    cout << "9. Exit\n\n";
}


//apkx---DISPLAY_MENU---------------------------------------------------
void appointment_list::make_appointment(void)
{
    //appointment variables
    int to_store;
    int atime;
    int aday;
    int amonth;
    int ayear;
    char * arecipient = NULL;
    char * my_description = NULL;

    //node * to get address for
    anode * to_fill;

    do
    {
        cout << "Please enter the day of the week your appointment is as an integer.\n\n";
        cout << "1. Monday\n";
        cout << "2. Tuesday\n";
        cout << "3. Wednesday\n";
        cout << "4. Thursday\n";
        cout << "5. Friday\n";
        cout << "6. Saturday\n";
        cout << "7. Sunday\n";
        cin >> to_store;
        cin.ignore(100, '\n');
        if(to_store < 1 || to_store > 7)
            cout << "Invalid entry. Please enter a number between 1 & 7\n";
    }while(to_store < 1 || to_store >7);

    cout << "Please enter the time of your appointment in 24 hour time (ex: 0800)\n";
    cin >> atime;
    cin.ignore(100, '\n');
    cout << "Please enter the date the appointment was made as day, month and year (05 23 1990)\n";
    cin >> aday >> amonth >> ayear;
    cin.ignore(100, '\n');
    cout << "Please enter the name whom the appointment is with\n";
    get_input(arecipient, input_size);
    cout << "Please enter the appointment description.\n";
    get_input(my_description, input_size);

    //use find day to retrieve node
    if(!find_day(to_fill,to_store))
        cout << "Schedule hasn't been created. Please contact your local systems administrator\n";

    //set appointment variables
    if(to_fill -> make_appointment(atime, aday, amonth, ayear, arecipient, my_description))
        cout << "Stored successfully\n";
    else
    {
        cout << "There isn't any room left in the schedule on the day you requested.\n";
        cout << "Please clear some room in your calender, and try again\n";
    }

    //deallocate memory
    to_fill = NULL;
    if(my_description != NULL)
    {
        delete [] my_description;
        my_description = NULL;
    }
    if(arecipient != NULL)
    {
        delete [] arecipient;
        arecipient = NULL;
    }
    return;
}



//aplx---EDIT APPOINTMENT---------------------------------------------------
void appointment_list::edit_appointment(void)
{
    //appointment variables
    int atime;
    int aday;
    int amonth;
    int ayear;
    int confirm;
    char * arecipient = NULL;
    char * my_description = NULL;
    char * to_match = NULL;

    //user input variable
    int to_store;

    //node * address to fill
    anode * to_fill;

    do
    {
        cout << "Please enter the day of the week your appointment is as an integer.\n\n";
        cout << "1. Monday\n";
        cout << "2. Tuesday\n";
        cout << "3. Wednesday\n";
        cout << "4. Thursday\n";
        cout << "5. Friday\n";
        cout << "6. Saturday\n";
        cout << "7. Sunday\n";
        cin >> to_store;
        cin.ignore(100, '\n');
        if(to_store < 1 || to_store > 7)
            cout << "Invalid entry. Please enter a number between 1 & 7\n";
    }while(to_store < 1 || to_store >7);

    if(!find_day(to_fill,to_store))
        cout << "Schedule hasn't been created. Please contact your local systems administrator\n";
    to_fill -> display_day();

    cout << "Please enter the description of the appointment you would like to edit.\n";
    get_input(to_match, input_size);


    cout << "Here is the current information. Please re-enter all information to edit\n\n";
    to_fill->display_appointment(to_match);


    cout << "\n\nPlease enter the time of your appointment in 24 hour time (ex: 0800)\n";
    cin >> atime;
    cin.ignore(100, '\n');
    cout << "Please enter the date the appointment was made as day, month and year (05 23 1990)\n";
    cin >> aday >> amonth >> ayear;
    cin.ignore(100, '\n');
    cout << "Please enter the name whom the appointment is with\n";
    get_input(arecipient, input_size);
    cout << "Please enter the appointment description.\n";
    get_input(my_description, input_size);
    cout << "would you like to confirm or cancel this appointment?\n";
    cout << "Enter 1 to confirm, or 0 to cancel\n";
    cin >> confirm;
    cin.ignore(100, '\n');

    //use find day to retrieve address
    if(!find_day(to_fill,to_store))
        cout << "Schedule hasn't been created. Please contact your local systems administrator\n";
    //use nodes edit function once found.
    if(to_fill -> edit(to_match, atime, aday, amonth, ayear, arecipient, my_description, confirm))
        cout << "Stored successfully\n";
    else
    {
        cout << "Unfortunately this can't be edited as entered. Please try again.\n";
    }
    //dallocate memory
    to_fill = NULL;
    if(my_description != NULL)
    {
        delete [] my_description;
        my_description = NULL;
    }
    if(arecipient != NULL)
    {
        delete [] arecipient;
        arecipient = NULL;
    }
    if(to_match != NULL)
    {
        delete [] to_match;
        to_match = NULL;
    }
    return;
}



// apm--DISPLAY APPOINTMENT------------------------------------------
void appointment_list::display_appointment(void)
{
    //user selected day
    int day_num;

    //user selected description
    char * adescription;

    //node * to store address to display
    anode * to_fill;

    cout << "Which day would you like to display an appointment from?\n";
    cout << "Please enter the day of the week your appointment is as an integer.\n\n";
    cout << "1. Monday\n";
    cout << "2. Tuesday\n";
    cout << "3. Wednesday\n";
    cout << "4. Thursday\n";
    cout << "5. Friday\n";
    cout << "6. Saturday\n";
    cout << "7. Sunday\n";
    cin >> day_num;
    cin.ignore(100, '\n');

    //use find day to capture node address
    if(!find_day(to_fill,day_num))
        cout << "Schedule hasn't been created. Please contact your local systems administrator\n";
    //use node address to display every entry as stubs
    to_fill -> display_day();
    cout << "\n\nHere are the appoinments on the day you requested. Please enter the description\n";
    cout << "of the day you would like to display. This is case sensitive\n";
    get_input(adescription, input_size);

    //Let user display all info from one appointment.
    if(!to_fill -> display_appointment(adescription))
        cout << "Unfortunately there wasn't a match for your input. Proceeding to menu\n";
    if(adescription != NULL)
    {
        delete [] adescription;
        adescription = NULL;
    }
    to_fill = NULL;
    return;
}



// apn---CONFIRM APPOINTMENT-----------------------------------------
void appointment_list::confirm_appointment(void)
{
    //user selected day
    int day_num;

    //user selected description
    char * to_match;

    //confirmation status selected by user
    int confirmation;

    //node address to catch
    anode * to_fill;

    cout << "Which day would you like to confirm an appointment for?\n";
    cout << "Please enter the day of the week your appointment is as an integer.\n\n";
    cout << "1. Monday\n";
    cout << "2. Tuesday\n";
    cout << "3. Wednesday\n";
    cout << "4. Thursday\n";
    cout << "5. Friday\n";
    cout << "6. Saturday\n";
    cout << "7. Sunday\n";

    cin >> day_num;
    cin.ignore(100, '\n');

    //use find day to retrieve node
    if(!find_day(to_fill,day_num))
        cout << "Schedule hasn't been created. Please contact your local systems administrator\n";

    //display the nodes data for user to see options
    to_fill -> display_day();
    cout << "\n\nHere are the appoinments on the day you requested. Please enter the description\n";
    cout << "of the appointment to confirm, or unconfirm. This is case sensitive.\n";
    get_input(to_match, input_size);
    cout << "Would you like to confirm, or unconfirm this appointment? Enter 1 to confirm, or 0\n";
    cout <<  "to unconfirm\n";
    cin >> confirmation;
    cin.ignore(100, '\n');

    //set confirmation information
    to_fill -> edit_confirmation(to_match, confirmation);

    //release memory
    if(to_match != NULL)
    {
        delete [] to_match;
        to_match = NULL;
    }
    to_fill = NULL;
}



// apo---DISPLAY_ALL-----------------------------------------


//recursive display all function
int appointment_list::display_all(void)
{
    //Initiate to first day of week
    int count = 1;

    //set temp pointer
    anode * temp = rear;

    //base case
    if(!rear)
        return 0;
    //display first day, and call display on the rest.
    cout << "Monday: \n";
    temp -> display_day();
    return display_all(temp -> to_next(), count);
}

int appointment_list::display_all(anode * &temp, int &count)
{
    if(!temp)
    {
        return 0;
        cout << "display all returned\n";
    }
    if(count > (asunday+1))
        return 1;
    else if(count == 2)
        cout << "\nTuesday: \n";
    else if(count == 3)
        cout << "\nWednesday: \n";
    else if(count == 4)
        cout << "\nThursday: \n";
    else if(count == 5)
        cout << "\nFriday: \n";
    else if(count == 6)
        cout << "\nSaturday: \n";
    else if(count == 7)
        cout << "\nSunday: \n";
    temp -> display_day();
    return display_all(temp -> to_next(), ++count);
}



// appx---DISPLAY DAY-----------------------------------------
int appointment_list::display_day(int day)
{
    anode * to_fill;
    cout << "\n\n";
    //fetch node from day requested
    if(!find_day(to_fill,day))
    {
        cout << "Schedule hasn't been created. Please contact your local systems administrator\n";
        return 0;
    }
    //call display day function in node.
    to_fill -> display_day();
    to_fill = NULL;
    cout << "\n\n";
    return 1;
}



// apq---REMOVE APPOINTMENT-----------------------------------------
void appointment_list::remove_appointment(void)
{
    //user entered day
    int day_num;

    //user entered description to display
    char * adescription;

    //catch node address
    anode * to_fill;

    cout << "Which day would you like to display an appointment from?\n";
    cout << "Please enter the day of the week your appointment is as an integer.\n\n";
    cout << "1. Monday\n";
    cout << "2. Tuesday\n";
    cout << "3. Wednesday\n";
    cout << "4. Thursday\n";
    cout << "5. Friday\n";
    cout << "6. Saturday\n";
    cout << "7. Sunday\n";
    cin >> day_num;
    cin.ignore(100, '\n');

    //use find day to retrieve node address
    if(!find_day(to_fill,day_num))
        cout << "Schedule hasn't been created. Please contact your local systems administrator\n";

    //display nodes data
    to_fill -> display_day();
    cout << "\n\nHere are the appoinments on the day you requested. Please enter the description\n";
    cout << "of the appointment you would like to delete. This is case sensitive\n";
    get_input(adescription, input_size);
    to_fill -> remove_appointment(adescription);

    //deallocate memory
    if(adescription != NULL)
    {
        delete [] adescription;
        adescription = NULL;
    }
    to_fill = NULL;
    return;
}


// apr---RETRIEVE-----------------------------------------
void appointment_list::retrieve(void)
{
    //day to "retrieve"
    int day_num;
    char * adescription;
    anode * to_fill;
    appointment * to_display;
    cout << "A user definitely shouldn't be retrieving anything, BUT\n";
    cout << "I'll permit you this one time to test the retrieve function since\n";
    cout << "I haven't used this one elsewhere. I hope that's ok.\n\n";
    cout << "Which day would you like to retrieve an appointment from?\n";
    cout << "Please enter the day of the week your appointment is as an integer.\n\n";
    cout << "1. Monday\n";
    cout << "2. Tuesday\n";
    cout << "3. Wednesday\n";
    cout << "4. Thursday\n";
    cout << "5. Friday\n";
    cout << "6. Saturday\n";
    cout << "7. Sunday\n";
    cin >> day_num;
    cin.ignore(100, '\n');

    //use find day function to retrieve node address
    if(!find_day(to_fill,day_num))
        cout << "Schedule hasn't been created. Please contact your local systems administrator\n";

    //display the days appointments for the user
    to_fill -> display_day();

    cout << "\n\nHere are the appoinments on the day you requested. Please enter the description\n";
    cout << "of the appointment you would like to retrieve. This is case sensitive\n";
    get_input(adescription, input_size);

    //retrieve the appointment object
    to_fill -> retrieve(adescription, to_display);

    //Call the classes display functions from the retrieved object.
    if(!to_display->display_description())
        cout << "Description: None\n";
    if(!to_display->display_recipient())
        cout << "Recipient: None\n";
    to_display->display_date();
    to_display->display_time();
    if(to_display->is_confirmed())
        cout << "Confirmed: YES!\n";
    else
        cout << "\nConfirmed: no :/\n\n";

    //deallocate memory
    if(adescription != NULL)
    {
        delete [] adescription;
        adescription = NULL;
    }
    to_fill = NULL;
    return;
}



//aps---HELPER FUNCTIONS---------------------------------------------------

//put in a char *, get a char * filled.
void appointment_list::get_input(char * &to_fill, int input_size)
{
    char temp_char[input_size];
    cin.get(temp_char, input_size, '\n');
    cin.ignore(100, '\n');
    to_fill = new char[strlen(temp_char) + 1];
    strcpy(to_fill, temp_char);
}



//copy an array
int appointment_list::copy_arr(char * &to_fill, char * copy)
{
    if(!copy)
        return 0;
    to_fill = new char[strlen(copy) + 1];
    strcpy(to_fill, copy);
    return 1;
}


//find required day. 
int appointment_list::find_day(anode *& to_fill, int to_traverse)
{
    if(!rear)
        return 0;
    anode * temp = rear;
    for(int i = 0; i < to_traverse; ++i)
    {
        temp = temp -> to_next();
    }
    to_fill = temp;
    return 1;
}

//**********************************************************************************************
//******apl-- END OF APPOINTMENT LIST 
//**********************************************************************************************
