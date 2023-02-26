#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
#include <cstdlib>
using namespace std;


// ***********************************************  
//                                               | 
// RYAN FILGAS                                   |
//                                               | 
// The purpose of this program is for the user   | 
// to create a set of flash cards, and then play | 
// a guessing game to see if they can properly   | 
// remember computer science terms that they've  | 
// selected. If they guess three correctly, they | 
// win, but if they guess three incorrectly, they| 
// lose.                                         |  
//                                               | 
// The program will be split into two parts. Part|  
// one will allow the user to create the set of  | 
// "flash cards", and part two will allow them   |  
// to play a guessing game. Upon completion,they |
// will be able to try again with the current    |  
// "cards",restart and make new cards from the   |  
// beginning, or exit.                           |  
//                                               |  
// ***********************************************



//CONSTANTS
const int KEYWORDNAME = 20;
const int WORDDESCRIPTION = 100;
const int SYNTAXEXAMPLE = 100;
const int KEYWORDS = 10;

//---------------------------------------------------------------------------------

//STRUCTURES
struct keyword
{
  char keywordName[KEYWORDNAME];
  char wordDescription[WORDDESCRIPTION];
  char topicNumber[2];  //not an int, since it's not being used as such, a char will do.
  char syntaxExample[SYNTAXEXAMPLE];
};


// To hold variables used by each function.
struct mainVariables
{
 int numKeywords = 0; // Number of keywords requested by user.
 int correct = 0; //Number of correct guesses in playGame.
 int incorrect = 0; // Number of incorrect guesses used in playGame.
 char restart = 'y'; // Keeps track of user response to restart. 
 char repeatIfAgain = 'y'; // Remains 'y' until user deides to quit. Used by repeatIf.
};

//------------------------------------------------------------------------------------

// FUNCTION PROTOTYPES
void introduceProgram(); //INTRODUCE PROGRAM TO USER.
void readKeywords(keyword library[], mainVariables & Variables);//reads in user input for flashcards.
void validateKeywords(keyword library[], mainVariables & variables);//USER CAN CHANGE KEYWORDS
void Save(keyword library[], mainVariables & variables);// SAVES KEYWORD LIBRARY TO FILE
int load(keyword flashcards[], mainVariables & variables); //READS KEYWORD LIBRARY FROM FILE
void clearScreen(); // STACKED '\n' to clear screen.	
void playGame(keyword flashCards[], mainVariables & variables); //lets user guess keywords.
//repeatIf lets user choose to start from beginning, use same cards and play, or quit.
void repeatIf(keyword library[], keyword flashcards[], mainVariables & variables);
void exit(); //output exit message to user.


//sub-functions used by functions other than main.
void makeFlashcard(keyword library[], int i); // Load info from user to keyword library.
void displayCardFront(keyword flashcards[], int & k); // Displays everything but name from card.
void resetAll(keyword library[], keyword flashcards[], mainVariables & variables);//Reset variables.

//---------------------------------------------------------------------------------------

int main()
{
  // variables
  keyword library[KEYWORDS];
  keyword flashcards[KEYWORDS];
  mainVariables variables;
  int mode = 0; // User chooses mode.
  int edit = 'n';
  do
  {
    introduceProgram(); // Introductions are in order.
    cout << "You have two options (Please enter in a 1, or 2 to select):" << endl;
    cout << "Mode 1: Input new Keywords (this will clear file contents)" << endl;
    cout << "Mode 2: Play Game with current keywords" << endl;
    cin >> mode;
    cin.ignore(100, '\n');

    // If user wants to enter in keywords let them. Rest of program will execute after);
    if(mode == 1)
    {
      readKeywords(library, variables);
      validateKeywords(library, variables);
      Save(library, variables);
    }
    variables.numKeywords = load(flashcards, variables);
    load(flashcards, variables);
    clearScreen();
    playGame(flashcards, variables);
    repeatIf(library, flashcards, variables);
  }while(variables.restart == 'y'); 
 
  exit();

  return 0;
}

