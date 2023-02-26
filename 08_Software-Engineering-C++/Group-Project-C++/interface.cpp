#include "interface.h"
//#include <iostream>
#include<vector>


int interface::start(){
    choice = 0;
    is_exit = '\0';

    //LOAD DATA
    while(login());
    //SAVE DATA
    //QUIT
    return 1;
}



void interface::quit(){
    return;
} // logout, save program and display exit message.



int interface::login(){
    cout << " Hello! Welcome to Chocoholics Anonymous!\n\n" 
         << "The place where you can have your cake and get treated too!\n";

    cout << "Please enter your Provider Number: ";
    getline(std::cin, u_login);
    p_login = u_login;
    int verified = 2;//call method to verify login status instead of using a constant
    input.clear();

    switch (verified)
    {
        case 1:
            cout << "LOGIN VALIDATED. INITIATING MANAGER INTERFACE\n";
            while(manager_menu() != -1);
            break;
        case 2:
            cout << "LOGIN VALIDATED. INITIATING PROVIDER INTERFACE\n";
            while(provider_menu() != -1);
            break;
        default:
            cout << "INVALID LOGIN. PLEASE TRY AGAIN.\n";
            break;
    }
    cout << "Please enter 'C' to continue to login screen or 'Q' to exit program and quit.\n";
    cin >> is_exit;
    cin.ignore(100, '\n');

    if('C' != toupper(is_exit)){
        cout << "PROGRAM IS EXITING. DATA WILL BE SAVED. GOODBYE...\n";
    }
    return ('C' == toupper(is_exit));
} //get input for UID as string and call login in access class use return to call proper menu.



// - interface::: access denied, 1: manager, 2: provider.
int interface::provider_menu(){
    //clear input.
    input.clear();
    int valid = 0;

    cout << "Please slide member card or key in member number: ";
    getline(std::cin, memberid);
    cout << "\n\n";
    valid = 1; //call method to verify member here

    switch (valid)
    {
        case 0:
            cout << "MEMBER SUSPENDED. MEMBER IS 1 MONTH OR MORE BEHIND ON PAYMENTS.\n";
            cout << "Enter 'C' to continue billing, or 'Q' to log out.\n";
            cin >> is_exit;
            cin.ignore(100, '\n');
            if(toupper(is_exit) != 'C'){
                return -1;
            }else return 1;
            break;
        case -1:
            cout << "INVALID MEMBER NUMBER.\n";
            cout << "Enter 'C' to continue billing, or 'Q' to log out.\n";
            cin >> is_exit;
            cin.ignore(100, '\n');
            if(toupper(is_exit) != 'C'){
                return -1;
            }else return 1;
            break;
        case 1:
            cout << "VALIDATED\n";
            log_service();
            break;
        default:
        cout << "AN ERROR OCCURED. RESTARTING PROVIDER MENU...\n\n";
        return 1;
            break;
    }
    return -1;
}

