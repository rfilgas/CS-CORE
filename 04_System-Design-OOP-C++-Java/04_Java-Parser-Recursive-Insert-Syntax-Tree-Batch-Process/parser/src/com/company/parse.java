package com.company;
import com.company.tokens.*;
import com.company.tokens.Conditionals.*;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.*;
import static java.lang.Character.*;

// Ryan Filgas
// 6/3/2020
// Program 4
// Prof. Karla Fant

// The purpose of this file is to manage the parsing functions for this language project. The bulk of the work
// to parse is done by the get_input function. It strips all white space, and keeps any special exceptions
// together to be tokenized later. There are several display functions available for the data at different stages.
// It can be displayed on input, after token conversion, displayed as token types, and displayed for individual
// errors. Of special note the tokenize and validate function iterates through the arrays calling the get type function
// to get the token type and check for syntax errors. Following this it calls the make token function to convert
// the strings into tokens and store them into a mirrored array of tokens instead of strings. In order to track
// the position of syntax errors, blank lines have been left in for now and will be handled separately by the parse tree.
// The tokenize_and_validate function returns the number of errors.
// The get_type function returns the type, and 0 for a syntax error.
// The make token function returns a 0 for a syntax error, and 1 for everything else. This is to handle error messages.
// All other functions return void.

// Parse all files, and display errors.
public class parse {
    // Import text file(s) and pass into a multidimensional array of strings where each index is a line, and each sub
    protected int errors;
    protected ArrayList<ArrayList<ArrayList<a_token>>> parsed = new ArrayList<>(); //Store tokens
    protected ArrayList<ArrayList<ArrayList<String>>> programs = new ArrayList<>(); //store strings
    protected ArrayList<String> filenames; //Store filenames

    public ArrayList<ArrayList<ArrayList<a_token>>> parse_file(ArrayList<String> files) throws Exception {
        filenames = files; //store filenames into class member from args
        //Get input from user
        get_input(programs, files);
        // Convert input into tokens and store, catch return to get number of errors.
        errors = tokenize_and_validate(programs, parsed);
        // Print number of errors.
        System.out.println("File validation completed with " + errors + " errors total.");
        return null;
    }



