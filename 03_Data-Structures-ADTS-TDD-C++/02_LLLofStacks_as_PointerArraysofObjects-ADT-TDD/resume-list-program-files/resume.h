// -------------------------------------------------------------------------
// Ryan Filgas
// Assignment_2
// Karla Fant
// CS 163
// 1/31/2021
//
// Filename:
// resume.h
//
// The purpose of this program is to implement an ADT of resume experiences passed in by
// a client function. The program will be implemented as a stack with the operations
// push, pop, peek, and display. A test program is implemented for the client to see 
// how this ADT works in practice. The data structure inside this ADT consists of
// a linear linked list of arrays, where each array contains 5 indices, and a new node
// with an array is added, or subtracted as the contents is added or removed by the client.
// This data structure will be useful if you need to implement a resume where the first
// data set put in needs to come out, or be displayed last, and the last to be displayed
// or retrieved first.
//
// INPUT:
//
// ----resume_list class----
// 
// resume_list.pop(experiences & to_fill) - This function takes an experiences object from
// the client.
//
// resume_list.peek(experiences & to_fill) - This function takes an experiences object to fill
// from the client.
//
// resume_list.push(const experiences & copy_from) - This function takes an experience in
// from the client.
//
// ----experiences class----
//
// an_experiences.copy_entry(const experiences & copy_from) - For copy entry, an experiences
// object is passed in by the resume_list class.
//
// an_experience.create_entry(char * employer_name, char * start_month, char * end_month,
// char * job_title, char * responsibilities) - For create entry, enter in the employer name,
// start month, end month, start year, end year, and list of responsibilities, all as char
// arrays.
//
//
// OUTPUT:
//
// ----resume_list class----
//
// resume_list.initialize(void) - This function initializes the stack, and returns 1 if successful,
// 0 for failure.
//
// resume_list.pop(experiences & to_fill) - The pop function will return an experiences object by 
// reference;
// 
// resume_list.peek(experiences & to_fill) - The peek function will return an experiences object
// by reference, and 1, or 0 for success/failure.
//
// resume_list.is_empty(void) - This function will return a 1 if true, and 0 if false.
//
// resume_list.display_list - This function will output the list to the user, and return the
// number of experiences, or 0 if the list is empty.
//
//
// ----experiences class----
//
// an_experiences.display(void) - This function will return 1 for success
// and 0 for failure. It will also output to the user when called by the resume_list class.
//
// an_experiences.copy_entry(const experiences & copy_from) - This function will return 1 for 
// success and 0 for failure.
//
// an_experience.create_entry(char employer_name[], char start_date[], char end_date[],
// char job_title[], char responsibilities[]) - This function will return 1 for success
// and 0 for failure.
//
// an_experience.clear_experience(void) - This function returns 1 for success and 0 for failure.
//
// an_experience.is_empty(void) - This function will return a 1 if the list is empty, and a zero if
// it's not.
//
// -------------------------------------------------------------------------

//This is a constant to control the number of items allowed per node in stack.
const int MAX = 5;


//The experiences class is responsible for managing its private data members. It is capable
//of display, copy, create, and clear functions.
class experiences
{
    public:

        //This is a constructor for experiences class, it sets data members to NULL.
        experiences(void);

        //This is a destructor for experiences class, it deletes data members, and
        //sets them to NULL.
        ~experiences(void);
        
        //This function displays data from an experiences object and returns 1 for success, 
        //No input is necessary to call display_experience.It will return true/false for success
        //or failure.
        int display_experience(void);

        //This function copies experience data into the private data members of the called experience
        //object. It will need an experience object to be passed by reference, and returns 1 if
        //successful, or 0 if the passed in experience didn't have all data members.
        int copy_entry(const experiences & copy_from);

        //This function lets the client create an experience object, it will need
        //an employer name, start date, end date, job title, and responsibilities passed in.
        //This function will return 1 if successful, or 0 if the input was incorrect.
        int create_entry(char the_employer_name[], char the_start_date[], char the_end_date[], char the_job_title[], char the_responsibilities[]);

        //This function clears an experience without calling the destructor.
        //It will return 1 for success and 0 for failure.
        int clear_experience(void);

    private:

        //These are self documenting private data members for an experience.
        char * employer_name;
        char * start_date;
        char * end_date;
        char * job_title;
        char * responsibilities;
};



//The node struct is responsible for the managing the top level linear linked list. Each
//node contains a pointer to the next node, and an array of experience objects.
struct node
{
    //This is a constructor for the node struct, it sets next to null.
    node(void);
    
    //This is a destructor fo the experiences class, it deletes the array, and calls
    //the destructor for the next node.
    ~node(void);

    //This is a pointer array to a list of experiences objects.
    experiences * experience_array;

    //This is a pointer to the next node, each of which holds 5 experiences.
    node * next;
};



//The resume_list class is responsible for overall management of the ADT. It manages the
//head of the linear linked list, and uses functions within the other class to build, and shrink
//the stack through push, pop, initiate, is_empty, and display functions.
class resume_list
{

    public:

        //This is a constructor for the resume list class.
        resume_list(void);

        //This is a destructor for the resume list class.
        ~resume_list(void);

        //This function initiates the stack. It will return 1 for success or
        //zero for failure.
        int initiate_stack(void);

        //The push function takes an experiences object from the client, and
        //copies it into the list of experiences, returning success or failure as
        //1, or 0 respectively.
        int push(const experiences & copy_from);

        //The pop function takes an experiences object from the client, fills it with the
        //data from the experiences object at the top of the stack, returns it to the
        //client and deletes it from the top of the stack; it returns 1 for success and 0
        //for failure.
        int pop(experiences & to_fill);

        //The peek function takes in an experiences object from the client, fills it with the
        //data from the experiences object at the top of the stack, returns it to the client,
        //and leaves the stack as it was, returning 1 or 0 for success or failure.
        int peek(experiences & to_fill);

        //The is_empty function checks if the head of the list is null, then returns 1 for true
        //and 0 for false.
        int is_empty(void);
        
        //The display function displays the data in all nodes by calling display_experience from
        //the experiences class, it will return the total number of experiences recorded.
        int display();

    
    private:

        //Keep track of the top of the stack.
        int index_top;

        //Node struct to hold resolutions.
        node * head;
};
