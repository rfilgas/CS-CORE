#include "concept-list.h"

// The purpose of this program is to display computer science topics to the user while gaining practical experience with classes and linear linked lists.. The main portion of this program
// will let the user choose from a list of computer science topics they may wish to learn using a do while loop, and
// the program will display the data chosen, let them add a topic, edit the data members, or quit. The program will loop until the user
// chooses the quit option, and trips a flag variable to leave the loop.

// The program will be broken up into two .cpp files, and a .h file. One .cpp file will hold the concept list class, another will hold main,
// and the other will be a header file to hold prototypes, variable declarations, #includes, namespace, background info, etc.


int main()
{
    //Declare new concept list to use class.
    conceptList newList;

    //Welcome User
    newList.welcome();

    //Clear screen
    do
    {
    for(int j = 0; j < 2; ++j)
        cout << "\n\n";
    

    //Display menu, and take in user input for edit selection.
    newList.displayMenu(); 


    cout << "\n\n\n"; //Formatting.

   
    //Ask user for class input in userExpAdd, then return it
    //to addConcept to store in array.
    if(!strcmp(newList.userReply, "a"))
        newList.addtoLLL();
   
    
    //Display all concepts.
    if(!strcmp(newList.userReply, "all"))
            newList.displayAll();
   
    //Let user edit concepts until finished.
    if(!strcmp(newList.userReply, "e"))
        newList.editConcept();
 
    //Display a single topic.
    if(!strcmp(newList.userReply, "d"))
        newList.displayName();

    //While loop that eits when user enters 'q' from main menu.
    }while(strcmp(newList.userReply, "q"));

    //Exit message.
    newList.exitMessage();
   
    return 0;
}


