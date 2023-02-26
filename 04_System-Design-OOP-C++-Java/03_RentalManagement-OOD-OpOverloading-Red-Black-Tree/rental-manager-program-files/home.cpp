#include "home.h"
#include "error.h"
#include <iostream>
#include <cstring>
// Ryan Filgas
// CS202
// Karla Fant
// Program 3
// 5/12/2021

// The purpose of this application is to manage
// a virtual posting board for potential roommates.
// The user will be able to make a post, or search
// for a matching room they would like to rent. This
// file will manage the data and fields for each type
// of living situation supported. The base class will
// be called home, and from that will be derived
// share, room, and multi.
//
//
// SUPPORTED OPERATORS
// These are implemented in all home and derived classes.
// 
// ::: = the equality operator will overide the second object
//       with the first.
//
// ::: + use the data from the first operand, and carry over 
//       common denominators (smoking, pets, etc.)
//
// ::: += will add a price onto any home.
//
// ::: == and != will test for a complete match for each type.
//
// ::: <, <=, >, >= will all test price.
//
// ::: << will output the objects data.
// ::: >> will allow data input like cin.
//
//
// Also supported:
// home class;
//
// edit_user, edit_place, edit_details, edit_basics -- all work with main edit function to
// break up the information gathering.
//
// virtual edit(this is the main edit function implemented in all derived classes)
// display_key -- outputs the price for diagnostic purposes
// is_username -- allows a roommate search by name




//---NODE-------
node::node(): right(NULL), left(NULL), parent(NULL), red(0), is_left(0){}
node::~node(){
    right = left = parent = NULL;
}

// getters for internal home * pointers
home *& node::get_left(){return left;}
home *& node::get_right(){return right;}
home *& node::get_parent(){return parent;}
void node::set_red(int is_red){
    red = is_red; 
    return;
}

// Flip switch to red or black
void node::set_black(int is_black){
    if(is_black == 0)
        red = 1;
    else red = 0;
    return;
}

// Return the value of red.
int node::check_red(void){return red;}

// Return the value of red as if it's black
int node::check_black(void)
{
    if(red == 1)
        return 0;
    else return 1;
}

//check pointers for null{}
int node::check_left(void)
{
    if(left == NULL)
        return 0;
    else return 1;
}

int node::check_right(void)
{
    if(right == NULL)
        return 0;
    else return 1;
}

int node::check_parent(void)
{
    if(parent == NULL)
        return 0;
    else return 1;
}



// Check if this node is a left or right child
int node::is_left_child(void)
{
    if(is_left == 1)
        return 1;
    else return 0;
}
int node::is_right_child(void){
    if(!is_left)
        return 1;
    else return 0;
}


// Set the node as left or right
void node::set_left_child(int value){
    is_left = value;
    return;
}

void node::set_right_child(int value){
    if(value == 0)
        is_left = 1;
    else is_left = 0;
    return;
}

//***************************************************************




//---HOME------- Derived from a node



// =  overide op1 with op2
home & home::operator = (const home &h2){
    if(this == &h2)
        return *this;
    username = h2.username;
    contact_info = h2.contact_info;
    ammenities = h2.ammenities;
    neighborhood = h2.neighborhood;
    app_process = h2.app_process;
    price = h2.price;
    smoking = h2.smoking;
    months_duration = h2.months_duration;
    pets = h2.pets;
    furnished = h2.furnished;
    laundry = h2.laundry;
    dishwasher = h2.dishwasher;
    return *this;
}

// +  use the data from one, and combine greatest 
// denominators. No smoking for 1 means no smoking 
// for both etc.
home home::operator + (const home &h2) const{
    if(this == &h2)
        return *this;
    home nhome(*this);
    if(!h2.smoking)
        nhome.smoking = h2.smoking;
    if(!h2.pets)
        nhome.pets = h2.pets;
    return nhome;
} 

// Return 1 if there is a username match
// else return 0
int home::is_username(string to_match){
    if(!username.compare(to_match))
        return 1;
    else return 0;
}

// Display the key for testing
void home::display_key(void)const
{
    cout << price;
    return;
}

//  >> Read in the application process.
istream & operator >> (istream &in, home &h2){
    return h2.input(in);
}

