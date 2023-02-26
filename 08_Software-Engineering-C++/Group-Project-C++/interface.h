#include "account_manager.h"
#include "provider_directory.h"


// The interface class will run a multi tiered menu. Main will call start which is the top level.
// This will provide options for login initially. Once login is achieved, they will be given either the provider or manager menu,
// as well as the options to logout or quit.
class interface{
    public:
        int start(); //loads program from memory. Opens login 
        void quit(); // logout, save program and display exit message.

    private:
        int login(); //get input for UID as string and call login in access class use return to call proper menu.
        // -1: access denied, 1: manager, 2: provider.
        int provider_menu(); //all provider options below + include logout.
        int log_service();
        void use_directory();

        int manager_menu(); //all manager options below + include logout and use_directory().
        void manage_members();
        int manage_member(); //sub menu returns -1 too end loop, return 1 to loop again
        void manage_providers();
        void manage_managers();
        int run_reports();

        // data members. Must be stored.
        account_manager manager;
        invoice_list invoices;
        provider_directory directory;


        //housekeeping members. Do not need to be stored
        int choice; //choice variable
        char is_exit; //exit variable
        string input; //dummy input string
        string u_login; //user login
        string p_login; //provider login if this is a manager looking
        string memberid; //current member id being looked at

};