using namespace std;
#include "divide.h"
#include <string>
#include <cstdlib>
#include <sys/time.h>
#include <iostream>

//---------------------------------------------------------------------------------------
// Ryan Filgas
// CS202
// Karla Fant
// 5/5/2021
// Program 2
// 
// The purpose of this file is to contain the base and derived classes for the
// game, as well as a player class. The base class is 'divide', and the derived
// classes are lava_flow, endless_ravine, and river_o_alligators. They contain
// the following functions. //This may need updating.
//
// ***player***:
//
// int use_item(string *& item_to_fill). This allows the client to pass an item
// by reference to the calling function. It will help the user remove things from
// their bag for use, and return the number of items left.
//
// int display_toolkit and int display_collected. These will display collected items
// and return thr quantity as an int.
//
// void set_lives(int adjust) - this will allow the users life value to be adjusted.
// An int must be passed in, and that will be added (or subtracted if negative) from the
// players life count.
//
// bool is_dead(void) - this function will return 1 if the player is out of lives.
// bool passed_all_checkpoints - this function will return 1 if the user passes
// 5 checkpoints with their life intact.
//
// void set_human_bridge(bool set). - flips sacrificed friend on or off.
//
// data members: string ** toolkit, string ** collected, int lives, int lasso,
// int checkpoints, int toolkit_size, int collected_size bool sacrificed friend.
//
// //check num lasso uses, and decrement. Return 0 if lasso is at 0.
// int player::check_lasso(void){return 0;}
// int player::use_lasso{return 0;}
// 
// ***divide***:
//
// void set_difficulty_level - this function takes an int between 1 and 10
//
// void set_consequence - sets the consequence in number of nodes the player
// must go back.
//
// int human_bridge - takes a player by reference, and returns 1 for success.
// It will flip the human bridge switch starting the players countdown to doom.
// *if* they choose this move.
//
// The following are virtual functions of divide. Below are explanations on how
// they will differ in each class.
//
// virtual int jump(player * &name, int &lasso, string * &item_to_fill) = 0;
// lava_flow: Player is given an initial 50% survival rate scaled up or down by difficulty.
// endless_ravine: Player is given an initial 80% survival rate scaled up or down.
// river_o_alligators: Player will lose a life.
// Success is indicated by a 1 or 0. Success will mean a filled item.
//
// virtual int macgyver(player * &name, string* &item1, string* &item2, string * &item_to_fill) = 0;
// lava_flow: pass in player name, two objects, item to fill. If items are parachute fabric
// and hulahoop, a 1 will be returned, if not, both items will be deleted, and a 0 returned.
// endless_ravine:passing in a large hook and a pogo stick will fill items and return success.
// river_o_alligators:passing in lamb chops and an inner tube will fill items and return success.
// Success is indicated by a 1 or 0. Success will mean a filled item.
// 
// virtual int run(player * &name) = 0;
// lava_flow: Player will go to a random location. Return 1.
// endless_ravine: Player will be sent to the nearest river. Return 1.
// river_o_alligators: Return 0. Player will be eaten.
// Success is indicated by a 1 or 0. Success will mean a filled item.
//
// virtual void display_outcome(int outcome) = 0;
// Always a display function with no return.
//
//
// The RTTI function is fight in the river_o_alligators class. The player will have an
// 80% chance of success. If successfully all three passed in items will be filled, and 1 returned.
// The player will still recieve a penalty in this case.
// int fight(player * &name, string* &item, string * &item_to_fill, string *&toolkit_to_fill1, 
// string *&toolkit_to_fill2);
//
//---------------------------------------------------------------------------------------

// const strings to use as responses to different events.
const string HUMAN_BRIDGE = "You've unfortunately lost a friend. I wish you no luck.\n\n";

const string T_LAVA_JUMP = "YOU DID IT! Please don't try that again.\n\n";
const string F_LAVA_JUMP = "Unfortunately you're a charred coal nugget.\n\n"; 
const string T_LAVA_MAC = "Damn. You're a good inventor. You've created a parachute! Next!\n\n";
const string F_LAVA_MAC = "Ouch. I'd call you a french fry, but that would be too nice.\n\n";
const string LAVA_RUN = "That works too. BYEEEEE\n\n";

const string T_RAVINE_JUMP = "This was highly unlikely. But you made it champ.\n\n";
const string F_RAVINE_JUMP = "You've fallen. Have fun with that.\n\n";
const string T_RAVINE_MAC = "YOU MADE A GRAPPLING HOOK!?!?!?......cool.\n\n";
const string F_RAVINE_MAC = "Human. This just isn't your day.\n\n";
const string RAVINE_RUN = "You can run, but I hope you like alligators\n\n";

