#include <string>
using namespace std;

// ---------------------------------------------------------
// Ryan Filgas
// CS202
// Karla Fant
// Program 2
// 5/5/2021
//
// The purpose of this file is to hold a player class, and obstacle classes that
// the player will traverse. The theme of the classes is that the player must cross
// a divide. The base class is divide, and the derived classes are lava_flow,
// endless_ravine, and river_o_alligators. As the client program will make use
// of dynamic binding, each of the classes functions will be identical with the same
// arguments, and return types, however the implementations, and results will be different.
// One of these functions will make use of RTTI. The RTTI function will have the player fight
// alligators, as alligators are unique to this class. The player will start with a toolkit of
// items, and collect trophy items throughout the game. If they get an item from each type
// of obstacle, they will win. If they pass 5 checkpoints in the list class they will win. If
// they lose all of their lives, they will lose.
// ---------------------------------------------------------

class player
{
    public:
        player(int bag_size = 10, int start_items = 6);
        player(const player &source);
        ~player();


        //Prompt user to choose item, delete it from memory and return it by reference..
        int use_item(string &item_to_fill,string &item_to_fill_2);

        int recieve_item(const string &item);

        //Display items, and return total.
        int display_toolkit(void);
        int display_collected(void);

        //Set # of lives. This will take a positive or negative
        //number and add it to the total.
        void set_lives(int adjust);

        //Returns true if the player still has lives left.
        bool is_dead(void);

        //Returns true if the user has passed enough checkpoints to win through persistence.
        bool passed_all_checkpoints(void);
        bool collected_all_items(void);

        //flips sacrificed friend switch on or off
        void set_human_bridge(bool set);

        int check_lasso(void);
        int use_lasso(void);
        int add_checkpoint(void);


    private:
        //These are the items the user will start with.
        //They may get tools as they go.
        string ** toolkit;
        //These are items collected. the player will win if they
        //win an item from each obstacle type.
        string ** collected;
        //This is how many lives the player has left. If they lose all of them,
        //of course they lose.
        int lives;
        //This is the number os uses the lasso has left.
        int lasso;
        //This is the number of checkpoints passed. It's an alternate way to win.
        int checkpoints;

        int toolkit_size;
        int collected_size;
        bool sacrificed_friend;
};



// The purpose of this class is to act as a base for the others. It will contain consequences in the form of
// sending the player backwards, and it will manage the difficulty level of the obstacle as well. This will
// increase or decrease the probability of a player bypassing. 
class divide
{
    public:
        divide();
        divide(int new_difficulty, int new_consequence);
        virtual ~divide();

        //This sets the difficulty level of the object. It will change based on the class type.
        //Adjusting it upwards will decrease the chance the user can bypass an abstacle without using an item.
        void set_difficulty_level(int new_difficulty);
        
        //returns an offset number based on difficulty level
        int offset_chances(void);

        //This sets the consequence for not bypassing the obstacle. The user will be sent backwards a number of spaces.
        void set_consequence(int num_spaces);

        

        //The player will survive without receiving an item, and they will perish at the next obstacle, but they don't
        //know it yet. Go back to last checkpoint.
        int human_bridge(player * &name);

        //Return a random number < 100.
        int random_num(void);

        // Virtual functions implemented in derived classes.
        virtual int jump(player * &name) = 0;
        virtual int macgyver(player * &name, string* &item1, string* &item2) = 0;
        virtual int run(player * &name) = 0;
        virtual void display_outcome(int outcome) = 0;
        

    protected:

        // Will increase or decrease the chance a player has to bypass an obstacle.
        int difficulty;

        // Will increase or decrease the penalty in number of spaces for not bypassing
        // the obstacle.
        int consequence;

        const int RANDOM_MOD;
};


// The purpose of the lava flow class is to serve as a unique obstacle to a player in this game.
// Jumping is less likely to result in survival, the player can mcguyver a parachute, and they can always run.
// Success will result in their passed in item being filled.
class lava_flow: public divide
{
    public:

