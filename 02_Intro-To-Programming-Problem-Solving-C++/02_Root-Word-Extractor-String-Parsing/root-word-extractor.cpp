#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

// ******************************************
// RYAN FILGAS                              |
//                                          |
// The purpose of this program is to remove |
// prefixes and suffixes from a sentence    |
// while ommitting punctuation so that      |
// the user can see root words. It will     |
// take a sentence as input from the user,  |
// and ask for three prefixes and three     |
// suffixes to remove. After removing them  |
// and presenting results, it will ask the  |
// user if they would like to restart.      |
// ******************************************

  void reverseArray(char reversedArray[]); // Reverses an array.
  void stripPrefix(char chosenAffix[], char sentence[], char tempSentence[]); // Removes a prefix.
  void stripSuffix(char chosenAffix[], char sentence[], char tempSentence[]); // Removes a suffix.
  void introduction(); // Introduce program to user.
  void getData(char prefix1[], char prefix2[], char prefix3[], char suffix1[],
       char suffix2[], char suffix3[]); // Get data input from user.
  void getSentence(char sentence[], char tempSentence[]); // Get sentence, remove punctuation.
  void stripAffixes(char prefix1[], char prefix2[], char prefix3[], char suffix1[],
       char suffix2[], char suffix3[], char sentence[], char tempSentence[]);// Removes all affixes.
  void deliverResults(char sentence[]); // Deliver results to user.
  void restartProgram(char &restart, char sentence[]); // Restart program.
  void lowerArray(char tempSentence[]); // Makes an array all lowercase letters.
  void lowerAffixes(char prefix1[], char prefix2[], char prefix3[], char suffix1[],
       char suffix2[], char suffix3[]); // Changes all affixes to lowercase.

int main()
{
  char sentence[200];     // User entered sentence to remove affixes from.
  char prefix1[20];
  char prefix2[20];
  char prefix3[20];       // User entered prefixes for removal.
  char suffix1[20];
  char suffix2[20];
  char suffix3[20];       // User entered suffixes.
  char restart;           // Restart variable.
  char tempSentence[200]; // To hold lowercase sentence for comparing.

  do
  {
    introduction();
    getSentence(sentence, tempSentence); // Get sentence for user and strip all punctuation.
    lowerArray(tempSentence); // Make temp sentence lowercase.
    getData(prefix1, prefix2, prefix3, suffix1, suffix2, suffix3); // Get data input from user.
    lowerAffixes(prefix1, prefix2, prefix3, suffix1, suffix2, suffix3); // Make affixes lowercase.
    stripAffixes(prefix1, prefix2, prefix3, suffix1, suffix2, suffix3, sentence, tempSentence);
    deliverResults(sentence);// Deliver results to user.
    restartProgram(restart, sentence);
  }while(tolower(restart) == 'y');

return 0;
}



// Introduce program to user, and describe function.
void introduction()
{
  cout << "\n\n";
  cout << "Hello, welcome to the MAJESTIC ROOT WORD EXTRACTOR!" << "\n\n";
  cout << "This program is designed to remove three prefixes and three suffixes to" << "\n";
  cout << "strip words down to their roots. The result will not include punctuation." << "\n";
}



// Get user input, and delete punctuation.
void getSentence(char sentence[],char tempSentence[])
{
  cout << "Please enter a sentence or list of words." << "\n";
  cin.get(sentence, 200, '\n');
  cin.ignore(200, '\n');
  cout << "You entered " << sentence << "\n\n";
  int j = 0; // Count letters added to temp sentence.
  int sentenceLength = strlen(sentence);
  for(int i = 0; i < sentenceLength; ++i)
  {
    if(isalpha(sentence[i]) || sentence[i] == ' ')
     {
       tempSentence[j] = sentence[i];
       j += 1;
     }
  }
  sentence[0] = '\0';
  strcpy(sentence, tempSentence);
  sentence[j] = '\0';
}



// Make tempSentence lowercase for comparison in stripPrefix function.
void lowerArray(char tempSentence[])
{
 int arrayLength = strlen(tempSentence);
  for(int i = 0; i < arrayLength; ++i)
    tempSentence[i] = tolower(tempSentence[i]);
}



// Get prefixes and suffixes from user
void getData(char prefix1[], char prefix2[], char prefix3[], char suffix1[], char suffix2[], char suffix3[]) // get data input from user.
{
  cout << "Please enter in three prefixes you'd like to remove, one at a time." << "\n";
  cin.get(prefix1, 20, '\n');
  cin.ignore(100, '\n');
  cin.get(prefix2, 20, '\n');
  cin.ignore(100, '\n');
  cin.get(prefix3, 20, '\n');
  cin.ignore(100, '\n');
  cout << "You entered " << prefix1 << " " << prefix2 << " "  << prefix3 << "\n\n";


  cout << "Please enter in three suffixes you'd like to remove, one at a time." << "\n";
  cin.get(suffix1, 20, '\n');
  cin.ignore(100, '\n');
  cin.get(suffix2, 20, '\n');
  cin.ignore(100, '\n');
  cin.get(suffix3, 20, '\n');
  cin.ignore(100, '\n');

  cout << "You entered " << suffix1 << " " << suffix2 << " "  << suffix3 << "\n\n";
}


