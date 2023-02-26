#include "utility.h"
#include <string>
#include <vector>
#include <ctime>

using std::string;
using std::vector;

// Check if in bounds, then if all are nums. Return Valid.
bool is_UID(const string &UID)
{
    int in_bounds = (UID >= "000000001" && UID <= "999999999");
    char *p;
    long int valid = strtol(UID.c_str(), &p, 10);
    return (in_bounds && valid);
}

bool is_CODE(const string &CODE)
{
    int in_bounds = (CODE >= "000000" && CODE <= "999999");
    char *p;
    long int valid = strtol(CODE.c_str(), &p, 10);
    return (in_bounds && valid);
}

bool is_LETTERS(const string &name){
  for(auto i : name)
    if(!isalpha(i) && !(i = ' '))
      return false;
  return true;
}


// if there are five digits zip is valid
bool is_ZIP(const string &zip){
    char *p;
    long int valid = strtol(zip.c_str(), &p, 10);
    return(valid && zip.size() == 5);
}

bool is_STATE(const string &state){
  vector<string> states = {"AK", "AL", "AR", "AS", "AZ", "CA", "CO", "CT", "DC", "DE", "FL", "GA", "GU", 
                          "HI", "IA", "ID", "IL", "IN", "KS", "KY", "LA", "MA", "MD", "ME", "MI", "MN", 
                          "MO", "MP", "MS", "MT", "NC", "ND", "NE", "NH", "NJ", "NM", "NV", "NY", "OH", 
                          "OK", "OR", "PA", "PR", "RI", "SC", "SD", "TN", "TX", "UM", "UT", "VA", "VI", 
                          "VT", "WA", "WI", "WV", "WY"};
  for(auto i : states)
    if(i == state)
      return true;
  return false;
}

bool is_DATE(const vector<int> &date){
  time_t now = time(NULL);
  tm * local_time = localtime(&now);
  vector<int> month_lengths = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if(date.size() != 3)
    return false;
  if(date[0] < 1 || date[0] > 12)
    return false;
  if(date[1] < 1 || date[1] > month_lengths[date[0]-1])
    return false;
  if(date[2] < 1970 || date[2] > local_time->tm_year + 1900)
    return false;
  // Added to check for leap year
  // A leap year is any year that is divisible by 4, with the
  // with the exception of a year divisible by 100, but not 400.  
  // The check for 100 and 400 may not be necessary, but adds 
  // robustness.
  if(date[0] == 2 && date[1] == 29){ // if Feb. 29  
    // if not divisible by 4, bad date
    if(date[2]%4 != 0)
      return false; 
    // if divisible by 4, and divisible by 100,
    // but not divisible by 400, bad date
    if(date[2]%100 == 0 && date[2]%400 != 0) 
      return false;
  }
  return true;
}

bool is_TIME(const vector<int> &time){
  if(time.size() != 3)
    return false;
  if(time[0] < 0 || time[0] > 24)
    return false;
  if(time[1] < 0 || time[1] > 60)
    return false;
  if(time[2] < 0 || time[2] > 60)
    return false;
  return true;
}
