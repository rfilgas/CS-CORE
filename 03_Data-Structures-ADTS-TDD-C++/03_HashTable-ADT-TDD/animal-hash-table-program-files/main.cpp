#include "animal.h"
#include <cstring>
#include <cctype>
#include <iostream>

using namespace std;

// -------------------------------------------------------------------------
// Ryan Filgas
// Assignment_3
// Karla Fant
// CS 163
// 02/16/2021
//
// Filename:
// main.cpp
//
// This program is designed to test the abstract data types animal_hash_table
// and favorite_list. Functions tested under the hash table class are add,
// display, remove, and retrieve. Each function will let the user search
// the hash table for their entries based on name, location, and breed. If the
// user wants to find all matches, they can type 'all' in as the name.
// -------------------------------------------------------------------------



struct main_data
{
    //This is a hash table to store data.
    animal_hash_table my_table;
    //This is an animals object to be filled by the client.
    animals my_animal;
    //This is an animals array to use with the retrieve function.
    animals * zoo;
    //This is a queue ADT to store animals objects.
    favorite_list my_favorites;
    //Store user selection.
    int selection = 0;
    //Store array size for fetching animals.
    int array_size = 10;
    //Store array size for user input.
    int SIZE = 100;
    //Store temp variable in main.
    int temp = 0;
};



//Welcome user.
void welcome_user(main_data &data);
//Display Menu.
void display_menu(main_data &data);
//Test add_animal function in hash table.
void add_my_animal(main_data &data);
//Test display animal function in hash table.
void display_animals(main_data &data);
//Test remove animal function in hash table.
void remove_my_animal(main_data &data);
//Test retrieve animal function in hash table.
void retrieve_animals(main_data & data);
//Test enqueue function in queue ADT.
void add_to_favorites(main_data &data);
//Test display function in queue ADT.
void display_my_favorites(main_data &data);
//Test Peek function in queue ADT.
void peek_favorite(main_data &data);
//Test dequeue function in queue ADT.
void dequeue_favorite(main_data &data);



int main()
{
    //Hold mains data.
    main_data data;

    //Welcome user.
    welcome_user(data);

    //hold array for choosing file to open.
    char temp[100];

    //Run through menu items until user selects
    //13 to exit.
    while(data.selection != 13)
    {
        display_menu(data);
        if(data.selection == 1)
            add_my_animal(data);
        if(data.selection == 2)
        {
           cout << "Please enter the name of the text file you wish to load,";
           cin.get(temp, 100, '\n');
           cin.ignore(100, '\n');
           data.temp = data.my_table.load_from_file(temp);
           cout << "there are " << data.temp << " values loaded\n";
        }
        if(data.selection == 3)
            remove_my_animal(data);
        if(data.selection == 4)
            retrieve_animals(data);
        if(data.selection == 5)
            display_animals(data);
        if(data.selection == 6)
        {
            data.temp = data.my_table.remove_all();
            cout << "Successfully removed " << data.temp << " items. Table is now empty\n";
        }
        if(data.selection == 7)
            add_to_favorites(data);
        if(data.selection == 8)
            display_my_favorites(data);
        if(data.selection == 9)
            peek_favorite(data);
        if(data.selection == 10)
            dequeue_favorite(data);
        if(data.selection == 11)//is_empty
        {
            if(data.my_favorites.is_empty())
                cout << "Favorites list is empty.\n";
            else
                cout << "Favorites list isn't empty.\n";
        }
        if(data.selection == 12)
        {
            if(data.my_favorites.initiate_queue())
                cout << "List is initiated\n";
            else
                cout << "List is already there\n";
        }
    }
    return 0;
}



//Welcome the user.
void welcome_user(main_data &data)
{
    cout << "Welcome to the Animal Database, complete with favorites list! \n";
    cout << "In this database, you will be able to add an animal, load from a file, remove one or\n";
    cout << "multiple animals, retrieve animals, display animals, and remove all animals.\n";
    cout << "Please start by adding an animal, or loading a file by selecting the";
    cout << " corresponding number from the list\n\n";
}



