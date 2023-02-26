#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>


// Ryan FIlgas
// CS201
// Mark Morrissey
// Program 4
//
//
// The purpose of this program is to perform different
// mathematic operations on given inputs. It will
// utilize a jump table to select which functions
// to execute, and the menu size will be determined
// by the menu function rather than stored in variables.
//
// Requirements:
//
// Input: 32 bit int, or Hex. Hex will start with 0x or 0X.
// Output: Decimal unless specified otherwise.
// Invalid selection: display an error message and repeat menu.
//
// Functions Included:
//
// initiate: Allocate memory for the menu.
// is_hex: return 1 if the number is a hex, 0 otherwise.
// Addition: Add all args left to right and return an int.
// Subtraction: Subtrace args left to right and return an int.
// Multiplication: Multiply all args left to right and return an int.
// Division: Divide the 1st arg by the second and return a float.
// Modulo: Mod the 1st arg by the second and return an int.
// Reverse Input: Display all args in reverse order.
// leave: Display an exit message.
// destroy: deallocate dynamic memory for menu.
// Menu: basecamp to run the functions.
//
// typedef a_menu: jump table
// exit: 0, addition: 1, sub: 2, mult: 3, div: 4, mod: 5, rev input: 6

//Only used for struct initation.
#define MENU_SIZE 7
struct mdata{
    char *choices[MENU_SIZE];
};

void initiate(struct mdata * menu_data, char * my_choices[], int menu_size);
int is_hex(char * hex);
void Addition(int argc, char ** argv);
void Subtraction(int argc, char ** argv);
void Multiplication(int argc, char ** argv);
void Division(int argc, char ** argv);
void Modulo(int argc, char ** argv);
void Reverse_input(int argc, char ** argv);
void leave(int argc, char ** argv);
void destroy(struct mdata * menu_data);

typedef void (* const a_menu)(int, char **);
void Menu(struct mdata * menu_data, a_menu table[], int argc, char ** argv);



int main(int argc, char ** argv)
{
    int menu_size = 7;
    struct mdata menu_data;
    static a_menu table[] = {leave, Addition, Subtraction, Multiplication, Division, Modulo, Reverse_input}; 
    char * my_choices[] = {"Exit", "Addition", "Subtraction", "Multiplication", "Division", "Modulo", "Reverse Input"};

    if(argc == 1)
        error(EXIT_FAILURE, 0, "No arguments!");

    initiate(&menu_data, my_choices, menu_size);
    Menu(&menu_data, table, argc, argv);
    destroy(&menu_data);

    exit(EXIT_SUCCESS);
};



// Allocate memory for menu, and set variables
void initiate(struct mdata * menu_data, char * my_choices[], int menu_size){
    int i;
    int size = sizeof(menu_data->choices)/ sizeof(menu_data -> choices[0]);
    for(i = 0; i < size; ++i){
        menu_data->choices[i] = malloc(sizeof(char) * (strlen(my_choices[i]) + 1));
        strncpy(menu_data -> choices[i], my_choices[i], (strlen(my_choices[i]) + 1));
    }
}



// deallocate choices array
void destroy(struct mdata * menu_data){
    int i;
    int size = sizeof(menu_data->choices)/ sizeof(menu_data -> choices[0]);
    for(i = 0; i < size; ++i){
    free(menu_data->choices[i]);
    }
}



void Menu(struct mdata * menu_data, a_menu table[], int argc, char ** argv){
    int choice = 0;
    int size = sizeof(menu_data->choices)/ sizeof(menu_data -> choices[0]);
    char ** start = menu_data -> choices;
    char ** to_print = start;
    int i;

    do
    {
        // Print out the name of each menu item
        for(i = 0; i < size; ++i){
            printf("%d. %s\n", i, *to_print);
            ++to_print;
         }
        
        //Let user select a menu item and give error message if invalid.
        printf("\nMenu item: ");
        if(!(scanf("%d", &choice)) || choice < 0 || choice > (size - 1)){
            printf("\nInvalid entry. Please enter an integer between 0 and %d.\n", (size-1));
            choice = -1;
        }
        // Else call correct function from the table.
        else
            table[choice](argc, argv);
        printf("\n");
        // Set pointer back to start value to redisplay menu.
        to_print = start;
    }while(choice != 0);
}



// Add args from left to right.
void Addition(int argc, char ** argv){
    int i;
    char * pend;
    int temp;

    int count = 0;
    // For each operator up to the 15 limit, do the following.
    for(i = 1; (i < argc && i < 16); ++i){
        if(i > 1)
            printf(" + ");
        // If hex, convert to int and store.
        if(is_hex(argv[i])){
            temp = (int)strtoul(argv[i], &pend, 16);
            count += temp;
            printf("%d", temp);
        }
        else{
            // If not a hex, take in as decimal.
            if(!(sscanf(argv[i], "%d", &temp)))
                error(EXIT_FAILURE, 0, "Invalid integer entry.");
            else count += temp;
            printf("%d", temp);
        }
    }
    printf(" = %d\n", count);
    return;
}