    // Take in stored files, give each top level index a file, each middle index a line, and each bottom index a word.
    // Take care of special input exceptions for function call and "." operator to make those strings the same token.
    protected void get_input(ArrayList<ArrayList<ArrayList<String>>> programs, ArrayList<String> files) throws FileNotFoundException {
        File file;
        int num_files = files.size();
        int tempint;
        StringBuilder temp_string;
        String temp_string_2;
        boolean function_flag = true;

        ArrayList<ArrayList<String>> program;
        for (int k = 0; k < num_files; ++k) {
            programs.add(new ArrayList<>());

            program = programs.get(k);
            file = new File(files.get(k));

            Scanner scan = new Scanner(file).useDelimiter("\n");
            Scanner templine;
            int count = 0;
            // Access each line
            while (scan.hasNextLine()) {


                //---------------------------------------------------------------
                // Use this code to remove blank lines. Checker won't number properly
                // if they are removed.

                // String astring = scan.nextLine();
                //while(astring.isBlank() || astring.isEmpty())
                //    astring = scan.nextLine();
                //templine = new Scanner(astring);
                //----------------------------------------------------------------


                // split input into individual lines to parse
                templine = new Scanner(scan.nextLine());

                // Add a new array to store input
                program.add(new ArrayList<>());

                // While there are more words in the line, keep parsing
                while (templine.hasNext()) {
                    temp_string = new StringBuilder(templine.next());

                    // Exception where "This is a sentence"

                    if (temp_string.charAt(0) == '"' && !(temp_string.toString().endsWith("\"")) && !(temp_string.toString().endsWith(","))) {
                        temp_string_2 = templine.next();
                        while (!(temp_string_2.endsWith("\""))) {
                            temp_string.append(" ");
                            temp_string.append(temp_string_2);
                            if (templine.hasNext())
                                temp_string_2 = templine.next();
                            //else break;
                            else templine.close();
                        }
                        if ((temp_string_2.endsWith("\""))) {
                            temp_string.append(" ");
                            temp_string.append(temp_string_2);
                            temp_string_2 = "";
                        }
                    }
                    // End of exception

                    // Exception where "This_is(a, function)"
                    else if (function_flag && temp_string.indexOf("(") != -1 && !(temp_string.toString().endsWith(")"))) {
                        temp_string_2 = templine.next();
                        while (!(temp_string_2.endsWith(")"))) {
                            temp_string.append(" ");
                            temp_string.append(temp_string_2);
                            if (templine.hasNext())
                                temp_string_2 = templine.next();
                            else function_flag = false;
                        }
                        function_flag = true; //reset flag
                        if ((temp_string_2.endsWith(")"))) {
                            temp_string.append(" ");
                            temp_string.append(temp_string_2);
                            temp_string_2 = "";
                        }
                    }
                    // End of exception

                    // "." operator exception //there are no spaces for operator.
                    tempint = temp_string.indexOf(".");
                    if (tempint != -1) {
                        // Add first half
                        temp_string_2 = temp_string.substring(0, (tempint));
                        program.get(count).add(temp_string_2);

                        // add "."
                        temp_string_2 = ".";
                        program.get(count).add(temp_string_2);

                        // add second half
                        temp_string_2 = temp_string.substring(tempint + 1);
                        program.get(count).add(temp_string_2);
                    }
                    // End of exception
                    else
                        // Add all non "." cases to stored program.
                        program.get(count).add(temp_string.toString());
                    temp_string = new StringBuilder();
                    temp_string_2 = "";
                }
                templine = null;
                ++count;
            }
            scan = null;
            file = null;
            program = null;
        }
    }



    // Display strings as they were recorded from text file
    public void display_input() {
        int count_1 = programs.size(); // #files
        int count_2; // #lines
        int count_3; // #tokens
        ArrayList<ArrayList<String>> array_2; //subdivide file into lines
        ArrayList<String> array_3 = null; //subdivide lines into indexes

        //file loop
        for (int k = 0; k < count_1; ++k) {
            array_2 = programs.get(k);
            count_2 = array_2.size();
            System.out.println("Filename: " + (filenames.get(k).substring(14)));

            //line loop
            for (int i = 0; i < count_2; ++i) {
                array_3 = array_2.get(i);
                count_3 = array_3.size();


                //display line numbers
                if(i < 9)
                    System.out.print("0" + (i+1) + ". ");
                else System.out.print((i+1) + ". ");

                //token loop
                for (int j = 0; j < count_3; ++j) {
                    System.out.print(array_3.get(j) + " ");
                }
                System.out.print("\n");
            }
            array_2 = null;
            System.out.println("\n");
        }
        array_3 = null;
    }



    // Display the contents of each token
    public void display_tokens() {
        int count_1 = parsed.size(); //file count
        int count_2; //line count
        int count_3; //word count
        ArrayList<ArrayList<a_token>> array_2; //subdivide file into lines
        ArrayList<a_token> array_3 = null; //subdivide lines into elements

        //file loop
        for (int k = 0; k < count_1; ++k) {
            array_2 = parsed.get(k);
            count_2 = array_2.size();
            System.out.println("Filename: " + (filenames.get(k).substring(14)));

            // line loop
            for (int i = 0; i < count_2; ++i) {
                array_3 = array_2.get(i);
                count_3 = array_3.size();

                //Print the line number
                if(i < 9)
                    System.out.print("0" + (i + 1) + ". ");
                else System.out.print((i+1) + ". ");

                //token loop
                for (int j = 0; j < count_3; ++j) {
                    array_3.get(j).display_text();
                    System.out.print(" ");
                }
                System.out.print("\n");
            }
            array_2 = null;
            System.out.println("\n");
        }
        array_3 = null;
    }



