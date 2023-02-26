#include "tree.h" 
// RYAN FILGAS
// CS202
// KARLA FANT
// PROGRAM 3
// 5/19/2021
//
//
// The purpose of tree.cpp is to manage a red_black tree of home *
// objects. Each object can be of three derived classes: multi,
// room, and share. The tree works like a normal binary tree until
// rules of a red black tree are violated, then it will rotate
// the nodes to balance the tree. Included functions are in a snap
// of the h file below.

/*
int destroy(home *&aroot);
tree & operator += (home *& to_add);
tree & operator = (const tree &h2);

friend tree operator + (const tree & t1, const home &t2);
friend tree operator + (const home & t1, const tree &t2);

void add(home * &to_add); 
int full_inorder_display(void);
int inorder_display(void);
int height(void);

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

// Get data about the tree.
int height(home * &aroot);
int count_black(home * &current);
int size;

home * root;
home * temphome;
*/

tree::tree():size(0), root(NULL), temphome(NULL){}



tree::~tree(){
    if(root == NULL)
        return;
    if(temphome){
        delete temphome;
        temphome = NULL;
    }
    destroy(root);
        return;
}


// Destroy a binary tree by recursing and deleteing on the way back.
int tree::destroy(home *&aroot){
    if(aroot == NULL)
        return 0;
    int left = destroy(aroot -> get_left());
    int right = destroy(aroot -> get_right());
    delete aroot;
    aroot = NULL;
    return (1 + left + right);
}



//copy constructor
tree::tree(const tree &source)
{
    root = new home;
    home * temp = root;
    home * rsource = source.root;
    copy_tree(temp, rsource);
}


//copy a binary tree from source to copy
int tree::copy_tree(home * &copy, home * &source){
    if(source == NULL)
        return 0;
    home * cright = copy -> get_right();
    home * cleft = copy -> get_left();
    home * sright = source -> get_right();
    home * sleft = source -> get_left();

    int type = check_type(source);
    if(type == 1)
        copy = new room;
    else if(type == 2)
        copy = new share;
    else if(type == 3)
        copy = new room;
    *copy = *source;

    int lcount = copy_tree(cleft, sleft);
    int rcount = copy_tree(cright, sright);
    return 1 + lcount + rcount;
}



//-----ADD-----------------------------------------------
// Add a pre-created home object to the binary tree.
void tree::add(home *& to_add){
    if(root == NULL)
    {
        root = to_add;
        ++size;
        root -> set_black(1);
        return;
    }
    add(root, to_add);
    ++size;
    return;
}


// Use the add function to add a home * to a tree
tree & tree::operator += (home *& to_add){
    add(to_add);
    return *this;
}


// copy one tree to another tree
tree & tree::operator = (const tree &h2){
    if(root == h2.root)
        return *this;
    if(root != NULL)
        destroy(root);
    root = new home;
    home * copy = root;
    home * source = h2.root;
    copy_tree(copy, source);
    return *this;
}


// Add make a copy, set it equal to the tree, and add the home, returning a copy.
tree operator + (const tree & t1, const home &t2){
    home  * hcopy = new home(t2);
    tree copy(t1);
    copy += hcopy;
    return copy;
}

// Add make a copy, set it equal to the tree, and add the home, returning a copy.
tree operator + (const home & t1, const tree &t2){
    home  * hcopy = new home(t1);
    tree copy(t2);
    copy += hcopy;
    return copy;
}


// Dynamic cast to find the object type.
int tree::check_type(home * to_check)
{
    room * aroom = dynamic_cast <room*>(to_check);
    share * ashare = dynamic_cast <share*>(to_check);
    multi * amulti = dynamic_cast <multi*>(to_check);
    if(aroom != NULL)
    {
        aroom = NULL;
        return 1;
    }
    if(ashare != NULL)
    {
        ashare = NULL;
        return 2;
    }
    if(amulti != NULL)
    {
        amulti = NULL;
        return 3;
    }
    else return 0;
}



// Pass in parent to add to, and new home
void tree::add(home * &parent, home * &to_add){

    if(*to_add >= *parent)
    {
        if(parent->check_right() == 0){
            parent -> get_right() = to_add;
            to_add -> get_parent() = parent;
            to_add->set_left_child(0);
            to_add->set_black(0);
            //return;
        }
        else add(parent -> get_right(), to_add);
    }

    else
    {
        if(parent->check_left() == 0){
            parent -> get_left() = to_add;
            to_add -> get_parent() = parent;
            to_add->set_left_child(1);
            to_add->set_black(0);
           // return;
        }
        else add(parent -> get_left(), to_add);
    }
    correct(to_add);
    return;
}



