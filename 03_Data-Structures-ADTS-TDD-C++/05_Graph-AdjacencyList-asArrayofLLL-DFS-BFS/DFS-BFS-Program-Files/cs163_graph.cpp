#include "cs163_graph.h"
using namespace std;


//-----------------------------------------------------------------------------------------------
//Ryan Filgas
//Program_5
//Karla Fant
//3/10/2021
//
//FILENAME:
//cs163_graph.cpp
//
//The purpose of this assignment is to apply depth, and breadth first search techniques
//to a graph containing vertexes where each vertex has an edge pointing to another vertex.
//These techniques require a combination of recursion, and iteration. For this implementation
//recursive calls reside within while loops to do most of the work with some help from a wrapper
//function to hold data passed into the recursive call to keep track of visited vertices.
//
//-----------------------------------------------------------------------------------------------


/* Implement these three functions for this lab */
table::table(int size)
{
      //Allocate the adjacency list and set each
      //head pointer to NULL
  adjacency_list = new vertex[size];
  list_size = size;
  
  for(int i = 0; i < size; ++i)
  {
      adjacency_list[i].entry = NULL;
      adjacency_list[i].head = NULL;
  }
}

//Store the vertex at this location.
int table::insert_vertex(const journal_entry & to_add)
{
    journal_entry * temp;

    //Place your code here
    int i = 0;
    while(i < list_size && adjacency_list[i].entry)
        ++i;

    //we're at the first empty location or the last node;
    if(adjacency_list[i].entry)
        return 0; //List is full, return.
    else
    {
        temp = new journal_entry;
        temp -> copy_entry(to_add);
        adjacency_list[i].entry = temp;
        cout << "inserted vertiex into index: " << i << "\n";
        return 1;
    }
}

//Attach an edge to a vertex
int table::insert_edge(char * current_vertex, char * to_attach)
{
    //Attach this vertices edge to the specified vertex
    //vertex.insert edge
    int success = 0;
    node * temp;

    int connection1 = find_location(current_vertex);
    int connection2 = find_location(to_attach);

    if(connection1 != -1 && connection2 != -1)
    {
        temp = new node;
        temp -> adjacent = &adjacency_list[connection2];
        temp -> next = adjacency_list[connection1].head;
        adjacency_list[connection1].head = temp;
        success = 1;
    }
    return success;
}

//Display all vertices adjacent to the one specified
int table::display_adjacent(char * key_value)
{
    int success = 0;
    int i = 0;
    node * current;

    while( i < list_size && !adjacency_list[i].entry->compare(key_value))
        ++i;
    if(adjacency_list[i].entry->compare(key_value))
    {
        current = adjacency_list[i].head;
        while(current)
        {
            if(current -> adjacent)
                current -> adjacent -> entry -> display();
            current = current -> next;
            success = 1;
        }
    }
    return success;
}

//Find a location in the graph
//Consider this a helper function for all of the other member functions!
int table::find_location(char * key_value)
{
    int i = 0;

    while( i < list_size && !adjacency_list[i].entry->compare(key_value))
        ++i;
    if(adjacency_list[i].entry->compare(key_value))
        return i;
    else
        return -1;
}



//IS COMPLETE:
//Use to determine if there's a direct connection from each node to every other node.
//This function uses a breadth first searching technique. This means that a vertexes edges
//are all checked before calling the recursive function on the next edge. This will more efficiently
//check for a complete graph than a depth first search.The function will return 1 if the graph is
//complete, and 0 if it isn't.
int table::is_complete(void)
{
    int num_entries = get_num_entries();
    int visited_flags[num_entries];
    for(int i = 0; i < num_entries; ++i)
        visited_flags[i] = 0;
    vertex * current_vertex = &adjacency_list[0];
    if(!(current_vertex->head))
        return 0;
    return is_complete(current_vertex, visited_flags, num_entries);
}



