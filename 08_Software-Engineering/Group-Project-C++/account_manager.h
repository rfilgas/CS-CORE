#include <map>
#include <string>
#include "account_object.h"
#include "invoice_list.h"
using std::string;
using std::map;




class account_manager{

  public:
//------GROUP 1----------------------------------------
    int load_program();
    //check manager and uid strings for membership. 
    // Set access level using set_access. 1 for managers, 2 for providers.
    int login(string &uid); //return user level as -1 for none, 1 for managers, 2 for providers. Record in access level.
    // used for logging out. Set access back to 0.
    int save_program();
    int logout(void); //reset access level, save program.



//------GROUP 2----------------------------------------
    // access level 1: assign uid and call add on member. Add to mem_accounts. Return UID.
   // int add_account(string &name, string &address, string &city, string &state, string &zip, int is_member);
    int add_account(account &to_add, string &UID);
    // access level 1: return UID.
    int update_account(account &to_add, string &UID); //lvl 1
    int remove_account(string &UID); //lvl 1
    int display_account(string &UID);

    int display_mems(void); //lvl 1
    int display_provs(void); //lvl 1

    int add_manager(); //add manager and return UID. Level 1
    int remove_manager(string &UID); // lvl 1
//------GROUP 3----------------------------------------

    //lvl 2: verify ids, and call access class to finish work.
    int log_service(service_provided &to_log); // 2
    int display_services(string &uid); // call display method in manager class - show them the actual 'index' number as a record #.
    int update_service(int selection, service_provided &to_copy);
    int remove_service(int selection);
    int remove_services(string &UID);

//------GROUP 4----------------------------------------
    int display_directory(void); //lvls 1 & 2
    int export_directory(void); //lvls 1 & 2
    int add_dir_entry(string &name, service_provided &to_add);



//------GROUP 5----------------------------------------
    int run_member_report(); //lvl 1
    int run_provider_report(); //lvl 1
    int run_EFT_report(); // lvl 1
    
    int get_UID(string name); //lvl 1 for managers only. Get from id data, NOT account objects.




    private:

//------GROUP 6----------------------------------------
      int retrieve_member(string &UID); //Return by reference and display. FOR EDITS. LOW PRIORITY.
      int retrieve_provider(string &UID); // lvl 1i
      int set_access(int level);
      int access_level; //access level of user
      string current_username;
      int assign_UID(string &to_fill); //assign random, convert to string, check all lists for membership.

//--------
    //add service index to user's list when given UID
    int add_service(string &UID, int index);


      map<string,account> accounts; //user id string is the key, account is the object

};



























/*
class account_manager{
 
    public:

        int retrieve(string &UID, account &to_retrieve); //provide a copy through the argument list
        int update(account &to_copy, string &UID); //call update method to copy data
        int remove(string &UID, vector<int> to_fill); //remove based on uidi, get vector of ints and remove entries from accounts map.
        int add(account &to_insert, string &UID); //insert based on uid. 

        // for each account pass in a vector of ints to fill, and for each index grabbed export service provided.
        // Handle this differently for member and provider reports.
        int run_member_report(); //this should export to a file
        int run_provider_report();
        int run_EFT(); //for each accunt pass in a vector of ints to fill, and for each index grabbed 
        // call get cost on each provided to calculate the total. have the object output provider name and number, then output the total.

        int display_members();
        int display_providers();

        // Add service to array, get position with account_MAX, add position as int to each member and provider. 
        //since we're using a map instead of a vector, we can remove from the structure without affecting other data.
        int log_service(service_provided &to_add, string &proid, string &memid); //call add service on proper object.

        //save data to file for reloading
        int save(ostream & to_save);

        int edit_services(); //get int array. Use their response to index into the int array,
                            // and use that corresponding entry to retrieve object for editing.
        int clear_services();
        int display_account_services(string &uid); //show users each acocunt in a foor loop. Show them the actual key and call it a record number.
        // the index should match up with the numbered choices they are provided. This will correspond to a key for edit services to use.
        //if the service can;t be found, remove its entry from the acocunt object using the uid to locate, and the int to remove via a remove service method.

        int remove_service(int selection); //Don't remove entry from member or provider onjects. this will be done by display when it comes up short.

  private:
  int account_MAX; //variable to keep track of next service record # to assign for th map key
  map<string,account> accounts; //user id string is the key, account is the object
  map<int,service_provided> provided; 

};

*/