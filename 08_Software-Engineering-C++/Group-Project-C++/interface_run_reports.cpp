#include "interface.h"

int interface::run_reports(){
    account_manager manager;
    char choice;
    do{
        std::cout << "Please choose from the following options:" << std::endl;
        std::cout << "1) Run member report" << std::endl;
        std::cout << "2) Run provider report" << std::endl;
        std::cout << "3) Run EFT report" << std::endl;
        std::cout << "4) Quit" << std::endl;
        std::cin >> choice;
        switch(choice){
            case '1':
                //manager.run_member_report();
                break;
            case '2':
                //manager.run_provider_report();
                break;
            case '3':
                //manager.run_EFT_report();
                break;
            case '4':
                return 1;
            default:
                std::cout << std::endl << "Invalid choice" << std::endl << std::endl;
        }
    } while(true);
    return -1; //this should never be reached
}

// Test Code

// int main(){
//     interface myif;
//     myif.run_reports();
//     return 1;
// }