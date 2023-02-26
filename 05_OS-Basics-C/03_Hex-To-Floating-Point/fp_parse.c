#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <math.h>
#include <string.h>


// Ryan Filgas
// CS201
// Mark Morrissey
// 5/9/2021
//
// The purpose of this program is to convert a hex
// representation of a binary number into its
// corresponding floating point value.
//
// Exit Failure conditions:
// 1. Number of fractional bits are less than 2 or greater than 10.
// 2. Number of exponent bits are less than 3 or greater than 5.
// 3. Size of hex input is larger than the maximum allowed frac bits.
// 4. Number of arguments is incorrect.
// 5. An invalid hex value was entered.
//
// Exit Success conditions:
// 1. Denormalized number present.
// 2. Special number present (-inf, +inf, nan).
// 3. Normalized floating point number present.


// Functions:

// Check for valid values 0-9, a - f, A - F. Return 0 for an exception.
int is_hex(char * hex);

// Return num_frac bits + num exp_bits + 1 for sign bit.
// subtract two if the hex is prefixed with 0x or 0X.

// get hex bits
int get_hex_bits(char * raw_hex, int num_fbits);
int count_leading_bits(int converted_hex, char * raw_hex, int num_bits);

// Return 0 to indicate exit conditions, 1 to proceed.
void args_valid(int on_bits, int frac_bits, int exp_bits, char * raw_hex, int maxbits); 

// Return binary int for the fraction, exponent, and sign bits.
int get_frac_bits(int converted_hex, int num_fbits); 
int get_exp_bits(int converted_hex, int num_fbots, int max_bits);
int get_sign_bit(int converted_hex, int max_bits);

// Return true if a spacial value.
int is_special(int hex_int, int num_frac_bits, int total_bits);

int main(int argc, char ** argv)
{

    // Number of arguments to expect.
    int proper_args = 3;
    // Sign bit variable for readability.
    int signed_bit_len = 1;

    // Bit quantities:
    int num_fbits;
    int num_hex_bits;
    int num_exp_bits;
    int num_fp_bits;
    int leading_on_bits;


    // Binaries:
    int hex_int;
    int frac_bits;
    int exp_bits;
    int sign_bits;

    // Conversions:
    float frac_value;
    float mantissa;
    int big_e;
    int bias;

    // Store final solution.
    float fp_rep;

    // Check if number of arguments is incorrect.
    if((argc-1) != proper_args)
        error(EXIT_FAILURE, 0, "Usage: fp_parse <# of frac_bits> <# of exp_bits>");

    //read in arguments.
    if(!(sscanf(argv[1], "%d", &num_fbits)))
            error(EXIT_FAILURE, 0, "Number of fractional bits not read in.");
    if(!(sscanf(argv[2], "%d", &num_exp_bits)))
            error(EXIT_FAILURE, 0, "Number of exponent bits not read in.");
    if(!(sscanf(argv[3], "%x", &hex_int)))
            error(EXIT_FAILURE, 0, "Hex bits not read in.");

    // Get the total number of bits in the floating point value according to arguments.
    num_fp_bits = num_fbits + num_exp_bits + signed_bit_len;

    // Get the number of bits in the passed in hex number.
    num_hex_bits = get_hex_bits(argv[3],num_fp_bits); 

    // Get the number of leading "on" bits.
    leading_on_bits = count_leading_bits(hex_int, argv[3], num_fp_bits); 

    //Check all arguments for validity before proceeding, and exit if not valid.
    args_valid(leading_on_bits, num_fbits, num_exp_bits, argv[3], num_hex_bits);

    // Get binary values for each field.
    frac_bits = get_frac_bits(hex_int, num_fbits);
    exp_bits = get_exp_bits(hex_int, num_fbits, num_fp_bits);
    sign_bits = get_sign_bit(hex_int, num_fp_bits);

    // Do intermediate calculations.
    frac_value = frac_bits/ pow(2, num_fbits);
    bias = pow(2,(num_exp_bits - 1)) -1;
    big_e = exp_bits - bias;
    if(big_e < 0)
        big_e = 0;
    mantissa = 1 + frac_value;
    

    // Denormalized values
    if(exp_bits == 0)
    {
        big_e = 1 - bias;
        --mantissa;
        fp_rep = mantissa * pow(2, big_e);
        if(sign_bits == 1)
            fp_rep = -fp_rep;
        printf("%f", fp_rep);
    }

    //Special values
    else if(is_special(hex_int, num_fbits, num_fp_bits))
    {
        if(frac_bits == 0)
        {
            if(sign_bits == 0)
                printf("+inf");
            else if(sign_bits == 1)
                printf("-inf");
        }
        else
            printf("NaN");
    }
    //Normalized values
    else
    {
        fp_rep = mantissa * pow(2, big_e);
        if(sign_bits == 1)
            fp_rep = -fp_rep;
        printf("%f", fp_rep);
    }


    printf("\n");
    exit(EXIT_SUCCESS);
}



