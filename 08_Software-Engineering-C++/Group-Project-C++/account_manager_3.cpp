#include "account_manager.h"

    //add service index to user's list when given UID
int account_manager::add_service(string &UID, int index){
//  map<string, account>::iterator it;


  auto it = accounts.find(UID); //check if provider exists in directory

  if(it != accounts.end()){
    it->second.add_service(index); //if so, add an entry to the list
    return 1;
  }
  return 0;
}