//------------------------------------------------------------------------------------------




void introduceProgram()
  {
    cout << "\n\n"; 
    cout << "Welcome to CS FLASH! The flashcard game to help you study computer science!" << "\n\n";
    cout << "This program will let you enter in up to ten keywords and associated information";
    cout << "\n" << "to be used as flash cards. If you guess three correctly, you win!" << "\n";
    cout << "If you miss three, you LOSE!!!" << "\n\n";
  }



//LETS USER ENTER KEYWORDS IN
void readKeywords(keyword library[], mainVariables & variables) //reads in user input for flashcards.
{
  //loop validates a user input for keyword number between 5 and 10.
  do
  {
    cout << "How many flashcards would you like to build? (enter an integer between 5 & 10)";
    cout << "\n\n";
    variables.numKeywords = 0; //reset
    cin >> variables.numKeywords;
    cin.ignore(100, '\n');
    // a minimum of five keywords is needed to win or lose game later.
    if(variables.numKeywords > 10 || variables.numKeywords < 5)
    {
      cout << "Invalid entry, please enter a number between 5 & 10." << "\n\n";
    }
  }while(variables.numKeywords > 10 || variables.numKeywords < 5);
  
  cout << "You have " << variables.numKeywords << " to enter" << "\n\n";
  for(int i = 0; i < variables.numKeywords; ++i)
  {
    makeFlashcard(library, i);
    if(i < (variables.numKeywords - 1))
      cout << "You have " << (variables.numKeywords - (i + 1)) << " keyword(s) left to enter." << "\n"; 
  }
  cout << "Your flashcards are complete!" << "\n\n";
}



//MAKE FLASHCARD
void makeFlashcard(keyword library[], int i)
{
  cout << "Please enter the name of keyword # " << (i+1) << "." << "\n";
  cin.get(library[i].keywordName, KEYWORDNAME, '\n');
  cin.ignore(100, '\n');
  cout << "Please enter the keyword description." << "\n";
  cin.get(library[i].wordDescription, WORDDESCRIPTION,'\n');
  cin.ignore(100, '\n');
  cout << "Please enter the topic number." << "\n";
  cin.get(library[i].topicNumber, 2, '\n');
  cin.ignore(100, '\n');
  cout << "Please enter an example of syntax use for the keyword." << "\n";
  cin.get(library[i].syntaxExample, SYNTAXEXAMPLE, '\n');
  cin.ignore(100, '\n');
  cout << "\n\n";
}



// LET USER CONFIRM KEYWORDS, ADD NEW ONES, OR CHANGE KEYWORDS
void validateKeywords(keyword library[], mainVariables & variables)
{
  cout << "You entered:" << "\n\n";
  int replaceWordNum;
  char reply = 'y';
  int i = 0;
  while(reply == 'y')
  {
    // output keyword library for user to see.	  
    for(int j = 0; j < variables.numKeywords; ++j)
      {
        cout << (j+1) << ". " << library[j].keywordName << "\n";
        cout << library[j].wordDescription << "\n";
        cout << library[j].topicNumber << "\n";
        cout << library[j].syntaxExample << "\n\n";
      } 

    //Ask user for changes
    cout << "Would you like to make changes? ('y' for yes, or 'n' for no.)" << "\n";
    cin >> reply;
    cin.ignore(100, '\n');

    //If user wants changes, show them menu.
    if(reply == tolower('y'))
    {
      cout << "Let's make some changes! You have two options." << "\n";
      cout << "1. Fix a keyword. To choose a keyword to fix, enter its number." << "\n";
      cout << "2. Add more keywords. To add another keyword, enter 0. Remember you only get 10.";
      cin >> replaceWordNum;
      cin.ignore(100, '\n');

      //User entered zero to ask for a new card, but they're already at max. Tell them no.
      if(replaceWordNum == 0 && variables.numKeywords >= 10)
        cout << "You can only have ten keywords total, but you're free to make changes." << "\n\n";
     
      //User entered zero, and is within the ten words allowed, let them enter in another keyword.
      if(replaceWordNum == 0 && variables.numKeywords < 10)
      {
        ++variables.numKeywords;
        i = (variables.numKeywords - 1);
        makeFlashcard(library, i);
      }
      //User wants to replace a specific keyword. Overwrite selected flashcard.
      if(replaceWordNum != 0)
      {
        makeFlashcard(library, (replaceWordNum - 1));
      }
  
    }
  }
}



