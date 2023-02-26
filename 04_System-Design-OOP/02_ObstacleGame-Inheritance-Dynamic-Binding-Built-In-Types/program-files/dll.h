#include "divide.h"

// ----------------------------------------------------------------------------------------------
// RYAN FILGAS
// CS202
// KARLA FANT
// 5-5-2021
// Program 2
//
//
// The purpose of this file is to hold the prototypes for the node, list, and game classes.
// Following are descriptions of how each are used. Top down the data structure is a game
// class derived from a list class which contains a doubly linked list of nodes. Each node
// contains randomly allocated divide class objects of different derived types.
//
//
// CLASS: node---------
//
// int random_num() - generates a random number. It's currently unnessesary, as it's
// calling rand, however it originally seeded random inside the function.
//
// to_previous() and to_next() both return a pointwr.
// set_next(node * connection) and set_previous(node * connection) set the local variable to the
// passed in node.
//
// int check_type() - uses RTTI to check the type of class object inside of the current node
// and returns a corresponding iteger. 1:lava, 2: gator, 3: ravine
//
// int make_move(int move, player * &name) - takes an integer to determine which derived function
// to call. 1: human bridge, 2: jump, 3: macgyver, 4: run, 5: fight. It takes the return of
// each function call and sets it as the result. This is meant to be the penalty number of
// squares the player must go backwards.
//
// data members: node * next, node * previous, divide * obstacle
//
//
//
// CLASS: list--------
// 
// int initiate(int max) - this function initiates the DLL and sets head nodes to NULL.
// It recieves the max number of indices allowed and returns the actual number of indices
// created by the random allocation.
//
// void set_null(node ** &head) - this is used by the initiate function to set head nodes to null.
//
// int destroy(node ** &head) - is used by the destructor. This deletes the top level array
// and causes the next destroy function to delete each attached DLL. It returns the toal number
// of nodes.
//
// int destroy(node * & head) - this is used by the above destroy function to delete a dll. It will
// return the number of nodes.
//
// int start(node * &human) - this function takes a passed in node pointer to represent the player
// and randomly assigns the pointer to a head pointer in the array. It returns the current
// index.
//
// int is_victorious - uses the player class functions to check winning conditions. If the number of
// checkpoints passed is greater than 5, or the player has collected more than 5 items by
// bypassing the obstacles successfully. It will return 1 if true, 0 if false.
//
// int forward() - moves the human node pointer to the next node, and returns 1 if there is a
// valid node.
//
// int back() - moves the human node pointer to the next node, and returns 1 if there is a
// valid node.
// 
// int get_size - returns the array size for the copy constructors.
//
// //NOT YET IMPLEMENTED
// int remove_next_obstacle(node * &current);
// int retrieve(string object_type);
// int insert(node * to_add);
// int display_all();
// int remove_all();
// 
//
// int build_list(node ** head) - will build a list after it's allocated returning the number of nodes.
// int build_dll(node *&head) - will build a doubly linked list given a node pointer and return
// the number of nodes.
// int copy_list(node ** &head) - will copy an array of dlls, returning the number of nodes.
// int copt_dll(node * &head) - will copy a dll returning the number of nodes.
// int random_num() - returns a random number.
//
// Data members: 
// MIN_PATHS - the minimum number of array indices.
// MAX_PATHS - the maximum number of array indices
// int difficulty - set by the user, and passed in to create a node.
// int consequence - set by the user and passed in to create a node
// int array_size - determined randomly during allocation of the array
// player * name - a name class member to hold player data.
// node ** paths - the array of DLLs.
// 
//
// 
// CLASS: game---------- derived from the list class
//
// menu() - void function called by main to start the game.
// setup() - void function to let the user set start values in the list class,
// play() - void function that acts as the controller for the game.
// int prompt(node * &human) - this function checks which kind of node the human pointer
// is currently pointed at, and prompts the user based on that object.
//
// Data members:
// node * human - points to different nodes in the array of DLLs.
//
// ----------------------------------------------------------------------------------------------


