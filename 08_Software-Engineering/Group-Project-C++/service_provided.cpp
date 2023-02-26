#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <fstream>

#include "service_provided.h"
//#include "utility.h"

using std::ostream;
using std::string;
using std::vector;

using namespace std;

service_provided::service_provided(){
  //default constructor will not produce a valid record
  //data will need to be added via copy.
  date_entered.resize(3, 0);
  time_entered.resize(3, 0);  
  date.resize(3, 0);
  //a zero cost may be used to comp a service
  //so cost is initated at a negative  
  cost = -1;
  provider_num = "";
  member_num = "";
  service_code = "";
  //space entered to tell if deleted or not
  comments = " "; 
}

//costructor that takes in member data
service_provided::service_provided(vector<int> &new_date, float new_cost, string &p_num, 
                    string &m_num, string &s_code, string &new_comments){
  date_entered.resize(3);
  time_entered.resize(3);  
  date.resize(3);
  set_time_entered();
  if(new_cost < 0)
    cost = 0;
  else
    cost = new_cost;
  date = new_date;
  provider_num = p_num;
  member_num = m_num;
  service_code = s_code;
  if(new_comments.empty())
    comments = " ";
  else{
    while(comments.size() > 100)
      comments.pop_back();
    comments = new_comments;
  }
  //Should throw error if bad data.  If time, add later.
}

service_provided::service_provided(service_provided & new_service){
  copy(new_service);
  //Should throw error if bad data.  If time, add later.
}



service_provided::~service_provided(){
  //since vectors and strings handle data descruction on their own, 
  // a destructor may not be neccessary
}



// allow null (zero sized) fields, and don't update that field if null
// Use ctime library to fill in date and time recieved.
int service_provided::edit(vector<int> &new_date, float new_cost, 
          string &p_num, string &m_num, string &s_code, string &new_comments){
  set_time_entered();
  if(new_date.size() != 0){
    if(!is_DATE(new_date))
      return -1;
    date = new_date;
  }
  if(!is_UID(p_num))
    return 0;
  if(!is_UID(m_num))
    return 0;
  if(!is_CODE(s_code))
    return 0;
  //if new cost is 0 or possitive
  if(new_cost >= 0)
    cost = new_cost;
  if(!p_num.empty())
    provider_num = p_num;
  if(!m_num.empty())
    member_num = m_num;
  if(!s_code.empty())
    service_code = s_code;
  //if new comments hava a change
  if(new_comments != " "){
    //if new comments were deleted put a space
    if(new_comments.empty())
      comments = " ";
    else{
      while(comments.size() > 100)
        comments.pop_back();
      comments = new_comments;
    }
  }
  //check if the changed record has valid data
  return good_record();
}

//overloaded edit function to take object insted of individual data.
int service_provided::edit(service_provided & to_save){
  return edit(to_save.date, to_save.cost, to_save.provider_num, 
            to_save.member_num, to_save.service_code, to_save.comments);
}

//takes an obeject and used to update everything but date and time entered.
int service_provided::update(service_provided & to_save){
  return edit(to_save.date, to_save.cost, to_save.provider_num, 
          to_save.member_num, to_save.service_code, to_save.comments);
}


int service_provided::copy(service_provided & to_fill){
  if(!to_fill.good_record())
    return 0;
  date = to_fill.date;
  date_entered = to_fill.date_entered;
  time_entered = to_fill.time_entered;
  cost = to_fill.cost;
  provider_num = to_fill.provider_num;
  member_num = to_fill.member_num;
  service_code = to_fill.service_code;
  comments = to_fill.comments;
  return good_record();
}

//will display if items are invalid
//returns 0 if record is invalid and 1 if good
int service_provided::display(){
  cout <<"Date service was provided: "; 
  if(is_DATE(date)){
    cout << setfill('0') << setw(2) << date[0] << "-";
    cout << setfill('0') << setw(2) << date[1] << "-"; 
    cout << setfill('0') << setw(4) << date[2] << "\n";
  }
  else
    cout << "INVALID DATE\n";
  cout <<"Date and time service was entered: ";
//  cout << setfill('0') << setw(5) << 25 << "\n";
  if(is_DATE(date_entered)){
    cout << setfill('0') << setw(2) << date_entered[0] << "-";
    cout << setfill('0') << setw(2) << date_entered[1] << "-"; 
    cout << setfill('0') << setw(4) << date_entered[2] << " ";
  }
  else
    cout << "INVALID DATE, ";
  if(is_TIME(time_entered)){
    cout<< setfill('0') << setw(2) <<time_entered[0] << ":";
    cout<< setfill('0') << setw(2) <<time_entered[1] << ":";
    cout<< setfill('0') << setw(2) <<time_entered[2] << "\n";
  }
  else
    cout << "INVALID TIME\n";
  cout<< "Provider Number: "; 
  if(!is_UID(provider_num))
    cout << "INVALID\n";
  else
    cout << provider_num << "\n";
  cout<< "Member Number: "; 
  if(!is_UID(member_num))
    cout << "INVALID\n";
  else
    cout << member_num << "\n";
  cout<< "Service Code: "; 
  if(!is_CODE(service_code))
    cout << "INVALID\n";
  else
    cout << service_code << "\n";

  //get default precision
  streamsize ss = cout.precision();
  cout<< "Cost: "; 
  if(cost < 0)
    cout << "INVALID\n";
  else  //print with precision set to 2 fixed
    cout << fixed << setprecision(2) << "$" << cost << "\n" << defaultfloat;
  //reset to normal precision
  cout.precision(ss);

  cout<< "Comments: "; 
  if(comments.empty())
    cout << "INVALID\n";
  else
    cout << comments << "\n";
  return good_record();
}


