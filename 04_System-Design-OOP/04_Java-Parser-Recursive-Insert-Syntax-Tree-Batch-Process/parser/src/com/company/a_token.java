package com.company;
public class a_token {

// Ryan Filgas
// 6/3/2020
// Program 4
// Prof. Karla Fant
//
// The purpose of this file is to serve as the base class for different token types.
// It will also hold the references to point to other nodes, while the specific
// connections will be controlled by each individual token with a recursive insert.
// This class currently contains functions to add and display.

    // Token references
    protected a_token right;
    protected a_token left;

    // Kid Program input
    protected String my_text;

    public void add(String to_add){
        my_text = to_add;
    }
    public void display_text(){
        System.out.print(my_text);
    }

    // constructor
    public a_token() {
        this.right = null;
        this.left = null;
    }
}
