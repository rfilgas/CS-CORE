#include <vector>
#include <string>
#include <iostream>
#include "utility.h"

using std::ostream;
using std::vector;
using std::string;



class dir_entry{
    public:
    // find by code, replace name and cost
    int edit(string &new_name, string &code, float cost_to_save, string &service_name);
    // add string code, and float to end
    int add(string &code, float cost_to_save, string &service_name);
    int remove_service(string &code);
    int clear_services();
    int display();
    int save(ostream & to_save);
    int load(std::istream & to_load);
    int output(ostream & to_export);
    float get_cost(string &lookup_code);

    private:
    string name;
    vector<string> codes;
    vector<float> costs;
    vector<string> services;
};