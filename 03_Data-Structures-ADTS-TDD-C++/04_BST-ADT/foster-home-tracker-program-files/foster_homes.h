// -----------------------------------------------------
// Ryan Filgas
// Assignment_4
// Karla Fant
// CS163
// 2/25/2021
//
// FILENAME:
// foster_homes.h
//
// The purpose of this program is to implement a searchable list of foster homes
// as a binary search tree. The tree will perform operations to remove all homes,
// display homes in order, display matches for animal type supported, add a home,
// and remove a home by name, in addition to returning the height if the BST. 
// The BST will consist of nodes where each member
// holds a class object of type foster home. Each home will contain a name,
// number of pets, time to add in months, relevant details as a char array, and
// animal types supported.
//
// INPUT:
//
// ----foster_home class-----
// 
// foster_home.input_entry(char home_name_to_add[], char num_pets_to_add[], char time_to_add[], char details_to_add[],char types[][]);
// Input entry takes in a home name as a char array, a number of pets to add as an int, months to foster as an int, details
// to add as a char array, and an array of foster names.
// 
// foster_home.copy_entry(foster_home &to_copy);
// Copy entry takes a foster_home object as an argument.
//
// foster_home.is_home_match(char * home_match);
// is home match takes a char array as input.
//
// foster_home.is_pet_match(char * type_match);
// is pet match takes in a an animal type as a char array.
//
// foster_home.clear_entry(void);
// This function takes no input.
//
// foster_home.compare_type(char * to_compare);
// compare name takes a char array as an argument.
//
// foster_home.display_home(void);
// display home takes in no input.
//
// ----foster_homes_table----
//
// foster_homes_table.remove_all_recursive(void);
// This function takes no inputs.
//
// foster_homes_table.add_home(foster_home &to_add);
// This function takes a foster home class object by reference.
//
// foster_homes_table.display_home(char home_to_find[]);
// Display home takes in a home to display as a char array.
//
// foster_homes_table.display_foster_matches(char type_to_match[]);
// The display foster matches function takes in a type to match as a char array.
//
// foster_homes_table.remove_home(char home_to_remove[]);
// This function takes in a home to remove as a char array
//
// foster_homes_table.display_sorted(void);
// This function takes no input.
//
// OUTPUT
//
// ----foster_home class---- 
//
// foster_home.input_entry(char home_name_to_add[], char num_pets_to_add[], char time_to_add[], char details_to_add[],char types[][]);
// Input entry returns 1 for success and 0 for failure.
// 
// foster_home.copy_entry(foster_home &to_copy);
// Copy entry returns 1 for success and 0 for failure.
//
// foster_home.is_home_match(char * home_match);
// Is home match returns returns 1 for a match, and 0 if not.
//
// foster_home.is_pet_match(char * type_match);
// Is pet match returns 1 for a matching type, or 0 for no match.
//
// foster_home.clear_entry(void);
// This function returns 1 for success, and 0 for failure.
//
// foster_home.compare_type(char * to_compare);
// This function returns a negative number if the input is smaller,
// 0 for a match, and a positive number if the input string is greater.
//
// foster_home.display_home(void);
// this function returns a 1 for success and a 0 for failure.
//
//
// ----foster_homes_table----
//
// foster_homes_table.remove_all_recursive(void);
// This function returns 0 for an empty list, and the number of nodes removed if not empty.
//
// foster_homes_table.add_home(foster_home &to_add);
// This function will return 1 for success and 0 for failure.
//
// foster_homes_table.display_home(char home_to_find[]);
// This function will return 1 for success, and 0 for failure.
//
// foster_homes_table.display_foster_matches(char type_to_match[]);
// This function will return the number of matches.
//
// foster_homes_table.remove_home(char home_to_remove[]);
// This function will return 1 for success and 0 for failure.
//
// foster_homes_table.display_sorted(void);
// This function will return the number of homes, and return 0 if empty. 
// 
// foster_homes_table.get_height(void);
// This function will return the height of the binary search tree as an int.
// -----------------------------------------------------