// Lower affixes, converts all entered affixes into lowercase for stripPrefix function.
void lowerAffixes(char prefix1[], char prefix2[], char prefix3[], char suffix1[],
                  char suffix2[], char suffix3[])
{
  lowerArray(prefix1);
  lowerArray(prefix2);
  lowerArray(prefix3);
  lowerArray(suffix1);
  lowerArray(suffix2);
  lowerArray(suffix3);
}



//Function and while loop Copies everything but prefix, and returns new sentence.
void stripPrefix(char chosenAffix[], char sentence[], char tempSentence[])
{
  char newSentence[200];
  char wordFragment[200];
  int affixLength = strlen(chosenAffix);
  int sentenceLength = strlen(sentence);
  int lettersAdded = 0; // Counter for # letters added to temp sentence.
  int i = 0;            // While loop variable.
  int fragIndex = 0; // To keep track of index for word fragment.
  while(i < sentenceLength)

  {   // If(at the first letter (index 0)) or:
      // (counter hasn't made it to last possible word fragment
      // and a space is followed by an alphabetical letter)
      // then make a word fragment from the letters.
      if(i == 0 || ((i < (sentenceLength - affixLength))
      && (sentence[i-1] == ' ' && isalpha(sentence[i]))))
      {
         for (int k = i; k < (i + (affixLength)); ++k)
         {
           wordFragment[fragIndex] = tolower(sentence[k]);
           fragIndex += 1;
         }
         wordFragment[fragIndex] = '\0';
         fragIndex = 0; // Reset fragment letter counter.
      }

      // If the word fragment doesn't match the prefix, copy the letter.
      if(strcmp(chosenAffix, wordFragment) != 0)
      {
        newSentence[lettersAdded] = sentence[i];
        i += 1;
        lettersAdded += 1;
        wordFragment[0] = '\0';
      }

      // If fragment matches prefix, advance i by length of prefix to 'skip' prefx.
      if(strcmp(chosenAffix, wordFragment) == 0)
      {
        i += affixLength;
        wordFragment[0] = '\0';
      }
  }
  newSentence[lettersAdded] = '\0'; //Prevent garbage when copying to larger array.
  strcpy(sentence, newSentence);    // Copy temp sentence into user sentence.
}



// Reverses an array by copying the last letter to the first,
// the second to last to the second, etc. Used by stripSuffix.
void reverseArray(char reversedArray[])
{
  char tempArray[200];
  int lengthArray = strlen(reversedArray);
  for(int i = 0; i < lengthArray; ++i)
  {
    tempArray[i] = reversedArray[(lengthArray - 1)-i];
    tempArray[lengthArray] = '\0';
  }
  reversedArray[0] = '\0'; // Reset array
  strcpy(reversedArray, tempArray);
}



// Strips suffix from a sentence. Reverses affixes and sentence,
// and processes the sentence backwards with the stripPrefix
// function before reversing the sentence back to normal.
void stripSuffix(char chosenAffix[], char sentence[],char tempSentence[])
{
  reverseArray(chosenAffix);
  reverseArray(tempSentence);
  reverseArray(sentence);
  stripPrefix(chosenAffix, sentence, tempSentence);
  reverseArray(sentence);
  reverseArray(chosenAffix);
  reverseArray(tempSentence);
}



// Strip prefixes and suffixes from sentence.
void stripAffixes(char prefix1[], char prefix2[], char prefix3[], char suffix1[],
                  char suffix2[], char suffix3[], char sentence[], char tempSentence[])
{
 stripPrefix(prefix1, sentence, tempSentence);
 stripPrefix(prefix2, sentence, tempSentence);
 stripPrefix(prefix3, sentence, tempSentence);
 stripSuffix(suffix1, sentence, tempSentence);
 stripSuffix(suffix2, sentence, tempSentence);
 stripSuffix(suffix3, sentence, tempSentence);
}



// Delivers results to user.
void deliverResults(char sentence[])
{
  cout << "Your majestic root words are: " << sentence << "\n\n\n";
}



// Restart program. Reset sentence if user restarts.
void restartProgram(char &restart, char sentence[])
{
  cout << "Would you like to restart? ( 'y' or 'n')" << "\n";
  cin >> restart;
  cin.ignore(100,'\n');
  if(tolower(restart) == 'y')
  {
    cout << "Restarting! Let's go!" << "\n\n\n";
    sentence[0] = '\0';
  }
  if(tolower(restart) == 'n')
    cout << "Thanks for coming! Have a good day!" << "\n\n\n";
  while(tolower(restart) != 'y' && tolower(restart) != 'n')
  {
    cout << "Invalid input, please enter 'y' or 'n'. " << "\n";
    cin >> restart;
    cin.ignore(100, '\n');
  }
}