// Check the current home for rule violations.
// and make corrections if nessesary.
void tree::correct(home * &current){
    if(current == NULL)
        return;
    if(current == this ->root)
    {
        return;
    }
   if(current->check_black() == 0 && current -> get_parent() -> check_black() == 0) 
       correct_tree(current);
    correct(current -> get_parent());
    return;
}



// Helpers: Pass in the home that violates rules.
void tree::correct_tree(home * &vhome){
        home * grandparent = NULL;
    if(vhome -> get_parent() && vhome -> get_parent() -> get_parent())
        grandparent = vhome -> get_parent() -> get_parent();


    if(vhome -> get_parent() -> is_left_child()){
        if(! (grandparent -> check_right()) || (grandparent -> get_right() -> check_black()))
            return rotate(vhome);

        if(grandparent -> check_right())
            grandparent -> get_right()-> set_black(1);
        grandparent -> set_black(0);
        vhome -> get_parent() -> set_black(1);
        if(root -> check_black() == 0)
            root -> set_black(1);
        return;
    }
    
    if(vhome -> get_parent() -> is_right_child()){
        if(!(grandparent -> check_left()) || (grandparent -> get_left() -> check_black()))
            return rotate(vhome);

        if(grandparent -> check_left())
            grandparent -> get_left()-> set_black(1);
        grandparent -> set_black(0);
        if(root -> check_black() == 0)
            root -> set_black(1);
        
        vhome -> get_parent() -> set_black(1);
        return;
    }
}


void tree::rotate(home * &vhome){
    // left side
    home * grandparent = vhome -> get_parent() -> get_parent();
    if(vhome -> is_left_child()){

        if(vhome -> get_parent() -> is_left_child()){
            right_rotate(grandparent);
            vhome -> set_black(0);
            vhome -> get_parent() -> set_black(1);

            if(vhome -> get_parent() -> check_right())
                vhome -> get_parent() -> get_right() -> set_black(0);
            return;
        }

        right_left_rotate(grandparent);
        vhome -> set_black(1);
        vhome -> get_right() -> set_black(0);
        vhome -> get_left() -> set_black(0);
        return;
    }
    
    // right side
    if(vhome -> is_right_child()){
        if(vhome -> get_parent() -> is_right_child()){
            left_rotate(grandparent);
            vhome -> set_black(0);
            vhome -> get_parent() -> set_black(1);

            if(vhome -> get_parent() -> check_left())
                vhome -> get_parent() -> get_left() -> set_black(0);
            return;
        }

        left_right_rotate(grandparent);
        vhome -> set_black(1);
        vhome -> get_left() -> set_black(0);
        vhome -> get_right() -> set_black(0);
        return; }
}



void tree::left_rotate(home * &vhome){
    home * temp = vhome -> get_right();
    (vhome -> get_right()) = (temp -> get_left());

    if((vhome -> check_right()) != 0){
       (vhome -> get_right() -> get_parent()) = vhome;
        vhome -> get_right() -> set_left_child(0);
    }

    if(vhome == root){
        root = temp;
        temp -> get_parent() = NULL;
    }

    else{
        (temp -> get_parent()) = (vhome -> get_parent());
        if(vhome -> is_left_child()){
            temp -> set_left_child(1);
            (temp -> get_parent() -> get_left()) = temp;
        }

        else{
            temp -> set_left_child(0);
            (temp -> get_parent() -> get_right()) = temp;
        }
    }

        (temp -> get_left()) = vhome;
        vhome -> set_left_child(1);
        (vhome -> get_parent()) = temp;
        return;
}



//the other is good check this one
void tree::right_rotate(home * &vhome){
    home * temp = vhome -> get_left();
    (vhome -> get_left()) = (temp -> get_right());

    if(vhome -> check_left() != 0){
        (vhome -> get_left() -> get_parent()) = vhome;
        vhome -> get_left() -> set_right_child(0);
    }

    if(vhome == root){
        root = temp;
        (temp -> get_parent()) = NULL;
    }

    else{
        (temp -> get_parent()) = (vhome -> get_parent());
        if(vhome -> is_right_child()){
            temp -> set_right_child(1);
            (temp -> get_parent() -> get_right()) = temp;
        }

        else{
            temp -> set_right_child(0);
            (temp -> get_parent() -> get_left()) = temp;
        }
    }

        (temp -> get_right()) = vhome;
        vhome -> set_right_child(1);
        (vhome -> get_parent()) = temp;
    return;
}



void tree::left_right_rotate(home * &vhome){
    home * aleft = vhome -> get_left();
    left_rotate(aleft);
    right_rotate(vhome);
    return;

}



void tree::right_left_rotate(home * &vhome){
    home * rightptr = vhome -> get_right();
    right_rotate(rightptr);
    left_rotate(vhome);
    return;
}


