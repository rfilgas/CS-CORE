

#include <iostream>
using namespace std;

//  ******************************************************
//  Ryan Filgas                                          |
//                                                       |
//  The purpose of this program is to determine if the   |
//  user has enough time to complete their weekly        |
//  programming assignment. It will use input from the   |
//  assignment parameters, as well as their schedule     |
//  to calculate the net hours whether positive, or      |
//  negative, if they proceed with the current schedule. |
//  It will then deliver the results, and ask if they'd  |
//  like to restart the program, or exit.                |
//  ******************************************************

int main()
{
  float programmingTime = 0.0;        // hrs total programming will take
  float hoursSpent = 0.0;             // hrs  spent writing program
  float workRemaining = 0.0;          // hrs left of programming to finish
  float daysUntilDue = 0;              // days until assignment is due
  float timeAvailable = 0.0;          // hrs until due(days until due * 24) - timeRemaining

  float hoursUnavailable = 0.0;       // hrs spent at work, school, etc.
  float personalHours = 0.0;          // hrs for sleep, dog walking, etc.
  float extraCurriculars = 0.0;       // hrs for hobbies, entertainment, etc.
  float classHours = 0.0;             // hrs for other classes  including homework
  float otherHours = 0.0;             // hrs for everything else
  float timeCommitments = 0.0;        // hrs :sum of all availability variables

  float netHours = 0.0;               // hrs: (timeAvailable - timeCommitments) - RESULT
  float netProgrammingTime = 0.0;     // hrs:  time available to program after time commitments.
  char yesOrNo = 'n';                 // temp variable to store 'y' or 'n'
  int userChange = 1;                 // temp variable to store user # selection
  char programRestart = 'n';          // variable to be used by restart loop
  int countDown = 0;                  // Dummy variable to countdown # of  attempts in for loops


  // This while loop is for user to restart the body of the program. It will exit when the user says they want to restart.
  do
  {
    //PROGRAM INTRODUCTION
    cout << endl << endl;
    cout << "Hello, welcome to the Computer Science Scheduling Calculator!" << endl;
    cout << "The professor has asked that you determine whether you have enough time to complete weekly programming assignments." << endl;
    cout <<  endl;
    cout << "This will require information about the assignment, and hours you may have available for homework." << endl;
    cout << "You will have an opportunity to double check answers before the end." << endl;




    //QUESTION BLOCK 1: Ask for assignment parameters: programmingTime, hoursSpent, timeRemaining, daysUntilDue.

    //PROGRAMMING TIME - Ask user for hours assignment will take, use for loop to give them 5 tries to answer.
    //If negative answer is still given, it will be corrected later.
    cout  << endl;
    cout << "How many hours do you expect implementing a weekly algorithm will take?" << endl;
    cout << "(Enter any positive number, decimals  like 1.5 are ok.)" << endl;
    cin >> programmingTime;
    cin.ignore(100,'\n');
    //Setting countdown variable for the following loop. It will allow the user five tries to enter a positive
    // number before proceeding.
    countDown = 5;
    for(int i = 0; i < 5; i += 1)
    {
      if(programmingTime < 0)
        {
          cout << "Please enter a positive number. " << countDown << " attempt(s) remaining." << endl;
          --countDown;
          cin >> programmingTime;
          cin.ignore(100,'\n');
        }
    }
    // Resetting countdown variable for later use.
    countDown = 0;
    cout << "You entered " << programmingTime << " hr(s)." << endl;
    cout << endl << endl;


    //HOURS SPENT -  Asks if user started program, if yes, gets hours spent. If no, moves on.
    cout << "Have you already started your program? (enter 'y' for yes or 'n' for no.)" << endl;
    // Do while loop requires user to enter a valid 'y' or 'n' response. If user answers yes,
    // asks user how many hours they've worked on programming. Requires a positive number entry. 
    do
    {
      cin >> yesOrNo;
      cin.ignore(100,'\n');
      cout << "You've selected " << yesOrNo << "." << endl;
      cout << endl;

      //if user answers 'y' for yes, ask how many hours they've worked on program.
      if(tolower(yesOrNo) == 'y')
      {
        cout << "How many hours have you worked on your program already? (Enter any positive number, decimal numbers like 4.3 are ok.)" << endl;
        cin >> hoursSpent;
        cin.ignore(100,'\n');
        cout << "You entered " << hoursSpent << "hr(s)." << endl;
      }
        // If user answers 'n' for no, make a comment, then proceed.
        else if(tolower(yesOrNo) == 'n')
          cout << "After this, it's time to get to work!" << endl;
        // If user enters something invalid, ask for a valid entry.
        else if (tolower(yesOrNo) != 'y' and tolower(yesOrNo) != 'n')
         cout << "Invalid entry. Please answer 'y' for yes, or 'n' for no to proceed.";
    //End of do while loop. User must answer 'y' or 'n' to proceed.
    }while(tolower(yesOrNo) != 'y' and tolower(yesOrNo) != 'n');
    cout << endl;

    //Loop prevents negative values from being entered.
    while(hoursSpent < 0)
      {
        cout << "You entered " << hoursSpent  << " hr(s)." << endl;
        cout << "Please enter a positive number to proceed." << endl;
        cin >> hoursSpent;
        cin.ignore(100,'\n');
      }


    //DAYS UNTIL PROGRAM IS DUE - ask user how many days until program is due. For loop gives the user 5 tries
    //to give a valid answer between 1 & 7. Invalid entries will be fixed by user later. Added for loop to get
    // more experience with for loops in c++.
    cout << "How many days until your program is due? (please enter any number between 0 & 7. Decimal approximations like 1.25 are ok)" << endl;
    cin >> daysUntilDue;
    cin.ignore(100,'\n');

    //Set countdown variable to 5, and initiate for loop.
    countDown = 5;
    for(int i = 0; i < 5; i += 1)
    { if(daysUntilDue <= 0 || daysUntilDue > 7)
      {
        cout << "Please enter a positive number between 0 & 7.  " << countDown << " attempt(s) remaining." << endl;
        --countDown;
        cin >> daysUntilDue;
        cin.ignore(100,'\n');
      }
    }
    // reset countdown variable for possible later use.
    countDown = 0;
    cout << "You entered " << daysUntilDue << " day(s)." << endl << endl;




    // QUESTION BLOCK 2: USER AVAILABILITY - hoursUnavailable, personalHours, classHours, extraCurriculars, otherHours.
    cout << "Thank you for providing assignment parameters. Please provide availability." << endl;


    //HOURS UNAVAILABLE - Asks user how many hours they work, requires a positive value with a while loop.
    cout << "How many hours a day are you unavailable due to work?" << endl;
    cout << "(Enter any positive number, decimals like 9.23 are ok.)" << endl;
    cin >> hoursUnavailable;
    cin.ignore(100,'\n');
    //If user enters a negative value, prompt them for a positive one.
    while(hoursUnavailable < 0)
    {
      cout << "Please enter a positive value to proceed." << endl;
      cin >> hoursUnavailable;
      cin.ignore(100,'\n');
    }
    cout << "You entered " << hoursUnavailable << "hr(s)." << endl << endl;


    // PERSONAL HOURS - Asks user how many hours they need for personal time, requires a positive value with a while loop.
    cout << "How many personal hours do you need on average each day for eating, sleep, dog walking, grooming etc." << endl;
    cout << "(As usual, enter any positive number, decimals like 9.99 are ok.)" << endl;
    cin >> personalHours;
    cin.ignore(100,'\n');
    // If user enters a negative value, prompt them for a positive one.
    while(personalHours < 0)
    {
      cout << "Please enter a positive value to proceed." << endl;
      cin >> personalHours;
      cin.ignore(100,'\n');
    }
    cout << "You entered " << personalHours  << "hr(s)." << endl << endl;


    //CLASS HOURS - Asks user how many hours they spend on other classes including homework, requires a positive value w/ while loop.
    cout << "How many hours on average do you spend on other classes and associated homework per day?" << endl;
    cout << "(Please enter any positive number, decimals like 4.33 are ok.)" << endl;
    cin >> classHours;
    cin.ignore(100,'\n');
   // If user enters a negative value, prompt them for a positive one.
    while(classHours < 0)
    {
      cout << "Please enter a positive value to proceed." << endl;
      cin >> classHours;
      cin.ignore(100,'\n');
    }
    cout << "You entered " << classHours  << "hr(s)." << endl << endl;


    //EXTRA CURRICULARS - Asks user how many hours they spend on extra curriculars, requires a positive value w/ while loop.
    cout << "How many hours per day do you spend on average doing extra curricular hobbies like TV, music, gaming, pogo sticks etc.?" << endl;
    cout << "(Please enter any positive number, decimals like 3.14 are ok.)" << endl;
    cin >> extraCurriculars;
    cin.ignore(100,'\n');
    // If user enters a negative value, prompt them for a positive one.
    while(extraCurriculars < 0)
    {
      cout << "Please enter a positive value to proceed." << endl;
      cin >> extraCurriculars;
      cin.ignore(100,'\n');
    }
    cout << "You entered " << extraCurriculars  << "hr(s)." << endl << endl;


    //OTHER HOURS - Asks user how many hours they spend that weren't covered, requires a positive value w/ while loop.
    cout << "How many total hours per day do you spend on activities not covered by the previous questions?" << endl;
    cout << "(Please enter any positive number, decimals like 7.77 are ok.)" << endl;
    cin >> otherHours;
    cin.ignore(100,'\n');
    // If user enters a negative value, prompt them for a positive one.
    while(otherHours < 0)
    {
      cout << "Please enter a positive value to proceed." << endl;
      cin >> otherHours;
      cin.ignore(100,'\n');
    }
    cout << "You entered " << otherHours  << "hr(s)." << endl << endl;




    //USER VERIFICATION - Give user the opportunity to verify answers.
    // Loop will break when user confirms their answers are correct, and no entries are negative. A nested "if" statement will
    // prompt them if the amount of hours available entered exceeds 24, and will require them to make corrections.
    // Reset variable yesOrNo for use in loop.
    yesOrNo = 'n';
    do
    {
      cout << "Now that we have the necessary data, it's time to verify answers." << endl;
      cout << endl;
      cout << "PROGRAM PARAMETERS:" << endl;
      cout << "1. Programming Time - (time assignment will take) : " << programmingTime << " hr(s)" << endl;
      cout << "2. Hours Spent Programming - (time already spent) : " << hoursSpent << " hr(s)" << endl;
      cout << "3. Days Until Due - (days until assignment is due : " << daysUntilDue << " day(s)" << endl;
      cout << endl;
      cout << "PERSONAL AVAILABILITY:" << endl;
      cout << "4. Hours Unavailable - (time at work or school)   : " << hoursUnavailable << "hr(s)" << endl;
      cout << "5. Personal Hours - (sleep, dog walking, etc.)    : " << personalHours << "hr(s)" << endl;
      cout << "6. Extra Curriculars - (hobbies, entertainment)   : " << extraCurriculars << "hr(s)" << endl;
      cout << "7. Class Hours - (other classes and homework)     : " << classHours  << "hr(s)" << endl;
      cout << "8. Other Hours - (Catch all, anything not covered): " << otherHours << "hr(s)" << endl;
      cout << endl << endl;
      cout << "These are the values you entered, would you like to change anything? (enter 'y' for yes or 'n' for no)" << endl;
      cout << "Please note, the program will not proceed if there are negative numbers, or total  availability in excess of 24 hours a day." << endl;
      cin >> yesOrNo;

      // Loop to stop program from terminating  when user hits a number before asked.
      while (tolower(yesOrNo) !=  'y' && tolower(yesOrNo) != 'n')
      {
        cout << "Invalid entry, please enter 'y' for yes, or 'n' for no." << endl;
        cin >> yesOrNo;
        cin.ignore(100,'\n');
      }
      cout << "You've selected " << yesOrNo << "." << endl;
      cout << endl;

      //MAX HOURS AVAILABLE EXCEEDED - totals available hours and checks that they don't exceed 24. If they do, prompt user for changes by
      //forcing a 'y' (yes) response to making changes.
      if((hoursUnavailable + personalHours + extraCurriculars + classHours + otherHours) > 24)
      {
        cout<< "User availability exceeds 24 hours a day, please change a value to proeed." << endl;
        yesOrNo = 'y';
      }

      //ANSWER SELECTION - Ask user to select answers to change from the menu. Loop requires answer between 1 & 8.
      if(tolower(yesOrNo) == 'y')
        {
          cout << "Which question would you like to change your answer for? (Please enter a whole number between 1 & 8)" << endl;
          cin >> userChange;
          cin.ignore(100,'\n');
          //Loop to stop improper entries. Only integers 1-8 are accepted.
          while(userChange < 1 || userChange > 8)
          {
            cout << "Invalid entry, please choose a whole number between 1 & 8." << endl;
            cin >> userChange;
            cin.ignore(100,'\n');
          }
          cout << "You've selected number " << userChange << "." << endl;
          cout << endl;
            // #1 QUESTIONS: For each of the following user corrections, user will enter new values and be directed back to main menu after.
            if(userChange == 1)
            {
              cout <<  "Programming Time: How many hours will the programming assignment take?" << endl;
              cin >> programmingTime;
              cin.ignore(100,'\n');

              cout << "You've entered " << programmingTime << " hr(s)" << endl;
              userChange = 0;
            }
            // #2
            if(userChange == 2)
            {
              cout <<  "Hours Spent: How many hours have you already spent programming?" << endl;
              cin >> hoursSpent;
              cin.ignore(100,'\n');
              cout << "You've entered " << hoursSpent << " hr(s)" << endl;
              userChange = 0;
            }
            // #3
            if(userChange == 3)
            {
              cout <<  "Days Until Due: How many days until the programming is due?" << endl;
              cin >> daysUntilDue;
              cin.ignore(100,'\n');
              cout << "You've entered " << daysUntilDue << " day(s)" << endl;
              userChange = 0;
            }

            // #4
            if(userChange == 4)
            {
              cout <<  "Hours Unavailable: How many hours per day do you spend at work and school (not in classes or doing homework)?" << endl;
              cin >> hoursUnavailable;
              cin.ignore(100,'\n');
              cout << "You've entered " << hoursUnavailable << " hr(s)" << endl;
              userChange = 0;
            }

            // #5
            if(userChange == 5)
            {
              cout <<  "Personal Hours: How many hours per day do you spend sleeping, dog walking, grooming, showers etc.??" << endl;
              cin >> personalHours;
              cin.ignore(100,'\n');
              cout << "You've entered " << personalHours << " hr(s)" << endl;
              userChange = 0;
            }

            // #6
            if(userChange == 6)
            {
              cout <<  "Extra Curriculars: How many hours per day  do you spend on entertainment and hobbies?" << endl;
              cin >> extraCurriculars;
              cin.ignore(100,'\n');
              cout << "You've entered " << extraCurriculars << " hr(s)" << endl;
              userChange = 0;
            }

            // #7
            if(userChange == 7)
            {
              cout <<  "Class Hours: How many hours per day do you spend on other classes including homework??" << endl;
              cin >> classHours;
              cin.ignore(100,'\n');
              cout << "You've entered " << classHours << " hr(s)" << endl;
              userChange = 0;
            }

            // #8
            if(userChange == 8)
            {
              cout <<  "Other Hours: Catch all. How many hours per day do you spend on things not covered above?" << endl;
              cin >> programmingTime;
              cin.ignore(100,'\n');
              cout << "You've entered " << programmingTime << " hr(s)" << endl;
              userChange = 0;
            }
        }
      //END OF DO WHILE LOOP FOR CORRECTIONS: If user chooses to put in a new value, or user has entered negative values, restart loop.
    }while(tolower(yesOrNo) == 'y' || otherHours < 0 || classHours < 0 || extraCurriculars < 0 || personalHours < 0
           || hoursUnavailable < 0 || daysUntilDue < 0 || hoursSpent < 0 || programmingTime < 0);



    //CALCULATIONS - Calculate different values for use in results.
    workRemaining = programmingTime - hoursSpent;
    timeAvailable = (daysUntilDue * 24) - workRemaining;
    timeCommitments =  daysUntilDue*(hoursUnavailable + personalHours + extraCurriculars + classHours + otherHours);
    netHours = timeAvailable - timeCommitments;
    netProgrammingTime = (daysUntilDue * 24) - timeCommitments;


    //DELIVER RESULTS TO USER - Tell user how much time they will have left over, or not. Give them reccomendations if they are too close to zero.
    cout << "You will have " << netProgrammingTime  << " hour(s) to complete " << workRemaining << " hour(s) of programming." << endl;
    if(netHours >= 0)
      cout << "Based on the information you've provided, you'll have " << netHours << " hour(s) to spare!" << endl;
    if (netHours < 0)
      cout << "Based on the information you've provided, you will need an extra " << (-netHours) << " hour(s)." << endl;
    if (netHours >= 0 && netHours <= 2)
      cout <<  "That's cutting it close. It might be best to budget some more time. " << endl;
    cout << endl;


    // CLOSING STATEMENT - Ask if user wants to restart program. Uses loop to require proper input.
    cout << "Thank you for using the Computer Science Scheduling Calculator!" << endl;
    cout << "Would you like to restart the program? (enter 'y' for yes, or 'n' to terminate.)" << endl;
    cin >> programRestart;
    // Change user response to a lowercase in variable.
    programRestart = tolower(programRestart);
    // Loop will break if a 'y' or 'n' are entered.
    while(programRestart != 'y' && programRestart != 'n')
    {
      cout << "Invalid entry. Please enter 'y' to restart, or 'n' to terminate." << endl;
      cin >> programRestart;
      cin.ignore(100,'\n');
    }
    if(programRestart == 'n')
      cout << "Terminating program. Goodbye!";
    if(programRestart == 'y')
      cout << "Restarting...";

  //PROGRAM RESTART LOOP. User must answer 'n' for no in closing statement; a 'y' response will restart.
  }while(tolower(programRestart) != 'n');
  cout << endl << endl;

  return 0;
}