istream & home::input(istream &in){
    in >> app_process;
    return in;
}

// Output the contents of any base or derived object
ostream & operator << (ostream &out, const home & h2){ 
    return h2.display(out);
}


// Display a home
ostream & home::display(ostream &out) const
{
    home h2 = *this;

    out << "\nUsername                : " << h2.username << "\n";
    out << "Contact info            : " << h2.contact_info << "\n";
    out << "Ammenities              : " << "\n";

    // Range based for loop with const as of C++ 11
    for(const auto& i: h2.ammenities)
    {
        out << "                        : ";
        out << i << "\n";
    }
    out << "Neighborhood            : " << h2.neighborhood << "\n";
    out << "App Process             : " << h2.app_process << "\n";
    out << "Price                   : " << h2.price << "\n";
    out << "Years Renting           : " << h2.months_duration << "\n";
    if(h2.smoking == 0)
        out << "Smoking                 : " << "No\n";
    else
        out << "Smoking                 : " << "Yes\n";
    if(h2.pets == 0)
        out << "Pets                    : " << "No\n";
    else
        out << "Pets                    : " << "Yes\n";
    if(h2.furnished == 0)
        out << "Furnished               : " << "No\n";
    else
        out << "Furnished               : " << "Yes\n";
    if(h2.laundry == 0)
        out << "Laundry                 : " << "No\n";
    else
        out << "Laundry                 : " << "Yes\n";
    if(h2.dishwasher == 0)
        out << "Dishwasher              : " << "No\n";
    else
        out << "Dishwasher              : " << "Yes\n";
    return out;
}

// += add to price
home & home::operator += (int aprice){
    NEGATIVE anerror;

    if(aprice < 0)
        throw(anerror);
    price += aprice;
    return *this;
}

// ==, != check price equality
int home::operator == (const home &h2) const{
    if(this == &h2)
        return 1;
    return (price == h2.price);
}

int home::operator != (const home &h2) const{
    if(this == &h2)
        return 0;
    return !(price == h2.price);
}

//------------------------------------------------
// <, <=, >, >= compare and return bool
// need virtual helper for each of these
bool operator < (const home & h1, const home &h2){
    if(&h1 == &h2)
        return 0;
    return h1.less_than(h2);
}
//HELPER
bool home::less_than(const home &op2) const{
    return (price < op2.price);
}
//------------------------------------------------


//------------------------------------------------
// return 1 if op 1 is <= op2
bool operator <= (const home &h1, const home &h2){
    if(&h1 == &h2)
        return 1;
    return h1.less_equal(h2);
}
//HELPER
bool home::less_equal(const home &op2) const{
    return (price <= op2.price);
}
//------------------------------------------------



// return 1 if op 1 is > op2
//------------------------------------------------
bool operator > (const home &h1, const home &h2){
    if(&h1 == &h2)
        return 0;
    return h1.greater_than(h2);
}
//HELPER
bool home::greater_than(const home &op2) const{
    return (price > op2.price);
}
//------------------------------------------------



// return 1 if op 1 is >= op2
//------------------------------------------------

bool operator >= (const home &h1, const home &h2){
    if(&h1 == &h2)
        return 1;
    return h1.greater_equals(h2);
}

bool home::greater_equals(const home &op2) const{
    return (price >= op2.price);
}
//------------------------------------------------

//edit user - called by main edit function.
int home::edit_user(string &user, string &my_contact_info){
    username = user;
    contact_info = my_contact_info;
    return 1;
}

//edit place - called by main edit function.
int home::edit_place(vector<string> &my_ammenities, string &my_neighborhood, string &my_app_process){
    ammenities = my_ammenities;
    neighborhood = my_neighborhood;
    app_process = my_app_process;
    return 1;
}

//edit details - called by main edit function.
int home::edit_details(int aprice, int asmoking, int amonths_duration, int apets){
    price = aprice;
    smoking = asmoking;
    months_duration = amonths_duration;
    pets = apets;
    return 1;
}

//edit basics - called by main edit function.
int home::edit_basics(int isfurnished, int haslaundry, int hasdishwasher){
    furnished = isfurnished;
    laundry = haslaundry;
    dishwasher = hasdishwasher;
    return 1;
}

