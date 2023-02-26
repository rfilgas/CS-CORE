#include "concept-list.h"

# Ryan Filgas

//CONCEPT CLASS****

//Constructor
concept::concept()
{
    topicName = NULL; 
    subTopic = NULL;
    studyTime = 0;
    toolsNeeded = NULL;
    usefulInfo = NULL;
}

//Destructor
concept::~concept()
{
    if(topicName != NULL)
        delete [] topicName;
    topicName = NULL;

    if(subTopic != NULL)
        delete [] subTopic;
    subTopic = NULL;
    
    if(toolsNeeded != NULL)
        delete [] toolsNeeded;
    toolsNeeded = NULL;
    
    if(usefulInfo != NULL)
        delete [] usefulInfo ;
    usefulInfo = NULL;
}

//NODE CONSTRUCTOR / DESTRUCTOR
//
//constructor for node. Set all elements to NULL.
node::node()
{
    data.topicName = NULL; 
    data.subTopic = NULL;
    data.studyTime = 0;
    data.toolsNeeded = NULL;
    data.usefulInfo = NULL;
    next = NULL;
}

//recursive destructor. Every node is connected by next.
//when next is deleted, it calls the destructor for
//the next node until the end. the last element gets
//destructed, followed by the second to last, all the
//way until the first element. node is a concept class, not
//an array, so the [] isn't necessary. concept has its own destructor.
node::~node()
{ 
        delete next;
}

//CONCEPT LIST CLASS****


//Constructor
conceptList::conceptList()
{
//    array = NULL; 
//    arraySize = 0;
    numConcepts = 0;
    editSelection = 0;
    head = NULL;
    userReply[0] = '\0';
}

//Destructor
conceptList::~conceptList()
{
   // if(NULL != array)
   //     delete [] array;
   // array = NULL;
        delete head;
}


//----------------------------------------------------------------------------------------------------------

//WELCOME USER

//Welcome user with message.
void conceptList::welcome()
{
    cout << "Hello! Welcome to the CS Study Helper! This program is designed to: " << "\n";
    cout << "Let you choose a topic to learn more about, and assist you in gathering" << "\n";
    cout << "the resources to start learning!" << "\n\n";
    cout << "Following is a list of topics you might wish to learn." << "\n\n";
}

//----------------------------------------------------------------------------------------------------------


//LLL FUNCTIONS
//to simplify the function call for build in main.
void conceptList::addtoLLL()
{
    build(userExpAdd());
}

//BUILD
//This function takes a class concept as input,adds a new node, and stores
//the concept into the new node, setting current ->next to null at end.
void conceptList::build(concept toAdd) 
{ //if head is NULL, the list is empty. Add a node, and fill it.
    if(head == NULL)
    {
        head = new node;
        head->next = NULL;
        head->data.topicName = new char[strlen(toAdd.topicName)];
        strcpy(head->data.topicName, toAdd.topicName);
        head->data.subTopic = new char[strlen(toAdd.subTopic)];
        strcpy(head->data.subTopic, toAdd.subTopic);
        head->data.studyTime = toAdd.studyTime;
        head->data.toolsNeeded = new char[strlen(toAdd.toolsNeeded)];
        strcpy(head->data.toolsNeeded, toAdd.toolsNeeded);
        head->data.usefulInfo = new char[strlen(toAdd.usefulInfo)];
        strcpy(head->data.usefulInfo, toAdd.usefulInfo);
    }
    else
    {
        //if current node isn't equal to null, traverse until current -> next is
        //null. Once there, create a new node, traverse to it, and input data.
        node*current = head;
        if(current)
        { 
            while(current->next != NULL)
            {
                current = current->next;
            }
                current->next = new node;
                current = current->next;


                current->data.topicName = new char[strlen(toAdd.topicName)];
                strcpy(current->data.topicName, toAdd.topicName);
                current->data.subTopic = new char[strlen(toAdd.subTopic)];
                strcpy(current->data.subTopic, toAdd.subTopic);
                current->data.studyTime = toAdd.studyTime;
                current->data.toolsNeeded = new char[strlen(toAdd.toolsNeeded)];
                strcpy(current->data.toolsNeeded, toAdd.toolsNeeded);
                current->data.usefulInfo = new char[strlen(toAdd.usefulInfo)];
                strcpy(current->data.usefulInfo, toAdd.usefulInfo);
                current->next = NULL;
        }
        
    }
    ++numConcepts; //need to increment whenever a concept is added, because this
                   // is our indexing variable.
}

