#include "home.h"
// Ryan Filgas
// CS202
// Karla Fant
// Program 3
// 5/12/2021
//
//
// The purpose of the tree class is to manage a red-black tree
// and provide an easily accessed data structure for the
// posting board. As this is a red black tree, the tree will
// provide for the ability to do efficient searches of the
// data structure.
//
// Below is also the contents of the board class. The board class
// is here to manage the client side of this program and is derived
// from the tree class.

class tree
{
    public:

        tree();
        tree(const tree &source); 
        ~tree();
        int destroy(home *&aroot);

        // Add a home to a tree, and set a tree = to another tree.
        tree & operator += (home *& to_add);
        tree & operator = (const tree &h2);

        // Add a home to a tree or vice a versa, and store the result in a copy.
        friend tree operator + (const tree & t1, const home &t2);
        friend tree operator + (const home & t1, const tree &t2);

        // Add a home to a tree.
        void add(home * &to_add); 
        //Display home objects in order.
        int full_inorder_display(void);
        int inorder_display(void);
        //get height of tree
        int height(void);

    protected:
        int retrieve(home * & aroot, string name, home * &to_fill);
        int copy_tree(home * &copy, home * &source);
        int check_type(home * to_check);

        //-------------------------------------------------------
        //ADD
        void add(home * &parent, home * &to_add);
        // Add Helpers: Pass in the home that violates rules.
        void correct(home * &current);
        void correct_tree(home * &vhome);
        void rotate(home * &vhome);
        void left_rotate(home * &vhome);
        void right_rotate(home * &vhome);
        void left_right_rotate(home * &vhome);
        void right_left_rotate(home * &vhome);
        //-------------------------------------------------------

        //-------------------------------------------------------
        //Display ALL
        int inorder_display(home * &aroot);
        int full_inorder_display(home * &aroot);
        //-------------------------------------------------------

        //-------------------------------------------------------
        //Display all by price
        int display_greater(home * & aroot, home * to_match);
        int display_not_equals(home * & aroot, home * to_match);
        int display_equals(home * & aroot, home * to_match);
        int display_lesser_equals(home * & aroot, home * to_match);
        int display_lesser(home * & aroot, home * to_match);
        int display_greater_equals(home * & aroot, home * to_match);
        //-------------------------------------------------------

        // Get tree height, and return height
        int height(home * &aroot);
        // Get black nodes to determine tree balance. Not used.
        int count_black(home * &current);
        // Size of the tree.
        int size;

        home * root;
        home * temphome;
};



// Manage main menu
class board: public tree // Would be client
{
    public:
        // add, edit, search, display all, add to favorites
        void main_menu(void);
        // add_posts, display all, search, delete all
        void setup_menu(void);
        void test_tree(void);
        void display_price_matches(void);

    protected:
        void create_post(void);
        //No time to implement favorites.
        void display_favorites(void);
        vector<home> favorites;
};
