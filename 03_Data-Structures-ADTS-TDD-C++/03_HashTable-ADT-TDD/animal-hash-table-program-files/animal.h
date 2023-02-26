// -----------------------------------------------------
// Ryan Filgas
// Assignment_3
// Karla Fant
// CS163
// 2/12/2021
//
// FILENAME:
// animal.h
//
// The purpose of this program is to hold and manage two separate data structures, the
// first being a hash table, and the second a circular linked list. The hash table will
// allow the client to distribute data semi-randomly throughout an array of node pointers
// where each node is the head to a linear linked list. Using the same hash function it 
// will be possible to look up each data entry with breed and name.Included in the 
// has table are functions to add an animal class object, load from a file, remove an
// animal, retrieve an animal, display an animal, and remove all animals. Below the hash
// table in the structure is an animal class, storing breed, name, location, story, and age
// data. This class will allow the client to make and use their own animal objects, as well
// as pass them into other functions. The circular linked list will be used to store user 
// favorites after they've accessed the information in the hash table. The CLL will be
// implemented as a queue, animals added will be added to the end, and animals dequeued
// will be taken from the front. Each function created as part of both data types will return
// an int to signify success or failure.
// -----------------------------------------------------
// 
// INPUT:
//
// ----animal_hash_table class----
//
// 
// table.hash_function(char * name_to_hash, char * location_to_hash);
// - the has function is passed a char array for name, and locaiton.
//
// table.add_animal(animal & to_add) - the add_animal function is passed in an 
// animal object by reference.
//
// table.load_from(char filename[]) - the load_from function loads from a client or user defined 
// data file,it must be in the same directory as the program files.
//
// table.remove_animal(char matching_name[], char matching_breed[], char matching_location[])
// the remove_animal function takes in name, breed, and location aschar array inputs. If the client 
// wants to remove all entries for a certain breed and location, rather than a specific
// entry, they may use 'all' in the name entry field.
//
// table.retrieve_animal(char matching_name[], char matching_breed[], char matching_location[], 
// animals array[], int array_size)
// the retrieve animal takes a name, breed, and location as input char arrays. 
//
// table.display_animal(char matching breed[], char matching_location[])
// the display animal function takes in a matching breed, and matching location as char arrays.
//
// table.remove_all(void) - remove_all takes no inputs.
//
//
// ----favorite_list_class----
//
//
// list.initiate_queue - no inputs
//
// list.is_empty - no inputs
//
// list.enqueue(animals &to_add) - the enqueue takes an animal class object by reference.
//
// list.dequeue(animals &to_fill) - the dequeu function takes an animal class object by reference.
//
// list.display_all(void) - no inputs
//
// list.peek(animals &to_fill) - the peek funciton takes an animal class object by reference.
//
//
// ----animals class----
//
//
// animal.display_entry(void) - no input
//
// animal.input_entry(char breed_to_add[], char name_to_add[], char location_to_add[], char story_to_add[], char age_to_add[]);
// the input entry function takes breed, name, location, and story in as char arrays, and age in as an int.
//
// animal.copy_entry(animals &to_copy) - the copy entry function takes in an animal object
// by reference.
//
// animal.is_match(char * matching name, char * matching_breed, char * matching_location)
// the is_match function takes in name, breed, and location as char arrays passed by pointer.
//
//
// OUTPUT:
//
// All functions output 1 for success, and 0 for failure, however there may be exceptions, they
// will be noted below under each function, otherwise they will be labeled as no exception.
//
//
// ----animal_hash_table_class----
//
//
// table.hash_function(char * name_to_hash, char * location_to_hash);
// -the hash function will output an integer corresponding to an indice in the 
// hash table.
//
// table.add_animal(animal & to_add) - no exception 
//
// table.load_from(char filename) - this will return the number of items loaded.
//
// table.remove_animal(char matching_name[], char matching_breed[], char matching_location[])
// - This function will return the number of animals removed.
//
// table.retrieve_animal(char matching_name[], char matching_breed[], char matching_location[], 
// animals array[], int array_size)
// - This function will return the number of animals retrieved.
//
// table.display_animal(char matching breed[], char matching_location[])
// -This function will return the number of animals displayed.
//
// table.remove_all(void) - remove_all takes no inputs.
// - this funciton will return the number of items removed.
//
//
// ----favorite_list_class----
//
//
// list.initiate_queue - no exception
//
// list.is_empty - no exception
//
// list.enqueue(animals &to_add) - this function will return the number of items added.
//
// list.dequeue(animals &to_fill) - no exception
//
// list.display_all(void) - this will return the number of animals displayed.
//
// list.peek(animals &to_fill) - no exception 
//
//
// ----animals class----
//
//
// animal.display_entry(void) - no input
//
// animal.input_entry(char breed_to_add[], char name_to_add[], char location_to_add[], char story_to_add[], int age_to_add);
// - no exception
//
// animal.copy_entry(animals &to_copy) - no exception
//
// animal.is_match(char * matching name, char * matching_breed, char * matching_location)
// - no exception
//
// -----------------------------------------------------------------------------------------------