        lava_flow();
        lava_flow(int new_difficulty, int new_consequence);
        //lava_flow(const lava_flow &source);
        ~lava_flow();

        // If a player tries to jump over lava, they will have a chance of survival. This function
        // will randomly choose a number between 0 and 100. If it's over 50, the player will survive,
        // and collect an item. The random selection will narrow the failure range for lower difficulties. 
        // If a player uses their lasso, they will survive, but using it twice
        // will tragically cause it to break. If they don't use their lasso, a null pointer is passed in as
        // an argument.
        int jump(player * &name);

        // If a player passes in parachute fabric and a hula hoop to macgyver, they will bypass this obstacle. 
        // If they don't,they will have lost both items, and won't be able to use them again. They also get 
        // sent backwards according to the consequence variable. Winning will restult in their passed in item being
        // filled.
        int macgyver(player * &name, string* &item1, string* &item2);

        //The player will be sent to a random square in the game.
        int run(player * &name);

        //Display positive or negative outcomes from each option.
        void display_outcome(int outcome);


    protected:

        //If the player successfully bypasses the obstacle, they recieve an item. This will be passed to the player.
        string item_to_pickup;
        int survival_rate;

};


// The purpose of the endless_ravine class is to serve as a unique obstacle to a player in this game.
// Jumping is more likely to result in survival, the player can mcguyver a grappling hook, and they can always run,
// but it will result in having to contend with alligators. Success will result in their item being filled.
class endless_ravine: public divide 
{
    public:

        endless_ravine();
        endless_ravine(int new_difficulty, int new_consequence);
        //endless_ravine(const endless_ravine &source);
        ~endless_ravine();

        //Lower chance of survival than jumping over lava.
        // Lassos always work if their lasso has uses left.
        int jump(player * &name);
        
        // If a player passes in a large hook, and a pogo stick to macgyver, they will bypass this 
        // obstacle. If they don't they will have lost both items, and won't be able to use them again. 
        // They also get sent backwards according to the consequence variable.
        int macgyver(player * &name, string* &item1, string* &item2);

        // Get sent to the nearest river o'alligators.
        int run(player * &name);

        //Display positive or negative outcomes from each option.
        void display_outcome(int outcome);


    protected:
        //If the player successfully bypasses the obstacle, they recieve an item. This will be passed to the player.
        string item_to_pickup;

};


// The purpose of the river_o_alligators class is to serve as a unique obstacle to a player in this game.
// Jumping is a recipe to be eaten, the player can mcguyver a distraction for the alligtors, and if they run they get eaten.
// They can however fight the alligators with a decent chance of success. Bypassing will result in their passed in item being
// filled.
class river_o_alligators: public divide
{
    public:

        river_o_alligators();
        river_o_alligators(int new_difficulty, int new_consequence);

        river_o_alligators(const river_o_alligators &source);
        ~river_o_alligators();

        //Jumping will not work. Player gets eaten by leaping alligators, and sent back.
        int jump(player * &name);

        // If a player passes in lamb chops and an inner tube to macgyver, they will bypass this obstacle. 
        // If they don't,they will have lost both items, and won't be able to use them again. 
        // They also get sent backwards according to the consequence variable.
        int macgyver(player * &name, string* &item1, string* &item2);

        //Running from alligators will result in being eaten. This will be met with a penalty,
        //and a lost life.
        int run(player * &name);

        // RTTI
        // This has an 80% chance of working for brave explorers. Winning will still result 
        // in being penalized, this is a fight with an alligator after all. The
        // player will still pick up an item, and this obstacle will be disabled in the alligators defeated
        // variable.
        int fight(player * &name);

        //Display positive or negative outcomes from each option.
        void display_outcome(int outcome);

    protected:
        //If the player successfully bypasses the obstacle, they recieve an item. This will be passed to the player.
        string item_to_pickup;

        //Fighting the alligator will add bonus items to toolkit.
        string** bonus_items;
        bool alligators_defeated;
        int fight_survival_rate;
};