//Display Menu to user.
void display_menu(main_data &data)
{
     cout << "Please select an option from below\n\n";
     cout << "1. Add an Animal\n";
     cout << "2. Load From File\n";
     cout << "3. Remove Animal\n";
     cout << "4. Retrieve Animal\n";
     cout << "5. Display_Animal\n";
     cout << "6. Delete All Animals\n";
     cout << "7. Enqueue: Add to Favorites\n";
     cout << "8. Display Favorites\n";
     cout << "9. Peek First Favorite\n";
     cout << "10. Dequeue: Remove from favorites, and fetch animal.\n";
     cout << "11. Check if favorites list is empty\n";
     cout << "12. Initiate List\n";
     cout << "13. Exit\n";

     cin >> data.selection;
     cin.ignore(100, '\n');
}



//Allow user to create their own animal object, and store it in hash table.
void add_my_animal(main_data &data)
{
    //Temp variables to let user enter data before allocating memory.
    char breed[data.SIZE];
    char name[data.SIZE];
    char location[data.SIZE];
    char story[data.SIZE];
    char link[data.SIZE];
    char age[data.SIZE];

    //Get user input.
    cout << "Please note all entries are case sensitive\n\n";
    cout << "Please enter the  animals breed : \n";
    cin.get(breed, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Please enter the animals name   : \n";
    cin.get(name, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Please enter animal location    : \n";
    cin.get(location, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Please enter the animals story  : \n";
    cin.get(story, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Please enter the animals link   :\n";
    cin.get(link, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Please enter the animals age    :\n";
    cin.get(age, 100, '\n');
    cin.ignore(100, '\n');

    //If creating an entry is successful, tell user; this tests the create_entry function.
    if(data.my_animal.input_entry(breed, name, location, story, link, age))
        cout << "Entry created successfully\n";
    else
        cout << "Couldn't create entry\n";

    //If transferring data into the ADT was successful, tell user; this tests the push function.
    if(data.my_table.add_animal(data.my_animal))
        cout << "Animal added successfully\n";
    else
        cout << "Couldn't add animal\n";
    if(data.my_animal.clear_animal())
        cout << "animal successfully cleared.\n";
}



// Allow user to enter in breed, and location to display all matching values in hash table.
void display_animals(main_data &data)
{
    //Return success to user
    int success = 0;
    char  breed[data.SIZE];
    char  location[data.SIZE];

    //Get user input.
    cout << "Please note all entries are case sensitive\n\n";
    cout << "Please enter the animals breed you wish to search.\n";
    cin.get(breed, 100, '\n');
    cin.ignore(100, '\n');
    
    cout << "Please enter animal location you wish to search. \n";
    cin.get(location, 100, '\n');
    cin.ignore(100, '\n');

    //Test display function, and return number of animals displayed.
    success = data.my_table.display_animal(breed, location); 
    cout << "Displayed " << success << " animals\n";
}



//Allow user to enter in breed, name, and location to delete an animal from the
//has table. If the user enters in 'all', all matches will be deleted. This tests the
//remove_animal function.
void remove_my_animal(main_data &data)
{

    //Return success to user
    int success = 0;

    //Temp variables to let user enter data.
    char breed[data.SIZE];
    char location[data.SIZE];
    char name[data.SIZE]; 


    //Get user input.
    cout << "Please note all entries are case sensitive\n\n";
    cout << "Please enter the animals breed you wish to delete.\n";
    cin.get(breed, 100, '\n');
    cin.ignore(100, '\n');
    
    cout << "Please enter animals location you wish to delete. \n";
    cin.get(location, 100, '\n');
    cin.ignore(100, '\n');

    cout << "Please enter animals name you wish to delete, If you wish to delete all animals\n";
    cout << "with a given breed, and location, just type 'all' in lowercase letters\n";
    cin.get(name, 100, '\n');
    cin.ignore(100, '\n');
    
    //Test remove_animal function in table class, and return the number of animals deleted.
    success = data.my_table.remove_animal(name, breed, location); 
    cout << "successfully deleted " << success << " items\n";
}



//Allow the user to enter in a vreed, location, name, or all to retrieve one or more animals. The
//animals in this case are sorted in a temporary array, and displayed after to test the function.
void retrieve_animals(main_data & data)
{
    //Return success to user
    int success = 0;

    //Temp variables to let user enter data.
    char breed[data.SIZE];
    char location[data.SIZE];
    char name[data.SIZE]; 

    //This is an animals object array to catch objects coming from the retrieve function.
    data.zoo = new animals[data.array_size];

    //Get user input.
    cout << "Please note all entries are case sensitive\n\n";
    cout << "Please enter the animals breed you wish to retrieve.\n";
    cin.get(breed, 100, '\n');
    cin.ignore(100, '\n');
    
    cout << "Please enter animals location you wish to retrieve\n";
    cin.get(location, 100, '\n');
    cin.ignore(100, '\n');

    cout << "Please enter animals name you wish to retrieve, If you wish to retrieve all animals\n";
    cout << "with a given breed, and location, just type 'all' in lowercase letters\n";
    cin.get(name, 100, '\n');
    cin.ignore(100, '\n');

    //Test retrieve function, passing the clients animals array by reference, and allow the
    //function to fill it. Use returned value to display the number of retrieved items.
    success = data.my_table.retrieve_animal(name, breed, location, data.zoo, data.array_size);

    cout << "Finished retrieving " << success << " items\n";
    success = 0;

    //Display the retrieved items to make sure they're in the array.
    cout << "Contents of retrieved array is displayed: \n\n";
    animals * temp = data.zoo;
    for(int i = 0; i < data.array_size; ++i)
    {
        success += temp -> display_entry();
        ++temp;
    }
    cout << "Finished displaying " << success << " retrieved items\n\n";
    delete [] data.zoo;
}



//Allow the user to retrieve entries from the hash table, and store them in the favorites list. This
//is a test of the enqueue function from the favorites list ADT.
void add_to_favorites(main_data &data)
{
    //Return success to user
    int temp_success = 0;

    //Return success to user
    int success = 0;

    //Temp arrays to take user input.
    char breed[data.SIZE];
    char location[data.SIZE];
    char name[data.SIZE]; 

    //Get user input, and allocate animal array to recieve animals.
    data.zoo = new animals[data.array_size];

    cout << "Please note all entries are case sensitive\n\n";
    cout << "Please enter the animals breed you wish to add to favorites.\n";
    cin.get(breed, 100, '\n');
    cin.ignore(100, '\n');
    
    cout << "Please enter animals location you wish to add to favorites\n";
    cin.get(location, 100, '\n');
    cin.ignore(100, '\n');

    cout << "Please enter animals name you wish to add to favorites, If you wish to add all animals\n";
    cout << "with a given breed, and location, just type 'all' in lowercase letters\n";
    cin.get(name, 100, '\n');
    cin.ignore(100, '\n');

    //Let client retrieve items to store into array. These will be added to the
    //favorites list.
    success = data.my_table.retrieve_animal(name, breed, location, data.zoo, data.array_size);
    cout << "Finished retrieving " << success << " items\n";
    temp_success = success;
    success = 0;
    
    // Use retrieved values, and insert each into list using the enqueue function. Since this functon
    // returns one for success, summing the return will result in the nulber of items added.
    animals * temp = data.zoo;
    for(int i = 0; i < temp_success; ++i)
    {
        success += data.my_favorites.enqueue((*temp));
        ++temp;
    }
    cout << "Finished adding" << success << " items to favorites\n\n";
    delete [] data.zoo;
}



// Allow the user to display all favorites in the favorites list.
void display_my_favorites(main_data &data)
{
    //Return success to user
    int success = 0;

    //test the display all function, and catch return value.
    success = data.my_favorites.display_all();
    cout << "# of items: " << success << "\n";;
}



// Allow user to 'peek' the first object in the queue ADT, passing it back by reference,
// displaying it to test the passed data.
void peek_favorite(main_data &data)
{
    //Return success to user
    int success = 0;

    //This is an animals object to be filled by the peek function.
    animals this_animal;

    //Test the peek function, and return success.
    success = data.my_favorites.peek(this_animal);

    //Display peeked data item, to make sure it's there.
    cout << "Displaying peeked entry\n";
    if(this_animal.display_entry())
        cout << "Success is " << success << "\n";
    else
        cout << "Entry couldn't be fetched or displayed\n";
}



//This is a test of the dequeue function. It allows the client to retrieve the first object
//from the list, delete it from the list, and in this case, displays the object.
void dequeue_favorite(main_data &data)
{
    //Return success to user
    int success = 0;

    //This is an animals object to be filled by the dequeue function.
    animals to_fill;
   
    //Test the dequeue function, and display object returned by reference.
    success = data.my_favorites.dequeue(to_fill);
    if(to_fill.display_entry())
        cout << "Success value is " << success << "\n";
    else
        cout << "Operation unsucsessful.\n";
}
