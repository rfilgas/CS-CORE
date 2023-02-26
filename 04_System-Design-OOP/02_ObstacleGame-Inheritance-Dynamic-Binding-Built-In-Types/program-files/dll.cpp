#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include "dll.h"


// ----------------------------------------------------------------------------------------------
// RYAN FILGAS
// CS202
// KARLA FANT
// 5-5-2021
// Program 2
//
//
// The purpose of this program is to hold the data structure for the dll class.
// The base of the DLL class is a node wich will contain 1 of three desrived
// class objects. Containing the nodes is an array of doubly linked lists.
// The size of the array and the attached lists are also randomly allocated with set
// limits for the maximum size.
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



node::node(): next(NULL), previous(NULL), obstacle(NULL){}
node::node(int new_difficulty, int new_consequence): next(NULL), previous(NULL)
{
    int type = rand() % 4;

    if(type == 1)
        obstacle = new lava_flow(new_difficulty, new_consequence);
    if(type == 2)
        obstacle = new river_o_alligators(new_difficulty, new_consequence);
    if(type == 3)
        obstacle = new endless_ravine(new_difficulty, new_consequence);
    if(type == 0)
        obstacle = NULL;
}

node::node(const node &source)
{
    lava_flow * lava = dynamic_cast <lava_flow*>(source.obstacle);
    river_o_alligators * gator = dynamic_cast <river_o_alligators*>(source.obstacle);
    endless_ravine * pit = dynamic_cast <endless_ravine*>(source.obstacle);
    
    if(lava)
    {
        obstacle = dynamic_cast <lava_flow*> (lava);
        obstacle = new lava_flow((*lava));
    }
    else if(gator)
    {
        obstacle = dynamic_cast <river_o_alligators*> (gator);
        obstacle = new river_o_alligators((*gator));
    }
    else if(pit)
    {
        obstacle = dynamic_cast <endless_ravine*> (pit);
        obstacle = new endless_ravine((*pit));
    }
    else 
        obstacle = NULL;
}

node::~node()
{
    if(obstacle != NULL)
        delete obstacle;
    previous = NULL;
    next = NULL;
}

node * &node::to_next()
{
    return next;
}

node * &node::to_previous()
{
    return previous;
}

void node::set_next(node * connection)
{
    next = connection;
}

void node::set_previous(node * connection)
{
    previous = connection;
}


int list::get_size(void)
{
    int temp = array_size;
    return temp;
}

int list::random_num(void)
{
   // struct timeval my_time;
   // gettimeofday(&my_time, NULL);
   // srand(my_time.tv_usec);
    return rand();
}


list::list(): MIN_PATHS(5), MAX_PATHS(0), MIN_NODES(10), difficulty(0), consequence(0), paths(NULL)
{}

int list::initiate(int max)
{
    name = new player;
    MAX_PATHS = max;
    array_size = random_num() % MAX_PATHS + MIN_PATHS;
    paths = new node*[array_size];
    node ** temp = paths;
    set_null(temp);
    temp = NULL;
    return array_size;
}





void list::set_null(node ** &head)
{
    if((head - this -> paths) == array_size)
        return;
    (*head) = NULL;
    return set_null(++head);
}




int list::build_list(node ** &head)
{
    if((head - this -> paths) == array_size)
        return 0;
    int num_nodes = random_num() % array_size + MIN_NODES;
    node * temp = NULL;
    (*head) = new node(difficulty, consequence);
   // (*head) -> to_next() = NULL;
   // (*head) -> to_previous() = NULL;
    int count = build_dll(((*head)-> to_next()), num_nodes, temp);
    int sum = count + build_list(++head);
    return sum;
}

//took out an & on the int
int list::build_dll(node * &head, int num_nodes, node * &previous)
{
    if(num_nodes == 0)
        return 0;
    head = new node(difficulty, consequence);
    head -> set_previous(previous);
    int count = 1 + build_dll(head -> to_next(), --num_nodes, head); 
    return count;
}



list::list(list & source)
{
    int mysize = (source.get_size());
    name = new player;
    paths = new node *[mysize];
    node ** copy = paths;
    node ** temp = source.paths;
    copy_list(copy, temp, mysize);
}


int list::copy_list(node ** &copy,node ** source, int size)
{
    if(copy - this -> paths == size)
        return 0;
    int count = copy_dll(*copy, *source, *copy);
    int sum = count + copy_list(++copy, ++source, size);
    return sum;
}

int list::copy_dll(node * &copy, node *&source, node * & previous)
{
    if(!source)
        return 0;
    copy = new node(*source);
    copy -> set_previous(previous);
    return 1 + copy_dll(copy -> to_next(), source -> to_next(), copy);
}


list::~list()
{
    if(!paths)
        return;
    node ** temp = paths;
    destroy(temp);
    temp = NULL;
    delete [] paths;
    paths = NULL;
    if(name != NULL)
    {
        delete name;
        name = NULL;
    }
}