// edit function calls the other subfunctions to accomplish the larger task.
// I didn't want to make the user sit through 20 entries, instead choosing
// what they would like to work on.
int home::edit(void){
    char answer;
    string temp;
    char ctemp;
    int i = -1; // set to negative 1 so input can be checked.
    int changes = 0;

    do{
        cout << "What would you like to edit?\n";
        cout << "1. User Info\n"; 
        cout << "2. Location & Application (Ammenities, neighborhood, application process)\n"; 
        cout << "3. Lease Details (price, smoking policy, months duration, pet policy)\n"; 
        cout << "4. Apartment Basics (is it furnished, is ther on-site laundry, or a dishwasher)\n"; 
        cout << "5. Exit edit menu.\n";
        cin >> answer;
        cin.ignore(100, '\n');
        
        if(answer == '1'){
            cout << "Enter username, and contact info on separate lines.\n";
            getline(cin, username);
            getline(cin, contact_info);
            ++changes;
        }
        else if(answer == '2'){
            cout << "Please enter ammenities one at a time. Type 'done' when you are finished\n";
            do
            {
                if(i > -1)
                {
                    ammenities.push_back(temp);
                    ++changes;
                }
                temp.clear();
                getline(cin, temp);
                ++i;
            }while(temp != "done");
            temp.clear();
        
            cout << "Enter in the name of the neighborhood or local area\n";
            cin >> neighborhood;
            cin.ignore(100, '\n');
            cout << "Input the application process\n";
            cin >> app_process;
            cin.ignore(100, '\n');
        }
        else if(answer == '3'){
            cout << "Enter the price per month of the lease\n";
            cin >> price;
            while(cin.fail())
            {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid Input Please enter an integer\n";
                cin >> price;
            }
            cin.ignore(100, '\n');
        
            cout << "Is smoking allowed? (y/n)\n";
            cin >> ctemp;
            cin.ignore(100, '\n');
            smoking = (tolower(ctemp) == 'y');
            ctemp = '\0';
        
            cout << "Enter the length of the lease in whole months\n";
            cin >> months_duration;
            while(cin.fail())
            {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid Input Please enter an integer\n";
                cin >> months_duration;
            }
            cin.ignore(100, '\n');
        
            cout << "Are pets allowed? (y/n)\n";
            cin >> ctemp;
            cin.ignore(100, '\n');
            pets = (tolower(ctemp) == 'y');
            ctemp = '\0';
            changes += 3;
        }
        else if(answer == '4'){
            cout << "Is it furnished? (y/n)\n";
            cin >> ctemp;
            cin.ignore(100, '\n');
            furnished = (tolower(ctemp) == 'y');
            ctemp = '\0';
            
            cout << "Is there in unit laundry? (y/n)\n";
            cin >> ctemp;
            cin.ignore(100, '\n');
            laundry = (tolower(ctemp) == 'y');
            ctemp = '\0';
        
            cout << "Is there an in unit dishwasher? (y/n)\n";
            cin >> ctemp;
            cin.ignore(100, '\n');
            dishwasher = (tolower(ctemp) == 'y');
            ctemp = '\0';
            changes += 3;
        }
    }while(answer != '5');
   //     changes += edit();
    return changes;
}

home::home():node(), price(0), smoking(0), months_duration(0), pets(0), furnished(0), laundry(0), dishwasher(0){}
home::~home(){}


//*********************************************************************************************
//*********************************************************************************************

//---SHARE------ This is a shared bedroom.
share::share(){}
share::~share(){}

// HALF HERE AND CALL PARENT
// =  overide op1 with op2
share & share::operator = (const share &s2){
    if(this == &s2)
        return *this;
    home:: operator = (s2);
    a_friend = s2.a_friend;
    live_work = s2.live_work;
    parties = s2.parties;
    preferences = s2.preferences;
    return *this;
}