//LOAD KEYWORDS STORED INTO "keywords.txt", and put them into flashcards.
int load(keyword flashcards[], mainVariables & variables)
{
  ifstream file_in; // read from a file
  int i = 0;
  file_in.open("keywords.txt");

  if (file_in)
  {
    file_in.get(flashcards[0].keywordName, KEYWORDNAME, '|');
    file_in.ignore(100, '|'); 

    //while not at end of file, and not finished entering variables.
    while(!file_in.eof() && i < KEYWORDS)
    {
      file_in.get(flashcards[i].wordDescription, WORDDESCRIPTION, '|');
      file_in.ignore(100, '|'); 
      file_in.get(flashcards[i].topicNumber, 2, '|');
      file_in.ignore(100, '|'); 
      file_in.get(flashcards[i].syntaxExample, SYNTAXEXAMPLE, '\n');
      file_in.ignore(100, '\n'); 
      ++i;
      file_in.get(flashcards[i].keywordName, KEYWORDNAME, '|');
      file_in.ignore(100, '|'); 
    }
    file_in.close();
    file_in.clear();
  }
  return i;
}



// SAVES INFO INTO FILE.
void Save(keyword library[], mainVariables & variables)
{
  ofstream file_out;
  
//  cout << "Would you like to read in the current contents of the file, or start fresh?" << "\n";

  file_out.open("keywords.txt", ios::app);
  if(file_out)
  {
    for(int i = 0; i < variables.numKeywords; ++i)
    {
      file_out << library[i].keywordName << '|'
	       << library[i].wordDescription << '|'
	       << library[i].topicNumber << '|'
	       << library[i].syntaxExample << endl;
    }
    file_out.close();
  } 
}



//CLEAR SCREEN
void clearScreen()
{
  for(int i = 0; i < 10; ++i)
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
}



//LETS USER PLAY GUESSING GAME WITH KEYWORDS
void playGame(keyword flashcards[], mainVariables & variables)
{
  cout << "Now that you've entered your flashcards , it's time to play CS FLASH!" << "\n";
  cout << "Here's a recap of the rules. If you guess three words correctly, you WIN!" << "\n";
  cout << "If you miss three, you LOSE!" << "\n";
  cout << "If at any time you wish to pass, and move to the next word, enter a lowercase 'p'." << "\n";
  cout << "Let's begin. For each flashcard, enter the keyword that matches." << "\n\n";
 
  int randCardNum = 11; // to choose a random card
  char guess[20];
 
  while(variables.correct < 3 && variables.incorrect < 3)
  { 
    cout << "You have " << variables.correct << " correct guesses, and " << variables.incorrect << " incorrect guesses." << "\n\n";  
    randCardNum = ((rand()+ 37) % (variables.numKeywords));
    displayCardFront(flashcards, randCardNum);
    cin.get(guess, 20, '\n');
    cin.ignore(100, '\n');

    //if guess matches, tell user, and increment correct +1.
    if(!strcmp(guess, flashcards[randCardNum].keywordName))
    {
      ++variables.correct;
      cout << "You got this one correct! Good Job!" << "\n\n";
    }

    // If user wants to guess this one, and the card doesn't match their guess
    // tell them the guess was incorrect, and increment incorrect +1.
    // If user puts "p" as their guess, this if statement will be skipped.
    if(strcmp(guess,"p")  && (strcmp(guess, flashcards[randCardNum].keywordName)))
      {
        ++variables.incorrect;
        cout << "You got this one incorrect! Keep at it!" << "\n\n";
      }
  }
  if(variables.correct == 3)
    cout << "YOU WIN!!!!!!!!!!!!" << "\n\n";
  if(variables.incorrect == 3)
    cout << "You lost the game, but you'll get there. Keep trying!" << "\n\n";
}



