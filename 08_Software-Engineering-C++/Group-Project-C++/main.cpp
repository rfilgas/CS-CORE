#include <iostream>
//#include "tests.h"
#include "interface.h"

using namespace std;

//heads up, we just use this to jump start the interface. Maybe we have it loop through menus.


int main(){
    int option = 0;
    interface chocann_program;

//Number menu 
    while(option != 5){
        cout<<"Please select from the following menu: \n1. Run Interface\n2. option\n3. option\n4. Run tests\n5. Quit\n\noption: ";
        cin>>option;
        cin.clear();
        cin.ignore(100, '\n');
        cout<<"\n\n";
        
        switch(option){
        case 1: 
            chocann_program.start();
            //Stuff
            break;

        case 2: 
            //stuff
            break;

        case 3: 
            //stuff
            break;

        case 4: 
            //Tests
            cout<<"Running tests\n\n";
            //Tests();
            break;
        case 5:
            cout<<"Have a good day!\n";
            break;
        default:
            cout<<"Invalid entry, please try again\n";
        }
}


    return 0;
}