//The purpose of the node class is to hold derived class objects, and serve as the building block
//for the data structure. To Access members, call node -> member. To access derived class functions,
//call node.obstacle -> function();

class node
{
    public:
        node();
        node(int new_difficulty, int new_consequence);
        node(const node &source);
        ~node();

        //generate a random number.
        int random_num();

        //Set and get next.
        node * &to_next(void);
        void set_next(node * connection);

        //Set and get previous.
        node * &to_previous(void);
        void set_previous(node * connection);

        //Return 1 for lava, 2 for gator, 3 for ravine, 0 for nothing.
        int check_type();

        //Takes an integer to determine which derived function
        //to call. 1: human bridge, 2: jump, 3: macgyver, 4: run, 5: fight. It takes the return of
        //each function call and sets it as the result. This is meant to be the penalty number of
        //squares the player must go backwards.
        int make_move(int move, player * &name);

    private:
        node * next;
        node * previous;

        // One of three desrived classes.
        divide * obstacle;
};


// The purpose of the list class is to manage the overall data structure, and facilitate
// the more complex parts of managing gameplay. The list class manages the array of doubly
// linked lists, as well as calling the player class to access completion data.
class list
{
    public:
    //COMPLETED
        list();
        //constructor helper function to allocate and initate array.
        //This will return the number of indices.
        int initiate(int max);
        //This will set the array to NULL.
        void set_null(node ** &head);
        list(list & source);
        ~list();
        //destructor helper functions.
        int destroy(node ** &head);
        int destroy(node * &head);

        //Set start values, and build list.
        int set_start_values(int adifficulty, int aconsequence);

        //sets human node passed in by menu to one of the arrays, returns the start number.
        int start(node * &human);
        //returns 1 if winning conditions are met. See above documentation.
        int is_victorious(void);
        //Lets player choose how to bypass an obstacle, and calls make_move in the node class.
        int make_move(node * &human);
        //increments the checkpoint variable in the player class.
        int add_checkpoint();

        //Go forward in the array, and return 0 if null.
        int forward(node * &human); // work on accurate returns.
        //go backwards in the array and return 0 if null.
        int back(node * &human); //work on accurate returns.
        //get array_size for copy constructor.
        int get_size(void);

    protected:

        //Mandatory functions - do last.*******************************************************************
        // int remove_next_obstacle(node * &current);
        //int retrieve(string object_type);
        //int insert(node * to_add);
        //int display_all();
        //int remove_all();


    //COMPLETED
        //Helper functions.
        // Build an array of DLLs and return number of nodes.
        int build_list(node ** &head);
        //Build DLL and return number of nodes.
        int build_dll(node * &head, int num_nodes, node * &previous);
        // Copy a list from source to copy, and return the number of nodes.
        int copy_list(node ** &copy, node ** source, int size);
        //copy a dll from source to copy and return the number of nodes.
        int copy_dll(node * &copy, node *&source, node * & previous);
        //generate a random number.
        int random_num(void);

        //Data members
        //Floor for number of indices in array.
        int MIN_PATHS;
        //Roof for number of indices in array.
        int MAX_PATHS;
        //Floor for number of nodes in DLL.
        int MIN_NODES;
        //Difficulty sent through nodes to derived class.
        int difficulty;
        //Consequence sent through nodes to derived class.
        int consequence;
        //Array size set by constructor after random allocation.
        int array_size;

        //Player object to hold items, benchmarks etc.
        player * name;

        //Array of DLLs
        node ** paths;
};



// The purpose of the game class is to act as a controller for the game.
// This will include the main menu, and some of the sub menus. It will pass
// the human node where appropriate to the list class.
class game: public list
{
    public:
        game();
        game(game & source);
        ~game();

        // Main menu
        void menu();
        //Setup menu
        void setup();
        //Main driver for game
        void play();



    private:
        // Find the object type and prompt the user. Return the type. 0: nothing. 1:lava. 2:gators. 3: ravine
        int prompt(node * &human);

        node * human;
        //list * game;
};








