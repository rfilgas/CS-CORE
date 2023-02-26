#include "tree.h"
#include "error.h"
#include <cctype>
// RYAN FILGAS
// CS202
// KARLA FANT
// PROGRAM 3
// 5/19/2021

// The purpose of the board.cpp file is to manage the red the menu system. 
// The board class is derived from the tree class, and has access 
// to all of its member functions.
//
// See tree.h for board function declarations.
//
// Board functions:
// main_menu - displays menu
// setup_menu - this displays a menu for setup, and testing
// test_tree - this allows the adding of nodes to the tree, and sorts them
// based on a price. This is for testing only to cut down on data entry.
// display_price_matches - this allows searching with <> = != <= >= operators.
// create_post - creates a post and calls the edit function of an object.
// combine_posts -- no time to immplement.
// display_favorites -- no time to implement



// Set up the main menu, outputting text to the user
void board::main_menu(void){
    
    char response = '\n';
    char menu_size = '4';

    cout << "Wecome to Roomie List!\n";

    do
    {
        cout <<"\nPlease select an option from below\n";
        cout << "1. Maintainence(add, edit, search, display)\n";
        cout << "2. Search for a Roommate\n";
        cout << "3. Display All Roommates\n";
        cout << "4. Exit\n";
        response = '\n';
        cin >> response;
        cin.ignore(100, '\n');
        
        if(response == '1')
            setup_menu();
        else if(response == '2')
            display_price_matches();
        else if(response == '3')
            full_inorder_display();
    }while(response != menu_size);
}


// Have the user enter in numbers, assignes those to nodes, then loads them into the tree
// with the += operators. The function will output everything in order as it is added,
// and prvide the final count and height at the end.
void board::test_tree(void){
    int temp = 0;
    int added = 0;
    int displayed = 0;
    int aheight = 0;
    home * my_home = NULL;
    cout << "It's time to test the tree, let's do this.\n";
    cout << "Please enter in as many numbers as you'd like to test. Enter -1 to stop.\n";

    do
    {
        cin >> temp;
        cin.ignore(100, '\n');
        while(cin.fail() || (temp < 0 && temp != -1))
        {
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(100, '\n');
            }
            temp = 0;
            cout << "Invalid Input Please enter an integer >= 0 or type -1 to finish.\n";
            cin >> temp;
            cin.ignore(100, '\n');
        }
        if(temp != -1)
        {
        cout << "\n";
        cout << "Before add, currently adding " << temp << "\n";
        inorder_display();

        my_home = new home;
        *my_home += temp;
        *this += my_home;
        my_home = NULL;

        ++added;
        cout << "\n";
        inorder_display();
        cout << "\nAfter add, just added" << temp << "\n\n";
        }
    }while(temp != -1);

    cout << "Adding complete\n";
    cout << "The nodes are displayed in order:\n";
    displayed = inorder_display();
    cout << "\nThe total number displayed is: " << displayed << ".\n";

    aheight = height();
    cout << "\nThe height is " << aheight << ".\n";
    return;
}


// Setup menu for adding posts, and testing user features.
void board::setup_menu(void){
    char response = '\n';
    char menu_size = '5';
    do{
        cout << "\nACCOUNT:\n";
        cout << "Please select an option from below by entering an integer\n";
        cout << "1. Add a posting\n";
        cout << "2. Search for a Roommate\n";
        cout << "3. Display All Roommates\n";
        cout << "4. Test Tree (for grading purposes)\n";
        cout << "5. Exit to Main Menu\n";

        response = '\n';
        cin >> response;
        cin.ignore(100, '\n');
        
        if(response == '1')
            create_post();
        else if(response == '2')
            display_price_matches();
        else if(response == '3')
            full_inorder_display();
        else if(response == '4')
            test_tree();
    }while(response != menu_size);
}



//Create a post and add it with the += operator.
void board::create_post(void){
    char response = '\n';

    cout << "Which type of posting would you like to create?\n";
    cout << "1. Roomshare (select this if your new roommate would be sharing a room\n";
    cout << "2. Full Room (select this if your new roommate would have a room to themselves\n";
    cout << "3. Multiple Rooms or House (select this if there is more than one room available\n";
    cout << "4. Cancel\n";
    cin >> response;
    cin.ignore(100, '\n');
    if(response == '4')
        return;
    if(response == '1')
        temphome = new share;
    if(response == '2')
        temphome = new room;
    if(response == '3')
        temphome = new multi;
    while(response < '1' || response > '3'){
        cout << "Enter a valid number between 1 & 3\n";
        cin >> response;
        cin.ignore(100, '\n');
    }
    temphome -> edit();
    *this += temphome;
    temphome = NULL;
    return;
}


// Display price matches by getting an operator (<) and a number from
// the user. For each operator, call a function that displays matching homes.
// Throw an error if the user enters anything negative.
void board::display_price_matches(void){
    string myop;
    int num = 0;
    int count = 0;
    home * key = new home;
    cout << "To find a match, enter the price requirement then the number in dollars/mo. Example: <500\n";
    cin >> myop >> num;
    while(cin.fail())
    {
        myop.clear();
        num = 0;
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid Input Please enter the sign and an integer\n";
        cin >> myop >> num;
    }
    cin.ignore(100, '\n');

    try{
    (*key) += num;
    }

    catch(NEGATIVE){
        cout << "No negatives!\n";
        if(key != NULL){
            delete key;
            key = NULL;
        }
        return;
    }

    if(!myop.compare(">")){
        cout << "\n";
        count = display_greater(root, key);
    }
    if(!myop.compare(">=")){
        cout << "\n";
        count = display_greater_equals(root, key);
    }
    if(!myop.compare("<")){
        cout << "\n";
        count = display_lesser(root, key);
    }
    if(!myop.compare("<=")){
        cout << "\n";
        count = display_lesser_equals(root, key);
    }
    if(!myop.compare("=")){
        cout << "\n";
        count = display_equals(root, key);
    }
    if(!myop.compare("!=")){
        cout << "\n";
        count = display_not_equals(root, key);
    }
    
    delete key;
    key = NULL;
    cout << count << " matches have been displayed.\n";
}


