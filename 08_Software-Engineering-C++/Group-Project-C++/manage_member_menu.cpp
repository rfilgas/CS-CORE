#include "interface.h"

int interface::manage_member(void)   // sub menu to manage members, returns -1 after finishing to end loop, otherwise return 1 to loop again
{   
    account_manager manager;
    int edit_type = 0;
    std::cout << "Enter 1 to add member, 2 to edit, or 3 to remove or 4 to return" << endl;
    std::cin >> edit_type;
    
    //data for member addition/alteration
    account input_acc;
    string in_name;
    string in_ID;
    string in_address;
    string in_city;
    string in_state;
    string in_zip;

    if(edit_type == 1 || edit_type == 2)
    {
        //alter or add accout get member details
        std::cout << "Enter member name: ";
        std::cin >> in_name;
            
        std::cout << "\nEnter member ID: ";
        std::cin >> in_ID;
                       
        std::cout << "\nEnter member address: ";
        std::cin >> in_address;

        std::cout << "\nEnter member city: ";
        std::cin >> in_city;

        std::cout << "\nEnter member state: ";
        std::cin >> in_state;

        std::cout << "\nEnter member zip: ";
        std::cin >> in_zip;
        
    }

    switch (edit_type)
    {
        case 1:
            //add member
            
            //assign_UID(in_ID);                        //not implemented yet from account manager group 6, but assigns a new ID for a new member
            input_acc.add(in_name,in_ID, in_address, in_city, in_state, in_zip);
            manager.add_account(input_acc, in_ID);    
            break;
        case 2:
            //edit an existing member by ID
            input_acc.add(in_name,in_ID, in_address, in_city, in_state, in_zip);
            manager.update_account(input_acc, in_ID);    
            break;
        case 3:
            //remove a member by ID
            std::cout << "\nEnter member ID: ";
            std::cin >> in_ID;
            manager.remove_account(in_ID);
            break;
        case 4:
	        return -1;
	    default:
            return 1;
    }
	
    return 1;
}