int list::destroy(node ** &head)
{
    if((head - this -> paths) == (array_size))
        return 0;
    int count = destroy((*head));
    ++head;
    int sum = count + destroy(head);
    return sum;
}

int list::destroy(node * &head)
{
    if(head == NULL)
        return 0;
    if(head -> to_previous() != NULL)
        head -> to_previous() = NULL;
    int destroyed = 1 + destroy((head -> to_next()));
    if(head -> to_next() != NULL)
        head -> to_next() = NULL;
    if(head != NULL)
    {
        delete head;
        head = NULL;
    }
    return destroyed;
}

int list::set_start_values(int adifficulty, int aconsequence)
{
    difficulty = adifficulty;
    consequence = aconsequence;
    node ** ptr = paths;
    int num_nodes = build_list(ptr);
    return num_nodes;
}


int list::start(node * &human)
{
    int human_start = random_num() % array_size;
    human = paths[human_start];
    return human_start;
}


int list::is_victorious()
{
    return (name -> passed_all_checkpoints() || name -> collected_all_items());
}


int list::make_move(node * &human)
{
    int penalty = 0;
    int choice = 0;
    int menu_size = 5;

    cout << "How will you confront this challenge? (choose a number)\n";
    cout << "1. Sacrifice your friend to the banana gods, and use them as a human bridge\n";
    cout << "2. Jump over the obstacle with your mad skills.\n";
    cout << "3. Macgyver your way out. Are you clever enough?\n";
    cout << "4. RUN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    if(human -> check_type() == 2)
            cout << "5. FIGHT!! LET ME AT EM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

    while(choice < 1 || choice > menu_size)
    {
        cin >> choice;
        cin.ignore(100, '\n');
        if(choice < 1 || choice > menu_size)
            cout << "Try again.\n";
    } 
    penalty = human -> make_move(choice, name);
    return penalty;
}

int list::add_checkpoint()
{
    return name -> add_checkpoint();
}

int list::forward(node * &human)
{
    human = human -> to_next();
    if(human == NULL)
        return 0;
    else return 1;
}

// give a better return code. Should say if obstacle is null specifically
int list::back(node * &human)
{
    human = human -> to_previous();
    if(human == NULL)
        return 0;
    else return 1;
}



//------node-----------------------------------------------------------------------
int node::check_type(void)
{
    lava_flow * lava = dynamic_cast <lava_flow*>(obstacle);
    river_o_alligators * gator = dynamic_cast <river_o_alligators*>(obstacle);
    endless_ravine * pit = dynamic_cast <endless_ravine*>(obstacle);
    if(lava != NULL)
    {
        lava = NULL;
        return 1;
    }
    if(gator != NULL)
    {
        gator = NULL;
        return 2;
    }
    if(pit != NULL)
    {
        pit = NULL;
        return 3;
    }
    else return 0;
}


int node::make_move(int move, player * &name)
{
    int type = check_type();
    int result = 0;
    string * temp1;
    temp1 = new string;
    string * temp2;
    temp2 = new string;
    //checks which obstacle the human is at. Return 1 for lava, 2 for gator, 3 for ravine, 0 for nothing.
    if(move == 1)
        result = obstacle -> human_bridge(name);
    if(move == 2)
        result = obstacle -> jump(name);
    if(move == 3)
    {
        name -> use_item(*temp1, *temp2);
        result = obstacle -> macgyver(name, temp1, temp2); 
    }
    if(move == 4)
        result = obstacle -> run(name);
    if(move == 5 && type == 2)
    {
        river_o_alligators * gator = dynamic_cast <river_o_alligators*>(obstacle);
        result = gator -> fight(name);
    }
    if(temp1)
    {
        delete temp1;
        temp1 = NULL;
    }
    if(temp2)
    {
        delete temp2;
        temp2 = NULL;
    }
    return result;
}







// ------------game-----------------------------------------------------------------------

game::game(): human(NULL)
{}

game::~game()
{
    if(human)
    {
        human = NULL;
    }
}


//input human node, return obstacle type
int game::prompt(node * &human)
{
    int type = human ->check_type();
    int message_num = random_num() % 4;
    if(type == 1)
        cout << "You have stumbled into a lava pit! You're in for a treat.\n";
    if(type == 2)
        cout << "You've happened upon a river of ferocious alligators. yay.\n";
    if(type == 3)
        cout << "OH NO! That's the biggest ravine you've ever seen!\n";
    if(type == 4)
    {
        if(message_num == 0)
            cout << "welcome to the middle of nowhere friend!\n";
        if(message_num == 1)
            cout << "Every day and night you walked, and every time you looked up there was nothing.\n";
        if(message_num == 2)
            cout << "Life is a journey, and sometimes there are no challenges. Enjoy the quiet.\n";
        if(message_num == 3)
            cout << "Do you ever ask yourself why you aren't at an obstacle?\n";
    }
    return type;
}