// +  use the data from one, and combine greatest 
// denominators. No smoking for 1 means no smoking 
// for both etc.
share share::operator + (const share &s2) const{
    if(this == &s2)
        return *this;
    share myobj = *this + s2;
    myobj.parties = s2.parties;
//range based for loop with const as of C++ 11
    int k = 0;
    for(const auto& i: s2.preferences)//***************** TEST
    {
        myobj.preferences[k] = i;
        ++k;
    }
    return myobj;
 } 

// << >> - input and output
istream & operator >> (istream &in, share &s2){ 
    s2. home::input(in);
return in;
}



// Output the contents of the home object
ostream & operator << (ostream &out, const share & s2){
    s2. home::display(out);

    if(s2.a_friend == 0)
        out << "Wants a friend          : " << "No\n";
    else
        out << "Wants a friend          : " << "Yes\n";

    if(s2.live_work == 0)
        out << "Live/Work available     : " << "No\n";
    else
        out << "Live/Work available     : " << "Yes\n";

    if(s2.parties == 0)
        out << "Likes to party          : " << "No\n";
    else
        out << "Likes to party          : " << "Yes\n";
    out << "Preferences             : " << "\n";

    // Range based for loop with const as of C++ 11
    for(const auto& i: s2.preferences)
    {
        out << "                        : ";
        out << i << "\n";
    }
    return out;
}
 


//CALL PARENT
// += add to price
share & share::operator += (int price){
    home:: operator += (price); //***************************** TEST
    return *this;
}

// ==, != check price equality
int share::operator == (const share &s2) const{
    if(this == &s2)
        return 1;
    return this -> home:: operator == (s2);
}

int share::operator != (const share &s2) const{
    if(this == &s2)
        return 0;
    return s2. home:: operator != (s2);
    }

// <, <=, >, >= compare and return bool
bool operator < (const share &s1, const share &s2){
    if(&s1 == &s2)
        return 0;
    return  s1.home::less_than(s2);
}


bool operator <= (const share &s1, const share &s2){
    if(&s1 == &s2)
        return 1;
    return s1.home::less_equal(s2);
}

bool operator > (const share &s1, const share &s2){
    if(&s1 == &s2)
        return 0;
    return s1.home::greater_than(s2);
}

bool operator >= (const share &s1, const share &s2){
    if(&s1 == &s2)
        return 1;
    return s1.home::greater_equals(s2);
}


int share::edit(void){
    char answer;
    string temp;
    char ctemp;
    int changes = 0;
    
    do{
        cout << "What would you like to edit?\n";
        cout << "1. Primary Info (everything but the kitchen sink)\n"; 
        cout << "2. Living Preferences (live/work, parties, friends, other)\n"; 
        cout << "3. Exit Roomshare Editing Menu\n";
        
        cin >> answer;
        cin.ignore(100, '\n');
        if(answer == '1')
            changes += home::edit();
        
        if(answer == '2'){
            cout << "Is this a live/work arrangement?(y/n)\n";
            cin >> ctemp;
            cin.ignore(100, '\n');
            live_work = (tolower(ctemp) == 'y');
            ctemp = '\0';
            
            cout << "Are you looking for a new friend to move in? (y/n)\n";
            cin >> ctemp;
            cin.ignore(100, '\n');
            a_friend = (tolower(ctemp) == 'y');
            ctemp = '\0';
        
        
            cout << "Do you enjoy frequent parties? (y/n)\n";
            cin >> ctemp;
            cin.ignore(100, '\n');
            parties = (tolower(ctemp) == 'y');
            ctemp = '\0';
            changes += 4;
        }
    }while(answer != '3');
    //    changes += edit();
    return changes;
}



//*********************************************************************************************
//*********************************************************************************************

//ROOM------- This is a room in a house.
room::room(){}
room::~room(){}

 //HALF HERE AND CALL PARENT
// =  overide op1 with op2
room & room::operator = (const room r2){
    if(this == &r2)
        return *this;
    home:: operator = (r2);
    preferences = r2.preferences;
    description = r2.description;
    rent_hist = r2.rent_hist;
    return *this;
}

// +  use the data from one, and combine greatest denominators.
// no smoking for 1 means no smoking for both etc.
room room::operator + (const room &r2) const{ 
    if(this == &r2)
        return *this;
    room myobj = *this + r2;

    int k = 0;
    for(const auto& i: r2.preferences)//***************** TEST
    {
        myobj.preferences[k] = i;
        ++k;
    }
    return myobj;
 } 



