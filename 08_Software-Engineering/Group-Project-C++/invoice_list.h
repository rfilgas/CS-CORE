#include <string>
#include <vector>
#include "utility.h"
#include "service_provided.h"
using std::vector;
using std::string;

using namespace std;

class invoice_list{
  public:
    invoice_list();

    ~invoice_list(); 


    int add(vector<int> &new_date, float  new_cost,string &p_num, 
                    string &m_num, string &s_code, string &new_comments);
    int add(service_provided & new_service);
    //Maybe write a copy constructor instead.
    
    int save(ostream & to_save);
    int load(istream & to_load);

    int good_list();


// these are old prototypes with no stub and may not be correct.  
// have not removed as they were used as a guide for what to implement next

    // same as add, but won't update if null passed in to field,.
    int edit_invoice(int index, vector<int> &new_date, float new_cost,
              string &p_num, string &m_num, string &s_code, string &new_comments);

    int update(invoice_list &to_copy);
    int copy(invoice_list &to_fill);

    int output(ostream & out);
    int display();

    int add_invoice(service_provided to_add);
    int remove_invoice(int index);
    int clear_all();
    //int update_service(service_provided & to_save, int user_choice);
    int output_invoices(ostream &out);
    //int display_services(); //include an index for them to choose from



    
//    
  protected:
    vector<service_provided*> invoices; 
};