const string ALLIGATOR_JUMP = "You've never tried to jump over an alligator, have you?\n\n";
const string T_ALLIGATOR_MAC = "You'll do well in a swamp. The gators are feasting, but not on you.\n\n";
const string F_ALLIGATOR_MAC = "Today you're gator food. Sorry. Not sorry.\n\n";
const string GATOR_RUN = "CRUNCH! Unfortunately.\n\n";



// The player class keeps all common information in one place as the player traverses
// the game. In addition to keeping track of lives, it also contains a toolbox, and
// collected bag.
player::player(int bag_size, int start_items): lasso(2), checkpoints(0)
{
    toolkit_size = collected_size = bag_size;

    toolkit = new string * [bag_size];
    collected = new string * [bag_size];
    
    for(int i = 0; i < start_items; ++i)
    {
        toolkit[i] = new string;
    }

    *(toolkit[0]) = "Parachute Fabric";
    *(toolkit[1]) = "Hulu Hoop";
    *(toolkit[2]) = "Large Hook";
    *(toolkit[3]) = "Pogo Stick";
    *(toolkit[4]) = "Lamb Chops";
    *(toolkit[5]) = "Inner Tube";

    for(int i = start_items; i < bag_size; ++i)
    {
        toolkit[i] = NULL;
    }

    for(int i = 0; i < bag_size; ++i)
    {
        collected[i] = NULL;
    }
}



//---------------------------------------------------------------------------------------------
player::player(const player & source): lives(source.lives), lasso(source.lasso), checkpoints(source.checkpoints), toolkit_size(source.toolkit_size), collected_size(source.collected_size), sacrificed_friend(source.sacrificed_friend)
{
    string ** toolstr = source.toolkit;
    string ** collstr = source.collected;
    toolkit = new string * [source.toolkit_size];
    collected = new string * [source.collected_size];
    for(int i = 0; i < source.toolkit_size; ++i)
    {
        if(toolstr && toolstr[i])
        {
            toolkit[i] = new string;
            toolkit[i] = toolstr[i];
        }
        else
            toolkit[i] = NULL;
    }

    for(int i = 0; i < source.collected_size; ++i)
    {
        if(collstr && collstr[i])
        {
            collected[i] = new string;
            collected[i] = collstr[i];
        }
        else
            collected[i] = NULL;
    }
}
//---------------------------------------------------------------------------------------------
player::~player()
{
    for(int i = 0; i < toolkit_size; ++i)
    {
        if(toolkit[i] != NULL)
        {
            delete toolkit[i];
            toolkit[i] = NULL;
        }
    }
    delete [] toolkit;
    toolkit = NULL;

    for(int i = 0; i < collected_size; ++i)
    {
        if(collected[i] != NULL)
        {
            delete collected[i];
            collected[i] = NULL;
        }
    }
    delete [] collected;
    collected = NULL;
}

//---------------------------------------------------------------------------------------------
int player::use_item(string &item_to_fill, string &item_to_fill_2)
{
    int item_1;
    int item_2;
    int count = 0;
    cout << "Which two items would you like to use? Enter two numbers separated by a space\n";

    for(int i = 0; i < toolkit_size; ++i)
    {
        if(toolkit[i])
        {
            cout << (i + 1) << ". "<< *(toolkit[i]) << "\n";
            ++count;
        }
        else cout << (i + 1) << ". Empty.\n";
    }
    cin >> item_1 >> item_2;
    cin.ignore(100, '\n');
    
    item_to_fill = *toolkit[item_1-1]; 
    item_to_fill_2 = *toolkit[item_2 - 1];

    if(toolkit[item_1-1])
    {
        delete toolkit[item_1-1];
        toolkit[item_1-1] = NULL;
        --count;
    }
    if(toolkit[item_2-1])
    {
        delete toolkit[item_2-1];
        toolkit[item_2-1] = NULL;
        --count;
    }
    
    return count;
}

int player::recieve_item(const string &item)
{
    int i = 0;
    while(collected[i] != NULL && i < collected_size)
    {
        ++i;
    }
    if(collected[i] == NULL)
    {
        collected[i] = new string(item);
       // (collected[i]) = item;
        return 1;
    }
    return 0;
}

void player::set_lives(int adjust)
{
    lives = adjust;
    return;
}

bool player::collected_all_items(void)
{
    int count = 0;
    for(int i = 0; i < collected_size; ++i)
    {
        if(collected[i] != NULL)
            ++count;
    }
    if(count  > 7)
        return 1;
    else return 0;
}

bool player::is_dead(void)
{
    return (lives > 0);
}