    //Display the errors along with their filename, line number, and syntax
    public void display_errors() {
        int count_1 = parsed.size(); // #files
        int count_2; // #lines
        int count_3; //#words
        a_token temp;
        ArrayList<ArrayList<a_token>> array_2;
        ArrayList<a_token> array_3 = null;

        //file array
        for (int k = 0; k < count_1; ++k) {
            array_2 = parsed.get(k);
            count_2 = array_2.size();

            //line array
            for (int i = 0; i < count_2; ++i) {
                array_3 = array_2.get(i);
                count_3 = array_3.size();

                // token array
                for (int j = 0; j < count_3; ++j) {
                    temp = array_3.get(j);

                    // If this is a syntax error object, display the message.
                    if(temp instanceof syntax_error)
                        ((syntax_error) temp).display_error();
                }
            }
            array_2 = null;
        }
        System.out.print("\n");
        array_3 = null;
    }


    // Display the class type of each token in the position it appears in the file.
    public void display_token_types() {
        // Access each program -> Line -> token
        int count_1 = parsed.size();
        int count_2;
        int count_3;
        ArrayList<ArrayList<a_token>> array_2;
        ArrayList<a_token> array_3 = null;

        // File array
        for (int k = 0; k < count_1; ++k) {
            array_2 = parsed.get(k);
            count_2 = array_2.size();
            System.out.println("Filename: " + (filenames.get(k).substring(14)));

            // Line array
            for (int i = 0; i < count_2; ++i) {
                array_3 = array_2.get(i);
                count_3 = array_3.size();

                // Display line number
                if(i < 9)
                    System.out.print("0" + (i+1) + ". ");
                else System.out.print((i+1) + ". ");

                //Token array
                for (int j = 0; j < count_3; ++j) {
                    System.out.print(array_3.get(j).getClass().getSimpleName());
                    System.out.print(" ");
                }
                System.out.print("\n");
            }
            System.out.print("\n");
            array_2 = null;
        }
        array_3 = null;
    }


    // Will traverse each element of a three dimensional array and tokenize each string. It will return the number of errors.
    protected int tokenize_and_validate(ArrayList<ArrayList<ArrayList<String>>> to_convert, ArrayList<ArrayList<ArrayList<a_token>>> to_fill) {
        // Access each program -> Line -> token
        int count_1 = to_convert.size(); // #files
        int count_2; // #lines
        int count_3; // #words
        int errors = 0; //#errors
        int token_type;
        String mytemp;
        ArrayList<ArrayList<String>> array_2; //File of strings
        ArrayList<String> array_3 = null; //Line of strings
        ArrayList<ArrayList<a_token>> nodes_2; //file of nodes
        ArrayList<a_token> nodes_3; //line of nodes


        // Top level array for each file
        for (int k = 0; k < count_1; ++k) {
            to_fill.add(new ArrayList<>());
            nodes_2 = to_fill.get(k);
            array_2 = to_convert.get(k);
            count_2 = array_2.size();

            //Mid level array for each line
            for (int i = 0; i < count_2; ++i) {
                nodes_2.add(new ArrayList<>());
                nodes_3 = nodes_2.get(i);
                array_3 = array_2.get(i);
                count_3 = array_3.size();

                // Base level array for each token.
                // String and token counters are separate to allow for skipping.
                int x = 0; // String counter
                int y = 0; // token counter
                while (x < count_3) {
                    // Get token type
                    token_type = get_type(array_3.get(x));

                    //Make token, and if it's a 0, store an error message into a syntax token
                    if (make_token(nodes_3, array_3, y, token_type) == 0) {
                        mytemp ="Syntax Error In File " + (filenames.get(k).substring(14)) + " Line " + (i+1) + ": " + array_3.get(x);
                        ((syntax_error)(nodes_3.get(x))).add_message(mytemp);
                        ++errors;
                    }
                    ++x; //increment string counter
                    ++y; //increment token counter
                }
            }
            array_2 = null;
        }
        array_3 = null;
        return errors;
    }



