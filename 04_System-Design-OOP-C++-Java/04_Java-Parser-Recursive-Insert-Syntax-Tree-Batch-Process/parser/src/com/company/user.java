package com.company;
import java.util.*;


// Ryan Filgas
// 6/3/2020
// Program 4
// Prof. Karla Fant


//The purpose of this file is to manage the user interface for the parser. It has
// functions display menu, menu select and setup. Display menu prints each entry in
// the my_menu variable. Menu select takes in user input to call functions to drive
// the program, and setup takes in filenames from the user before updating the
// number of files, and storing the filenames into the filenames variable.

public class user {
    //Menu options. To maintain the menu, add to the list, and update the switch statement in menu_select.
    protected List<String> my_menu = Arrays.asList("Exit", "Load File(s)", "Parse File(s)", "Display All Parsed Files", "Display Token Text", "Display Syntax Errors", "Display Token Types");
    protected int menu_size = my_menu.size();

    //File info to be updated
    protected ArrayList<String> filenames = new ArrayList<>();
    protected int NUM_FILES;

    //Parse object to store parsed data into arrays. This is the workhorse.
    public parse my_program = new parse();

    // Token list to store programs before loading into tree.
    ArrayList<ArrayList<ArrayList<a_token>>> program_list;

    // Run the program.
    public void initiate() throws Exception {
        while(menu_select() != 0);
    }

    // Display each index in the my_menu variable along with the option number.
    public void display_menu(){
        System.out.println("\nThis is a Parser. It parses files for no good dirty rotten meddling kids.\n");
        for(int i = 0; i < menu_size; ++i){
            System.out.println((i) + ". " + my_menu.get(i));
        }
        System.out.println("\n");
    }



    // Let user select an option, and call proper function. Return choice so 0 can quit.
    protected int menu_select() throws Exception {
        int choice;

        display_menu();
        Scanner myObj = new Scanner(System.in);  // Create a Scanner object

        System.out.println("Make sure to load(1) and parse(2) before display.");
        System.out.print("Select a choice: ");

        //Read user input.
        choice = myObj.nextInt();
        System.out.print("\n");

        // ("Exit", "Load File(s)", "Parse File(s)", "Display All Parsed Files", "Display Token Text", "Display Syntax Errors", "Display Token Types");
        switch (choice) {
            case 0 -> System.out.println("Thanks for coming!");
            case 1 -> this.setup();
            case 2 -> program_list = my_program.parse_file(filenames);
            case 3 -> my_program.display_input();
            case 4 -> my_program.display_tokens();
            case 5 -> my_program.display_errors();
            case 6 -> my_program.display_token_types();
        }
        return choice;
    }


    // Get filenames from user and load them into filenames array.
    protected void setup() {
        String temp = "";
        Scanner scan = new Scanner(System.in);  // Create a Scanner object

        System.out.println("IMPORTANT! Type exit to finish entering file names.");
        System.out.println("Please note all files must be in the resources directory under src.\n");

        System.out.println("Please enter a list of filenames, and type exit to finish.");
        System.out.println("For testing copy and paste one or full string: text_game.txt. text_game2.txt exit\n");

        //Read in until the user types exit
        while(scan.hasNext() && !((temp = scan.next()).equalsIgnoreCase("exit")))
            filenames.add(temp);

        //Update the number of files
        NUM_FILES = filenames.size();

        // Add directory to filename
        for(int i = 0; i < NUM_FILES; ++i){
            filenames.set(i, ("src/resources/" + filenames.get(i)));
            System.out.println("Loaded file from source: " + filenames.get(i));
        }
        System.out.println("Filenames Successfully Stored.");
    }























}