bool player::passed_all_checkpoints(void)
{
    return(checkpoints > 5);
}

int player::add_checkpoint(void)
{
    ++checkpoints;
    return checkpoints;
}


void player::set_human_bridge(bool set)
{
    sacrificed_friend = set;
    return;
}

int player::check_lasso(void)
{
    return lasso;
}

int player::use_lasso(void)
{
    --lasso;
    return 1 + lasso;
}

//---------------------------------------------------------------------------------------------
//END OF PLAYER********************************************************************************
//---------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------
//DIVIDE********************************************************************************
//---------------------------------------------------------------------------------------------

divide::divide():difficulty(0), consequence(0), RANDOM_MOD(100){}
divide::divide(int new_difficulty, int new_consequence): difficulty(new_difficulty), consequence(new_consequence), RANDOM_MOD(100)
{}
divide::~divide(){}

void divide::set_difficulty_level(int new_difficulty)
{
    difficulty = new_difficulty;
}

void divide::set_consequence(int num_spaces)
{
    consequence = num_spaces;
}

int divide::human_bridge(player * &name)
{
    cout << HUMAN_BRIDGE;
    name -> set_human_bridge(1);
    return 1;
}


//Get a random number between 0 and 100.
int divide::random_num()
{
//    struct timeval my_time;
//    gettimeofday(&my_time, NULL);
//    srand(my_time.tv_usec);
    return rand() % RANDOM_MOD;
}

// This will allow the player to get up to 45 points credit.
// 10 is the max level, and 5 was enough to make the variation
// correct between easy and hard difficulties.
int divide::offset_chances(void)
{
    return (10 - difficulty * 5);
}


//---------------------------------------------------------------------------------------------
//END OF DIVIDE********************************************************************************
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
//LAVA FLOW************************************************************************************
//---------------------------------------------------------------------------------------------

lava_flow::lava_flow()
{}

lava_flow::lava_flow(int new_difficulty, int new_consequence): divide(new_difficulty, new_consequence)
{  
    item_to_pickup="Hypnotic Umbrella Hat";
}

lava_flow::~lava_flow(){}

//If player uses lasso, decrement, and fill item, return 1. If not, roll and if they succeed, return 1.
//else return 0;
int lava_flow::jump(player * &name)
{
    if(name ->check_lasso() > 0)
    {
        name->use_lasso();
        if(!name -> recieve_item(item_to_pickup))
            cout << "Bag is full.\n";
        return 1;
    }

    int roll = random_num() + offset_chances();
    if(roll > 50)
    {
        if(!name -> recieve_item(item_to_pickup))
            cout << "Bag is full.\n";
        display_outcome(1);
        return 1;
    }
    display_outcome(2);
    name -> set_lives(-1);
    return consequence;
}


int lava_flow::macgyver(player * &name, string* &item1, string* &item2)
{
    if((*item1 == "Parachute Fabric" && *item2 == "Hula Hoop") || (*item1 == "Hula Hoop" && *item2 == "Parachute Fabric"))
    {
        if(!name -> recieve_item(item_to_pickup))
            cout << "Bag is full.\n";
        display_outcome(3);
        return 1;
    }
    else
    {
        name -> set_lives(-1);
        display_outcome(4);
        return consequence;
    }
}

int lava_flow::run(player * &name)
{
    display_outcome(5);
    return 1;
}

void lava_flow::display_outcome(int outcome)
{
    //jump success
    if(outcome == 1)
        cout << T_LAVA_JUMP;;
    //jump failure
    if(outcome == 2)
        cout << F_LAVA_JUMP;
    //macgyver success
    if(outcome == 3)
        cout << T_LAVA_MAC;
    //macgyver failure
    if(outcome == 4)
        cout << F_LAVA_MAC;
    //run
    if(outcome == 5)
        cout << LAVA_RUN;
    if(outcome == 6)
        cout << HUMAN_BRIDGE;
}




//---------------------------------------------------------------------------------------------
//END OF LAVA FLOW*****************************************************************************
//---------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------
// ENDLESS RAVINE******************************************************************************
//---------------------------------------------------------------------------------------------

//NNN
endless_ravine::endless_ravine(){}
endless_ravine::endless_ravine(int new_difficulty, int new_consequence): divide(new_difficulty, new_consequence)
{
    item_to_pickup = "Purple Rain Pants";
}
endless_ravine::~endless_ravine(){}


int endless_ravine::jump(player * &name)
{
    if(name ->check_lasso() > 0)
    {
        name->use_lasso();
        if(!name -> recieve_item(item_to_pickup))
            cout << "Bag is full.\n";
        display_outcome(1);
        return 1;
    }

    int roll = random_num() + offset_chances();
    if(roll > 40)
    {
        if(!name -> recieve_item(item_to_pickup))
            cout << "Bag is full.\n";
        display_outcome(2);
        return 1;
    }
    name -> set_lives(-1);
    return consequence;
}