// subtract args from left to right
void Subtraction(int argc, char ** argv){
    int i;
    char * pend;
    int temp;
    int count = 0;

    // For each operator up to the 15 limit, do the following.
    for(i = 1; (i < argc && i < 16); ++i){
        // Print the operator after every operation
        if(i > 1)
            printf(" - ");

        // If hex, convert to int and store.
        if(is_hex(argv[i])){
            temp = (int)strtoul(argv[i], &pend, 16);

            // If this is the first number, set it to count
            if(i == 1)
                count = temp;
            else
                count -= temp;
            printf("%d", temp);
        }
        else{
            // If not a hex, take in as decimal. If it's the first arg,
            // store it into count, if not subtract it from total.
            if(!(sscanf(argv[i], "%d", &temp)))
                error(EXIT_FAILURE, 0, "Invalid integer entry.");
            else {
                if(i == 1)
                    count = temp;
                else
                    count -= temp;
            }
            printf("%d", temp);
        }
    }
    printf(" = %d\n", count);
    return;
}



// Multiply arguments left to right.
void Multiplication(int argc, char ** argv){
    int i;
    char * pend;
    int temp;
    int count = 0;

    // For each operator up to the 15 limit, do the following.
    for(i = 1; (i < argc && i < 16); ++i){
        // Print the operator after every operation
        if(i > 1)
            printf(" * ");

        // If hex, convert to int and store.
        if(is_hex(argv[i])){
            temp = (int)strtoul(argv[i], &pend, 16);

            // If this is the first number, set it to count
            if(i == 1)
                count = temp;
            else
                count *= temp;
            printf("%d", temp);
        }
        else{
            // If not a hex, take in as decimal. If it's the first arg,
            // store it into count, if not multiply with total.
            if(!(sscanf(argv[i], "%d", &temp)))
                error(EXIT_FAILURE, 0, "Invalid integer entry.");
            else {
                if(i == 1)
                    count = temp;
                else
                    count *= temp;
            }
            printf("%d", temp);
        }
    }
    printf(" = %d\n", count);
    return;
}



// Process the first two args. Make sure float is an option and ignore the rest.
void Division(int argc, char ** argv){
    int i;
    char * pend;
    int temp;
    float count = 0;

    // For each operator up to the 2 limit, do the following.
    for(i = 1; (i < argc && i < 3); ++i){
        // Print the operator after every operation
        if(i > 1)
            printf(" / ");

        // If hex, convert to int and store.
        if(is_hex(argv[i])){
            temp = (int)strtoul(argv[i], &pend, 16);

            // If this is the first number, set it to count
            if(i == 1)
                count = (float)temp;
            else
                count /= (float)temp;
            printf("%d", temp);
        }
        else{
            // If not a hex, take in as decimal. If it's the first arg,
            // store it into count, if not multiply with total.
            if(!(sscanf(argv[i], "%d", &temp)))
                error(EXIT_FAILURE, 0, "Invalid integer entry.");
            else {
                if(i == 1)
                    count = (float)temp;
                else
                    count /= (float)temp;
            }
            printf("%d", temp);
        }
    }
    printf(" = %f\n", count);
    return;
}



// perform a modulo operation on the first two args ignoring the rest.
void Modulo(int argc, char ** argv){
    int i;
    char * pend;
    int temp;
    int count = 0;

    // For each operator up to the 2 limit, do the following.
    for(i = 1; (i < argc && i < 3); ++i){
        // Print the operator after every operation
        if(i > 1)
            printf(" mod ");

        // If hex, convert to int and store.
        if(is_hex(argv[i])){
            temp = (int)strtoul(argv[i], &pend, 16);

            // If this is the first number, set it to count
            if(i == 1)
                count = temp;
            else
                count %= temp;
            printf("%d", temp);
        }
        else{
            // If not a hex, take in as decimal. If it's the first arg,
            // store it into count, if not multiply with total.
            if(!(sscanf(argv[i], "%d", &temp)))
                error(EXIT_FAILURE, 0, "Invalid integer entry.");
            else {
                if(i == 1)
                    count = temp;
                else
                    count %= temp;
            }
            printf("%d", temp);
        }
    }
    printf(" = %d\n", count);
    return;
}



void Reverse_input(int argc, char ** argv){
    int i;
    int j;
    int k;
    char * temp;

    // Access each arg in reverse.
    for(i = (argc - 1); i >= 1; --i){
        temp = argv[i];
        j = strlen(temp);

        //Access each element of the arg
        //and print in reverse.
        for(k = (j-1); k >= 0; --k)
            printf("%c", temp[k]);
        printf(" ");
    }
    printf("\n");
    return;
}



void leave(int argc, char ** argv){
    printf("Goodbye!\n");
    return;
}



// Test each index for a valid hex value, and return 0 if not found
int is_hex(char * hex){
    return (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'));
}