// DISPLAY CONTENTS OF CARD, BUT NOT KEYWORD NAME, JUST CARD NUMBER
void displayCardFront(keyword flashcards[], int & k)
{
  cout << "Card "<< (k+1) << "." << "\n";
  cout << flashcards[k].wordDescription << "\n";
  cout << flashcards[k].topicNumber << "\n";
  cout << flashcards[k].syntaxExample << "\n\n";
}



//Lets user repeat from beginning, guess flashcards again, or quit.
void repeatIf(keyword library[], keyword flashcards[], mainVariables & variables)
{
  int userChoice = 0;
  do //Loop repeats until user chooses to exit.
  {
    cout << "Now that you've played (and hopefully won!) the game, please choose from the following options." << "\n\n";
   
    cout << "Mode 1: Create a new flashcard set, and replay the game" << "\n";
    cout << "Mode 2: Restart game with current flashcard set" << "\n";
    cout << "Mode 3: Game Over. Please Exit. (Please enter 1, 2, or 3.)" << "\n\n";
    cin >> userChoice;
    cin.ignore(100, '\n');

    //for file clearing.
    ofstream file_out;
    
    // User chose to start from beginning. Reset everything, and leave restart set to 'y'.
    if(userChoice == 1)
    {
      resetAll(library, flashcards, variables); 
      cout << "Thank you for playing, let's restart.";
      //RESET FILE
      file_out.open("keywords.txt");
      file_out.close();
      clearScreen();
    }
   
    //User chose to keep current flashcards, and try again. Resset correct counters, and play game.
    if(userChoice == 2)
    {
      variables.correct = 0;
      variables.incorrect = 0;
      clearScreen();
      cout << "Thank you for playing, we'll try guessing with the same keywords again." << "\n\n";
      playGame(flashcards, variables);
      variables.repeatIfAgain = 'y';
    }
   
    //User wants to quit. Empty file and set restart to 'n' for no.
    if(userChoice == 3)
    {
      cout << "Would you like to keep your flashcards saved? (Enter 0 to save, or 3 to not save)";
      cin >> userChoice;
      cin.ignore(100, '\n');
      // If user wants to delete file, clear file.  
      if(userChoice == 3)
      {
        file_out.open("keywords.txt");
        file_out.close();
      } 
      variables.restart = 'n';
      variables.repeatIfAgain = 'n';
    }
   
  }while(variables.repeatIfAgain == 'y'); 
}



//RESET ALL VARIABLES
void resetAll(keyword library[], keyword flashcards[], mainVariables & variables)
{
      int resetArrays = variables.numKeywords;
      for(int i = 0; i < resetArrays; ++i)
        {
          library[i].keywordName[0] = '\0';
	  library[i].wordDescription[0] = '\0';
	  library[i].topicNumber[0] = '\0';
	  library[i].syntaxExample[0] = '\0';  
          flashcards[i].keywordName[0] = '\0';
	  flashcards[i].wordDescription[0] = '\0';
	  flashcards[i].topicNumber[0] = '\0';
	  flashcards[i].syntaxExample[0] = '\0';  
	}
      variables.correct = 0;
      variables.incorrect = 0;
      variables.restart = 'y';
      variables.numKeywords = 0;
      variables.repeatIfAgain = 'n';
}


//PLAY EXIT MESSAGE
void exit()
{
  cout << "Thank you for playing! Goodbye." << "\n\n\n";
}