// << >> - input and output
istream & operator >> (istream &in, room &r2){
    r2.home::input(in);
return in;
}

ostream & operator << (ostream &out, const room & r2){
    r2. home::display(out);
    out << "Preferences   : " << "\n";
    // Range based for loop with const as of C++ 11
    for(const auto& i: r2.preferences)
    {
        out << "                        : ";
        out << i << "\n";
    }
    out << "Description             : " << r2.description << "\n";
    out << "months Rent History     : " << r2.rent_hist << "\n";
    return out;
}

//CALL PARENT
// += add to price
//--------------------------------------------------------------------------------

room & room::operator += (int price){
    home:: operator += (price);
    return *this;
}

// ==, != check price equality
int room::operator == (const room &r2) const{
    if(this == &r2)
        return 1;
    return this -> home:: operator == (r2);
}

int room::operator != (const room &r2) const{
    if(this == &r2)
        return 0;
    return r2. home:: operator != (r2);
    }

// <, <=, >, >= compare and return bool
bool operator < (const room &r1, const room &r2){
    if(&r1 == &r2)
        return 0;
    return  r1.home::less_than(r2);
}


bool operator <= (const room &r1, const room &r2){
    if(&r1 == &r2)
        return 1;
    return r1.home::less_equal(r2);
}

bool operator > (const room &r1, const room &r2){
    if(&r1 == &r2)
        return 0;
    return r1.home::greater_than(r2);
}

bool operator >= (const room &r1, const room &r2){
    if(&r1 == &r2)
        return 1;
    return r1.home::greater_equals(r2);
}

// Edit room, works with main edit function.
int room::edit(void){
    char answer;
    string temp;
    int changes = 0;
    int i = -1;
    
    do{
        cout << "What would you like to edit?\n";
        cout << "1. Primary Info (everything but the kitchen sink)\n"; 
        cout << "2. Room Information (preferences, description, rent history)\n"; 
        cout << "3. Exit Roomshare Editing Menu\n";
        
        cin >> answer;
        cin.ignore(100, '\n');
        if(answer == '1')
            changes += home::edit();
        
        if(answer == '2'){
        cout << "Please enter the room description\n";
        getline(cin, description);
        
        cout << "How long of a rent history will be required (yrs)?\n";
        cin >> rent_hist;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid Input Please enter an integer\n";
            cin >> rent_hist;
        }
        cin.ignore(100, '\n');
        ++changes;
        
        cout << "Enter roommate preferences one at a time. Type 'done' when you are finished\n";
        do
        {
            if(i > -1)
            {
                preferences.push_back(temp);
                ++changes;
            }
            temp.clear();
            getline(cin, temp);
            ++i;
        }while(temp != "done");
        temp.clear();
        
        }
    }while(answer != '3');
    return changes;
}



//*********************************************************************************************
//*********************************************************************************************
//---HOUSE------- This is multiple rooms or a house.

//Do some work here and call parent for the rest.
// =  overide op1 with op2
multi & multi::operator = (const multi &m2){
    if(this == &m2)
        return *this;
    home:: operator = (m2);
    c_score = m2.c_score;
    rent_hist = m2.rent_hist;
    roommates = m2.roommates;
    empty_house = m2.empty_house;
    bedrooms = m2.bedrooms;
    bathrooms = m2.bathrooms;
    return *this;
}


// +  use the data from one, and combine greatest 
// denominators. No smoking for 1 means no smoking 
// for both etc.
multi multi::operator + (const multi &m2) const{ 
    if(this == &m2)
        return *this;
    multi myobj = *this + m2;
    myobj.roommates += m2.roommates;
    return myobj;
}

// << >> - input and output
istream & operator >> (istream &in, multi &m2){
    m2.home::input(in);
    return in;
}