    // Convert strings into tokens. Return 0 for syntax errors, else return 1.
    protected int make_token(ArrayList<a_token> token_list, ArrayList<String> to_convert, int index, int token_type) {
        // Variable names, and spelling check status
        // 1. Variables        // Fully checked
        // 2. Operators        // Fully Checked
        // 3. Reserved Words   // Fully Checked
        // 4. Words / strings  // Fully checked
        // 5. Conditional if   // Fully Checked
        // 6. conditional elif // Fully Checked
        // 7. conditional else // Fully Checked
        // 8. Function call    // Fully Checked
        // 0. No matching type. Store as Syntax error.

        switch (token_type) {
            case 1 -> token_list.add(new variable());
            case 2 -> token_list.add(new operator());
            case 3 -> token_list.add(new reserved());
            case 4 -> token_list.add(new word());
            case 5 -> token_list.add(new conditional_if());
            case 6 -> token_list.add(new conditional_elif());
            case 7 -> token_list.add(new conditional_else());
            case 8 -> token_list.add(new function_call());
            case 0 -> token_list.add(new syntax_error());
        }

        token_list.get(index).add(to_convert.get(index));
        if (token_type == 0)
            return 0;
        return 1;
    }



   // Get type and check for syntax errors within each potential token. Return the type.
    protected int get_type(String s) {
        int type = 0;

        List<String> my_operators = Arrays.asList("+", "==", ">>", "=", ".");
        Set<String> operators = new HashSet<>(my_operators);

        List<String> my_keywords = Arrays.asList("EVERYTHING", "START", "FIGHT!", "SAY", "THROW", "END", "HAS", "EVERYONE", "FINISH");
        Set<String> keywords = new HashSet<>(my_keywords);

        List<String> conditionals = Arrays.asList("if", "elif", "else");

        //3. Reserved words. This needed to be first for the keywords EVERYTHING and EVERYONE.
        if (keywords.contains(s))
            type = 3;
        //1. Variables
        else if (is_variable(s))
            type = 1;
        //2. Operators
        else if (operators.contains(s))
            type = 2;
            //4. Words / strings:
        else if (s.charAt(0) == '\"' && (s.endsWith(",") || (s.endsWith("\""))))
            type = 4;
            //5. Conditional if
        else if (conditionals.get(0).equals(s))
            type = 5;
            //6. conditional elif
        else if (conditionals.get(1).equals(s))
            type = 6;
            //7. conditional else
        else if (conditionals.get(2).equals(s))
            type = 7;
            // 8. Function Call
        else if (s.contains("(") && is_function(s, keywords))
            type = 8;
        //0 Syntax error.
        return type;
    }


    // Return true if function is valid. Inner strings must follow variable rules.
    protected boolean is_function(String s, Set<String> keywords){
        String tempstring;
        boolean success = false;
        int leftparens;
        int rightparens;
        int space;

        leftparens = s.indexOf("(");
        rightparens = s.indexOf(")");
        space = s.indexOf(" ");

        // Checking function_name
        tempstring = s.substring(0, leftparens);
        if (keywords.contains(tempstring)) {
            tempstring = s.substring((leftparens + 1), space);
            // Checking keyword 1
            if (is_variable(tempstring)) {
                tempstring = s.substring((space+1), rightparens);
                // Checking keyword 2
                if (is_variable(tempstring))
                    success = true;
            }
        }
        return success;
    }

    //Return true if first letter is upper and the second is lower
    protected boolean is_variable(String s) {
        return (isUpperCase(s.charAt(0)) && isLowerCase(s.charAt(1)));
    }
}