//ACCESS LLL
//This function takes the desired index, and the head of a LLL
//as input, and returns a pointer to that element in the list so
//it can be accessed for output, or editing.

node * conceptList::accessLLL(node * &head, int index)
{
    node*current = head;
        
    int i = 0;
    //while we haven't hit the end, and we still have elements left until
    //the one the user asked for, traverse each node. When we hit the desired
    //node, return a pointer to that node so the calling function can
    //have direct access to the data.
    while(current->next != NULL && i < index)
    {
        current = current->next;
        ++i;
    }
    return current;
}






//----------------------------------------------------------------------------------------------------------

//DISPLAY MENU

//This function displays the main menu. The user will choose an option, and be redirected to the
//associated function.

void conceptList::displayMenu()
{
    cout << "To display a topic, enter 'd', then enter the topic number." << "\n";
    cout << "To add a topic, enter 'a'." << "\n";
    cout << "To display all topics, enter 'all'." << "\n";
    cout << "To edit a topic, enter 'e', then enter the topic number to edit." << "\n";
    cout << "To quit, and exit the program, enter 'q'." << "\n\n"; 
    

    //If list is empty, tell user that the list is empty, otherwise, display the first member of each topic.
    if(!numConcepts)
        cout <<"Your list is currently empty, please add something by entering 'a'." << "\n\n";
        else
        {
            //for i < size of the list, display the index number + 1, followed by the topic name. (e.g. 1. Structs)
            for(int i = 0; i < numConcepts; ++i)
               cout << (i+1) << ". " << (accessLLL(head, i))->data.topicName << " " << "\n";
               // cout << (i+1) << ". " << array[i].topicName << " " << "\n";
        }
   

    //Get user reply to the menu, and make lowercase.
    cin >> userReply;
    cin.ignore(100, '\n');
    //Make reply into all lowercase letters for main to read.
    int replyLength = strlen(userReply); // variable to length of reply for following loop.
    for(int i = 0; i < replyLength; ++i)
            userReply[i] = tolower(userReply[i]);

    //User chose to edit. Record which number they would like to edit, and let the edit function take over from main.
    if(!strcmp(userReply, "e"))
    {
        cin >> editSelection; //take input asked for in the display menu function.
        cin.ignore(100, '\n');
    }
}

//----------------------------------------------------------------------------------------------------------

//USER EXPERIENCE ADD CONCEPT

//This function lets the user add a concept to the list. This concept is stored in a temporary class, and
//returned to the back end add concept function listed next.

concept conceptList::userExpAdd() 
{
    concept toAdd; // Declare a temporary concept class variable to hold user input.
    char temp[100];

    //Take user input into temp, declare a new dynamic array, and copy temp to array. Return class from function.
    cout << "You've chosen to add a concept, please enter the concept name." << "\n";
    cin.get(temp, 100, '\n');
    cin.ignore(100, '\n');
    toAdd.topicName = new char[strlen(temp)+1];
    strcpy(toAdd.topicName, temp);

    cout << "Please enter the subtopic(s) you wish to improve understanding of as a single line of text" << "\n";
    cin.get(temp, 100, '\n');
    cin.ignore(100, '\n');
    toAdd.subTopic = new char[strlen(temp)+1];
    strcpy(toAdd.subTopic, temp);
  
    cout << "Please enter the amount of study time in hours you expect learning this subject will take. Enter a positive number." << "\n";
    cin >> toAdd.studyTime;
    cin.ignore(100, '\n');

    cout << "Please enter any tools you will need to study as a single line of text. (books, linux, study materials etc.)" << "\n";
    cin.get(temp, 100, '\n');
    cin.ignore(100, '\n');
    toAdd.toolsNeeded = new char[strlen(temp) + 1];
    strcpy(toAdd.toolsNeeded, temp);
    
    cout << "Please enter any other useful information as a single line of text" << "\n";
    cin.get(temp, 100, '\n');
    cin.ignore(100, '\n');
    toAdd.usefulInfo = new char[strlen(temp) + 1];
    strcpy(toAdd.usefulInfo, temp);

    return toAdd; //Returning concept class.
}

//----------------------------------------------------------------------------------------------------------