ostream & operator << (ostream &out, const multi & m2){
    m2. home::display(out);
    out << "Room Descriptions : " << "\n";
    // Range based for loop with const as of C++ 11
    for(const auto& i: m2.room_descriptions)
    {
        out << "                  : ";
        out << i << "\n";
    }
    out << "Credit Score            : " << m2.c_score << "\n";
    out << "Rent History(mo)        : " << m2.rent_hist << "\n";
    out << "Current Roommates       : " << m2.roommates << "\n";
    out << "House is Empty          : " << m2.empty_house << "\n";
    out << "Number of Bedrooms      : " << m2.bedrooms << "\n";
    out << "Number of Bathrooms     : " << m2.bathrooms << "\n";
    return out;
}


//Call parent to do their part.
// += add to price

// //--------------------------------------------------------------------------------
multi & multi::operator += (int price){
    home:: operator += (price); //***************************** TEST
    return *this;
}

// ==, != check price equality
int multi::operator == (const multi &m2) const{
    if(this == &m2)
        return 1;
    return this -> home:: operator == (m2);
}

int multi::operator != (const multi &m2) const{
    if(this == &m2)
        return 0;
    return m2. home:: operator != (m2);
    }

// <, <=, >, >= compare and return bool
bool operator < (const multi &m1, const multi &m2){
    if(&m1 == &m2)
        return 0;
    return  m1.home::less_than(m2);
}


bool operator <= (const multi &m1, const multi &m2){
    if(&m1 == &m2)
        return 1;
    return m1.home::less_equal(m2);
}

bool operator > (const multi &m1, const multi &m2){
    if(&m1 == &m2)
        return 0;
    return m1.home::greater_than(m2);
}

bool operator >= (const multi &m1, const multi &m2){
    if(&m1 == &m2)
        return 1;
    return m1.home::greater_equals(m2);
}

// Edit multi. Works with other edit functions.
int multi::edit(void){
    char answer;
    string temp;
    char ctemp;
    int changes = 0;
    int i = -1;
    
    do{
        cout << "What would you like to edit?\n";
        cout << "1. Primary Info (everything but the kitchen sink)\n"; 
        cout << "2. Tenant requirements (credit score, rent history)\n"; 
        cout << "3. House details (empty, # bedrooms, #bathrooms, room descriptions)\n";
        cout << "4. Exit Roomshare Editing Menu\n";
        
        cin >> answer;
        cin.ignore(100, '\n');
        if(answer == '1')
            changes += home::edit();
        
        if(answer == '2'){
            
            cout << "What credit score is required to rent?\n";
            cin >> c_score;
            while(cin.fail())
            {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid Input Please enter an integer\n";
                cin >> c_score;
            }
            cin.ignore(100, '\n');
            ++changes;
            
            cout << "How long of a rental history is required to rent (years)?\n";
            cin >> rent_hist;
            if(cin.fail()){
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid Input Please enter an integer\n";
                    cin >> rent_hist;
                }
            }
            else
                cin.ignore(100, '\n');
            ++changes;
        
        }
        
        
        if(answer == '3'){
            cout << "Enter room descriptions one at a time, and type 'done' when finished.\n";
            do
            {
                if(i > -1)
                {
                    room_descriptions.push_back(temp);
                    ++changes;
                }
                temp.clear();
                getline(cin, temp);
                ++i;
            }while(temp != "done");
            temp.clear();
            
            cout << "Is the house completely empty (y/n)\n";
            cin >> ctemp;
            cin.ignore(100, '\n');
            empty_house = (tolower(ctemp) == 'y');
            ++changes;
            ctemp = '\0';
            
            
            cout << "How many roommates can sign?\n";
            cin >> roommates;
            if(cin.fail()){
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid Input Please enter an integer\n";
                    cin >> roommates;
                }
            }
            else cin.ignore(100, '\n');
            ++changes;
            
            
            cout << "How many bedrooms are in the home?\n";
            cin >> bedrooms;
            if(cin.fail()){
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid Input Please enter an integer\n";
                    cin >> bedrooms;
                }
            }
            else cin.ignore(100, '\n');
            ++changes;
            
            cout << "How many bathrooms?\n";
            cin >> bathrooms;
            if(cin.fail()){
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid Input Please enter an integer\n";
                    cin >> bathrooms;
                }
            }
            else cin.ignore(100, '\n');
            ++changes;
        }
    }while(answer != '4');
    return changes;
}
