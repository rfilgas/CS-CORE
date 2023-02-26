#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


// ---------------------------------------------------
// Ryan Filgas
// Mark Morrissey
// CS 201
// Assignment 1
//
// The following program is designed as a typing game. The human
// at the keyboard will be given 9 words of a sentence in random
// order to type. If they type a match, they move to the next
// word, if they don't, they have to try again. When they get to
// the end, the program will tell them how long it took for them
// to type all of the words.
// ---------------------------------------------------


struct main_data
{
    //Objects to hold time at different intervals.
    struct timeval start_time;
    struct timeval end_time;
    struct timeval total_time;
    int total_seconds;
    int total_microseconds;

    //Keep track of where in the array the program is.
    int current_index;

    // Numbers to be shuffled by the shuffle function, and used as indices
    // to "shuffle" the sentence.
    int shuffled_nums[9];
};


// This function prompts the user for data.
void prompt_word(struct main_data *data, char sentence[][10], int guess_num);
void get_input(struct main_data *data, char sentence[][10]);

// This function serves as a stopwatch for the game.
void get_time(struct main_data *data, char key); //enter in b for begin timer, and e for end.
void shuffle(struct main_data *data);



int main()
{
    struct main_data data;
    char sentence[9][10] = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    data.current_index = 0;
    shuffle(&data);

    printf("This is a game that tests typing speed\n\n");
    printf("Type the following words:\n");

    // Ask user to type first word, start time, and get their input.
    prompt_word(&data, sentence, 0);
    get_time(&data, 'b');
    get_input(&data, sentence);

    // Prompt user for remaining words until complete.
    int i;
    for(i = 1; i < 9; ++i)
    {
        prompt_word(&data, sentence, i);
        get_input(&data, sentence);
    }

    //Get end time and perform calculations to find the difference between start and end times,
    //then display them to the user.
    get_time(&data, 'e');
    printf("You took %ld seconds and %ld microseconds", data.total_time.tv_sec, data.total_time.tv_usec);  
    printf("\n\n");

    exit(EXIT_SUCCESS);
}



// This is an implementation of the Fisher - Yates Shuffle.
// It will shuffle the shuffled_nums array held in main_data.
void shuffle(struct main_data *data)
{
    struct timeval current_time;
    int temp;
    
    gettimeofday(&current_time, NULL);
    srand(current_time.tv_usec);

    //Set array to 0 - 8 before shuffling.
    int m;
    for(m = 0; m < 9; ++m)
        data->shuffled_nums[m] = m;

    //Implement shuffle. Let J be any random number between the
    // current index, and the last index. Swap the current index
    // with the random index until the end is complete.
    int i;
    int j;
    for(i = 0; i < 9; ++i)
    {
        j = (rand() % (9 - i)) + i;
        temp = data->shuffled_nums[i];
        data -> shuffled_nums[i] = data -> shuffled_nums[j];
        data -> shuffled_nums[j] = temp;
        temp = 0;
    }
    return;
}



//This function prompts the user with a word to type.
void prompt_word(struct main_data *data, char sentence[][10], int guess_num)
{
    printf("word #%d is %s: ", guess_num + 1, sentence[data->shuffled_nums[data -> current_index]]); 
    return;
}



// This function gets the users input, and compares it with the requested sentence word.
void get_input(struct main_data *data, char sentence[][10])
{
    char user_input[10];
    char buffer;
    int is_match = 0;

    // The user has been asked to type selected words.
    // While the input isn't a match, prompt the user to retype their answer.
    while(is_match == 0)
    {
        //If there is an error, leave a message.
        if(scanf("%s", user_input) == 0)
                printf("Invalid input.");
        //Clear buffer.
        while ((buffer = getchar() != '\n') && (buffer != EOF));

        //Compare data, and ask user to retype if incorrect.
        if(!strncmp(sentence[data->shuffled_nums[data -> current_index]], user_input, 10))
            is_match = 1;
        else
            printf("Please retype the word again. Note that input is case sensitive.");

        //Clear Input.
        int i;
        for(i = 0; i < 10; ++i)
            user_input[i] = '\0';
        i = 0;
    }
    ++data->current_index;
    return;
}



// This function is a stop watch for the users typing.
void get_time(struct main_data *data, char key) //Enter in b for the key to begin timer, and e to end.
{
    if(key == 'b')
        gettimeofday(&(data->start_time), NULL);
    else if(key == 'e')
    {
        gettimeofday(&(data->end_time), NULL);
        timersub(&data->end_time, &data->start_time, &data->total_time);
    }
    return;
}