int endless_ravine::macgyver(player * &name, string* &item1, string* &item2)
{
    if((*item1 == "Large Hook" && *item2 == "Pogo Stick") || (*item1 == "Pogo Stick" && *item2 == "Large Hook"))
    {
        if(!name -> recieve_item(item_to_pickup))
            cout << "Bag is full.\n";
        display_outcome(3);
        return 1;
    }
    else
    {
        display_outcome(4);
        name -> set_lives(-1);
        return consequence;
    }
}

// Return a -1, and get sent to alligators.
int endless_ravine::run(player * &name)
{
    display_outcome(5);
    return -1;
}
void endless_ravine::display_outcome(int outcome)
{
    //jump success
    if(outcome == 1)
        cout << T_RAVINE_JUMP;;
    //jump failure
    if(outcome == 2)
        cout << F_RAVINE_JUMP;
    //macgyver success
    if(outcome == 3)
        cout << T_RAVINE_MAC;
    //macgyver failure
    if(outcome == 4)
        cout << F_RAVINE_MAC;
    //run
    if(outcome == 5)
        cout << RAVINE_RUN;
    if(outcome == 6)
        cout << HUMAN_BRIDGE;
}



//---------------------------------------------------------------------------------------------
// NOT QUITE ENDLESS RAVINE********************************************************************
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
// RIVER O ALLIGATORS**************************************************************************
//---------------------------------------------------------------------------------------------

river_o_alligators::river_o_alligators(): bonus_items(NULL){}

river_o_alligators::river_o_alligators(int new_difficulty, int new_consequence): divide(new_difficulty, new_consequence), alligators_defeated(0), fight_survival_rate(80)
{
    item_to_pickup = "Purple Puffy Coat";
    bonus_items = new string* [2];
    bonus_items[0] = new string("Large Hook");
    bonus_items[1] = new string("Pogo Stick");
}

river_o_alligators::river_o_alligators(const river_o_alligators & source): divide(source.difficulty, source.consequence),alligators_defeated(source.alligators_defeated), fight_survival_rate(source.fight_survival_rate)
{
    item_to_pickup = source.item_to_pickup;
    bonus_items = new string* [2];
   *(bonus_items[0]) = *(source.bonus_items[0]);
    *(bonus_items[1]) = *(source.bonus_items[1]);
}
river_o_alligators::~river_o_alligators()
{
    if(bonus_items != NULL && bonus_items[0] != NULL && bonus_items[1] != NULL)
    {
        delete (bonus_items[0]);
        delete (bonus_items[1]);
        bonus_items[0] = NULL;
        bonus_items[1] = NULL;
    }
    if(bonus_items != NULL)
        delete [] bonus_items;
}


// No chance of survival, and a lasso use is given up.
int river_o_alligators::jump(player * &name)
{
    if(name ->check_lasso() > 0)
        name->use_lasso();
    name -> set_lives(-1);
    return consequence;
}

int river_o_alligators::macgyver(player * &name, string* &item1, string* &item2)
{
    if((*item1 == "Lamb Chops" && *item2 == "Inner Tube") || (*item1 == "Inner Tube" && *item2 == "Lamb Chops"))
    {
        if(!name -> recieve_item(item_to_pickup))
            cout << "Bag is full.\n";
        return 1;
    }
    else
    {
        name -> set_lives(-1);
        return consequence;
    }
}

// lose a life, and go to random square.
int river_o_alligators::run(player * &name)
{
    name -> set_lives(-1);
    return 0;
}

void river_o_alligators::display_outcome(int outcome)
{
    //jump
    if(outcome == 1)
        cout << ALLIGATOR_JUMP;;
    //macgyver success
    if(outcome == 2)
        cout << T_ALLIGATOR_MAC;
    //macgyver failure
    if(outcome == 3)
        cout << F_ALLIGATOR_MAC;
    //run
    if(outcome == 4)
        cout << GATOR_RUN;
    if(outcome == 5)
        cout << HUMAN_BRIDGE;
}

int river_o_alligators::fight(player * &name)
{
    int roll = random_num() + offset_chances();
    if(roll > 20)
    {
        if(!name -> recieve_item(item_to_pickup))
            cout << "Bag is full.\n";
        return 1;
    }
    else return consequence;
}

//---------------------------------------------------------------------------------------------
// END OF RIVER O ALLIGATORS**************************************************************************
//---------------------------------------------------------------------------------------------
