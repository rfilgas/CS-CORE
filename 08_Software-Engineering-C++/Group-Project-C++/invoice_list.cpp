#include "invoice_list.h"

invoice_list::invoice_list(){
  
}

// deconstructs vector of pointers by deleteing last item and 
// and then poping of the back of the list.
invoice_list::~invoice_list(){
  while(invoices.size() != 0){
    delete *(invoices.end());
    invoices.pop_back();
  }
}

//adds to list, returns index if successful
int invoice_list::add(vector<int> &new_date, float new_cost,string &p_num, 
                    string &m_num, string &s_code, string &new_comments){
  service_provided new_serv(new_date, new_cost, p_num, m_num, s_code, new_comments);
  return add(new_serv);
}

//adds to list, returns index if successful
int invoice_list::add(service_provided & new_service){
  int error = -1;
  // if its a bad record
  if(!new_service.good_record())
    return -1;  //can't use 0 because it is a valid index
  //push onto back of list
  invoices.push_back(&new_service);
  error = good_list();
  if(error < 0)
    return error;
  //return index = list size minus one
  return invoices.size()-1;
}


int invoice_list::save(ostream & out){
//  out << " ~ ";
  int size = invoices.size();
  if(size != 0)
    return 0;
  for(int i = 0; i < size; i++){
    invoices[i]->save(out);
  }
  out << " ~~ ";
  return 1;
}



int invoice_list::load(std::istream & in){
    
    // Loads data from a file and stores it in account class. Always returns 1
    //service_provided service;
    int check = 1;
    while(check){
      service_provided *service = new service_provided();
      check = service->load(in);
      if(check)
        invoices.push_back(service);
    }
    return good_list();
}

int invoice_list::good_list(){
  for (service_provided* sp: invoices){
    if(!sp->good_record())
      return 0;
  }
  return 1;
}



// old code from account.cpp - left to use for example and will delete later
/*
//  same as add, but won't update if null passed in to field,.
int account::edit(string &name, string &address, string &city, string &state, string &zip){
    if(name.length() != 0 && is_LETTERS(name))
        account::name = name;
    if(address.length() != 0)
        account::address = address;
    if(city.length() != 0 && is_LETTERS(city))
        account::city = city;
    if(state.length() == 2 && is_STATE(state))
        account::state = state;
    if(zip.length() == 5 && is_ZIP(zip))
        account::zip_code = zip;
    return 1;
}


int account::make_provider(){
    account_type = 1;
    return 1;
}


int account::update(account &to_copy){
    name = to_copy.name;
    address = to_copy.address;
    city = to_copy.city;
    state = to_copy.state;
    UID = to_copy.UID;
    zip_code = to_copy.zip_code;
    account_type = to_copy.account_type;
    return 1;
}



int account::copy(account &to_fill){
    to_fill.name = name;
    to_fill.address = address;
    to_fill.city = city;
    to_fill.state = state;
    to_fill.UID = UID;
    to_fill.zip_code = zip_code;
    to_fill.account_type = account_type;
    return 1;
}

 

int account::output(ostream & out){
    out << name << std::endl;
    out << UID << std::endl;
    out << (account_type == 0 ? "Member" : "Provider") << std::endl; //if account_type is 0, output gets Member, else Provider
    out << address << std::endl;
    out << city << ", " << state << " " << zip_code << std::endl;
    return 1;
}


//output provider name and provider number. Return -1 if not provider.
int account::out_EFT(ostream & out){
    if(account_type == 0)
        return -1;
    out << name << std::endl;
    out << UID << std::endl;
    return 1;
}


int account::display(){
    return output(std::cout);
}



int account::add_service(int to_add){
    services.push_back(to_add);
    return 1;
}



int account::remove_service(int user_choice){
    int current = 0;
    int end = services.size();
    while(current < end && services[current] != user_choice){
        current++;
    }
    if(current < end){
        services.erase(services.begin() + current);
        return 1;
    }
    return -1;
}



// int account::update_service(service_provided & to_save, int user_choice){
//     return 0;
// }



int account::output_services(ostream &out){
    for(uint i = 0; i < services.size(); i++){
        out << services[i] << " ";
    }
    out << "~~ ";
    return 1;
}



// int account::display_services(){
//     return 0;
// } //include an index for them to choose from




bool account::is_provider(){
    return account_type;
}

// int main()
// {
//     //std::cout << "Creating first account" << std::endl << std::endl;
//     account myaccount;
//     string name = "Bob";
//     string uid = "111111111";
//     string address = "1600 SW Pennsylvania Ave";
//     string city = "Las Vegas";
//     string state = "DC";
//     string zip = "97302";
//     myaccount.add(name, uid, address, city, state, zip);
//     // myaccount.display();
//     myaccount.make_provider();
//     // std::cout << std::endl <<std::endl;
//     myaccount.display();
//     std::cout << std::endl << "Saving account information to account.txt" << std::endl;
//     std::ofstream out("account.txt");
//     myaccount.save(out);
//     out.close();
//     std::cout << std::endl << "Loading saved file into new account" << std::endl << std::endl;
//     account myaccount2;
//     std::ifstream filein("account.txt");
//     myaccount2.load(filein);
//     myaccount2.display();
//     filein.close();
//     return 0;
// }

*/