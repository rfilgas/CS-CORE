#include <iostream>
#include <vector>
#include<string>
using namespace std;

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
// Further explanation of the included classes is below.

// The node class manages the node function of a larger
// data structure. The base class of the hierarchy is derived
// from a node. This is to separate the non object oriented
// functions from the OO hierarchy.
//
class node
{
    public:
        node();
        ~node();

        // Fetch pointers
        class home *& get_left();
        class home *& get_right();
        class home *& get_parent();

        // Set variables to simulate a red black tree
        void set_red(int is_red);
        void set_black(int is_black);
        int check_red(void);
        int check_black(void);

        //check left  or right for null;
        int check_left(void);
        int check_right(void);
        int check_parent(void);

        // Set and check is left child variable.
        // allow for opposite to make coding easier.
        void set_left_child(int value);
        void set_right_child(int value);
        int is_left_child(void);
        int is_right_child(void);

    protected:

        //node pointers
        home * right;
        home * left;
        home * parent;

        //black is the default, so red is initiated to 0;
        bool red;
        bool is_left;
};


// The purpose of the home class is to
// be a base class for derived objects and handle
// in common items such as price and username.
// It also manages things that may be important
// to a potential renter like number of bathrooms,
// or whether smoking or pets are allowed.
//
//---HOME-------
class home: public node
{
    public:

        home();
        virtual ~home();

        // =  overide op1 with op2
        home & operator = (const home &h2);

        // +  use the data from one, and combine greatest 
        // denominators. No smoking for 1 means no smoking 
        // for both etc.
        home operator + (const home &h2) const; 

        // << >> - input and output
        friend istream & operator >> (istream &in, home &h2);
        istream & input(istream &in);
        friend ostream & operator << (ostream &out, const home & h2);
        ostream & display(ostream & out) const;

        // += add to price
        home & operator += (int aprice);
        
        // ==, != check price equality
        int operator == (const home &h2) const;
        int operator != (const home &h2) const;

        // <, <=, >, >= compare and return bool
        // need virtual helper for each of these
        friend bool operator < (const home & h1, const home &h2);
        bool less_than(const home &op2) const;
        friend bool operator <= (const home &h1, const home &h2);
        bool less_equal(const home &op2) const;
        friend bool operator > (const home &h1, const home &h2);
        bool greater_than(const home &op2) const;
        friend bool operator >= (const home &h1, const home &h2);
        bool greater_equals(const home &op2) const;

        // Used by operator overloading funtions
        int edit_user(string &user, string &my_contact_info);
        int edit_place(vector<string> &my_ammenities, string &my_neighborhood, string &my_app_process);
        int edit_details(int aprice, int asmoking, int amonths_duration, int apets);
        int edit_basics(int isfurnished, int haslaundry, int hasdishwasher);

        // Independent functions
        virtual int edit(void);
        void display_key(void) const;
        int is_username(string to_match);

    private:
        string username;
        string contact_info;
        vector<string> ammenities; // List of amenities
        string neighborhood; // neghborhood it's located in
        string app_process; //application process

        int price; //cost - this the sorting variable
        int smoking; // smoking allowed
        int months_duration; //Term of stay
        int pets; // accepts pets
        int furnished; // in unit furniture
        int laundry; // in unit laundry
        int dishwasher; // in unit dishwasher
};


// The purpose of this class is to manage items relavant
// to a shared bedroom. It manages things like live/work
// priorities, whether the roommate should be
// a friend, or whether parties are appreciated.
//---SHARE------ This is a shared bedroom.
class share: public home
{
    public:
        share();
        ~share();

        //DO HALF HERE AND CALL PARENT
        // =  overide op1 with op2
        share & operator = (const share &s2);

        // +  use the data from one, and combine greatest 
        // denominators. No smoking for 1 means no smoking 
        // for both etc.
        share operator + (const share &s2) const; 

        // << >> - input and output
        friend istream & operator >> (istream &in, share &s2);
        friend ostream & operator 
            << (ostream &out, const share & s2);


        //CALL PARENT
        // += add to price
        share & operator += (int price);
        
        // ==, != check price equality
        int operator == (const share &s2) const;
        int operator != (const share &s2) const;

        // <, <=, >, >= compare and return bool
        friend bool operator < (const share &s1, const share &s2);
        friend bool operator <= (const share &s1, const share &s2);
        friend bool operator > (const share &s1, const share &s2);
        friend bool operator >= (const share &s1, const share &s2);
        
        //Virtual
        int edit(void);

    private:
        int a_friend; // Looking for a friend roommate.
        int live_work; // Partial work for rent arrangement
        int parties; // Parties acceptable.
        vector<string> preferences;
};



//---ROOM------- This is a room in a house.
class room: public home
{
    public:
        room();
        ~room();

        //DO HALF HERE AND CALL PARENT
        // =  overide op1 with op2
        room & operator = (const room r2);

        // +  use the data from one, and combine greatest denominators.
        // no smoking for 1 means no smoking for both etc.
        room operator + (const room &r2) const; 

        // << >> - input and output
        friend istream & operator >> (istream &in, room &r2);
        friend ostream & operator << (ostream &out, const room & r2);

        //CALL PARENT
        // += add to price
        room & operator += (int price);
        
        // ==, != check price equality
        int operator == (const room &r2) const;
        int operator != (const room &r2) const;

        // <, <=, >, >= compare and return bool
        friend bool operator < (const room &r1, const room &r2);
        friend bool operator <= (const room &r1, const room &r2);
        friend bool operator > (const room &r1, const room &r2);
        friend bool operator >= (const room &r1, const room &r2);

        //Virtual
        int edit(void);

    private:
        vector<string> preferences; // General preferences.
        string description; // room description
        int rent_hist; // Years required rent history
};


// The purpose of this class is to manage multiple rooms
// in the same location going up for rent. This could be a 
// couple rooms, or a while house. It has stricter requirements.
//---HOUSE------- This is multiple rooms or a house.
class multi: public home
{
    public:

        // ------------------------------------------------------------------------------
        //These functions do partial work and call the parent class for the rest.
        // =  overide op1 with op2
        multi & operator = (const multi &m2);

        // +  use the data from one, and combine greatest 
        // denominators. No smoking for 1 means no smoking 
        // for both etc.
        multi operator + (const multi &m2) const; 

        // << >> - input and output
        friend istream & operator >> (istream &in, multi &m2);
        friend ostream & operator << (ostream &out, const multi & m2);
        // ------------------------------------------------------------------------------


        // ------------------------------------------------------------------------------
        //Call parent to do their part.
        // += add to price
        multi & operator += (int price);
        
        // ==, != check price equality
        int operator == (const multi &m2) const;
        int operator != (const multi &m2) const;

        
        // <, <=, >, >= compare price  and return bool
        friend bool operator < (const multi &m1, const multi &m2);
        friend bool operator <= (const multi &m1, const multi &m2);
        friend bool operator > (const multi &m1, const multi &m2);
        friend bool operator >= (const multi &m1, const multi &m2);


        //Virtual
        int edit(void);
        // ------------------------------------------------------------------------------

    private:
        vector<string> room_descriptions;
        int c_score; // Required credit score for approval
        int rent_hist; // Rent history required in years.
        int roommates; // Number of roomies if applicable.
        int empty_house; // full house available
        int bedrooms; //num bedrooms
        int bathrooms; //num_bathrooms
};