// This is to hold animal type info in the foster home class,
// and to manage the dynamic memory associated.
struct animal_type
{
    animal_type();
    ~animal_type();
    char * name;
};

// The foster home class manages the local data members for each foster home. It also manages a number of operations used
// by the binary search tree. The class has input_entry, cop_entry, clear_entry, is_pet_match, is_home_match, compare_type, 
// and display_home.
class foster_home
{
    public:

        //This is a constructor and destructor to set local members to NULL, and deallocate dynamically allocated memory.
        foster_home();
        ~foster_home();

        //The input entry function takes in a home name as a char array, number of pets as an int, time to foster in months as an int,
        //details to add as a char array, and an array of char arrays for animal types accepted. This copy the inputs into
        //the created objects memory, so the client can create their own object.
        int input_entry(char home_name_to_add[], char num_pets_to_add[], char time_to_add[], char details_to_add[],animal_type types_to_add[], int num_types_to_add);
        
        //Copy entry takes in a foster home class object to copy, copies the data to internal class members, and returns a 1 for
        //success or a 0 for failure.
        int copy_entry(foster_home &to_copy);

        //This function takes in a home match as a char array to compare. It will return 1 if the home name is a match, and 0 otherwise.
        int is_home_match(char * home_match);

        //This function takes an animal type in as a char array, and returns 1 if there's a matching animal type supported,
        //or a 0 for no match.
        int display_if_pet_match(char * type_match);

        //The clear entry function clears internal data members, and returns 1 for success.
        int clear_entry(void);

        //This function uses string compare to compare the passed in name with the local foster homes name.
        //It will return negative if the input name is smaller, 0 if they're a match, or positive if it's larger.
        int sort_homes(foster_home & to_compare);
        int sort_homes(char to_compare[]);

        //display home will display the objects class members.
        int display_home(void);

    private:

        //These are local data members of a foster home.
        char * home_name;
        char * num_pets;
        char * time;
        char * details;
        int num_types;
        animal_type * types;
};




//This is a node to use in a binary search tree which will manage foster homes.
struct node
{
    //Constructor
    node();
    //Destructor
    ~node();
    //Foster home object.
    foster_home a_home;
    //Left pointer.
    node * left;
    //Right pointer.
    node * right;
};



// The foster_homes_table class is the client facing implementation of a binary search tree to manage
// foster home class objects, and allocation of the data. It has member functions remove_all_recursive,
// add_home, display_home, display_foster_matches, remove_home, and display_sorted. This class will manage
// nodes containing foster_home class objects.
class foster_homes_table
{
    public:

        //Constructor and destructor to set values to NULL and delete tree.
        foster_homes_table(void);
        ~foster_homes_table(void);

        //Load from external data file.
        int load_file(char filename[]);

        //Remove all will delete every node, and return the number of nodes.
        int remove_all(void);
        int remove_all_recursive(node *&root);

        //Add home will take in a home object passed by reference, and copy it into the table.
        int add_home(foster_home &to_add);
        int add_home(node * &root, foster_home &to_add);

        //display_home will take in a home to find as a char array, and return 1 for success or 0 for failure.
        int display_home(char home_to_find[]);
        int display_home(node * &root, char home_to_find[]);

        //This function will take in a foster animal type as a char array, and display corresponding matches in the table. It
        //will return the number of homes that will take that type of animal.
        int display_foster_matches(char type_to_match[]);
        int display_foster_matches(node * root, char type_to_match[]);

        //remove home will let the client enter in a home name, and the function will remove it from the table, returning
        //1 for success or 0 for failure.
        int remove_home(char home_to_remove[]);
        int remove_home(node * &root, char home_to_remove[]);

        //This function will display every node in the tree, alphabetically by home name, and it will return the number of homes.
        int display_sorted(void);
        int display_sorted(node * root);

        //This function will traverse the tree, returning the height of the binary tree as an int.
        int get_height(void);
        int get_height(node * root);

    private:
    
    //Root node of a BST.
    node * root;
};