game::game(game & source): human(NULL) 
{
    int mysize = source.get_size();
    array_size = mysize;
    initiate(mysize);
    node ** copy = paths;
    node ** temp = source.paths;
    copy_list(copy, temp, mysize);
}




void game::setup(void)
{
    int difficulty = 0;
    int consequence = 0;
    int max_levels = 0;
    int num_spaces = 0;
    int num_arrays = 0;

    struct timeval my_time;
    gettimeofday(&my_time, NULL);
    srand(my_time.tv_usec);



    cout << "\n\nCurrently you are in setup mode.\n";


    cout << "The size of this game will be allocated randomly, but there are 5 levels miniumum.\n";
    cout << "How many levels would you like to increase the maximum by? \n";
    cout << "(enter any number above 0).\n";
    while(max_levels < 1)
    {
        cin >> max_levels;
        cin.ignore(100, '\n');
        if(max_levels < 1)
            cout << "Sorry. Please try again.\n";
    }
    //game = new list(max_levels);
    num_arrays = initiate(max_levels);


    cout << "Please enter which difficulty you would like to play (any number between 1 and 10).\n";
    while(difficulty < 1 || difficulty > 10)
    {
        cin >> difficulty;
        cin.ignore(100, '\n');
        if(difficulty < 1 || difficulty > 10)
            cout << "Sorry. Please try again.\n";
    }
    cout << "\nThank you. Please enter the number of spaces to be set back if your\n";
    cout << "adventure is horribly unsuccessful (please enter a number between 1 and 5).\n";
    while(consequence < 1 || consequence > 5)
    {
        cin >> consequence;
        cin.ignore(100, '\n');
        if(consequence < 1 || consequence > 5)
            cout << "Sorry. Please try again.\n";
    }
    if(difficulty == 4 && consequence == 2)
        cout << "You have discovered the secrets of the universe. Good job.\n";

    num_spaces = set_start_values(difficulty, consequence);
    cout << "There are " << num_spaces << " possible journeys to travel. How many Obstacles? Nobody knows!!\n";
    cout << "On these journeys you will explore " << num_arrays << " lands.\n";
    return;
}

//CCC
void game::play(void)
{
    int type = 0;
    int penalty = 0;
    char direction = '\0';
    int valid_square = 0;
    int num_checkpoints = 0;

    //set path
    int current_path = start(human);

//START LOOP


    do{

        //prompt user with path type
        type = prompt(human);
        
        //ask user to confront the obstacle
        penalty = make_move(human);

        //ask user to make a move backwrds or forwards
        do{
            cout << "b' to move backwards, or 'f' to move forwards\n";
            cin >> direction;
            cin.ignore(100, '\n');
            direction = tolower(direction);
            if(direction != 'b' && direction != 'f')
                cout << "Please try again.";
        }while(direction != 'b' && direction != 'f');

        if(direction == 'f')
            valid_square = forward(human);
        else if(direction == 'b')
            valid_square = back(human);
        
        
        //if player hits a null pointer, sent them down a random path
        //and increment checkpoint flag in player
        if(valid_square == 0)
        {
            num_checkpoints = add_checkpoint();
            cout << "\nYou've passed checkpoint " << num_checkpoints << "out of 5";
            current_path = start(human);
            cout << "You are now in level " << current_path << ".\n";
        }

        //ask user to go forwards or backwards
    }while(!is_victorious());

        cout << "YOU DID IT. HOW DID THIS HAPPEN!?!?!\n\n";

//END LOOP
    

}

void game::menu()
{
    int input = 0;
    int menu_size = 3;
    int is_setup = 0;
    int is_played = 0;
    cout << "\n\nWelcome! Today you must be very brave. Before you is an obstacle course of\n";
    cout << "Unknown size. There are rivers o' alligators, endless ravines, and lava flows\n";
    cout << "you must traverse to get to the finish. To win this game you must survive five\n";
    cout << "rounds of grueling mind puzzles, or collect items from each of the obstacles.\n";

    do{
        input = 0;
        cout << "\nMain Menu\n";
        cout << "Please select from the following by entering the corresponding number:\n";
        cout << "1. Setup Mode\n";
        cout << "2. Play game\n";
        cout << "3. Exit\n";
        
        while(input < 1 || input > menu_size)
        {
            cin >> input;
            cin.ignore(100, '\n');
            if(input < 1 || input > menu_size)
                cout << "Please try again\n";
        }
        if(input == 1)
        {
            if(is_setup == 0)
            {
                setup();
                is_setup = 1;
            }
            else if(is_setup == 1)
                cout << "The game can only be set up and played once.\n";
        }
        
        if(input == 2)
        {
            if(is_played == 0)
            {
                play();
                is_played = 1;
            }
            else
                cout << "The game can only be set up and played once. Please restart.\n";
        }
    }while(input != menu_size);
}




