void service_provided::set_time_entered(){
	time_t now = time(NULL);
	tm* local_time = localtime(&now);
  if(date_entered.size() != 3){
    date_entered.resize(3);
  }
  date_entered.at(0) = local_time->tm_mon+1;
  date_entered.at(1) = local_time->tm_mday;
  date_entered.at(2) = local_time->tm_year+1900;
  if(time_entered.size() != 3){
    time_entered.resize(3);
  }
  time_entered.at(0) = local_time->tm_hour;
  time_entered.at(1) = local_time->tm_min;
  time_entered.at(2) = local_time->tm_sec;
  return;
}


//-----ryan added vv

//need for eft reports. Costs will be updated at the access level.
void service_provided::update_cost(float to_copy){
  cost = to_copy;
  return;
}

//need for eft reports. the manager class will calculate the total costs for each provider before exporting
float service_provided::get_cost(){
  return cost;
}


int service_provided::get_code(string & to_fill){
  if(service_code.size() == 0)
    return -1;
  to_fill = service_code;
  return 1;
}
//-----ryan added ^^

//for verifying data members are valid info
int service_provided::good_record(){
  //check if each piec is valid
  if(!is_DATE(date))
    return 0;
  if(!is_DATE(date_entered))
    return 0;
  if(!is_TIME(time_entered))
    return 0;
  //a zero cost may be used to comp a service
  //so a negative cost is invalid data.
  if(cost < -1)
    return 0;
  if(!is_UID(provider_num))
    return 0;
  if(!is_UID(member_num))
    return 0;
  if(!is_CODE(service_code))
    return 0;
  //comments should alway have a " " (space) at the very least.
  if(comments.empty())
    return 0;
  return 1;  
}

int service_provided::save(ostream &out){
  if(!good_record())
    return 0;
  out << date_entered[0] << " ~ ";
  out << date_entered[1] << " ~ ";
  out << date_entered[2] << " ~ ";
  out << time_entered[0] << " ~ ";
  out << time_entered[1] << " ~ ";
  out << time_entered[2] << " ~ ";
  out << date[0] << " ~ ";
  out << date[1] << " ~ ";
  out << date[2] << " ~ ";
  out << cost << " ~ ";
  out << provider_num << " ~ ";
  out << member_num << " ~ ";
  out << service_code << " ~ ";
  out << comments << " ~ ";
  return 1;
}


int service_provided::load(istream &in){
  if(!in)  //if no input, return 0
    return 0;
  string temp = ""; //variable to store current loaded string

  //get date_entered and fill
  while(in >> temp && temp != "~" && temp != "~~")
    date_entered[0] = stoi(temp);
  while(in >> temp && temp != "~" && temp != "~~")
    date_entered[1] = stoi(temp);
  while(in >> temp && temp != "~" && temp != "~~") 
    date_entered[2] = stoi(temp);

  //get time_entered and fill
  while(in >> temp && temp != "~" && temp != "~~") 
    time_entered[0] = stoi(temp);
  while(in >> temp && temp != "~" && temp != "~~") 
    time_entered[1] = stoi(temp);
  while(in >> temp && temp != "~" && temp != "~~") 
    time_entered[2] = stoi(temp);

  //get date and fill
  while(in >> temp && temp != "~" && temp != "~~") 
    date[0] = stoi(temp);
  while(in >> temp && temp != "~" && temp != "~~") 
    date[1] = stoi(temp);
  while(in >> temp && temp != "~" && temp != "~~") 
    date[2] = stoi(temp);

  //get cost and fill
  while(in >> temp && temp != "~" && temp != "~~") 
    cost = stof(temp);

  //get provider_num and fill
  while(in >> temp && temp != "~" && temp != "~~")
    provider_num = temp;

  //get member_num and fill
  while(in >> temp && temp != "~" && temp != "~~")
    member_num = temp;

  //get service_code and fill
  while(in >> temp && temp != "~" && temp != "~~")
    service_code = temp;

  //get comments and fill
  while(in >> temp && temp != "~" && temp != "~~"){
    comments += temp + ' ';
  }
  return good_record();
}


/* Data Members
        vector<int> date;
        vector<int> date_entered;
        vector<int> time_entered;
        float cost; //ryan added
        string provider_num; //between 999,999,999 -> 000,000,001
        string member_num; //between 999,999,999 -> 000,000,001
        string service_code; // between 000,000 and 999,999
        string comments;
*/