// This is a recursive function for the above wrapper.
int table::is_complete(vertex * current_vertex, int visited_flags[], int &num_vertices)
{
    //These are temporary node pointers to assist with traversal.
    node * head = current_vertex->head;
    node * current = head;
    node * temp;

    //Initiate and clear temp flags for each recursive call.
    int temp_flags[num_vertices];
    for(int i = 0; i < num_vertices; ++i)
        temp_flags[i] = 0;

    //Variable keeps track of which edge in a vertexes edge list is currently being checked.
    int current_edge = 0;

    //Complete will be the default. Finding a contradiction is faster
    //than proving this true,so any contradiction will cause the function
    //to return false. The Success variable is multiplying rather than adding,
    //so a 0 returned as success *= (return_value) will return false up the stack.
    int success = 1;
    int vertex_index = 0;
    
    //CASE 1: Head is NULL.
    //The function doen't allow for visiting NULL unless it's failed.
    if(!head)
            return 0;

    //CASE 2: If we've been here before, return 1, and go back up the stack.Else trip visit flags.
    vertex_index = get_index(current_vertex);
    if(visited_flags[vertex_index] == 1)
        return 1;
    else
    {
        visited_flags[vertex_index] = 1;
        temp_flags[vertex_index] = 1;
    }

    //CASE 3: We haven't been here, and head isn't null. Iterate through the list in a while
    //loop, and if at any point the temp flags all show true, call the function on the next vertex
    //and return success. If the temp flags don't show true, a 0 will be returned, and the
    //function won't call itself on the next edge node.
    while(current)
    {
        //Get vertex index for current edge.
        current_edge = get_index(current -> adjacent);
        //Set flag for current edge.
        temp_flags[current_edge] = 1;

        //If all vertexes are visited, the sum will be the number of vertices.
        if((find_sum(temp_flags, num_vertices)) == num_vertices)
        {
            temp = head;

            //If at any point a 0 is returned, the function fails. Stop Executing.
            while(temp && success)
            {
                //Once each node has been checked, traverse for each vertex. If a 0 is
                //returned, it means that this vertex didn't have a path to all nodes.
                success *= is_complete((temp -> adjacent), visited_flags, num_vertices);
                temp = temp -> next;
            }
        }
        //Traverse to next node.
        current = current -> next;
    }
    
    //POST CASE:
    //If vertex doesn't contain all other vertexes as edges, return 0;
    if((find_sum(temp_flags, num_vertices)) != num_vertices)
        success = 0;
    return success;
}


//IS CONNECTED:
//This solution works to determine connection assuming an undirected graph. If the path is directed
//it will tell you if there is an indirect edge list leading from each node to every other node.
//You forgot to make sure there was a way back from the swiss alps! OH NO!
//
//This function can easily be modified to output the edge list of each vertex,
//or output any locations that aren't reachable from the other vertex locations.
//
//If you simply wish to know if there are any isolated nodes, comment out the recursive call.
//
//This function will return 1 if the graph is connected, and 0 if it isn't. If the graph is directed,
//it will return true if there is a path from each node to every other node, and false otherwise.

int table::is_connected(void)
{
    int num_entries = get_num_entries();
    //Make flags to record visits for overall traversals.
    int visited_flags[num_entries];
    int valid_paths = 0;

    //Vertex pointer to simplify readability.
    vertex * current_vertex;
    
    for(int i = 0; i < num_entries; ++i)
    {
        //Clear flag list.
        for(int l = 0; l < num_entries; ++l)
            visited_flags[l] = 0;

        current_vertex = &adjacency_list[i];

        //If vertex or head is null, there is an isolated node. This is not connected.
        if(!current_vertex || !(current_vertex->head))
            return 0;

        //comment this recursive call out to only check for isolated nodes.
        valid_paths += is_connected(current_vertex, visited_flags, num_entries);
    }
    //If there is a valid path from each node, this graph is connected. If we only need to see one valid
    //path for an undirected graph, the for loop isn't necessary. Simply call the recursive function on a single vertex,
    //and use the return from the recursive function, as the return for the wrapper.
    return (valid_paths == num_entries);
}