// The animal class is responsible for holding animal data. It will be the basic building block
// for the client to interact with the hash_table and favorite_list ADTs. Functions include
// display, input, copy, and is_match.
class animals
{

    public:

        //This is aconstructor for the animal class. Set all values to null or 0.
        animals(void);

       //This is a destructor for the animal class, it will deallocate all dynamically allocated
       //memory in the animal object.
        ~animals(void);

        //display_entry will display each data member of the animals object to the user
        //and return 1 for success or 0 for failure,
        int display_entry(void);

        //input_entry takes breed, name, location, and story in as char arrays, and age as an int.
        //This function lets the client fill an animal object with new data. This function returns
        //1 for success and 0 for failure.
        int input_entry(char breed_to_add[], char name_to_add[], char location_to_add[], char story_to_add[], char link_to_add[], char age_to_add[]);


        //copy_entry takes in an animal object by reference, and copies it into the calling
        //animal objects memory. It will return 1 for success and 0 for failure.
        int copy_entry(animals &to_copy);
       
        // This is a sub function to copy just a name and location to passed in 
        // char arrays. It will return the number of successfully copied entries.
        int copy_entry(char * &breed_to_fill, char * &location_to_fill);

        //is_match takes in name, breed, and location as inputs, and compares them with the
        //local objects memory, returning 1 if a match is found, and 0 if no match is found.
        int is_match(char * matching_name, char * matching_breed, char * matching_location);

        //Lets the client manually clear their animal object. Returns 1 for success.
        int clear_animal(void);

        //Lets the client see if an animal object is empty. This is used by the is_empty function
        //in the queue adt, so when the queue is initiated, but not filled, the function will
        //still no that it contains no data.
        int is_empty(void);


    private:

        //These are data members of an animal object. All arrays will be allocated
        //dynamically.
        char * breed;
        char * name;
        char * location;
        char * story;
        char * link;
        char * age;
};



//This struct is a node, which will be the building block of the linear and circular linked
//lists in the favorite_list class, and the animal_hash_table class.
struct node
{
    //This constructor will set the next pointer to null.
    node(void);

    //This function will call the destructor on an the residing animal object.
    ~node(void);

    //This is an object of class type animals.
    animals animal;

    //This is a pointer to the next node in an LLL or CLL.
    node * next;
};



//This is a node for the queue ADT.
struct qnode
{
    //This constructor will set the next pointer to null.
    qnode(void);

    //This function will call the destructor on an the residing animal object.
    ~qnode(void);

    //This is an object of class type animals.
    animals animal;

    //This is a pointer to the next node in an LLL or CLL.
    qnode * next;
};



/*The animal hash table class, is the core ADT of this program. It will allow the user to distribute
data evenly in an array of node pointers leading to linear linked lists. If there are any collisions
where two data points get mapped to the same node, they will be added to an LLL at that node. This
class includes functions add_animal, load_from_file, remove_animal, retrieve_animal, display_animal,
and remove_all.*/
class animal_hash_table
{
    public:

        //this constructor will set the hash table to null.
        animal_hash_table(int size = 59);

        //This destructor will delete the array, and accompanying linear linked lists.
        ~animal_hash_table(void);
        

        //The hash function will take in a name, and location, and output an indice number
        //corresponding to a location in the hash table array.
        int hash_function(char * breed_to_hash, char * location_to_hash);

        //The add animal function will take an animals object as input, run the animal through the hash
        //function where it will insert the object into the array. This function will return 1
        //for success and 0 for failure.
        int add_animal(animals &to_add);

        //The load from file function will load animal data from a file passed in by the client
        //assign it to individual animal objects, and copy them into the hash table using the 
        //hash function to dictate the location. It will return the number of objects loaded.
        int load_from_file(char filename[]);

        //Remove animal will take in name, breed, and location as char arrays, and using the 
        //hash function will find the location of the corresponfing data. From there it will
        //compare each object using the is_match animals class function, and it will
        //delete the matching class object. If the client inputs 'all' instead of a name
        //all matching objects will be deleted. This function will return the number of animals
        //deleted. The second call of this function is a recursive removal.
        int remove_animal(char matching_name[], char matching_breed[], char matching_location[]);

        //The retrieve animal function takes in a name, breed, and location from the client, find
        //the corresponding animal in the array using the hash function, and load the data into
        //an array of animals objects.This function will return the number of animals retrieved.
        int retrieve_animal(char matching_name[], char matching_breed[], char matching_location[], animals * &array, int &array_size);

        //the diplay_animal function takes in a breed, and location, then displays all matches
        //to the user. This function will return the number of animals displayed.
        int display_animal(char matching_breed[], char matching_location[]);

        //the remove_all function will iterate through the table, deleting linear linked]
        //lists if there are any, and it will set all heads to NULL.
        int remove_all(void);



    private:

        //This is a recursive helper function for the remove animal function.
        int remove_animal(node * &head, char matching_name[], char matching_breed[], char matching_location[]);
        //This is a helper function for the hash table. It takes in the hash table by reference,
        //and does math operations on it based on a single input.
        int hash_helper(char * to_hash, int &hash_number);

        //This is a pointer to a headpointer at the beginning of an array. This will store
        //entried in the table.
        node ** table;

        //This is the hash table size.
        int tablesize = 59;
};



// The favorite list class will be used to store user favorites selected from output of the display
// function in the hash table class. This ADT will be implemented as a queue, and contain functions
// to enwueu, dequeue, initiate, display all, and peek. Data items will be added to the end of
// the list and removed at the front. It will be implemented as a circular linked list, where the
// last items next pointer, points to the first item.
class favorite_list
{
    public:

        //This is a constructor to set rear to null.
        favorite_list(void);

        //This is a destructor to delete the CLL.
        ~favorite_list(void);

        //This function initiates the queue by allocating memory for rear, and setting its
        //next pointer to head. This function will return 0 for failure, and 1 for success.
        int initiate_queue(void);

        //is_empty will return 0 if there's data in the list, and 1 if rear is null.
        int is_empty(void);

        //enqueue will take in an animal object by reference, and copy it into a new node
        //at the end of the list. Enqueue will return the number of animals added.
        int enqueue(animals &to_add);

        //dequeue will load the first item in the list into an animal object passed by reference
        //and delete the item from the list.
        int dequeue(animals &to_fill);

        //The display all function displays the entire favorites list, accessing each node. This
        //function will return 1 for success and 0 for failure.
        int display_all(void);
        

        //The peek function will fill an animal object passed by reference with the data from
        //the first node in the CLL without changing the CLL.
        int peek(animals &to_fill);



    private:

        //This is the rear node of the CLL. From here, the rest of the list
        //can be accessed.
        qnode * rear;

};
