#include <map>
#include <set>
#include "provider_dir_entry.h"
#include <ostream>
using std::ostream;
using std::map;

class provider_directory{
    public:

    // assign code, if name exists, store data, if not, create new entry in map, and store name mapping in names.
    int add_entry(string &p_name, string &s_name, float cost);
    //don't assign code, but do overwrite data. Use code to replace entry.
    int update_entry(string &p_name, string &s_code, float cost);
    //call clear_services()
    int clear_services(string &pname);
    // delete match
    int remove_service(string &pname, string &s_name);
    int edit_service_name(string &p_name,  string &s_name, string &s_name_to_save);
    int edit_service_cost(string &p_name,  string &s_name, float new_cost);
    //display services for one provider at request
    int display_p_services(string &p_name);
    int display_all();
    int output(ostream & out);
    int save(ostream & to_save);
    int load(std::istream & to_load);
    float get_cost(string & service_id); //given a service ID, use the names map to get the name, then the entries map to get the entry. Finally call get cost and return.

    private:
    int top = 0; //top is the current number of services + 1. Use max to assign service code. If services are removed, that number
    // can't be used again. This should help with records since there will never be overlapping codes on reports.

    //string is the provider num. 
    map<string, dir_entry> entries; // provider name --> directory entry
    map<string, string> names; //service id --> service name
};