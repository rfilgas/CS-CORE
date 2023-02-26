#include <stdio.h>
#include <stdlib.h>
#include <error.h>

//----------------------------------------------------------------------------------
// Ryan Filgas
// CS201
// 4/26/2021
//
// The purpose of this program is to flip bits requested by the user. Values entered
// will return with an error if they aren't between 0 and 15 inclusive. This program
// only handles unsigned shorts.
// ---------------------------------------------------------------------------------


#define MAX_BITS (sizeof(unsigned short) * 8)


//For each bit, check the status of the bit using bitwise 'and' and shift right to repeat.
//Print the bit value of each index.
void print_binary(unsigned short mask, unsigned short value)
{
    int i;
    for(i = MAX_BITS - 1; i >= 0; --i)
    {
        if(mask & value)
            printf("%d", 1);
        else
            printf("%d", 0);
        mask = mask >> 1;
    }

}



int
main(int argc, char ** argv)
{
    int i;
    int index;

    //Keep track of new short's value
    //Use bit mask to flip bits, or check their status.
    unsigned short value = 0;
    unsigned short mask = 1;

    //For each argument given, convert it into an integer, and exit if it's out of bounds.
    for(i = 1; i < argc; ++i) {
        index = atoi(argv[i]);
        if(index < 0 || index > 15){
            error(EXIT_FAILURE, 0, "Argument %d format error. Not in valid range [0 .. 15]", index);
        }

        //Shift the mask to the desired index.
        //Use bitwise 'or' to flip the bit if it's off.
        mask = mask << index;
        value = value | mask;

        //reset variables.
        mask = 1;
        index = 0;
    }

    //Shift the bitmask to the last place so we can display in reverse using print_binary.
    mask = mask << (MAX_BITS - 1);
    print_binary(mask, value);

    exit(EXIT_SUCCESS);
}