// Return num_frac bits + num exp_bits + 1 for sign bit.
// subtract two if the hex is prefixed with 0x or 0X.
int get_hex_bits(char * raw_hex, int num_fbits)
{
    int hex_bits = 4;
    int sign_offset = 3;
    int total = 0;
    int max = strlen(raw_hex);

    // Test if the number is prefixed with 0x or 0X
    if(raw_hex[0] == '0' && (raw_hex[1] == 'x' || raw_hex[1] == 'X')){
        max -= 2;
        total = max * hex_bits;
        if(num_fbits == (total - sign_offset) && raw_hex[2] == '1')
            total -= sign_offset; 
    }
    // If the number is prefixed with a 1, decrement by 3 for the leading 0 bits.
    else if((num_fbits == (((max * hex_bits) - sign_offset)) && raw_hex[0] == '1')){
        total = (max * hex_bits) - 3;
    }
    else total = max * hex_bits;

    return total;
}



// count the number of "1" bits before the signed bit
int count_leading_bits(int converted_hex, char * raw_hex, int num_bits)
{
    int mask = 0;
    int count = 0;
    int i;

    int length = strlen(raw_hex) * 4;
    int offset = length - num_bits;

    for(i = length; i > (length - offset + 1); --i){
        mask = mask | (1 << i);
        if( ~(~mask & converted_hex))
            ++count;
    }
    return count;
}



// Test each index for a valid hex value, and return 0 if not found
int is_hex(char * hex)
{
    int length = strlen(hex);
    int success = 1;
    int i = 0;
    do
    {
        if(!((hex[i] >= '0' && hex[i] <= '9')
        || (hex[i] >= 'a' && hex[i] <= 'f')
        || (hex[i] >= 'A' && hex[i] <= 'F')))
            --success;
        ++i;
    }while(i < length && success != 0);
    return success;
}



//Exit if arguments are invalid.
void args_valid(int on_bits, int frac_bits, int exp_bits, char * raw_hex, int hex_bits)
{
    int signed_bit_length = 1;
    
    // An invalid hex value was entered.
    if(!is_hex(raw_hex))
            error(EXIT_FAILURE, 0, "Correct values for exponent and fraction bit but 3rd argument is not a valid hexadecimal number.");

    // Number of fractional bits are less than 2 or greater than 10.
    if(frac_bits < 2 || frac_bits > 10)
        error(EXIT_FAILURE, 0, "Invalid number of fraction bits(%d). Should be between 2 and 10.", frac_bits);
    // Number of exponent bits are less than 3 or greater than 5.
    if(exp_bits < 3 || exp_bits > 5)
        error(EXIT_FAILURE, 0, "Invalid number of exponent bits(%d). Should be between 3 and 5.", exp_bits);
    // Size of hex input is larger than the maximum allowed frac bits.
    if((hex_bits > (frac_bits + exp_bits + signed_bit_length)) && on_bits != 0)
        error(EXIT_FAILURE, 0, "Number %s exceeds maximum number of bits.Only %d allowed here.", raw_hex, (frac_bits + exp_bits + signed_bit_length));

    return;
}


// get the binary representation of the fraction bits
int get_frac_bits(int converted_hex, int num_fbits)
{
    int mask = 0;
    int isolated_frac_bits = 0;
    int i;

    for(i = 0; i < num_fbits; ++i){
        mask = mask | (1 << i);
    }
    isolated_frac_bits = mask & converted_hex;
    return isolated_frac_bits;
}


//get the binary representation of the exponent bits
int get_exp_bits(int converted_hex, int num_fbots, int max_bits)
{
    int mask = 0;
    int isolated_exp_bits = 0;
    int i;

    for(i = (num_fbots + 1); i < (max_bits - 1); ++i){
        mask = mask | (1 << i);
    }
    isolated_exp_bits = (mask & converted_hex) >> num_fbots;
    return isolated_exp_bits;
}


// get the value of the signed bit
int get_sign_bit(int converted_hex, int max_bits)
{
    int mask = 0;
    int sign_bit = 0;
    mask = mask | (1 << (max_bits - 1));
    sign_bit = converted_hex & mask; 
    sign_bit = sign_bit >> (max_bits - 1);
    return sign_bit;
}


// return 1 if the exponent bits are all set to 1
int is_special(int hex_int, int num_frac_bits, int total_bits)
{
    int mask = 0;
    int i;

    for(i = (num_frac_bits); i < (total_bits-1); ++i){
        mask = mask | (1 << i);
    }
    int result = (mask  == (hex_int & mask));
    return result;
}

