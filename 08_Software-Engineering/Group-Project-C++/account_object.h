#include <string>
#include <vector>
#include "utility.h"
#include <iostream>
//#include "service_provided.h"
using std::vector;
using std::string;
using std::ostream;

//using namespace chocann; //isUID(uid), isSTATE(state), is_ZIP(zip), is_LETTERS(letters)

class account{
    public:
    //Maybe write a copy constructor instead.
    int add(string &name, string &uid, string &address, string &city, string &state, string &zip);
    int save(ostream & to_save);
    int load(std::istream & to_load);

    // same as add, but won't update if null passed in to field,.
    int edit(string &name, string &address, string &city, string &state, string &zip);
    int make_provider(); //sets account type to member
    int make_manager();
    int update(account &to_copy);
    int copy(account &to_fill);
    int output(ostream & out);
    int display();

    int add_service(int to_add);
    int remove_service(int user_choice);
    //int update_service(service_provided & to_save, int user_choice);
    int output_services(ostream &out);
    //int display_services(); //include an index for them to choose from
    bool is_provider();

    //output provider name and provider number. Return -1 if not provider.
    int out_EFT(ostream & out);

    bool member_status(); //checks to see if account is an active member
    int set_member_status(bool status);
    int get_account_type();
    
    protected:

    //member class data members
    string name; //verify with is_LETTERS(city)
    string address; //validation of this is too complicated. Out of scope for now.
    string city; //verify with is_LETTERS(city)
    string state; //verify using is_STATE. Decided to stick to US states for now.
    string UID; //changed to string. Easier to check data and allows leading zeros. Verify with is_UID(string uid)
    string zip_code; //needs to allow leading zeros. See zipcodes on wikipedia.Verify with is_ZIP(string zip)
    int account_type; //0 if member, 1 if provider
    int status; //0 if inactive, 1 if active

    private:
     vector<int> services; //vector<int> for now may change
};