// get tree height by recursing through both
// sides of the tree and returning the
// longest path.
int tree::height(void){
    if(root == NULL)
        return 0;
    return (height(root) -1);
}



int tree::height(home * &aroot){
    if(aroot == NULL)
        return 0;
    home * my_left = aroot -> get_left();
    home * my_right = aroot -> get_right();
    int left_height = 1 + height(my_left);
    int right_height = 1 + height(my_right);
    if(left_height > right_height)
        return left_height;
    else return right_height;
}


// Display each node, then recurse left followed
// by right.
int tree::inorder_display(void){
    if(root == NULL)
        return 0;
    return inorder_display(root);
}


// Display keys
int tree::inorder_display(home * &aroot) {
    if(!aroot)
        return 0;
    home * aright = aroot -> get_right();
    home * aleft = aroot -> get_left();
    int counter = inorder_display(aleft);
    ++counter;
    aroot -> display_key();
    cout << " ";
    counter += inorder_display(aright);
    return counter;
}



// display all inner variables, not just key. 
int tree::full_inorder_display(void){
    if(root == NULL)
        return 0;
    return full_inorder_display(root);
}



int tree::full_inorder_display(home * &aroot) {
    if(!aroot)
        return 0;
    home * aright = aroot -> get_right();
    home * aleft = aroot -> get_left();
    int counter = full_inorder_display(aleft);
    ++counter;
    cout << *aroot;
    cout << "\n";
    counter += full_inorder_display(aright);
    return counter;
}


// Display all nodes that have a greater price
int tree::display_greater(home * & aroot, home * to_match){
    if(aroot == NULL)
        return 0;
    int countleft = 0;
    int countright = 0;
    home * left = aroot -> get_left();
    home * right = aroot -> get_right();
    countleft = display_greater(left, to_match);
    if(*to_match < *aroot){
        cout << *aroot;
        ++countleft;
    }
    countright = display_greater(right, to_match);
    return countright + countleft;
}



// Display all nodes that have a greater than or equal price
int tree::display_greater_equals(home * & aroot, home * to_match){
    if(aroot == NULL)
        return 0;
    int countleft = 0;
    int countright = 0;
    home * left = aroot -> get_left();
    home * right = aroot -> get_right();
    countleft = display_greater_equals(left, to_match);
    if(*to_match <= *aroot){
        cout << *aroot;
        ++countleft;
    }
    countright = display_greater_equals(right, to_match);
    return countright + countleft;
}



// Display all nodes that have a lesser price
int tree::display_lesser(home * & aroot, home * to_match){
    if(aroot == NULL)
        return 0;
    int countleft = 0;
    int countright = 0;
    home * left = aroot -> get_left();
    home * right = aroot -> get_right();
    countleft = display_lesser(left, to_match);
    if(*to_match > *aroot){
        cout << *aroot;
        ++countleft;
    }
    countright = display_lesser(right, to_match);
    return countright + countleft;
}



// Display all nodes that have a lesser than or equal price
int tree::display_lesser_equals(home * & aroot, home * to_match){
    if(aroot == NULL)
        return 0;
    int countleft = 0;
    int countright = 0;
    home * left = aroot -> get_left();
    home * right = aroot -> get_right();
    countleft = display_lesser_equals(left, to_match);
    if(*to_match >= *aroot){
        cout << *aroot;
        ++countleft;
    }
    countright = display_lesser_equals(right, to_match);
    return countright + countleft;
}



// Display all nodes that have an equal price
int tree::display_equals(home * & aroot, home * to_match){
    if(aroot == NULL)
        return 0;
    int countleft = 0;
    int countright = 0;
    home * left = aroot -> get_left();
    home * right = aroot -> get_right();
    countleft = display_equals(left, to_match);
    if(*to_match == *aroot){
        cout << *aroot;
        ++countleft;
    }
    countright = display_equals(right, to_match);
    return countright + countleft;
}



// Retrieve a node by name
int tree::retrieve(home * & aroot, string name, home * &to_fill){
    if(aroot == NULL)
        return 0;
    home * right = aroot -> get_right();
    home * left = aroot -> get_left();
    if(aroot -> is_username(name)){
        to_fill = aroot;
        return 1;
    }
    int success = retrieve(right, name, to_fill);
    success += retrieve(left, name, to_fill);
    return success;
}



// Display all nodes that have a not equal price
int tree::display_not_equals(home * & aroot, home * to_match){
    if(aroot == NULL)
        return 0;
    int countleft = 0;
    int countright = 0;
    home * left = aroot -> get_left();
    home * right = aroot -> get_right();
    countleft = display_not_equals(left, to_match);
    if(*to_match != *aroot){
        cout << *aroot;
        ++countleft;
    }
    countright = display_not_equals(right, to_match);
    return countright + countleft;
}



