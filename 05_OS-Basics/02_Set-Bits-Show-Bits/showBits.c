#include <stdio.h>
#include <stdlib.h>
#include <error.h>

// Ryan Filgas
// CS201
// 4/25/21
// Program 2
//
// The purpose of this program is to find and display the common
// 'on' bits between two hex numbers, and print the resulting number
// in hexadecimal, signed, and unsigned integers.


#define MAX_BITS (sizeof(int) * 8)

//Print in different formats.
void
print_formatted(unsigned int common)
{
   printf(" in common. ");
   printf("Hexadecimal: %x, ", common);
   printf("Signed: %i, ", common);
   printf("Unsigned: %u.", common);

}


int
main(int argc, char** argv){

   char * pend;
   unsigned int mask = 1;
   unsigned int common;
   int i;

   //If the user enters in more or less than two hex numbers, exit.
  if(argc != 3){
      printf("Error: please provide two hexadecimal numbers as arguments to the program.");
      exit(0);
  }

  //convert the input into unsugned ints, bitwise and them, and store the result in a variable.
  else{
   common = strtoul(argv[2], &pend, 16) & strtoul(argv[1], &pend, 16);
  }

   //Iterate through the bits, displaying them if they are a 1.
   printf("Bits: ");
   for(i = 0; i < MAX_BITS; ++i)
   {
       if(mask & common)
           printf("%d, ", i);
       mask = mask << 1;
   }
   print_formatted(common);

  exit(EXIT_SUCCESS);
}
