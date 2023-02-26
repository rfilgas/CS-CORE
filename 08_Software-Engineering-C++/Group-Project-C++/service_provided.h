#include <string>
//#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "utility.h"

using std::ostream;
using std::string;
using std::vector;

using namespace std;

class service_provided{
  public:
    //
    service_provided();
    service_provided(vector<int> &new_date, float new_cost,string &p_num, 
                    string &m_num, string &s_code, string &new_comments);
    service_provided(service_provided & new_service);
    ~service_provided();
    //allow null fields, and don't update that field if null
    // Use ctime library to fill in date and time recieved.
    int edit(vector<int> &new_date, float new_cost, string &p_num, 
            string &m_num, string &s_code, string &new_comments);
    //overloaded edit to take the object
    int edit(service_provided & to_save);
    
    int update(service_provided & to_save);
    int copy(service_provided & to_fill);
    int output(ostream &out);
    int display();

    //ryan added
    void update_cost(float to_copy); //needed for eft report
    float get_cost(); //needed to do eft reports.
    int get_code(string & to_fill); //needed to get cost at the access level for looking up.
    //end ryan added


    //for verifying data members are valid info
    int good_record();
    //take in stream variable and file path/name.
    int save(ostream &out);
    int load(istream &in);
    
    

  protected:
    void set_time_entered();
    //vectors of ints can be checked for equality using ==.
    vector<int> date_entered;
    vector<int> time_entered;
    vector<int> date;
    float cost;
    string provider_num;
    string member_num; //between 999,999,999 -> 000,000,001
    string service_code;
    string comments;
};



class service_provided_TEST{
    public:
        service_provided_TEST();
        ~service_provided_TEST();
        
        int copy_success();
        int copy_invalidDate();
        int copy_EmptyPName();
        int copy_WhitespacePName();
        int copy_EmptySName();
        int copy_WhitespaceSName();
};