//This function displays each concept + members in the list.
void conceptList::displayAll()
{
    node*tempMember;
    char temp = 0; //To pause menu viewing for user.
    for(int i = 0; i < numConcepts; ++i)
    {
        tempMember = accessLLL(head, i); 
        cout << "Concept " << (i+1) << "." << "\n";
        cout << "a. Topic Name  : " << tempMember->data.topicName << "\n";
        cout << "b. Sub Topic(s): " << tempMember->data.subTopic << "\n";
        cout << "c. Study Time  : " << tempMember->data.studyTime << "\n";
        cout << "d. Tools Needed: " << tempMember->data.toolsNeeded << "\n";
        cout << "e. Useful Info : " << tempMember->data.usefulInfo << "\n";
        cout << "\n\n";
    }

    cout << "Once you are done looking, enter any letter to continue." << "\n\n";
    cin >> temp; //Pause the screen until the user is ready to proceed.
}

//----------------------------------------------------------------------------------------------------------

//DISPLAY NAME

//This function lets the user choose which concept they'd like to display.

void conceptList::displayName() 
{   char temp = 0; // To keep the screen paused for the user.
    int selection = 0; //We asked the user to enter a selection in the display menu function. It will be
                       // a temporary variable in this case.
    node*tempMember;
    cin >> selection;
    cin.ignore(100, '\n');
    --selection; // Need concept 1 to go to index 0 etc.

     
    tempMember = accessLLL(head, selection); 
    cout << "a. Topic Name  : " << tempMember->data.topicName << "\n";
    cout << "b. Sub Topic(s): " << tempMember->data.subTopic << "\n";
    cout << "c. Study Time  : " << tempMember->data.studyTime << "\n";
    cout << "d. Tools Needed: " << tempMember->data.toolsNeeded << "\n";
    cout << "e. Useful Info : " << tempMember->data.usefulInfo << "\n";
    cout << "Once you are done looking, enter any letter to continue" << "\n\n";
    cin >> temp;
    cin.ignore(100, '\n');
}

//----------------------------------------------------------------------------------------------------------

//EDIT CONCEPT

//This function will allow the user to edit any part of a concept they'd like.
//It uses a while loop and nested if statements to change values.

//Notes:

//The variable editSelection is part of the conceptList class. We had the user
//enter this in the display menu function.


void conceptList::editConcept()
{
    int subtopicChange = 0;  //to record which entry the user would like to change.
    char doneEditing = 'n';   //variable to exit while loop when user is doing edits.
    //need to rename a returned node pointer for code legibility.
    node*tempMember;    


    tempMember = accessLLL(head, editSelection); 
    do //Will exit when user replies with a 'y'.
    {
    cout << "You've chosen to change topic #" << (editSelection) << "." << "\n" << "Enter an integer for the list member you wish to edit" << "\n\n"; 
    cout << "1. Topic Name  : " << tempMember->data.topicName << "\n";
    cout << "2. Sub Topic(s): " << tempMember->data.subTopic << "\n";
    cout << "3. Study Time  : " << tempMember->data.studyTime << "\n";
    cout << "4. Tools Needed: " << tempMember->data.toolsNeeded << "\n";
    cout << "5. Useful Info : " << tempMember->data.usefulInfo << "\n";
    
    cin >> subtopicChange; //class member the user wished to edit
    cin.ignore(100, '\n');

    cout << "You chose list member # " << subtopicChange << ", please enter your replacement. Enter a number if you chose to edit study time, and text for everything else." << "\n\n";
   
    if(subtopicChange == 1)
        cin.get(tempMember->data.topicName, 100);
    if(subtopicChange == 2)
        cin.get(tempMember->data.subTopic, 100);
    if(subtopicChange == 3)
        cin >> tempMember->data.studyTime;
    if(subtopicChange == 4)
        cin.get(tempMember->data.toolsNeeded, 100);
    if(subtopicChange == 5)
        cin.get(tempMember->data.usefulInfo, 100);
    cin.ignore(100, '\n'); //ignore for all of the above. Only one will execute, so only need one cin.ignore.

    //Ask user if they want to keep editing.
    cout << "Are you finished editing? (enter 'y' for yes, or 'n' for no)" << "\n";
    cin >> doneEditing;
    cin.ignore(100, '\n');
 
    doneEditing = tolower(doneEditing);// turn their reply to lower case if they enter a capital.
    subtopicChange = 0; //reset for the while loop.

    //Until user enters a non 'n' value, this will loop.
    }while(doneEditing == 'n');
}

//----------------------------------------------------------------------------------------------------------

//EXIT MESSAGE

void conceptList::exitMessage()
{
    cout << "We regret to see you leave so quickly, but are happy you studied! Goodbye!";
    cout << "\n\n";
}



//----------------------------------------------------------------------------------------------------------