int table::is_connected(vertex * current_vertex, int visited_flags[], int &num_vertices)
{
    //Vertex is NULL in edge list because of a vertex deletion. This doesn't mean the graph isn't connected.
    if(!current_vertex)
        return 1;

    //These are temp variables to assist with traversal.
    node * head = current_vertex->head;
    node * current = head;

    //CASE 1: Head is NULL.
    if(!head)
            return 0;

    //Index to keep track of flag variable.
    int vertex_index = get_index(current_vertex);

    //CASE 2: If we've been here before, return 1, and go back up the stack.Else trip visit flags.
    if(visited_flags[vertex_index] == 1)
        return 1;
    else visited_flags[vertex_index] = 1;

    //Visit each edge in list.
    while(current)
    {
        // If we haven't visted each vertex, call the function on the next edge.
        // It will mark visits where they happen, so we don't need
        // to catch the return.  We still need !head to return false,
        // but that doesn't mean the function fails, so we don't want it returning
        // a false negative. The test for success will be at the end, and will return
        // success or failure to the calling routine.
        //
        // If we haven't visited every node, call the function on the current edge.
        if((find_sum(visited_flags, num_vertices)) != num_vertices)
            is_connected((current -> adjacent), visited_flags, num_vertices);

        //proceed to the next edge.
        current = current -> next;
    }
    //The work has been done, and flags have been marked. Return true if all vertices have been visited.
    return((find_sum(visited_flags, num_vertices)) == num_vertices);
}



//display_vertex_depth_first
//Assume this is a public function, where the user needs to find and display their data.
//Use a depth first search to do so, and return false if unsuccessful.
int table::display_vertex_depth_first(char * key_value)
{
    // Get the number of entries, so we will know if there are unconnected vertices.
    // For efficiency, this could be passed in by the client, or a class member, 
    // but for the purposes of this function,it needed to be self contained.
    int num_entries = get_num_entries();

    //Set flags for each vertex visit.
    int visited_flags[num_entries];
    vertex * current_vertex;

    //For each vertex, set its visit flag to 0
    for(int l = 0; l < num_entries; ++l)
        visited_flags[l] = 0;

    //Return false if the given node has no edges.
    current_vertex = &adjacency_list[0];
    if(!current_vertex || !(current_vertex->head))
            return 0;

    //Enter recursive call.
    return display_vertex_depth_first(key_value, current_vertex, visited_flags, num_entries);
}


//This is a recursive function for the above wrapper.
int table::display_vertex_depth_first(char * key_value, vertex * current_vertex, int visited_flags[], int &num_vertices)
{
    //Vertex is null, return failure.
    if(!current_vertex)
        return 0;

    //Make pointers for use in traversal.
    node * head = current_vertex->head;
    node * current = head;

    //Return success to calling function.
    int success = 0;
    //Use index of vertex to trip flags.
    int vertex_index = 0;

    
    //CASE 1: Entry found?
    //If we found the entry we're looking for, display it.
    if((current_vertex -> entry -> compare(key_value)))
        return current_vertex -> entry -> display();

    //If this isn't the right entry and we've visited every node, return failure.
    else if((find_sum(visited_flags, num_vertices)) == num_vertices || !head)
            return 0;

    //Get the address for this vertex.
    vertex_index = get_index(current_vertex);
    
    //CASE 2: If we've been here before, return 0, and go back up the stack.Else trip visit flags and contine to recursive call.
    if(visited_flags[vertex_index] == 1)
        return 0;
    else visited_flags[vertex_index] = 1;

    //CASE 3: We haven't been here, keep searching. The success variable will remain 0 until a match is found.
    while(current && success == 0)
    {
        //Enter recursive call, and capture the return.
        success = display_vertex_depth_first(key_value, (current -> adjacent), visited_flags, num_vertices);

        //Traverse to next node.
        current = current -> next;
    }
    return success;
}



//Helper function to find the sum of a list of ints.
int table::find_sum(int list[], int &size)
{
    //Keep track of sum.
    int newsum = 0;
    // For each index, add it to the sum variable, and return the sum at the end.
    for(int i = 0; i < size; ++i)
        newsum += list[i];
   return newsum; 
}



//Helper function to get the index of a vertex given an edge.
int table::get_index(vertex * edge)
{
    //This is a variable for looping.
    int i = 0;

    //While i is less than the list size, keep checking each vertex to see if the edge matches
    //the edge passed in.If it does, stop searching.
    while( i < list_size && &adjacency_list[i] != edge)
        ++i;

    //If this edge has the same address as the one passed in, return its index.
    if(&adjacency_list[i] == edge)
        return i;
    return -1;
}



//Helper function to count the number of entries. Couldn't add variables to the class,
//and as we aren't turning in main, I couldn't store that data in a struct held by the client.
int table::get_num_entries()
{
    int i = 0;
    int count = 0;
    while( i < list_size)
    {
        //If there is an entry, count it.
        if(adjacency_list[i].entry)
            ++count;
        ++i;
    }
    return count;
}
