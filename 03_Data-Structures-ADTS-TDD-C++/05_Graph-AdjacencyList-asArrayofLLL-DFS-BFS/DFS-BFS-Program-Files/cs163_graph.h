#include "cs163_entry.h"

//-----------------------------------------------------------------------------------------------
//Ryan Filgas
//Program_5
//Karla Fant
//3/10/2021
//
//FILENAME:
//cs163_graph.h
//
//The purpose of this assignment is to apply depth, and breadth first search techniques
//to a graph containing vertexes where each vertex has an edge pointing to another vertex.
//These techniques require a combination of recursion, and iteration. For this implementation
//recursive calls reside within while loops to do most of the work with some help from a wrapper
//function to hold data passed into the recursive call to keep track of visited vertices.
//
//-----------------------------------------------------------------------------------------------


//Compare these structs to the ones in your answers on Page #1
struct vertex
{
       journal_entry * entry;        //NULL, if the vertex isn't set
       struct node * head;           //edge list
};

struct node
{
       vertex * adjacent;	  //Additional data would be needed
                              //for a weighted graph
       node * next;
};



class table
{
      public:
            /* Implement these three functions for this lab */ 
             table(int size=5);                                //Step 6
             int insert_vertex(const journal_entry & to_add);  //Step 6
             int find_location(char * key_value);              //Step 7
             int insert_edge(char * current_vertex, char * to_attach); //Step 7
             int display_adjacent(char * key_value);           //Step 8


             //MY FUNCTIONS----------------------------------------------------------------------------
             
             //Determine if a graph is complete. Return 1 if true, and 0 if false. This uses breadth first search.
             int is_complete(void);
             int is_complete(vertex * current_vertex, int visited_flags[], int &num_vertices);

             //Determine if an undirected graph is connected, or if a directed graph has a path from each node to
             //every other node. Return 1 for true, and 0 for false. This uses depth first search.
             int is_connected(void);
             int is_connected(vertex * current_vertex, int visited_flags[], int &num_vertices);

             //Use depth first search to find an entry, and display it. Return false if the entry couldn;t be found.
             int display_vertex_depth_first(char * key_value, vertex * current_vertex, int visited_flags[], int &num_vertices);
             int display_vertex_depth_first(char * key_value);

             //END MY FUNCTIONS----------------------------------------------------------------------------
  
            /* These functions are ALREADY implemented for you */
             ~table(void);    // Already implemented in methods.o   
             int display_all(void) const; /*This is already implemented */
      private:
              //HELPER FUNCTIONS--------------------------------------------------------------------------
              
              //Get sum of flag list.
              int find_sum(int list[], int &size);

              //Get index from a vertex address.
              int get_index(vertex * edge);

              //Get number of entries in vertex list.
              int get_num_entries(void);

              //END HELPER FUNCTIONS--------------------------------------------------------------------------

              vertex * adjacency_list;
	          int list_size;

};