//logs a bill of a service rendered into three lists
// service_provided into the invoice_list
// and the index for the entry into the list in the 
// provider object and the member object
// returns -1 when good to exit
// this method is complete and ready to be tested
int interface::log_service(){

        vector<int> date;
        char month[3];
        char day[3];
        char year[5];
        char correct = 'N';
        string service_name;
        string service_code;
        string comments;
//        float cost = 0;
        int code_valid = 1;
 //       int index;

        //load service to log and use login and member number to log service.
        cout << "Please enter the date of the service MM-DD-YYYY: ";
        cin.get(month, 3, '-');
        cin.ignore(1, '-');
        cin.get(day, 3, '-');
        cin.ignore(1, '-');
        cin.get(year, 5, '\n');
        date.push_back(atoi(month)); //can push into 
        date.push_back(atoi(day));
        date.push_back(atoi(year));
        cout << "\n";
        //cout << date[0] << "-" << date[1] << "-" << date[2] << "\n";
        
        cout << " Please Enter in the service name: ";
        getline(std::cin, service_name);
        cin.ignore(100, '\n');
        cout << "\n";
        
        cout << "Opening Provider Directory...\n";
        cout << "Press enter when you're ready to procees\n";
        //display provider directory here
        cin.ignore(); //to make the screen pause for user.
        
        cout << "Please Key in the Service Code: ";
        getline(std::cin, service_code);
        cin.ignore(100, '\n');
        cout << "\n";

        // IF SERVICE CODE IS INVALID ERROR
        do{
            code_valid = 1; //change this to a method call to check for code!
            if(!code_valid){
                cout << "Invalid Service code. Please try again.\n";
                getline(std::cin, service_code);
                cin.ignore(100, '\n');
            }
        }while(!code_valid);

        
        while(toupper(correct) == 'N'){
            cout << "The service keyed in is: "; //call display
            // display service name
            cout << "\n";
            cout << "Is this correct? : ";
            cin >> correct;
            cin.ignore(100, '\n');
            cout << "\n";

            if(toupper(correct) == 'N'){
                cout << "It's unfortunate this isn't correct. Would you like to exit? (Y/N).\n";
                cin >> correct;
                cin.ignore(100, '\n');
                if(toupper(correct) == 'Y'){
                    return 0;
            }

            cout << "Please enter a different service code:";
            getline(std::cin, service_code);
            cin.ignore(100, '\n');
            cout << "\n";
        }
        do{
            if(comments.size() > 100)
                cout << "Only 100 charactars are allowed. Please reenter comments\n";
            cout << "Enter any comments related to the service, or leave blank: ";
            getline(std::cin, comments);
            cin.ignore(100, '\n');
            cout << "\n";
            //Fetch and display fee.
            // WRITE SERVICE: date provided(vector), provider number, member number, service code, comments, FEE
        }while(comments.size() <= 100);

      //get cost
//      cost = directory.get_cost(service_code);
      // using gathered data to add to list of invoices
//      index = invoices.add(date, cost, p_login, memberid, service_code ,comments); 
      
      //these two always return 1 - no point in error checking
      //memberid

      //memberid.add_service(index);
      //p_login.add_service(index);
      

    }
    return -1;

} //all provider options below + include logout.





void interface::use_directory(){
    return;
}




int interface::manager_menu(){
    char choice;
    do{
        std::cout << "Please choose from the following options:" << std::endl;
        std::cout << "1) Manage members" << std::endl;
        std::cout << "2) Manage providers" << std::endl;
        std::cout << "3) Manage managers" << std::endl;
        std::cout << "4) Run reports" << std::endl;
        std::cout << "5) Quit";
        std::cin >> choice;
        switch(choice){
            case '1':
                manage_members();
                break;
            case '2':
                manage_providers();
                break;
            case '3':
                manage_managers();
                break;
            case '4':
                run_reports();
                break;
            case '5':
                break;
            default:
                std::cout << "Invalid choice" << std::endl;
        }
    } while(choice != '5');
    return -1; //may need something else. needed to compile
} //all manager options below + include logout and use_directory().




void interface::manage_members(){
    return;
}




void interface::manage_providers(){
    return;
}




void interface::manage_managers(){
    return;
}



/*
int interface::run_reports(){
    char choice;
    do{
        std::cout << "Please choose from the following options:" << std::endl;
        std::cout << "1) Run member report" << std::endl;
        std::cout << "2) Run provider report" << std::endl;
        std::cout << "3) Run EFT report" << std::endl;
        std::cout << "4) Return to menuc" << std::endl;
        std::cin >> choice;
        switch(choice){
            case '1':
                manager.run_member_report();
                break;
            case '2':
                manager.run_provider_report();
                break;
            case '3':
                manager.run_EFT();
                break;
            case '4':
                break;
            default:
                std::cout << std::endl << "Invalid choice" << std::endl << std::endl;
        }
    } while(choice != '4');
    return -1; //this should never be reached
}
*/