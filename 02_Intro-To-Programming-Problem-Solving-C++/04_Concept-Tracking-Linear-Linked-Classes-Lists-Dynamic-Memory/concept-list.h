#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;


//-----------------------------------------------------------
// RYAN FILGAS
//
// The purpose of this program is to display computer science
// topics to the user. The main portion of this program will
// let the user choose from a list of computer science topics
// they may wish to learn using a do while loop, and the 
// program will display the data chosen, let them add a topic,
// edit the data members, or quit. The program will loop until
// the user chooses the quit option, and trips a flag variable
// to leave the loop. The program will use dynamically
// allocated arrays where prctical.
//------------------------------------------------------------

// Programming Notes------------------------------------------
// Header files include:
// 1. Includes
// 2. Structures
// 3. Prototypes
// 4. Class interfaces
// 5. Constants
//------------------------------------------------------------




//CLASSES

class concept //defines class members to be used in dynamic class array.
{
    public:
        concept();
        ~concept();
        char *topicName; 
        char *subTopic;
        float studyTime;
        char *toolsNeeded;
        char *usefulInfo;
};


struct node
{
    concept data;
    node * next;
    node();
    ~node();
};




class conceptList // This class is broken up into two public sections. The first operates on the
                  // array only, to make the code easier to reuse. The second takes input from,
                  // and sends data out to the user.
                  
{
    public:
        conceptList();       // Constructor to initialize data members.
        ~conceptList();      // Destructor to clear memory and prevent memory leaks.
       // void addConcept(concept & toAdd); // add a concept.
        
        void initiateArray(); //Ask user how much room they need, and create array.
        void addConcept(concept toAdd);// Add a concept. Not pass by reference because it takes a function return as argument.
        void displayAll();   // Display all concepts.
        void displayName();  // Display just the concepts info.
        void editConcept();  // Clear the contents and overwrite a list member.
        char userReply[4]; //User reply for use in displayMenu. Input will either be a single char or 'all'.

        //User Experience functions.
        void welcome();       // Welcome the user.
        void displayMenu();   // Display a list of concept names. Each first member of list.
        void exitMessage();   // Thank user, and say goodbye.
        void userExpEdit();   // Let user edit concept selected in displayMenu. 
        concept userExpAdd(); // This will return a concept to be added to the array.


        void addtoLLL();
        void build(concept toAdd); 
        node * accessLLL(node * &head, int index);
    private:
        concept *array;
        node *head;
        int editSelection;   //what user would like to edit, used by editConcept function.
        int arraySize;   // Size of struct array.
        int numConcepts; // Records the number of list topics stored.
        concept toAdd;

};

